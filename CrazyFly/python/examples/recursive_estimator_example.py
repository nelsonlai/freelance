"""
Recursive Estimator Example for Quadrotor Control System
=======================================================

This example demonstrates the usage of the recursive estimator system for
quadrotor state estimation with multiple sensors and estimation algorithms.

The example shows:
- Setting up different types of estimators (EKF, UKF, Particle Filter)
- Multi-sensor data fusion with the SensorFusionManager
- Real-time state estimation with performance monitoring
- Adaptive sensor weighting and failure detection
- Comparison of different estimation algorithms

This serves as a comprehensive demonstration of the estimation capabilities
for quadrotor control systems.

Author: [Your Name]
Date: [Current Date]
License: MIT
"""

import numpy as np
import time
import matplotlib.pyplot as plt
from typing import List, Dict, Any
import logging

# Import estimation modules
from estimation import (
    RecursiveEstimatorFactory, EstimatorConfig, EstimatorType,
    SensorMeasurement, SensorType, SensorFusionManager, 
    SensorFusionConfig, FusionStrategy, ParticleFilterConfig,
    ResamplingStrategy
)

# Configure logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class QuadrotorSimulator:
    """
    Simple quadrotor simulator for generating test data.
    
    This class simulates a quadrotor with realistic dynamics and sensor
    measurements for testing the estimation algorithms.
    """
    
    def __init__(self, dt: float = 0.01):
        """
        Initialize quadrotor simulator.
        
        Args:
            dt (float): Simulation time step
        """
        self.dt = dt
        
        # Quadrotor parameters
        self.mass = 0.5  # kg
        self.gravity = 9.81  # m/s^2
        
        # State: [x, y, z, vx, vy, vz, roll, pitch, yaw, roll_rate, pitch_rate, yaw_rate]
        self.state = np.zeros(12)
        self.state[2] = 1.0  # Start at 1m height
        
        # Control input: [motor1, motor2, motor3, motor4]
        self.control_input = np.array([0.25, 0.25, 0.25, 0.25])  # Hover thrust
        
        # Sensor noise parameters
        self.imu_noise_std = 0.01
        self.gps_noise_std = 0.5
        self.vicon_noise_std = 0.001
        self.barometer_noise_std = 0.1
        
        # Simulation time
        self.time = 0.0
        
        logger.info("Quadrotor simulator initialized")
    
    def step(self, control_input: np.ndarray = None) -> Dict[str, Any]:
        """
        Step the simulation forward.
        
        Args:
            control_input (np.ndarray): Control input (optional)
            
        Returns:
            Dict[str, Any]: Simulation data including state and measurements
        """
        if control_input is not None:
            self.control_input = control_input
        
        # Simple quadrotor dynamics
        self._update_dynamics()
        
        # Generate sensor measurements
        measurements = self._generate_measurements()
        
        # Update time
        self.time += self.dt
        
        return {
            'time': self.time,
            'state': self.state.copy(),
            'control_input': self.control_input.copy(),
            'measurements': measurements
        }
    
    def _update_dynamics(self):
        """Update quadrotor dynamics."""
        # Extract state components
        position = self.state[0:3]
        velocity = self.state[3:6]
        attitude = self.state[6:9]
        angular_velocity = self.state[9:12]
        
        # Control input
        thrust = np.sum(self.control_input)
        
        # Simple dynamics (simplified for demonstration)
        # Position update
        self.state[0:3] = position + velocity * self.dt
        
        # Velocity update (simplified)
        self.state[3] = velocity[0] + (thrust * np.sin(attitude[1]) * np.cos(attitude[2])) * self.dt
        self.state[4] = velocity[1] + (-thrust * np.sin(attitude[2])) * self.dt
        self.state[5] = velocity[2] + (thrust * np.cos(attitude[1]) * np.cos(attitude[2]) - self.gravity) * self.dt
        
        # Attitude update
        self.state[6:9] = attitude + angular_velocity * self.dt
        
        # Angular velocity update (simplified)
        self.state[9:12] = angular_velocity
    
    def _generate_measurements(self) -> Dict[SensorType, SensorMeasurement]:
        """Generate sensor measurements with noise."""
        measurements = {}
        
        # IMU measurement (acceleration and angular velocity)
        imu_data = np.concatenate([
            self.state[3:6],  # velocity
            self.state[9:12]  # angular velocity
        ])
        imu_noise = np.random.normal(0, self.imu_noise_std, 6)
        
        measurements[SensorType.IMU] = SensorMeasurement(
            sensor_type=SensorType.IMU,
            data=imu_data + imu_noise,
            timestamp=self.time,
            covariance=np.eye(6) * self.imu_noise_std**2,
            quality=0.9
        )
        
        # GPS measurement (position)
        gps_data = self.state[0:3]  # position
        gps_noise = np.random.normal(0, self.gps_noise_std, 3)
        
        measurements[SensorType.GPS] = SensorMeasurement(
            sensor_type=SensorType.GPS,
            data=gps_data + gps_noise,
            timestamp=self.time,
            covariance=np.eye(3) * self.gps_noise_std**2,
            quality=0.8
        )
        
        # Vicon measurement (position and velocity)
        vicon_data = np.concatenate([
            self.state[0:3],  # position
            self.state[3:6]   # velocity
        ])
        vicon_noise = np.random.normal(0, self.vicon_noise_std, 6)
        
        measurements[SensorType.VICON] = SensorMeasurement(
            sensor_type=SensorType.VICON,
            data=vicon_data + vicon_noise,
            timestamp=self.time,
            covariance=np.eye(6) * self.vicon_noise_std**2,
            quality=0.95
        )
        
        # Barometer measurement (altitude)
        barometer_data = np.array([self.state[2]])  # z position
        barometer_noise = np.random.normal(0, self.barometer_noise_std, 1)
        
        measurements[SensorType.BAROMETER] = SensorMeasurement(
            sensor_type=SensorType.BAROMETER,
            data=barometer_data + barometer_noise,
            timestamp=self.time,
            covariance=np.eye(1) * self.barometer_noise_std**2,
            quality=0.7
        )
        
        return measurements
    
    def set_control_input(self, control_input: np.ndarray):
        """Set control input for the next simulation step."""
        self.control_input = control_input.copy()
    
    def get_state(self) -> np.ndarray:
        """Get current state."""
        return self.state.copy()


def compare_estimators():
    """
    Compare different estimation algorithms.
    
    This function demonstrates the performance of different estimation
    algorithms (EKF, UKF, Particle Filter) on the same data.
    """
    print("Comparing Estimation Algorithms")
    print("=" * 50)
    
    # Simulation parameters
    dt = 0.01
    simulation_time = 10.0
    num_steps = int(simulation_time / dt)
    
    # Create simulator
    simulator = QuadrotorSimulator(dt)
    
    # Create estimators
    estimators = {}
    
    # EKF
    ekf_config = EstimatorConfig(
        estimator_type=EstimatorType.EKF,
        state_dimension=12,
        process_noise_covariance=np.eye(12) * 0.01,
        initial_state=np.zeros(12),
        initial_covariance=np.eye(12) * 0.1,
        update_rate=100.0
    )
    estimators['EKF'] = RecursiveEstimatorFactory.create_estimator(EstimatorType.EKF, ekf_config)
    
    # UKF
    ukf_config = EstimatorConfig(
        estimator_type=EstimatorType.UKF,
        state_dimension=12,
        process_noise_covariance=np.eye(12) * 0.01,
        initial_state=np.zeros(12),
        initial_covariance=np.eye(12) * 0.1,
        update_rate=100.0
    )
    estimators['UKF'] = RecursiveEstimatorFactory.create_estimator(EstimatorType.UKF, ukf_config)
    
    # Particle Filter
    pf_config = ParticleFilterConfig(
        num_particles=500,
        resampling_strategy=ResamplingStrategy.SYSTEMATIC,
        resampling_threshold=0.5,
        state_dimension=12,
        process_noise_covariance=np.eye(12) * 0.01,
        initial_state=np.zeros(12),
        initial_covariance=np.eye(12) * 0.1,
        update_rate=100.0
    )
    estimators['Particle Filter'] = ParticleFilter(pf_config)
    
    # Storage for results
    true_states = []
    estimates = {name: [] for name in estimators.keys()}
    estimation_times = {name: [] for name in estimators.keys()}
    
    # Run simulation
    for step in range(num_steps):
        # Step simulator
        sim_data = simulator.step()
        true_state = sim_data['state']
        measurements = sim_data['measurements']
        
        # Store true state
        true_states.append(true_state.copy())
        
        # Update each estimator
        for name, estimator in estimators.items():
            start_time = time.time()
            
            # Add measurements to estimator
            for measurement in measurements.values():
                estimator.add_measurement(measurement)
            
            # Get estimate
            estimate = estimator.get_latest_estimate()
            if estimate is not None:
                estimates[name].append(estimate.state.copy())
            else:
                estimates[name].append(np.zeros(12))
            
            estimation_time = time.time() - start_time
            estimation_times[name].append(estimation_time)
        
        # Print progress
        if step % 100 == 0:
            print(f"Step {step}/{num_steps} ({step/num_steps*100:.1f}%)")
    
    # Compute performance metrics
    print("\nPerformance Comparison:")
    print("-" * 30)
    
    for name in estimators.keys():
        # Compute position error
        position_errors = []
        for i in range(len(true_states)):
            true_pos = true_states[i][0:3]
            est_pos = estimates[name][i][0:3]
            error = np.linalg.norm(true_pos - est_pos)
            position_errors.append(error)
        
        avg_position_error = np.mean(position_errors)
        max_position_error = np.max(position_errors)
        avg_estimation_time = np.mean(estimation_times[name])
        
        print(f"{name}:")
        print(f"  Average position error: {avg_position_error:.3f} m")
        print(f"  Maximum position error: {max_position_error:.3f} m")
        print(f"  Average estimation time: {avg_estimation_time*1000:.3f} ms")
        print()
    
    return true_states, estimates, estimation_times


def demonstrate_sensor_fusion():
    """
    Demonstrate multi-sensor fusion capabilities.
    
    This function shows how the SensorFusionManager coordinates multiple
    sensors and provides robust state estimation.
    """
    print("Demonstrating Sensor Fusion")
    print("=" * 50)
    
    # Create sensor fusion configuration
    fusion_config = SensorFusionConfig(
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
    fusion_manager = SensorFusionManager(fusion_config)
    
    # Add callbacks
    def estimate_callback(estimate):
        """Callback for state estimates."""
        print(f"Fused estimate: pos={estimate.state[0:3]}, confidence={estimate.confidence:.3f}")
    
    def error_callback(error):
        """Callback for errors."""
        print(f"Fusion error: {error}")
    
    fusion_manager.add_estimate_callback(estimate_callback)
    fusion_manager.add_error_callback(error_callback)
    
    # Start fusion
    fusion_manager.start_fusion()
    
    # Create simulator
    simulator = QuadrotorSimulator(0.01)
    
    try:
        # Run simulation
        for step in range(1000):
            # Step simulator
            sim_data = simulator.step()
            measurements = sim_data['measurements']
            
            # Add measurements to fusion manager
            for measurement in measurements.values():
                fusion_manager.add_measurement(measurement)
            
            # Print sensor status every 100 steps
            if step % 100 == 0:
                sensor_status = fusion_manager.get_sensor_status()
                sensor_weights = fusion_manager.get_sensor_weights()
                print(f"\nStep {step}:")
                for sensor_type, status in sensor_status.items():
                    weight = sensor_weights[sensor_type]
                    print(f"  {sensor_type.value}: {status.value}, weight={weight:.3f}")
            
            time.sleep(0.01)  # 100Hz
        
        # Print final statistics
        print("\nFinal Statistics:")
        print("-" * 20)
        
        stats = fusion_manager.get_performance_stats()
        for key, value in stats.items():
            print(f"  {key}: {value:.3f}")
        
        sensor_stats = fusion_manager.get_sensor_statistics()
        for sensor_type, stats in sensor_stats.items():
            print(f"  {sensor_type.value}: {stats}")
    
    finally:
        # Stop fusion
        fusion_manager.stop_fusion()
        print("Sensor fusion stopped")


def demonstrate_adaptive_weighting():
    """
    Demonstrate adaptive sensor weighting.
    
    This function shows how the system adapts sensor weights based on
    performance and handles sensor failures.
    """
    print("Demonstrating Adaptive Sensor Weighting")
    print("=" * 50)
    
    # Create sensor fusion configuration
    fusion_config = SensorFusionConfig(
        fusion_strategy=FusionStrategy.ADAPTIVE,
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
    fusion_manager = SensorFusionManager(fusion_config)
    
    # Start fusion
    fusion_manager.start_fusion()
    
    # Create simulator
    simulator = QuadrotorSimulator(0.01)
    
    try:
        # Run simulation with varying sensor quality
        for step in range(2000):
            # Step simulator
            sim_data = simulator.step()
            measurements = sim_data['measurements']
            
            # Simulate sensor degradation
            if step > 500:
                # Degrade GPS quality
                if SensorType.GPS in measurements:
                    measurements[SensorType.GPS].quality *= 0.95
                    measurements[SensorType.GPS].covariance *= 1.1
            
            if step > 1000:
                # Degrade IMU quality
                if SensorType.IMU in measurements:
                    measurements[SensorType.IMU].quality *= 0.98
                    measurements[SensorType.IMU].covariance *= 1.05
            
            if step > 1500:
                # Simulate Vicon failure
                if SensorType.VICON in measurements:
                    measurements[SensorType.VICON].quality = 0.0
                    measurements[SensorType.VICON].valid = False
            
            # Add measurements to fusion manager
            for measurement in measurements.values():
                fusion_manager.add_measurement(measurement)
            
            # Print sensor weights every 200 steps
            if step % 200 == 0:
                sensor_weights = fusion_manager.get_sensor_weights()
                sensor_status = fusion_manager.get_sensor_status()
                print(f"\nStep {step}:")
                for sensor_type, weight in sensor_weights.items():
                    status = sensor_status[sensor_type]
                    print(f"  {sensor_type.value}: weight={weight:.3f}, status={status.value}")
            
            time.sleep(0.01)  # 100Hz
    
    finally:
        # Stop fusion
        fusion_manager.stop_fusion()
        print("Adaptive weighting demonstration stopped")


def main():
    """Main function to run all demonstrations."""
    print("Recursive Estimator Example for Quadrotor Control System")
    print("=" * 60)
    print()
    
    try:
        # Compare different estimation algorithms
        print("1. Comparing Estimation Algorithms")
        print("-" * 40)
        true_states, estimates, estimation_times = compare_estimators()
        print()
        
        # Demonstrate sensor fusion
        print("2. Demonstrating Sensor Fusion")
        print("-" * 40)
        demonstrate_sensor_fusion()
        print()
        
        # Demonstrate adaptive weighting
        print("3. Demonstrating Adaptive Sensor Weighting")
        print("-" * 40)
        demonstrate_adaptive_weighting()
        print()
        
        print("All demonstrations completed successfully!")
        
    except KeyboardInterrupt:
        print("\nDemonstration interrupted by user")
    except Exception as e:
        print(f"\nError during demonstration: {e}")
        logger.exception("Demonstration error")


if __name__ == "__main__":
    main()
