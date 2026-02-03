"""
Advanced Kalman Filter for Quadrotor State Estimation
===================================================

This module implements an advanced Kalman filter system for quadrotor state estimation,
featuring adaptive parameter tuning, multi-model filtering, and integration with IMU data
for improved accuracy and robustness.

Key Features:
- Adaptive parameter tuning based on flight conditions
- Multi-model Kalman filtering for different flight phases
- Integration with IMU data for better state estimation
- Robust outlier rejection and static window detection
- Real-time performance monitoring and diagnostics

This implementation extends the existing Kalman filter in the NCKU-Quadrotor-Navigation
project with enhanced capabilities for improved flight performance.

Author: [Your Name]
Date: [Current Date]
License: MIT
"""

import numpy as np
import time
from typing import Dict, List, Tuple, Optional, Callable
from dataclasses import dataclass
from enum import Enum
import logging
from scipy.linalg import inv, cholesky
from scipy.stats import chi2

# Configure logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class FlightPhase(Enum):
    """Enumeration of different flight phases for multi-model filtering."""
    GROUND = "ground"              # On ground, no motion
    TAKEOFF = "takeoff"            # Takeoff phase
    HOVER = "hover"                # Hovering flight
    MANEUVER = "maneuver"          # Active maneuvering
    LANDING = "landing"            # Landing phase
    UNKNOWN = "unknown"            # Unknown phase


@dataclass
class KalmanParameters:
    """
    Data structure for Kalman filter parameters.
    
    Attributes:
        Q (np.ndarray): Process noise covariance matrix
        R (np.ndarray): Measurement noise covariance matrix
        P0 (np.ndarray): Initial state covariance matrix
        dt (float): Time step for prediction
        adaptive_enabled (bool): Enable adaptive parameter tuning
        outlier_threshold (float): Threshold for outlier detection
        static_window_size (int): Window size for static detection
    """
    Q: np.ndarray
    R: np.ndarray
    P0: np.ndarray
    dt: float = 0.01
    adaptive_enabled: bool = True
    outlier_threshold: float = 3.0
    static_window_size: int = 50


@dataclass
class KalmanState:
    """
    Data structure for Kalman filter state.
    
    Attributes:
        x (np.ndarray): State estimate
        P (np.ndarray): State covariance matrix
        timestamp (float): Timestamp of last update
        phase (FlightPhase): Current flight phase
        innovation (np.ndarray): Innovation (measurement residual)
        innovation_covariance (np.ndarray): Innovation covariance
        mahalanobis_distance (float): Mahalanobis distance for outlier detection
    """
    x: np.ndarray
    P: np.ndarray
    timestamp: float = 0.0
    phase: FlightPhase = FlightPhase.UNKNOWN
    innovation: np.ndarray = None
    innovation_covariance: np.ndarray = None
    mahalanobis_distance: float = 0.0


class AdaptiveKalmanFilter:
    """
    Advanced Kalman filter with adaptive parameter tuning and multi-model filtering.
    
    This class implements a sophisticated Kalman filter that adapts its parameters
    based on flight conditions and uses multiple models for different flight phases.
    """
    
    def __init__(self, params: KalmanParameters, state_dim: int = 12, measurement_dim: int = 6):
        """
        Initialize adaptive Kalman filter.
        
        Args:
            params (KalmanParameters): Initial filter parameters
            state_dim (int): Dimension of state vector
            measurement_dim (int): Dimension of measurement vector
        """
        self.params = params
        self.state_dim = state_dim
        self.measurement_dim = measurement_dim
        
        # Initialize state
        self.state = KalmanState(
            x=np.zeros(state_dim),
            P=params.P0.copy(),
            timestamp=time.time()
        )
        
        # State transition matrix (constant velocity model)
        self.F = self._create_state_transition_matrix()
        
        # Measurement matrix
        self.H = self._create_measurement_matrix()
        
        # Multi-model parameters for different flight phases
        self.phase_models = self._initialize_phase_models()
        
        # Adaptive tuning parameters
        self.adaptation_window = 100
        self.innovation_history = []
        self.parameter_history = []
        
        # Performance monitoring
        self.total_updates = 0
        self.outlier_count = 0
        self.phase_transitions = 0
        
        # Static detection
        self.static_buffer = []
        self.static_threshold = 0.01  # m/s for velocity
        
        logger.info(f"Adaptive Kalman filter initialized: state_dim={state_dim}, measurement_dim={measurement_dim}")
    
    def _create_state_transition_matrix(self) -> np.ndarray:
        """
        Create state transition matrix for constant velocity model.
        
        State vector: [x, y, z, vx, vy, vz, roll, pitch, yaw, roll_rate, pitch_rate, yaw_rate]
        
        Returns:
            np.ndarray: State transition matrix
        """
        dt = self.params.dt
        F = np.eye(self.state_dim)
        
        # Position-velocity relationships
        F[0, 3] = dt  # x += vx * dt
        F[1, 4] = dt  # y += vy * dt
        F[2, 5] = dt  # z += vz * dt
        
        # Attitude-angular rate relationships
        F[6, 9] = dt   # roll += roll_rate * dt
        F[7, 10] = dt  # pitch += pitch_rate * dt
        F[8, 11] = dt  # yaw += yaw_rate * dt
        
        return F
    
    def _create_measurement_matrix(self) -> np.ndarray:
        """
        Create measurement matrix for position and attitude measurements.
        
        Returns:
            np.ndarray: Measurement matrix
        """
        H = np.zeros((self.measurement_dim, self.state_dim))
        
        # Position measurements (x, y, z)
        H[0, 0] = 1.0  # x
        H[1, 1] = 1.0  # y
        H[2, 2] = 1.0  # z
        
        # Attitude measurements (roll, pitch, yaw)
        H[3, 6] = 1.0  # roll
        H[4, 7] = 1.0  # pitch
        H[5, 8] = 1.0  # yaw
        
        return H
    
    def _initialize_phase_models(self) -> Dict[FlightPhase, KalmanParameters]:
        """
        Initialize Kalman parameters for different flight phases.
        
        Returns:
            Dict[FlightPhase, KalmanParameters]: Parameters for each flight phase
        """
        models = {}
        
        # Ground phase: low process noise, high measurement trust
        models[FlightPhase.GROUND] = KalmanParameters(
            Q=self.params.Q * 0.1,  # Low process noise
            R=self.params.R * 0.5,  # High measurement trust
            P0=self.params.P0,
            dt=self.params.dt,
            adaptive_enabled=False  # No adaptation on ground
        )
        
        # Takeoff phase: high process noise, moderate measurement trust
        models[FlightPhase.TAKEOFF] = KalmanParameters(
            Q=self.params.Q * 2.0,  # High process noise
            R=self.params.R * 1.5,  # Moderate measurement trust
            P0=self.params.P0,
            dt=self.params.dt,
            adaptive_enabled=True
        )
        
        # Hover phase: moderate process noise, high measurement trust
        models[FlightPhase.HOVER] = KalmanParameters(
            Q=self.params.Q * 0.8,  # Moderate process noise
            R=self.params.R * 0.8,  # High measurement trust
            P0=self.params.P0,
            dt=self.params.dt,
            adaptive_enabled=True
        )
        
        # Maneuver phase: high process noise, moderate measurement trust
        models[FlightPhase.MANEUVER] = KalmanParameters(
            Q=self.params.Q * 3.0,  # High process noise
            R=self.params.R * 1.2,  # Moderate measurement trust
            P0=self.params.P0,
            dt=self.params.dt,
            adaptive_enabled=True
        )
        
        # Landing phase: moderate process noise, high measurement trust
        models[FlightPhase.LANDING] = KalmanParameters(
            Q=self.params.Q * 1.5,  # Moderate process noise
            R=self.params.R * 0.6,  # High measurement trust
            P0=self.params.P0,
            dt=self.params.dt,
            adaptive_enabled=True
        )
        
        return models
    
    def predict(self, dt: Optional[float] = None) -> np.ndarray:
        """
        Predict next state estimate.
        
        Args:
            dt (float, optional): Time step. If None, uses default dt.
            
        Returns:
            np.ndarray: Predicted state estimate
        """
        if dt is None:
            dt = self.params.dt
        
        # Update state transition matrix for current dt
        self.F[0, 3] = dt
        self.F[1, 4] = dt
        self.F[2, 5] = dt
        self.F[6, 9] = dt
        self.F[7, 10] = dt
        self.F[8, 11] = dt
        
        # Predict state
        self.state.x = self.F @ self.state.x
        
        # Predict covariance
        self.state.P = self.F @ self.state.P @ self.F.T + self.params.Q
        
        # Update timestamp
        self.state.timestamp += dt
        
        return self.state.x.copy()
    
    def update(self, measurement: np.ndarray, measurement_covariance: Optional[np.ndarray] = None) -> np.ndarray:
        """
        Update state estimate with new measurement.
        
        Args:
            measurement (np.ndarray): New measurement
            measurement_covariance (np.ndarray, optional): Measurement covariance. If None, uses default R.
            
        Returns:
            np.ndarray: Updated state estimate
        """
        # Detect flight phase
        new_phase = self._detect_flight_phase(measurement)
        if new_phase != self.state.phase:
            self._transition_phase(new_phase)
        
        # Use phase-specific parameters
        current_params = self.phase_models[self.state.phase]
        R = measurement_covariance if measurement_covariance is not None else current_params.R
        
        # Check for outliers
        if self._is_outlier(measurement, R):
            self.outlier_count += 1
            logger.warning(f"Outlier detected: measurement={measurement}")
            return self.state.x.copy()
        
        # Compute innovation
        predicted_measurement = self.H @ self.state.x
        self.state.innovation = measurement - predicted_measurement
        
        # Compute innovation covariance
        self.state.innovation_covariance = self.H @ self.state.P @ self.H.T + R
        
        # Compute Kalman gain
        try:
            K = self.state.P @ self.H.T @ inv(self.state.innovation_covariance)
        except np.linalg.LinAlgError:
            logger.error("Singular matrix in Kalman gain computation")
            return self.state.x.copy()
        
        # Update state estimate
        self.state.x = self.state.x + K @ self.state.innovation
        
        # Update covariance
        I = np.eye(self.state_dim)
        self.state.P = (I - K @ self.H) @ self.state.P
        
        # Compute Mahalanobis distance for outlier detection
        self.state.mahalanobis_distance = np.sqrt(
            self.state.innovation.T @ inv(self.state.innovation_covariance) @ self.state.innovation
        )
        
        # Store innovation for adaptive tuning
        self.innovation_history.append(self.state.innovation.copy())
        if len(self.innovation_history) > self.adaptation_window:
            self.innovation_history.pop(0)
        
        # Adaptive parameter tuning
        if current_params.adaptive_enabled:
            self._adaptive_tuning()
        
        # Update static detection buffer
        self._update_static_detection()
        
        self.total_updates += 1
        return self.state.x.copy()
    
    def _detect_flight_phase(self, measurement: np.ndarray) -> FlightPhase:
        """
        Detect current flight phase based on measurements and state.
        
        Args:
            measurement (np.ndarray): Current measurement
            
        Returns:
            FlightPhase: Detected flight phase
        """
        # Extract velocity from state (indices 3, 4, 5)
        velocity = self.state.x[3:6]
        velocity_magnitude = np.linalg.norm(velocity)
        
        # Extract position from measurement (indices 0, 1, 2)
        position = measurement[:3]
        
        # Static detection
        if self._is_static():
            return FlightPhase.GROUND
        
        # Height-based detection
        height = position[2]
        
        # Takeoff detection: low height, increasing velocity
        if height < 0.5 and velocity_magnitude > 0.5:
            return FlightPhase.TAKEOFF
        
        # Landing detection: low height, decreasing velocity
        if height < 1.0 and velocity_magnitude < 0.3:
            return FlightPhase.LANDING
        
        # Maneuver detection: high velocity or angular rates
        angular_rates = self.state.x[9:12]
        angular_rate_magnitude = np.linalg.norm(angular_rates)
        
        if velocity_magnitude > 2.0 or angular_rate_magnitude > 1.0:
            return FlightPhase.MANEUVER
        
        # Default to hover
        return FlightPhase.HOVER
    
    def _transition_phase(self, new_phase: FlightPhase):
        """
        Handle transition to new flight phase.
        
        Args:
            new_phase (FlightPhase): New flight phase
        """
        if new_phase != self.state.phase:
            logger.info(f"Flight phase transition: {self.state.phase.value} -> {new_phase.value}")
            self.state.phase = new_phase
            self.phase_transitions += 1
            
            # Update parameters for new phase
            new_params = self.phase_models[new_phase]
            self.params.Q = new_params.Q.copy()
            self.params.R = new_params.R.copy()
    
    def _is_outlier(self, measurement: np.ndarray, R: np.ndarray) -> bool:
        """
        Check if measurement is an outlier using Mahalanobis distance.
        
        Args:
            measurement (np.ndarray): Measurement to check
            R (np.ndarray): Measurement covariance
            
        Returns:
            bool: True if measurement is an outlier
        """
        predicted_measurement = self.H @ self.state.x
        innovation = measurement - predicted_measurement
        innovation_covariance = self.H @ self.state.P @ self.H.T + R
        
        try:
            mahalanobis_distance = np.sqrt(
                innovation.T @ inv(innovation_covariance) @ innovation
            )
            return mahalanobis_distance > self.params.outlier_threshold
        except np.linalg.LinAlgError:
            return False
    
    def _is_static(self) -> bool:
        """
        Check if the system is in a static state.
        
        Returns:
            bool: True if system is static
        """
        if len(self.static_buffer) < self.params.static_window_size:
            return False
        
        # Check if velocity has been consistently low
        recent_velocities = [state[3:6] for state in self.static_buffer[-self.params.static_window_size:]]
        velocity_magnitudes = [np.linalg.norm(v) for v in recent_velocities]
        
        return all(v < self.static_threshold for v in velocity_magnitudes)
    
    def _update_static_detection(self):
        """Update static detection buffer with current state."""
        self.static_buffer.append(self.state.x.copy())
        if len(self.static_buffer) > self.params.static_window_size:
            self.static_buffer.pop(0)
    
    def _adaptive_tuning(self):
        """
        Adaptively tune filter parameters based on innovation statistics.
        """
        if len(self.innovation_history) < 10:
            return
        
        # Compute innovation statistics
        innovations = np.array(self.innovation_history)
        innovation_mean = np.mean(innovations, axis=0)
        innovation_covariance = np.cov(innovations.T)
        
        # Compute theoretical innovation covariance
        theoretical_covariance = self.H @ self.state.P @ self.H.T + self.params.R
        
        # Compute adaptation factor
        try:
            adaptation_factor = np.trace(innovation_covariance) / np.trace(theoretical_covariance)
            adaptation_factor = np.clip(adaptation_factor, 0.1, 10.0)  # Limit adaptation range
        except:
            return
        
        # Adapt measurement noise covariance
        self.params.R = self.params.R * adaptation_factor
        
        # Store parameter history
        self.parameter_history.append({
            'timestamp': time.time(),
            'adaptation_factor': adaptation_factor,
            'innovation_covariance': innovation_covariance.copy(),
            'R': self.params.R.copy()
        })
        
        if len(self.parameter_history) > 100:
            self.parameter_history.pop(0)
    
    def get_state_estimate(self) -> np.ndarray:
        """
        Get current state estimate.
        
        Returns:
            np.ndarray: Current state estimate
        """
        return self.state.x.copy()
    
    def get_state_covariance(self) -> np.ndarray:
        """
        Get current state covariance matrix.
        
        Returns:
            np.ndarray: Current state covariance matrix
        """
        return self.state.P.copy()
    
    def get_innovation(self) -> np.ndarray:
        """
        Get last innovation (measurement residual).
        
        Returns:
            np.ndarray: Last innovation
        """
        return self.state.innovation.copy() if self.state.innovation is not None else np.zeros(self.measurement_dim)
    
    def get_flight_phase(self) -> FlightPhase:
        """
        Get current flight phase.
        
        Returns:
            FlightPhase: Current flight phase
        """
        return self.state.phase
    
    def get_performance_stats(self) -> Dict[str, float]:
        """
        Get performance statistics.
        
        Returns:
            Dict[str, float]: Performance statistics
        """
        return {
            'total_updates': self.total_updates,
            'outlier_count': self.outlier_count,
            'outlier_rate': self.outlier_count / max(self.total_updates, 1),
            'phase_transitions': self.phase_transitions,
            'current_phase': self.state.phase.value,
            'mahalanobis_distance': self.state.mahalanobis_distance,
            'static_detected': self._is_static()
        }
    
    def reset(self):
        """Reset filter state."""
        self.state.x = np.zeros(self.state_dim)
        self.state.P = self.params.P0.copy()
        self.state.phase = FlightPhase.UNKNOWN
        self.state.innovation = None
        self.state.innovation_covariance = None
        self.state.mahalanobis_distance = 0.0
        
        # Clear history
        self.innovation_history.clear()
        self.parameter_history.clear()
        self.static_buffer.clear()
        
        # Reset counters
        self.total_updates = 0
        self.outlier_count = 0
        self.phase_transitions = 0
        
        logger.info("Kalman filter state reset")


class MultiModelKalmanFilter:
    """
    Multi-model Kalman filter for handling different flight conditions.
    
    This class implements a bank of Kalman filters, each optimized for different
    flight conditions, and selects the best filter based on current conditions.
    """
    
    def __init__(self, base_params: KalmanParameters, num_models: int = 5):
        """
        Initialize multi-model Kalman filter.
        
        Args:
            base_params (KalmanParameters): Base parameters for all models
            num_models (int): Number of models in the bank
        """
        self.num_models = num_models
        self.filters = []
        self.model_weights = np.ones(num_models) / num_models  # Equal initial weights
        
        # Create filter bank with different parameter sets
        for i in range(num_models):
            # Vary process noise for different models
            Q_factor = 0.5 + i * 0.5  # 0.5 to 2.5
            params = KalmanParameters(
                Q=base_params.Q * Q_factor,
                R=base_params.R,
                P0=base_params.P0,
                dt=base_params.dt,
                adaptive_enabled=base_params.adaptive_enabled,
                outlier_threshold=base_params.outlier_threshold,
                static_window_size=base_params.static_window_size
            )
            
            filter_instance = AdaptiveKalmanFilter(params)
            self.filters.append(filter_instance)
        
        # Performance tracking
        self.model_likelihoods = np.zeros(num_models)
        self.total_updates = 0
        
        logger.info(f"Multi-model Kalman filter initialized with {num_models} models")
    
    def predict(self, dt: Optional[float] = None) -> np.ndarray:
        """
        Predict next state estimate using all models.
        
        Args:
            dt (float, optional): Time step
            
        Returns:
            np.ndarray: Weighted state estimate
        """
        # Predict with all models
        predictions = []
        for filter_instance in self.filters:
            prediction = filter_instance.predict(dt)
            predictions.append(prediction)
        
        # Weighted combination
        weighted_prediction = np.zeros_like(predictions[0])
        for i, prediction in enumerate(predictions):
            weighted_prediction += self.model_weights[i] * prediction
        
        return weighted_prediction
    
    def update(self, measurement: np.ndarray, measurement_covariance: Optional[np.ndarray] = None) -> np.ndarray:
        """
        Update all models and compute weighted state estimate.
        
        Args:
            measurement (np.ndarray): New measurement
            measurement_covariance (np.ndarray, optional): Measurement covariance
            
        Returns:
            np.ndarray: Weighted state estimate
        """
        # Update all models
        updates = []
        likelihoods = []
        
        for i, filter_instance in enumerate(self.filters):
            # Update filter
            update = filter_instance.update(measurement, measurement_covariance)
            updates.append(update)
            
            # Compute likelihood
            innovation = filter_instance.get_innovation()
            innovation_covariance = filter_instance.state.innovation_covariance
            
            if innovation_covariance is not None:
                try:
                    # Compute likelihood using innovation
                    likelihood = self._compute_likelihood(innovation, innovation_covariance)
                    likelihoods.append(likelihood)
                except:
                    likelihoods.append(1.0 / self.num_models)
            else:
                likelihoods.append(1.0 / self.num_models)
        
        # Update model weights using Bayes' rule
        likelihoods = np.array(likelihoods)
        self.model_likelihoods = likelihoods
        
        # Normalize and update weights
        total_likelihood = np.sum(likelihoods)
        if total_likelihood > 0:
            self.model_weights = likelihoods / total_likelihood
        else:
            self.model_weights = np.ones(self.num_models) / self.num_models
        
        # Compute weighted state estimate
        weighted_update = np.zeros_like(updates[0])
        for i, update in enumerate(updates):
            weighted_update += self.model_weights[i] * update
        
        self.total_updates += 1
        return weighted_update
    
    def _compute_likelihood(self, innovation: np.ndarray, innovation_covariance: np.ndarray) -> float:
        """
        Compute likelihood of measurement given model.
        
        Args:
            innovation (np.ndarray): Innovation vector
            innovation_covariance (np.ndarray): Innovation covariance matrix
            
        Returns:
            float: Likelihood value
        """
        try:
            # Compute Mahalanobis distance
            mahalanobis_distance = np.sqrt(
                innovation.T @ inv(innovation_covariance) @ innovation
            )
            
            # Compute likelihood using chi-squared distribution
            likelihood = chi2.pdf(mahalanobis_distance**2, df=len(innovation))
            
            return max(likelihood, 1e-10)  # Avoid zero likelihood
        except:
            return 1e-10
    
    def get_best_model_index(self) -> int:
        """
        Get index of the best performing model.
        
        Returns:
            int: Index of best model
        """
        return np.argmax(self.model_weights)
    
    def get_model_weights(self) -> np.ndarray:
        """
        Get current model weights.
        
        Returns:
            np.ndarray: Model weights
        """
        return self.model_weights.copy()
    
    def get_performance_stats(self) -> Dict[str, float]:
        """
        Get performance statistics for all models.
        
        Returns:
            Dict[str, float]: Performance statistics
        """
        stats = {
            'total_updates': self.total_updates,
            'best_model_index': self.get_best_model_index(),
            'model_weights': self.model_weights.tolist(),
            'model_likelihoods': self.model_likelihoods.tolist()
        }
        
        # Add individual filter stats
        for i, filter_instance in enumerate(self.filters):
            filter_stats = filter_instance.get_performance_stats()
            for key, value in filter_stats.items():
                stats[f'model_{i}_{key}'] = value
        
        return stats


# Example usage and testing
if __name__ == "__main__":
    """
    Example usage of the advanced Kalman filter system.
    
    This demonstrates how to set up and use the adaptive and multi-model
    Kalman filters for quadrotor state estimation.
    """
    
    # Initialize parameters
    state_dim = 12
    measurement_dim = 6
    
    # Create base parameters
    Q = np.eye(state_dim) * 0.1  # Process noise
    R = np.eye(measurement_dim) * 0.01  # Measurement noise
    P0 = np.eye(state_dim) * 1.0  # Initial state covariance
    
    base_params = KalmanParameters(Q=Q, R=R, P0=P0, dt=0.01)
    
    # Create adaptive Kalman filter
    adaptive_filter = AdaptiveKalmanFilter(base_params, state_dim, measurement_dim)
    
    # Create multi-model Kalman filter
    multi_model_filter = MultiModelKalmanFilter(base_params, num_models=5)
    
    # Simulation parameters
    dt = 0.01
    simulation_time = 10.0
    num_steps = int(simulation_time / dt)
    
    print("Advanced Kalman Filter Simulation")
    print("=" * 40)
    
    # Simulate flight data
    for step in range(num_steps):
        t = step * dt
        
        # Simulate true state (circular motion)
        true_position = np.array([2 * np.cos(t), 2 * np.sin(t), 1.0 + 0.5 * np.sin(2*t)])
        true_velocity = np.array([-2 * np.sin(t), 2 * np.cos(t), np.cos(2*t)])
        true_attitude = np.array([0.1 * np.sin(t), 0.1 * np.cos(t), t % (2*np.pi)])
        true_angular_rate = np.array([0.1 * np.cos(t), -0.1 * np.sin(t), 1.0])
        
        true_state = np.concatenate([true_position, true_velocity, true_attitude, true_angular_rate])
        
        # Simulate noisy measurement
        measurement = true_state[:6] + np.random.normal(0, 0.1, 6)  # Position and attitude only
        
        # Update filters
        adaptive_estimate = adaptive_filter.update(measurement)
        multi_model_estimate = multi_model_filter.update(measurement)
        
        # Print progress every second
        if step % 100 == 0:
            adaptive_error = np.linalg.norm(adaptive_estimate[:3] - true_position)
            multi_model_error = np.linalg.norm(multi_model_estimate[:3] - true_position)
            
            print(f"Time: {t:.1f}s | Adaptive Error: {adaptive_error:.3f}m | "
                  f"Multi-Model Error: {multi_model_error:.3f}m | "
                  f"Phase: {adaptive_filter.get_flight_phase().value}")
    
    # Print final statistics
    print("\n" + "=" * 40)
    print("Simulation Results:")
    
    adaptive_stats = adaptive_filter.get_performance_stats()
    multi_model_stats = multi_model_filter.get_performance_stats()
    
    print(f"Adaptive Filter:")
    print(f"  Total Updates: {adaptive_stats['total_updates']}")
    print(f"  Outlier Rate: {adaptive_stats['outlier_rate']:.3f}")
    print(f"  Phase Transitions: {adaptive_stats['phase_transitions']}")
    
    print(f"\nMulti-Model Filter:")
    print(f"  Total Updates: {multi_model_stats['total_updates']}")
    print(f"  Best Model: {multi_model_stats['best_model_index']}")
    print(f"  Model Weights: {multi_model_stats['model_weights']}")
