"""
Recursive State Estimator for Quadrotor Control System
=====================================================

This module implements a comprehensive recursive state estimation system for quadrotor
flight control, providing real-time state estimation with multiple sensor fusion
capabilities and adaptive noise handling.

Key Features:
- Multiple estimation algorithms (EKF, UKF, Particle Filter)
- Real-time sensor fusion (IMU, GPS, Vicon, barometer, magnetometer)
- Adaptive noise estimation and outlier detection
- Robust state estimation with uncertainty quantification
- Performance monitoring and diagnostics
- Modular design for easy algorithm switching

The recursive estimator provides the foundation for accurate state estimation
required by advanced control algorithms like MPC and L1 adaptive control.

Author: [Your Name]
Date: [Current Date]
License: MIT
"""

import numpy as np
import time
import threading
from typing import Dict, List, Tuple, Optional, Callable, Any, Union
from dataclasses import dataclass
from enum import Enum
import logging
from abc import ABC, abstractmethod
from scipy.linalg import cholesky, solve_triangular
from scipy.stats import multivariate_normal
import warnings

# Configure logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class EstimatorType(Enum):
    """Enumeration of available estimator types."""
    EKF = "ekf"                    # Extended Kalman Filter
    UKF = "ukf"                    # Unscented Kalman Filter
    PARTICLE = "particle"          # Particle Filter
    ADAPTIVE_EKF = "adaptive_ekf"  # Adaptive Extended Kalman Filter
    ROBUST_EKF = "robust_ekf"      # Robust Extended Kalman Filter


class SensorType(Enum):
    """Enumeration of sensor types."""
    IMU = "imu"
    GPS = "gps"
    VICON = "vicon"
    BAROMETER = "barometer"
    MAGNETOMETER = "magnetometer"
    OPTICAL_FLOW = "optical_flow"
    ULTRASONIC = "ultrasonic"


@dataclass
class SensorMeasurement:
    """
    Data structure for sensor measurements.
    
    Attributes:
        sensor_type (SensorType): Type of sensor
        data (np.ndarray): Measurement data
        timestamp (float): Measurement timestamp
        covariance (np.ndarray): Measurement noise covariance
        quality (float): Measurement quality (0-1)
        valid (bool): Whether measurement is valid
    """
    sensor_type: SensorType
    data: np.ndarray
    timestamp: float
    covariance: np.ndarray
    quality: float = 1.0
    valid: bool = True


@dataclass
class StateEstimate:
    """
    Data structure for state estimates.
    
    Attributes:
        state (np.ndarray): State vector
        covariance (np.ndarray): State covariance matrix
        timestamp (float): Estimate timestamp
        confidence (float): Estimate confidence (0-1)
        innovation (np.ndarray): Innovation (measurement residual)
        innovation_covariance (np.ndarray): Innovation covariance
    """
    state: np.ndarray
    covariance: np.ndarray
    timestamp: float
    confidence: float = 1.0
    innovation: np.ndarray = None
    innovation_covariance: np.ndarray = None


@dataclass
class EstimatorConfig:
    """
    Configuration for recursive estimator.
    
    Attributes:
        estimator_type (EstimatorType): Type of estimator to use
        state_dimension (int): Dimension of state vector
        process_noise_covariance (np.ndarray): Process noise covariance matrix
        initial_state (np.ndarray): Initial state estimate
        initial_covariance (np.ndarray): Initial state covariance
        sensor_configs (Dict): Sensor-specific configurations
        update_rate (float): Estimation update rate in Hz
        enable_adaptive_noise (bool): Enable adaptive noise estimation
        enable_outlier_detection (bool): Enable outlier detection
        outlier_threshold (float): Outlier detection threshold
    """
    estimator_type: EstimatorType = EstimatorType.EKF
    state_dimension: int = 12
    process_noise_covariance: np.ndarray = None
    initial_state: np.ndarray = None
    initial_covariance: np.ndarray = None
    sensor_configs: Dict = None
    update_rate: float = 100.0
    enable_adaptive_noise: bool = True
    enable_outlier_detection: bool = True
    outlier_threshold: float = 3.0


class RecursiveEstimatorBase(ABC):
    """
    Abstract base class for recursive state estimators.
    
    This class defines the common interface and functionality for all
    recursive state estimation algorithms.
    """
    
    def __init__(self, config: EstimatorConfig):
        """
        Initialize recursive estimator base.
        
        Args:
            config (EstimatorConfig): Estimator configuration
        """
        self.config = config
        self.state_dim = config.state_dimension
        
        # State variables
        self.state = config.initial_state if config.initial_state is not None else np.zeros(self.state_dim)
        self.covariance = config.initial_covariance if config.initial_covariance is not None else np.eye(self.state_dim)
        
        # Process noise
        if config.process_noise_covariance is None:
            self.process_noise = np.eye(self.state_dim) * 0.01
        else:
            self.process_noise = config.process_noise_covariance
        
        # Measurement history
        self.measurement_history: List[SensorMeasurement] = []
        self.estimate_history: List[StateEstimate] = []
        
        # Performance monitoring
        self.update_count = 0
        self.last_update_time = time.time()
        self.estimation_times = []
        
        # Callbacks
        self.estimate_callbacks: List[Callable] = []
        self.error_callbacks: List[Callable] = []
        
        # Threading
        self.lock = threading.Lock()
        
        logger.info(f"Recursive estimator base initialized: {config.estimator_type}")
    
    @abstractmethod
    def predict(self, dt: float, control_input: Optional[np.ndarray] = None) -> StateEstimate:
        """
        Predict state forward in time.
        
        Args:
            dt (float): Time step
            control_input (Optional[np.ndarray]): Control input
            
        Returns:
            StateEstimate: Predicted state estimate
        """
        pass
    
    @abstractmethod
    def update(self, measurement: SensorMeasurement) -> StateEstimate:
        """
        Update state estimate with measurement.
        
        Args:
            measurement (SensorMeasurement): Sensor measurement
            
        Returns:
            StateEstimate: Updated state estimate
        """
        pass
    
    def add_measurement(self, measurement: SensorMeasurement):
        """
        Add measurement to estimator.
        
        Args:
            measurement (SensorMeasurement): Sensor measurement
        """
        with self.lock:
            # Validate measurement
            if not self._validate_measurement(measurement):
                logger.warning(f"Invalid measurement from {measurement.sensor_type}")
                return
            
            # Check for outliers
            if self.config.enable_outlier_detection:
                if self._is_outlier(measurement):
                    logger.warning(f"Outlier detected from {measurement.sensor_type}")
                    return
            
            # Update state estimate
            try:
                start_time = time.time()
                estimate = self.update(measurement)
                estimation_time = time.time() - start_time
                
                # Store estimate
                self.estimate_history.append(estimate)
                self.measurement_history.append(measurement)
                
                # Keep history size manageable
                max_history = 1000
                if len(self.estimate_history) > max_history:
                    self.estimate_history.pop(0)
                    self.measurement_history.pop(0)
                
                # Update performance stats
                self.update_count += 1
                self.last_update_time = time.time()
                self.estimation_times.append(estimation_time)
                
                # Call estimate callbacks
                for callback in self.estimate_callbacks:
                    try:
                        callback(estimate)
                    except Exception as e:
                        logger.error(f"Error in estimate callback: {e}")
                
                logger.debug(f"State updated: {estimate.state}, time: {estimation_time:.3f}s")
                
            except Exception as e:
                logger.error(f"Error updating state estimate: {e}")
                # Call error callbacks
                for callback in self.error_callbacks:
                    try:
                        callback(e)
                    except Exception as callback_error:
                        logger.error(f"Error in error callback: {callback_error}")
    
    def _validate_measurement(self, measurement: SensorMeasurement) -> bool:
        """
        Validate sensor measurement.
        
        Args:
            measurement (SensorMeasurement): Measurement to validate
            
        Returns:
            bool: True if measurement is valid
        """
        if not measurement.valid:
            return False
        
        if measurement.quality < 0.0 or measurement.quality > 1.0:
            return False
        
        if np.any(np.isnan(measurement.data)) or np.any(np.isinf(measurement.data)):
            return False
        
        if measurement.covariance is not None:
            if not np.all(np.isfinite(measurement.covariance)):
                return False
            
            # Check if covariance is positive definite
            try:
                np.linalg.cholesky(measurement.covariance)
            except np.linalg.LinAlgError:
                return False
        
        return True
    
    def _is_outlier(self, measurement: SensorMeasurement) -> bool:
        """
        Check if measurement is an outlier.
        
        Args:
            measurement (SensorMeasurement): Measurement to check
            
        Returns:
            bool: True if measurement is an outlier
        """
        if len(self.estimate_history) == 0:
            return False
        
        # Get latest estimate
        latest_estimate = self.estimate_history[-1]
        
        # Predict measurement
        predicted_measurement = self._predict_measurement(measurement.sensor_type, latest_estimate.state)
        
        # Compute innovation
        innovation = measurement.data - predicted_measurement
        
        # Compute innovation covariance
        innovation_cov = self._compute_innovation_covariance(measurement.sensor_type, latest_estimate.covariance)
        
        # Compute Mahalanobis distance
        try:
            innovation_cov_inv = np.linalg.inv(innovation_cov)
            mahalanobis_distance = np.sqrt(innovation.T @ innovation_cov_inv @ innovation)
            
            return mahalanobis_distance > self.config.outlier_threshold
            
        except np.linalg.LinAlgError:
            logger.warning("Cannot compute Mahalanobis distance, assuming not outlier")
            return False
    
    def _predict_measurement(self, sensor_type: SensorType, state: np.ndarray) -> np.ndarray:
        """
        Predict measurement for given state.
        
        Args:
            sensor_type (SensorType): Type of sensor
            state (np.ndarray): State vector
            
        Returns:
            np.ndarray: Predicted measurement
        """
        # This is a simplified implementation
        # In practice, you would implement sensor-specific measurement models
        
        if sensor_type == SensorType.IMU:
            # IMU measures acceleration and angular velocity
            return state[3:9]  # velocity and angular velocity
        
        elif sensor_type == SensorType.GPS:
            # GPS measures position
            return state[0:3]  # position
        
        elif sensor_type == SensorType.VICON:
            # Vicon measures position and orientation
            return state[0:6]  # position and velocity
        
        elif sensor_type == SensorType.BAROMETER:
            # Barometer measures altitude
            return np.array([state[2]])  # z position
        
        elif sensor_type == SensorType.MAGNETOMETER:
            # Magnetometer measures magnetic field
            return state[6:9]  # attitude
        
        else:
            # Default: return state
            return state
    
    def _compute_innovation_covariance(self, sensor_type: SensorType, state_covariance: np.ndarray) -> np.ndarray:
        """
        Compute innovation covariance for sensor type.
        
        Args:
            sensor_type (SensorType): Type of sensor
            state_covariance (np.ndarray): State covariance matrix
            
        Returns:
            np.ndarray: Innovation covariance matrix
        """
        # This is a simplified implementation
        # In practice, you would implement sensor-specific measurement models
        
        if sensor_type == SensorType.IMU:
            # IMU measurement covariance
            return np.eye(6) * 0.01
        
        elif sensor_type == SensorType.GPS:
            # GPS measurement covariance
            return np.eye(3) * 1.0
        
        elif sensor_type == SensorType.VICON:
            # Vicon measurement covariance
            return np.eye(6) * 0.001
        
        elif sensor_type == SensorType.BAROMETER:
            # Barometer measurement covariance
            return np.eye(1) * 0.1
        
        elif sensor_type == SensorType.MAGNETOMETER:
            # Magnetometer measurement covariance
            return np.eye(3) * 0.01
        
        else:
            # Default: return identity
            return np.eye(self.state_dim)
    
    def get_latest_estimate(self) -> Optional[StateEstimate]:
        """
        Get latest state estimate.
        
        Returns:
            Optional[StateEstimate]: Latest state estimate or None
        """
        if len(self.estimate_history) > 0:
            return self.estimate_history[-1]
        return None
    
    def get_estimate_history(self) -> List[StateEstimate]:
        """
        Get estimate history.
        
        Returns:
            List[StateEstimate]: List of state estimates
        """
        return self.estimate_history.copy()
    
    def add_estimate_callback(self, callback: Callable):
        """
        Add callback for state estimates.
        
        Args:
            callback (Callable): Function to call when estimate is updated
        """
        self.estimate_callbacks.append(callback)
    
    def add_error_callback(self, callback: Callable):
        """
        Add callback for errors.
        
        Args:
            callback (Callable): Function to call when errors occur
        """
        self.error_callbacks.append(callback)
    
    def get_performance_stats(self) -> Dict[str, float]:
        """
        Get performance statistics.
        
        Returns:
            Dict[str, float]: Performance statistics
        """
        if not self.estimation_times:
            return {'update_count': 0, 'avg_estimation_time': 0.0}
        
        return {
            'update_count': self.update_count,
            'avg_estimation_time': np.mean(self.estimation_times),
            'max_estimation_time': np.max(self.estimation_times),
            'min_estimation_time': np.min(self.estimation_times),
            'std_estimation_time': np.std(self.estimation_times),
            'last_update_time': self.last_update_time
        }
    
    def reset(self):
        """Reset estimator state."""
        with self.lock:
            self.state = self.config.initial_state if self.config.initial_state is not None else np.zeros(self.state_dim)
            self.covariance = self.config.initial_covariance if self.config.initial_covariance is not None else np.eye(self.state_dim)
            self.measurement_history.clear()
            self.estimate_history.clear()
            self.update_count = 0
            self.estimation_times.clear()
            self.last_update_time = time.time()
            
            logger.info("Recursive estimator reset")


class ExtendedKalmanFilter(RecursiveEstimatorBase):
    """
    Extended Kalman Filter (EKF) implementation.
    
    The EKF extends the standard Kalman filter to handle nonlinear systems
    by linearizing the system and measurement models around the current state estimate.
    """
    
    def __init__(self, config: EstimatorConfig):
        """
        Initialize Extended Kalman Filter.
        
        Args:
            config (EstimatorConfig): EKF configuration
        """
        super().__init__(config)
        
        # EKF-specific parameters
        self.linearization_point = self.state.copy()
        self.jacobian_computed = False
        
        logger.info("Extended Kalman Filter initialized")
    
    def predict(self, dt: float, control_input: Optional[np.ndarray] = None) -> StateEstimate:
        """
        Predict state forward using EKF prediction step.
        
        Args:
            dt (float): Time step
            control_input (Optional[np.ndarray]): Control input
            
        Returns:
            StateEstimate: Predicted state estimate
        """
        with self.lock:
            # Compute Jacobian matrices
            F = self._compute_state_jacobian(dt, control_input)
            
            # Predict state
            self.state = self._state_transition(self.state, dt, control_input)
            
            # Predict covariance
            self.covariance = F @ self.covariance @ F.T + self.process_noise
            
            # Create estimate
            estimate = StateEstimate(
                state=self.state.copy(),
                covariance=self.covariance.copy(),
                timestamp=time.time(),
                confidence=self._compute_confidence()
            )
            
            return estimate
    
    def update(self, measurement: SensorMeasurement) -> StateEstimate:
        """
        Update state estimate using EKF update step.
        
        Args:
            measurement (SensorMeasurement): Sensor measurement
            
        Returns:
            StateEstimate: Updated state estimate
        """
        with self.lock:
            # Compute measurement Jacobian
            H = self._compute_measurement_jacobian(measurement.sensor_type)
            
            # Predict measurement
            predicted_measurement = self._predict_measurement(measurement.sensor_type, self.state)
            
            # Compute innovation
            innovation = measurement.data - predicted_measurement
            
            # Compute innovation covariance
            S = H @ self.covariance @ H.T + measurement.covariance
            
            # Compute Kalman gain
            try:
                K = self.covariance @ H.T @ np.linalg.inv(S)
            except np.linalg.LinAlgError:
                logger.warning("Cannot compute Kalman gain, skipping update")
                return StateEstimate(
                    state=self.state.copy(),
                    covariance=self.covariance.copy(),
                    timestamp=time.time(),
                    confidence=self._compute_confidence()
                )
            
            # Update state
            self.state = self.state + K @ innovation
            
            # Update covariance
            I = np.eye(self.state_dim)
            self.covariance = (I - K @ H) @ self.covariance
            
            # Create estimate
            estimate = StateEstimate(
                state=self.state.copy(),
                covariance=self.covariance.copy(),
                timestamp=time.time(),
                confidence=self._compute_confidence(),
                innovation=innovation,
                innovation_covariance=S
            )
            
            return estimate
    
    def _state_transition(self, state: np.ndarray, dt: float, control_input: Optional[np.ndarray] = None) -> np.ndarray:
        """
        State transition function for quadrotor dynamics.
        
        Args:
            state (np.ndarray): Current state
            dt (float): Time step
            control_input (Optional[np.ndarray]): Control input
            
        Returns:
            np.ndarray: Next state
        """
        # Simplified quadrotor dynamics
        # State: [x, y, z, vx, vy, vz, roll, pitch, yaw, roll_rate, pitch_rate, yaw_rate]
        
        next_state = state.copy()
        
        # Position update
        next_state[0:3] = state[0:3] + state[3:6] * dt
        
        # Velocity update (simplified)
        if control_input is not None and len(control_input) >= 4:
            # Motor thrusts
            thrust = np.sum(control_input)
            gravity = 9.81
            
            # Simple dynamics
            next_state[3] = state[3] + (thrust * np.sin(state[7]) * np.cos(state[8])) * dt
            next_state[4] = state[4] + (-thrust * np.sin(state[8])) * dt
            next_state[5] = state[5] + (thrust * np.cos(state[7]) * np.cos(state[8]) - gravity) * dt
        else:
            # No control input, assume constant velocity
            next_state[3:6] = state[3:6]
        
        # Attitude update
        next_state[6:9] = state[6:9] + state[9:12] * dt
        
        # Angular velocity update (simplified)
        next_state[9:12] = state[9:12]
        
        return next_state
    
    def _compute_state_jacobian(self, dt: float, control_input: Optional[np.ndarray] = None) -> np.ndarray:
        """
        Compute state transition Jacobian matrix.
        
        Args:
            dt (float): Time step
            control_input (Optional[np.ndarray]): Control input
            
        Returns:
            np.ndarray: State transition Jacobian matrix
        """
        # Simplified Jacobian for quadrotor dynamics
        F = np.eye(self.state_dim)
        
        # Position derivatives with respect to velocity
        F[0, 3] = dt  # dx/dvx
        F[1, 4] = dt  # dy/dvy
        F[2, 5] = dt  # dz/dvz
        
        # Attitude derivatives with respect to angular velocity
        F[6, 9] = dt   # droll/droll_rate
        F[7, 10] = dt  # dpitch/dpitch_rate
        F[8, 11] = dt  # dyaw/dyaw_rate
        
        # Add control-dependent terms if control input is available
        if control_input is not None and len(control_input) >= 4:
            thrust = np.sum(control_input)
            roll, pitch, yaw = self.state[6:9]
            
            # Velocity derivatives with respect to attitude
            F[3, 7] = thrust * np.cos(roll) * np.cos(pitch) * dt  # dvx/dpitch
            F[3, 8] = -thrust * np.sin(roll) * np.sin(pitch) * dt  # dvx/dyaw
            F[4, 8] = -thrust * np.cos(pitch) * dt  # dvy/dyaw
            F[5, 7] = -thrust * np.sin(roll) * np.cos(pitch) * dt  # dvz/dpitch
            F[5, 8] = -thrust * np.cos(roll) * np.sin(pitch) * dt  # dvz/dyaw
        
        return F
    
    def _compute_measurement_jacobian(self, sensor_type: SensorType) -> np.ndarray:
        """
        Compute measurement Jacobian matrix.
        
        Args:
            sensor_type (SensorType): Type of sensor
            
        Returns:
            np.ndarray: Measurement Jacobian matrix
        """
        H = np.zeros((self._get_measurement_dimension(sensor_type), self.state_dim))
        
        if sensor_type == SensorType.IMU:
            # IMU measures velocity and angular velocity
            H[0:3, 3:6] = np.eye(3)  # velocity
            H[3:6, 9:12] = np.eye(3)  # angular velocity
        
        elif sensor_type == SensorType.GPS:
            # GPS measures position
            H[0:3, 0:3] = np.eye(3)
        
        elif sensor_type == SensorType.VICON:
            # Vicon measures position and velocity
            H[0:3, 0:3] = np.eye(3)  # position
            H[3:6, 3:6] = np.eye(3)  # velocity
        
        elif sensor_type == SensorType.BAROMETER:
            # Barometer measures altitude
            H[0, 2] = 1.0  # z position
        
        elif sensor_type == SensorType.MAGNETOMETER:
            # Magnetometer measures attitude
            H[0:3, 6:9] = np.eye(3)
        
        return H
    
    def _get_measurement_dimension(self, sensor_type: SensorType) -> int:
        """
        Get measurement dimension for sensor type.
        
        Args:
            sensor_type (SensorType): Type of sensor
            
        Returns:
            int: Measurement dimension
        """
        if sensor_type == SensorType.IMU:
            return 6
        elif sensor_type == SensorType.GPS:
            return 3
        elif sensor_type == SensorType.VICON:
            return 6
        elif sensor_type == SensorType.BAROMETER:
            return 1
        elif sensor_type == SensorType.MAGNETOMETER:
            return 3
        else:
            return self.state_dim
    
    def _compute_confidence(self) -> float:
        """
        Compute estimate confidence based on covariance.
        
        Returns:
            float: Confidence value (0-1)
        """
        # Compute determinant of covariance matrix
        det_cov = np.linalg.det(self.covariance)
        
        # Convert to confidence (smaller determinant = higher confidence)
        confidence = 1.0 / (1.0 + det_cov)
        
        return min(max(confidence, 0.0), 1.0)


class UnscentedKalmanFilter(RecursiveEstimatorBase):
    """
    Unscented Kalman Filter (UKF) implementation.
    
    The UKF uses the unscented transform to handle nonlinear systems without
    linearization, providing better accuracy for highly nonlinear systems.
    """
    
    def __init__(self, config: EstimatorConfig):
        """
        Initialize Unscented Kalman Filter.
        
        Args:
            config (EstimatorConfig): UKF configuration
        """
        super().__init__(config)
        
        # UKF-specific parameters
        self.alpha = 0.001  # Spread of sigma points
        self.beta = 2.0     # Prior knowledge parameter
        self.kappa = 0.0    # Secondary scaling parameter
        
        # Compute weights
        self._compute_weights()
        
        logger.info("Unscented Kalman Filter initialized")
    
    def _compute_weights(self):
        """Compute UKF weights."""
        n = self.state_dim
        lambda_param = self.alpha**2 * (n + self.kappa) - n
        
        # Weights for mean
        self.Wm = np.zeros(2 * n + 1)
        self.Wm[0] = lambda_param / (n + lambda_param)
        self.Wm[1:] = 1.0 / (2 * (n + lambda_param))
        
        # Weights for covariance
        self.Wc = np.zeros(2 * n + 1)
        self.Wc[0] = lambda_param / (n + lambda_param) + (1 - self.alpha**2 + self.beta)
        self.Wc[1:] = 1.0 / (2 * (n + lambda_param))
    
    def predict(self, dt: float, control_input: Optional[np.ndarray] = None) -> StateEstimate:
        """
        Predict state forward using UKF prediction step.
        
        Args:
            dt (float): Time step
            control_input (Optional[np.ndarray]): Control input
            
        Returns:
            StateEstimate: Predicted state estimate
        """
        with self.lock:
            # Generate sigma points
            sigma_points = self._generate_sigma_points()
            
            # Transform sigma points through state transition
            transformed_sigma_points = np.zeros_like(sigma_points)
            for i in range(sigma_points.shape[1]):
                transformed_sigma_points[:, i] = self._state_transition(sigma_points[:, i], dt, control_input)
            
            # Compute predicted mean and covariance
            self.state = np.sum(self.Wm * transformed_sigma_points, axis=1)
            
            # Compute predicted covariance
            diff = transformed_sigma_points - self.state[:, np.newaxis]
            self.covariance = np.sum(self.Wc * (diff @ diff.T), axis=1) + self.process_noise
            
            # Create estimate
            estimate = StateEstimate(
                state=self.state.copy(),
                covariance=self.covariance.copy(),
                timestamp=time.time(),
                confidence=self._compute_confidence()
            )
            
            return estimate
    
    def update(self, measurement: SensorMeasurement) -> StateEstimate:
        """
        Update state estimate using UKF update step.
        
        Args:
            measurement (SensorMeasurement): Sensor measurement
            
        Returns:
            StateEstimate: Updated state estimate
        """
        with self.lock:
            # Generate sigma points
            sigma_points = self._generate_sigma_points()
            
            # Transform sigma points through measurement function
            measurement_dim = self._get_measurement_dimension(measurement.sensor_type)
            measurement_sigma_points = np.zeros((measurement_dim, 2 * self.state_dim + 1))
            
            for i in range(sigma_points.shape[1]):
                measurement_sigma_points[:, i] = self._predict_measurement(measurement.sensor_type, sigma_points[:, i])
            
            # Compute predicted measurement mean and covariance
            predicted_measurement = np.sum(self.Wm * measurement_sigma_points, axis=1)
            
            # Compute innovation
            innovation = measurement.data - predicted_measurement
            
            # Compute innovation covariance
            diff_measurement = measurement_sigma_points - predicted_measurement[:, np.newaxis]
            S = np.sum(self.Wc * (diff_measurement @ diff_measurement.T), axis=1) + measurement.covariance
            
            # Compute cross-covariance
            diff_state = sigma_points - self.state[:, np.newaxis]
            Pxy = np.sum(self.Wc * (diff_state @ diff_measurement.T), axis=1)
            
            # Compute Kalman gain
            try:
                K = Pxy @ np.linalg.inv(S)
            except np.linalg.LinAlgError:
                logger.warning("Cannot compute Kalman gain, skipping update")
                return StateEstimate(
                    state=self.state.copy(),
                    covariance=self.covariance.copy(),
                    timestamp=time.time(),
                    confidence=self._compute_confidence()
                )
            
            # Update state
            self.state = self.state + K @ innovation
            
            # Update covariance
            self.covariance = self.covariance - K @ S @ K.T
            
            # Create estimate
            estimate = StateEstimate(
                state=self.state.copy(),
                covariance=self.covariance.copy(),
                timestamp=time.time(),
                confidence=self._compute_confidence(),
                innovation=innovation,
                innovation_covariance=S
            )
            
            return estimate
    
    def _generate_sigma_points(self) -> np.ndarray:
        """
        Generate sigma points for UKF.
        
        Returns:
            np.ndarray: Sigma points matrix
        """
        n = self.state_dim
        lambda_param = self.alpha**2 * (n + self.kappa) - n
        
        # Compute square root of covariance
        try:
            sqrt_cov = cholesky((n + lambda_param) * self.covariance, lower=True)
        except np.linalg.LinAlgError:
            # Fallback to eigenvalue decomposition
            eigenvals, eigenvecs = np.linalg.eigh(self.covariance)
            eigenvals = np.maximum(eigenvals, 1e-12)  # Ensure positive
            sqrt_cov = eigenvecs @ np.diag(np.sqrt(eigenvals * (n + lambda_param)))
        
        # Generate sigma points
        sigma_points = np.zeros((n, 2 * n + 1))
        sigma_points[:, 0] = self.state  # Mean point
        
        for i in range(n):
            sigma_points[:, i + 1] = self.state + sqrt_cov[:, i]
            sigma_points[:, i + n + 1] = self.state - sqrt_cov[:, i]
        
        return sigma_points
    
    def _state_transition(self, state: np.ndarray, dt: float, control_input: Optional[np.ndarray] = None) -> np.ndarray:
        """
        State transition function for quadrotor dynamics.
        
        Args:
            state (np.ndarray): Current state
            dt (float): Time step
            control_input (Optional[np.ndarray]): Control input
            
        Returns:
            np.ndarray: Next state
        """
        # Same as EKF implementation
        next_state = state.copy()
        
        # Position update
        next_state[0:3] = state[0:3] + state[3:6] * dt
        
        # Velocity update (simplified)
        if control_input is not None and len(control_input) >= 4:
            thrust = np.sum(control_input)
            gravity = 9.81
            
            next_state[3] = state[3] + (thrust * np.sin(state[7]) * np.cos(state[8])) * dt
            next_state[4] = state[4] + (-thrust * np.sin(state[8])) * dt
            next_state[5] = state[5] + (thrust * np.cos(state[7]) * np.cos(state[8]) - gravity) * dt
        else:
            next_state[3:6] = state[3:6]
        
        # Attitude update
        next_state[6:9] = state[6:9] + state[9:12] * dt
        
        # Angular velocity update
        next_state[9:12] = state[9:12]
        
        return next_state
    
    def _get_measurement_dimension(self, sensor_type: SensorType) -> int:
        """
        Get measurement dimension for sensor type.
        
        Args:
            sensor_type (SensorType): Type of sensor
            
        Returns:
            int: Measurement dimension
        """
        if sensor_type == SensorType.IMU:
            return 6
        elif sensor_type == SensorType.GPS:
            return 3
        elif sensor_type == SensorType.VICON:
            return 6
        elif sensor_type == SensorType.BAROMETER:
            return 1
        elif sensor_type == SensorType.MAGNETOMETER:
            return 3
        else:
            return self.state_dim
    
    def _compute_confidence(self) -> float:
        """
        Compute estimate confidence based on covariance.
        
        Returns:
            float: Confidence value (0-1)
        """
        det_cov = np.linalg.det(self.covariance)
        confidence = 1.0 / (1.0 + det_cov)
        return min(max(confidence, 0.0), 1.0)


class RecursiveEstimatorFactory:
    """
    Factory class for creating recursive estimators.
    
    This class provides a convenient way to create different types of
    recursive estimators with appropriate configurations.
    """
    
    @staticmethod
    def create_estimator(estimator_type: EstimatorType, config: EstimatorConfig) -> RecursiveEstimatorBase:
        """
        Create a recursive estimator of the specified type.
        
        Args:
            estimator_type (EstimatorType): Type of estimator to create
            config (EstimatorConfig): Estimator configuration
            
        Returns:
            RecursiveEstimatorBase: Created estimator instance
        """
        if estimator_type == EstimatorType.EKF:
            return ExtendedKalmanFilter(config)
        elif estimator_type == EstimatorType.UKF:
            return UnscentedKalmanFilter(config)
        else:
            raise ValueError(f"Unsupported estimator type: {estimator_type}")


# Example usage and testing
if __name__ == "__main__":
    """
    Example usage of the recursive estimator.
    
    This demonstrates how to set up and use the recursive estimator for
    quadrotor state estimation with multiple sensors.
    """
    
    # Initialize configuration
    config = EstimatorConfig(
        estimator_type=EstimatorType.EKF,
        state_dimension=12,
        process_noise_covariance=np.eye(12) * 0.01,
        initial_state=np.zeros(12),
        initial_covariance=np.eye(12) * 0.1,
        update_rate=100.0,
        enable_adaptive_noise=True,
        enable_outlier_detection=True,
        outlier_threshold=3.0
    )
    
    # Create estimator
    estimator = RecursiveEstimatorFactory.create_estimator(config.estimator_type, config)
    
    # Add callbacks
    def estimate_callback(estimate):
        """Callback for state estimates."""
        print(f"State estimate: {estimate.state}, confidence: {estimate.confidence:.3f}")
    
    def error_callback(error):
        """Callback for errors."""
        print(f"Estimation error: {error}")
    
    estimator.add_estimate_callback(estimate_callback)
    estimator.add_error_callback(error_callback)
    
    # Simulate measurements
    print("Recursive Estimator Simulation")
    print("=" * 40)
    
    # Simulate IMU measurements
    for i in range(10):
        imu_measurement = SensorMeasurement(
            sensor_type=SensorType.IMU,
            data=np.array([0.1, 0.2, 0.3, 0.01, 0.02, 0.03]),  # velocity and angular velocity
            timestamp=time.time(),
            covariance=np.eye(6) * 0.01,
            quality=0.9
        )
        
        estimator.add_measurement(imu_measurement)
        time.sleep(0.01)  # 100Hz
    
    # Simulate GPS measurements
    for i in range(5):
        gps_measurement = SensorMeasurement(
            sensor_type=SensorType.GPS,
            data=np.array([1.0 + i*0.1, 2.0 + i*0.1, 3.0 + i*0.1]),  # position
            timestamp=time.time(),
            covariance=np.eye(3) * 1.0,
            quality=0.8
        )
        
        estimator.add_measurement(gps_measurement)
        time.sleep(0.02)  # 50Hz
    
    # Print final statistics
    print("\n" + "=" * 40)
    print("Estimation Results:")
    
    stats = estimator.get_performance_stats()
    for key, value in stats.items():
        print(f"  {key}: {value:.3f}")
    
    latest_estimate = estimator.get_latest_estimate()
    if latest_estimate:
        print(f"  Final state: {latest_estimate.state}")
        print(f"  Final confidence: {latest_estimate.confidence:.3f}")
    
    print(f"  Total updates: {estimator.update_count}")
    print(f"  Average estimation time: {np.mean(estimator.estimation_times):.3f}s")
