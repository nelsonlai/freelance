"""
Sensor Fusion Manager for Quadrotor State Estimation
===================================================

This module implements a comprehensive sensor fusion manager that coordinates
multiple sensors and estimation algorithms to provide robust state estimation
for quadrotor control systems.

Key Features:
- Multi-sensor data fusion and coordination
- Adaptive sensor weighting and selection
- Sensor failure detection and handling
- Real-time sensor calibration and bias estimation
- Performance monitoring and diagnostics
- Modular sensor integration framework

The sensor fusion manager provides a unified interface for integrating
various sensors (IMU, GPS, Vicon, barometer, magnetometer) and estimation
algorithms (EKF, UKF, Particle Filter) to achieve robust state estimation.

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
from queue import Queue, Empty
import warnings

# Import base classes and estimators
from .recursive_estimator import (
    RecursiveEstimatorBase, EstimatorConfig, SensorMeasurement, 
    StateEstimate, SensorType, EstimatorType, RecursiveEstimatorFactory
)
from .particle_filter import ParticleFilter, ParticleFilterConfig

# Configure logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class FusionStrategy(Enum):
    """Enumeration of sensor fusion strategies."""
    SINGLE_ESTIMATOR = "single_estimator"      # Use single estimator for all sensors
    MULTIPLE_ESTIMATORS = "multiple_estimators"  # Use different estimators for different sensors
    HIERARCHICAL = "hierarchical"              # Hierarchical fusion with multiple levels
    ADAPTIVE = "adaptive"                      # Adaptive fusion based on sensor performance


class SensorStatus(Enum):
    """Enumeration of sensor status."""
    ACTIVE = "active"
    INACTIVE = "inactive"
    FAILED = "failed"
    CALIBRATING = "calibrating"
    DEGRADED = "degraded"


@dataclass
class SensorInfo:
    """
    Information about a sensor in the fusion system.
    
    Attributes:
        sensor_type (SensorType): Type of sensor
        status (SensorStatus): Current sensor status
        weight (float): Sensor weight in fusion
        last_update_time (float): Last update timestamp
        update_count (int): Number of updates received
        error_count (int): Number of errors encountered
        quality_history (List[float]): History of measurement quality
        bias_estimate (np.ndarray): Estimated sensor bias
        scale_estimate (np.ndarray): Estimated sensor scale
    """
    sensor_type: SensorType
    status: SensorStatus = SensorStatus.ACTIVE
    weight: float = 1.0
    last_update_time: float = 0.0
    update_count: int = 0
    error_count: int = 0
    quality_history: List[float] = None
    bias_estimate: np.ndarray = None
    scale_estimate: np.ndarray = None


@dataclass
class SensorFusionConfig:
    """
    Configuration for sensor fusion manager.
    
    Attributes:
        fusion_strategy (FusionStrategy): Sensor fusion strategy
        primary_estimator_type (EstimatorType): Primary estimator type
        secondary_estimator_types (Dict): Secondary estimator types for specific sensors
        sensor_weights (Dict): Initial sensor weights
        enable_adaptive_weighting (bool): Enable adaptive sensor weighting
        enable_sensor_calibration (bool): Enable sensor calibration
        enable_failure_detection (bool): Enable sensor failure detection
        failure_threshold (float): Threshold for sensor failure detection
        calibration_samples (int): Number of samples for calibration
        update_rate (float): Fusion update rate in Hz
    """
    fusion_strategy: FusionStrategy = FusionStrategy.SINGLE_ESTIMATOR
    primary_estimator_type: EstimatorType = EstimatorType.EKF
    secondary_estimator_types: Dict[SensorType, EstimatorType] = None
    sensor_weights: Dict[SensorType, float] = None
    enable_adaptive_weighting: bool = True
    enable_sensor_calibration: bool = True
    enable_failure_detection: bool = True
    failure_threshold: float = 0.1
    calibration_samples: int = 100
    update_rate: float = 100.0


class SensorFusionManager:
    """
    Sensor fusion manager for coordinating multiple sensors and estimators.
    
    This class provides a unified interface for sensor fusion, handling
    multiple sensors, estimation algorithms, and providing robust state
    estimation through intelligent sensor coordination.
    """
    
    def __init__(self, config: SensorFusionConfig):
        """
        Initialize sensor fusion manager.
        
        Args:
            config (SensorFusionConfig): Sensor fusion configuration
        """
        self.config = config
        
        # Sensor management
        self.sensors: Dict[SensorType, SensorInfo] = {}
        self.sensor_measurements: Dict[SensorType, Queue] = {}
        self.sensor_callbacks: Dict[SensorType, List[Callable]] = {}
        
        # Estimator management
        self.estimators: Dict[str, RecursiveEstimatorBase] = {}
        self.primary_estimator: Optional[RecursiveEstimatorBase] = None
        
        # Fusion state
        self.current_estimate: Optional[StateEstimate] = None
        self.estimate_history: List[StateEstimate] = []
        
        # Performance monitoring
        self.fusion_times = []
        self.update_count = 0
        self.last_update_time = time.time()
        
        # Callbacks
        self.estimate_callbacks: List[Callable] = []
        self.error_callbacks: List[Callable] = []
        
        # Threading
        self.lock = threading.Lock()
        self.fusion_thread = None
        self.running = False
        
        # Initialize sensors and estimators
        self._initialize_sensors()
        self._initialize_estimators()
        
        logger.info("Sensor fusion manager initialized")
    
    def _initialize_sensors(self):
        """Initialize sensor information and queues."""
        # Default sensor weights
        default_weights = {
            SensorType.VICON: 1.0,      # High accuracy
            SensorType.IMU: 0.8,        # High frequency
            SensorType.GPS: 0.6,        # Medium accuracy
            SensorType.BAROMETER: 0.4,  # Low accuracy
            SensorType.MAGNETOMETER: 0.3,  # Low accuracy
            SensorType.OPTICAL_FLOW: 0.5,  # Medium accuracy
            SensorType.ULTRASONIC: 0.3   # Low accuracy
        }
        
        # Initialize sensor information
        for sensor_type in SensorType:
            weight = self.config.sensor_weights.get(sensor_type, default_weights.get(sensor_type, 0.5))
            
            sensor_info = SensorInfo(
                sensor_type=sensor_type,
                status=SensorStatus.INACTIVE,
                weight=weight,
                quality_history=[]
            )
            
            self.sensors[sensor_type] = sensor_info
            self.sensor_measurements[sensor_type] = Queue()
            self.sensor_callbacks[sensor_type] = []
        
        logger.info(f"Initialized {len(self.sensors)} sensors")
    
    def _initialize_estimators(self):
        """Initialize estimation algorithms."""
        # Create primary estimator
        primary_config = EstimatorConfig(
            estimator_type=self.config.primary_estimator_type,
            state_dimension=12,
            process_noise_covariance=np.eye(12) * 0.01,
            initial_state=np.zeros(12),
            initial_covariance=np.eye(12) * 0.1,
            update_rate=self.config.update_rate,
            enable_adaptive_noise=True,
            enable_outlier_detection=True
        )
        
        self.primary_estimator = RecursiveEstimatorFactory.create_estimator(
            self.config.primary_estimator_type, primary_config
        )
        self.estimators['primary'] = self.primary_estimator
        
        # Create secondary estimators if configured
        if self.config.secondary_estimator_types:
            for sensor_type, estimator_type in self.config.secondary_estimator_types.items():
                secondary_config = EstimatorConfig(
                    estimator_type=estimator_type,
                    state_dimension=12,
                    process_noise_covariance=np.eye(12) * 0.01,
                    initial_state=np.zeros(12),
                    initial_covariance=np.eye(12) * 0.1,
                    update_rate=self.config.update_rate,
                    enable_adaptive_noise=True,
                    enable_outlier_detection=True
                )
                
                estimator = RecursiveEstimatorFactory.create_estimator(estimator_type, secondary_config)
                self.estimators[f'secondary_{sensor_type.value}'] = estimator
        
        logger.info(f"Initialized {len(self.estimators)} estimators")
    
    def start_fusion(self):
        """Start sensor fusion process."""
        if self.running:
            logger.warning("Sensor fusion already running")
            return
        
        self.running = True
        self.fusion_thread = threading.Thread(target=self._fusion_loop, daemon=True)
        self.fusion_thread.start()
        
        logger.info("Sensor fusion started")
    
    def stop_fusion(self):
        """Stop sensor fusion process."""
        self.running = False
        
        if self.fusion_thread:
            self.fusion_thread.join(timeout=1.0)
        
        logger.info("Sensor fusion stopped")
    
    def add_measurement(self, measurement: SensorMeasurement):
        """
        Add sensor measurement to fusion system.
        
        Args:
            measurement (SensorMeasurement): Sensor measurement
        """
        if not self.running:
            logger.warning("Sensor fusion not running, cannot add measurement")
            return
        
        # Validate measurement
        if not self._validate_measurement(measurement):
            logger.warning(f"Invalid measurement from {measurement.sensor_type}")
            return
        
        # Update sensor information
        sensor_info = self.sensors[measurement.sensor_type]
        sensor_info.last_update_time = measurement.timestamp
        sensor_info.update_count += 1
        sensor_info.quality_history.append(measurement.quality)
        
        # Keep quality history manageable
        if len(sensor_info.quality_history) > 100:
            sensor_info.quality_history.pop(0)
        
        # Add to measurement queue
        try:
            self.sensor_measurements[measurement.sensor_type].put_nowait(measurement)
        except:
            # Queue full, remove oldest measurement
            try:
                self.sensor_measurements[measurement.sensor_type].get_nowait()
                self.sensor_measurements[measurement.sensor_type].put_nowait(measurement)
            except:
                pass
        
        # Update sensor status
        if sensor_info.status == SensorStatus.INACTIVE:
            sensor_info.status = SensorStatus.ACTIVE
        
        # Call sensor callbacks
        for callback in self.sensor_callbacks[measurement.sensor_type]:
            try:
                callback(measurement)
            except Exception as e:
                logger.error(f"Error in sensor callback: {e}")
    
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
        
        return True
    
    def _fusion_loop(self):
        """Main sensor fusion loop."""
        while self.running:
            try:
                start_time = time.time()
                
                # Process measurements from all sensors
                self._process_measurements()
                
                # Update sensor weights if adaptive weighting is enabled
                if self.config.enable_adaptive_weighting:
                    self._update_sensor_weights()
                
                # Detect sensor failures
                if self.config.enable_failure_detection:
                    self._detect_sensor_failures()
                
                # Perform sensor calibration
                if self.config.enable_sensor_calibration:
                    self._update_sensor_calibration()
                
                # Compute fused state estimate
                self._compute_fused_estimate()
                
                # Update performance stats
                fusion_time = time.time() - start_time
                self.fusion_times.append(fusion_time)
                self.update_count += 1
                self.last_update_time = time.time()
                
                # Keep fusion times manageable
                if len(self.fusion_times) > 1000:
                    self.fusion_times.pop(0)
                
                # Sleep to maintain update rate
                sleep_time = max(0, 1.0 / self.config.update_rate - fusion_time)
                time.sleep(sleep_time)
                
            except Exception as e:
                logger.error(f"Error in fusion loop: {e}")
                # Call error callbacks
                for callback in self.error_callbacks:
                    try:
                        callback(e)
                    except Exception as callback_error:
                        logger.error(f"Error in error callback: {callback_error}")
    
    def _process_measurements(self):
        """Process measurements from all sensors."""
        for sensor_type, measurement_queue in self.sensor_measurements.items():
            # Process all available measurements
            while not measurement_queue.empty():
                try:
                    measurement = measurement_queue.get_nowait()
                    
                    # Add to appropriate estimator
                    if self.config.fusion_strategy == FusionStrategy.SINGLE_ESTIMATOR:
                        # Use primary estimator for all sensors
                        self.primary_estimator.add_measurement(measurement)
                    
                    elif self.config.fusion_strategy == FusionStrategy.MULTIPLE_ESTIMATORS:
                        # Use sensor-specific estimator if available
                        estimator_key = f'secondary_{sensor_type.value}'
                        if estimator_key in self.estimators:
                            self.estimators[estimator_key].add_measurement(measurement)
                        else:
                            self.primary_estimator.add_measurement(measurement)
                    
                    elif self.config.fusion_strategy == FusionStrategy.HIERARCHICAL:
                        # Hierarchical fusion (implement as needed)
                        self.primary_estimator.add_measurement(measurement)
                    
                    elif self.config.fusion_strategy == FusionStrategy.ADAPTIVE:
                        # Adaptive fusion based on sensor performance
                        self._adaptive_fusion(measurement)
                    
                except Empty:
                    break
                except Exception as e:
                    logger.error(f"Error processing measurement from {sensor_type}: {e}")
    
    def _adaptive_fusion(self, measurement: SensorMeasurement):
        """
        Perform adaptive sensor fusion.
        
        Args:
            measurement (SensorMeasurement): Sensor measurement
        """
        sensor_info = self.sensors[measurement.sensor_type]
        
        # Choose estimator based on sensor performance
        if sensor_info.status == SensorStatus.ACTIVE and sensor_info.weight > 0.5:
            # Use primary estimator for high-quality sensors
            self.primary_estimator.add_measurement(measurement)
        else:
            # Use secondary estimator for lower-quality sensors
            estimator_key = f'secondary_{measurement.sensor_type.value}'
            if estimator_key in self.estimators:
                self.estimators[estimator_key].add_measurement(measurement)
            else:
                self.primary_estimator.add_measurement(measurement)
    
    def _update_sensor_weights(self):
        """Update sensor weights based on performance."""
        for sensor_type, sensor_info in self.sensors.items():
            if sensor_info.status != SensorStatus.ACTIVE:
                continue
            
            # Compute performance metrics
            if len(sensor_info.quality_history) > 10:
                avg_quality = np.mean(sensor_info.quality_history[-10:])
                quality_variance = np.var(sensor_info.quality_history[-10:])
                
                # Update weight based on quality and consistency
                base_weight = avg_quality
                consistency_factor = 1.0 / (1.0 + quality_variance)
                sensor_info.weight = base_weight * consistency_factor
                
                # Ensure weight is within bounds
                sensor_info.weight = max(0.0, min(1.0, sensor_info.weight))
    
    def _detect_sensor_failures(self):
        """Detect sensor failures based on performance metrics."""
        current_time = time.time()
        
        for sensor_type, sensor_info in self.sensors.items():
            if sensor_info.status == SensorStatus.INACTIVE:
                continue
            
            # Check for timeout
            time_since_update = current_time - sensor_info.last_update_time
            if time_since_update > 1.0:  # 1 second timeout
                sensor_info.status = SensorStatus.FAILED
                logger.warning(f"Sensor {sensor_type} failed: timeout")
                continue
            
            # Check for low quality
            if len(sensor_info.quality_history) > 10:
                avg_quality = np.mean(sensor_info.quality_history[-10:])
                if avg_quality < self.config.failure_threshold:
                    sensor_info.status = SensorStatus.DEGRADED
                    logger.warning(f"Sensor {sensor_type} degraded: low quality")
                    continue
            
            # Check for high error rate
            if sensor_info.update_count > 0:
                error_rate = sensor_info.error_count / sensor_info.update_count
                if error_rate > 0.1:  # 10% error rate threshold
                    sensor_info.status = SensorStatus.DEGRADED
                    logger.warning(f"Sensor {sensor_type} degraded: high error rate")
                    continue
            
            # Sensor is healthy
            if sensor_info.status == SensorStatus.DEGRADED:
                sensor_info.status = SensorStatus.ACTIVE
                logger.info(f"Sensor {sensor_type} recovered")
    
    def _update_sensor_calibration(self):
        """Update sensor calibration parameters."""
        for sensor_type, sensor_info in self.sensors.items():
            if sensor_info.status != SensorStatus.ACTIVE:
                continue
            
            # Simple bias estimation (implement more sophisticated calibration as needed)
            if len(sensor_info.quality_history) > self.config.calibration_samples:
                # Estimate bias and scale (simplified implementation)
                if sensor_info.bias_estimate is None:
                    sensor_info.bias_estimate = np.zeros(self._get_sensor_dimension(sensor_type))
                if sensor_info.scale_estimate is None:
                    sensor_info.scale_estimate = np.ones(self._get_sensor_dimension(sensor_type))
    
    def _get_sensor_dimension(self, sensor_type: SensorType) -> int:
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
        elif sensor_type == SensorType.OPTICAL_FLOW:
            return 2
        elif sensor_type == SensorType.ULTRASONIC:
            return 1
        else:
            return 12  # Default state dimension
    
    def _compute_fused_estimate(self):
        """Compute fused state estimate from all estimators."""
        if self.config.fusion_strategy == FusionStrategy.SINGLE_ESTIMATOR:
            # Use primary estimator estimate
            self.current_estimate = self.primary_estimator.get_latest_estimate()
        
        elif self.config.fusion_strategy == FusionStrategy.MULTIPLE_ESTIMATORS:
            # Fuse estimates from multiple estimators
            self._fuse_multiple_estimates()
        
        elif self.config.fusion_strategy == FusionStrategy.HIERARCHICAL:
            # Hierarchical fusion (implement as needed)
            self.current_estimate = self.primary_estimator.get_latest_estimate()
        
        elif self.config.fusion_strategy == FusionStrategy.ADAPTIVE:
            # Adaptive fusion based on estimator performance
            self._adaptive_estimate_fusion()
        
        # Store estimate in history
        if self.current_estimate is not None:
            self.estimate_history.append(self.current_estimate)
            
            # Keep history size manageable
            if len(self.estimate_history) > 1000:
                self.estimate_history.pop(0)
            
            # Call estimate callbacks
            for callback in self.estimate_callbacks:
                try:
                    callback(self.current_estimate)
                except Exception as e:
                    logger.error(f"Error in estimate callback: {e}")
    
    def _fuse_multiple_estimates(self):
        """Fuse estimates from multiple estimators."""
        estimates = []
        weights = []
        
        # Collect estimates from all estimators
        for estimator_name, estimator in self.estimators.items():
            estimate = estimator.get_latest_estimate()
            if estimate is not None:
                estimates.append(estimate)
                # Use estimator performance as weight
                weight = estimate.confidence
                weights.append(weight)
        
        if not estimates:
            self.current_estimate = None
            return
        
        # Normalize weights
        weights = np.array(weights)
        weights = weights / np.sum(weights)
        
        # Compute weighted average
        fused_state = np.zeros(12)
        fused_covariance = np.zeros((12, 12))
        
        for estimate, weight in zip(estimates, weights):
            fused_state += weight * estimate.state
            fused_covariance += weight * estimate.covariance
        
        # Create fused estimate
        self.current_estimate = StateEstimate(
            state=fused_state,
            covariance=fused_covariance,
            timestamp=time.time(),
            confidence=np.mean(weights)
        )
    
    def _adaptive_estimate_fusion(self):
        """Perform adaptive estimate fusion."""
        # Use primary estimator as base
        primary_estimate = self.primary_estimator.get_latest_estimate()
        
        if primary_estimate is None:
            self.current_estimate = None
            return
        
        # Adjust estimate based on sensor performance
        sensor_weights = [sensor_info.weight for sensor_info in self.sensors.values()]
        avg_sensor_weight = np.mean(sensor_weights)
        
        # Scale confidence based on sensor performance
        adjusted_confidence = primary_estimate.confidence * avg_sensor_weight
        
        self.current_estimate = StateEstimate(
            state=primary_estimate.state,
            covariance=primary_estimate.covariance,
            timestamp=primary_estimate.timestamp,
            confidence=adjusted_confidence
        )
    
    def get_latest_estimate(self) -> Optional[StateEstimate]:
        """
        Get latest fused state estimate.
        
        Returns:
            Optional[StateEstimate]: Latest state estimate or None
        """
        return self.current_estimate
    
    def get_estimate_history(self) -> List[StateEstimate]:
        """
        Get estimate history.
        
        Returns:
            List[StateEstimate]: List of state estimates
        """
        return self.estimate_history.copy()
    
    def get_sensor_status(self) -> Dict[SensorType, SensorStatus]:
        """
        Get status of all sensors.
        
        Returns:
            Dict[SensorType, SensorStatus]: Sensor status dictionary
        """
        return {sensor_type: sensor_info.status for sensor_type, sensor_info in self.sensors.items()}
    
    def get_sensor_weights(self) -> Dict[SensorType, float]:
        """
        Get weights of all sensors.
        
        Returns:
            Dict[SensorType, float]: Sensor weight dictionary
        """
        return {sensor_type: sensor_info.weight for sensor_type, sensor_info in self.sensors.items()}
    
    def get_sensor_statistics(self) -> Dict[SensorType, Dict[str, Any]]:
        """
        Get statistics for all sensors.
        
        Returns:
            Dict[SensorType, Dict[str, Any]]: Sensor statistics dictionary
        """
        stats = {}
        for sensor_type, sensor_info in self.sensors.items():
            stats[sensor_type] = {
                'status': sensor_info.status,
                'weight': sensor_info.weight,
                'update_count': sensor_info.update_count,
                'error_count': sensor_info.error_count,
                'avg_quality': np.mean(sensor_info.quality_history) if sensor_info.quality_history else 0.0,
                'last_update_time': sensor_info.last_update_time
            }
        return stats
    
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
    
    def add_sensor_callback(self, sensor_type: SensorType, callback: Callable):
        """
        Add callback for specific sensor measurements.
        
        Args:
            sensor_type (SensorType): Type of sensor
            callback (Callable): Function to call when measurement is received
        """
        self.sensor_callbacks[sensor_type].append(callback)
    
    def get_performance_stats(self) -> Dict[str, float]:
        """
        Get performance statistics.
        
        Returns:
            Dict[str, float]: Performance statistics
        """
        if not self.fusion_times:
            return {'update_count': 0, 'avg_fusion_time': 0.0}
        
        return {
            'update_count': self.update_count,
            'avg_fusion_time': np.mean(self.fusion_times),
            'max_fusion_time': np.max(self.fusion_times),
            'min_fusion_time': np.min(self.fusion_times),
            'std_fusion_time': np.std(self.fusion_times),
            'last_update_time': self.last_update_time
        }
    
    def reset(self):
        """Reset sensor fusion manager."""
        with self.lock:
            # Reset sensors
            for sensor_info in self.sensors.values():
                sensor_info.status = SensorStatus.INACTIVE
                sensor_info.update_count = 0
                sensor_info.error_count = 0
                sensor_info.quality_history.clear()
                sensor_info.last_update_time = 0.0
            
            # Clear measurement queues
            for measurement_queue in self.sensor_measurements.values():
                while not measurement_queue.empty():
                    try:
                        measurement_queue.get_nowait()
                    except Empty:
                        break
            
            # Reset estimators
            for estimator in self.estimators.values():
                estimator.reset()
            
            # Reset fusion state
            self.current_estimate = None
            self.estimate_history.clear()
            self.fusion_times.clear()
            self.update_count = 0
            self.last_update_time = time.time()
            
            logger.info("Sensor fusion manager reset")


# Example usage and testing
if __name__ == "__main__":
    """
    Example usage of the sensor fusion manager.
    
    This demonstrates how to set up and use the sensor fusion manager for
    multi-sensor state estimation in quadrotor control systems.
    """
    
    # Initialize configuration
    config = SensorFusionConfig(
        fusion_strategy=FusionStrategy.SINGLE_ESTIMATOR,
        primary_estimator_type=EstimatorType.EKF,
        sensor_weights={
            SensorType.VICON: 1.0,
            SensorType.IMU: 0.8,
            SensorType.GPS: 0.6,
            SensorType.BAROMETER: 0.4
        },
        enable_adaptive_weighting=True,
        enable_sensor_calibration=True,
        enable_failure_detection=True,
        update_rate=100.0
    )
    
    # Create sensor fusion manager
    fusion_manager = SensorFusionManager(config)
    
    # Add callbacks
    def estimate_callback(estimate):
        """Callback for state estimates."""
        print(f"Fused estimate: {estimate.state[:3]}, confidence: {estimate.confidence:.3f}")
    
    def error_callback(error):
        """Callback for errors."""
        print(f"Fusion error: {error}")
    
    def imu_callback(measurement):
        """Callback for IMU measurements."""
        print(f"IMU measurement: {measurement.data[:3]}")
    
    fusion_manager.add_estimate_callback(estimate_callback)
    fusion_manager.add_error_callback(error_callback)
    fusion_manager.add_sensor_callback(SensorType.IMU, imu_callback)
    
    # Start fusion
    fusion_manager.start_fusion()
    
    # Simulate measurements from multiple sensors
    print("Sensor Fusion Manager Simulation")
    print("=" * 40)
    
    try:
        # Simulate IMU measurements
        for i in range(10):
            imu_measurement = SensorMeasurement(
                sensor_type=SensorType.IMU,
                data=np.array([0.1, 0.2, 0.3, 0.01, 0.02, 0.03]),
                timestamp=time.time(),
                covariance=np.eye(6) * 0.01,
                quality=0.9
            )
            fusion_manager.add_measurement(imu_measurement)
            time.sleep(0.01)
        
        # Simulate GPS measurements
        for i in range(5):
            gps_measurement = SensorMeasurement(
                sensor_type=SensorType.GPS,
                data=np.array([1.0 + i*0.1, 2.0 + i*0.1, 3.0 + i*0.1]),
                timestamp=time.time(),
                covariance=np.eye(3) * 1.0,
                quality=0.8
            )
            fusion_manager.add_measurement(gps_measurement)
            time.sleep(0.02)
        
        # Simulate Vicon measurements
        for i in range(3):
            vicon_measurement = SensorMeasurement(
                sensor_type=SensorType.VICON,
                data=np.array([1.0 + i*0.1, 2.0 + i*0.1, 3.0 + i*0.1, 0.1, 0.2, 0.3]),
                timestamp=time.time(),
                covariance=np.eye(6) * 0.001,
                quality=0.95
            )
            fusion_manager.add_measurement(vicon_measurement)
            time.sleep(0.033)
        
        # Print final statistics
        print("\n" + "=" * 40)
        print("Sensor Fusion Results:")
        
        stats = fusion_manager.get_performance_stats()
        for key, value in stats.items():
            print(f"  {key}: {value:.3f}")
        
        sensor_stats = fusion_manager.get_sensor_statistics()
        for sensor_type, stats in sensor_stats.items():
            print(f"  {sensor_type.value}: {stats}")
        
        latest_estimate = fusion_manager.get_latest_estimate()
        if latest_estimate:
            print(f"  Final estimate: {latest_estimate.state[:3]}")
            print(f"  Final confidence: {latest_estimate.confidence:.3f}")
        
        print(f"  Total updates: {fusion_manager.update_count}")
        print(f"  Average fusion time: {np.mean(fusion_manager.fusion_times):.3f}s")
        
    finally:
        # Stop fusion
        fusion_manager.stop_fusion()
        print("Sensor fusion stopped")
