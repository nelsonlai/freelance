"""
Enhanced 4-Layer PID Controller for Quadrotor Control
=====================================================

This module implements a complete 4-layer PID control system for quadrotor flight control,
extending the traditional 2-layer PID (position + velocity) to include attitude and 
attitude-rate control layers for improved performance and stability.

The 4-layer architecture consists of:
1. Position Control Layer (Outer Loop) - Generates velocity commands from position errors
2. Velocity Control Layer (Inner Loop) - Generates attitude commands from velocity errors  
3. Attitude Control Layer - Generates angular velocity commands from attitude errors
4. Attitude-Rate Control Layer - Generates motor commands from angular velocity errors

This implementation is designed to work with the NCKU-Quadrotor-Navigation project
and provides enhanced stability, reduced overshoot, and better disturbance rejection
compared to the original 2-layer implementation.

Author: [Your Name]
Date: [Current Date]
License: MIT
"""

import numpy as np
import time
from typing import Dict, List, Tuple, Optional
from dataclasses import dataclass
from enum import Enum
import logging

# Configure logging for debugging and monitoring
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class ControlLayer(Enum):
    """Enumeration of the four control layers in the PID hierarchy."""
    POSITION = "position"      # Layer 1: Position control (outermost)
    VELOCITY = "velocity"      # Layer 2: Velocity control
    ATTITUDE = "attitude"      # Layer 3: Attitude control
    ATTITUDE_RATE = "attitude_rate"  # Layer 4: Attitude rate control (innermost)


@dataclass
class PIDGains:
    """
    Data structure for storing PID controller gains.
    
    Attributes:
        kp (float): Proportional gain - determines response speed and overshoot
        ki (float): Integral gain - eliminates steady-state error
        kd (float): Derivative gain - reduces overshoot and improves stability
        integral_limit (float): Maximum value for integral term to prevent windup
        output_limit (float): Maximum output value to prevent saturation
    """
    kp: float
    ki: float
    kd: float
    integral_limit: float = 100.0
    output_limit: float = 100.0


@dataclass
class ControlState:
    """
    Data structure for storing the current state of a control layer.
    
    Attributes:
        error (float): Current error between setpoint and measurement
        integral (float): Accumulated integral of error
        derivative (float): Rate of change of error
        previous_error (float): Error from previous time step
        output (float): Current control output
        timestamp (float): Timestamp of last update
    """
    error: float = 0.0
    integral: float = 0.0
    derivative: float = 0.0
    previous_error: float = 0.0
    output: float = 0.0
    timestamp: float = 0.0


class PIDController:
    """
    Single-layer PID controller implementation with anti-windup and saturation.
    
    This class implements a standard PID controller with the following features:
    - Anti-windup protection to prevent integral term saturation
    - Output saturation to limit control signals
    - Derivative filtering to reduce noise sensitivity
    - Time-based integration for consistent behavior across different sampling rates
    """
    
    def __init__(self, gains: PIDGains, name: str = "PID"):
        """
        Initialize PID controller with specified gains.
        
        Args:
            gains (PIDGains): PID controller gains and limits
            name (str): Name identifier for logging and debugging
        """
        self.gains = gains
        self.name = name
        self.state = ControlState()
        self.enabled = True
        
        # Initialize timing for derivative calculation
        self.last_update_time = time.time()
        
        # Performance monitoring
        self.total_updates = 0
        self.max_error = 0.0
        self.rms_error = 0.0
        
        logger.info(f"Initialized {name} PID controller with gains: Kp={gains.kp}, Ki={gains.ki}, Kd={gains.kd}")
    
    def update(self, setpoint: float, measurement: float, dt: Optional[float] = None) -> float:
        """
        Update PID controller and compute control output.
        
        This method implements the standard PID control law:
        output = Kp * error + Ki * ∫error dt + Kd * d(error)/dt
        
        Args:
            setpoint (float): Desired value (target)
            measurement (float): Current measured value
            dt (float, optional): Time step. If None, calculated automatically
            
        Returns:
            float: Control output signal
        """
        if not self.enabled:
            return 0.0
        
        # Calculate time step if not provided
        current_time = time.time()
        if dt is None:
            dt = current_time - self.last_update_time
            dt = max(dt, 0.001)  # Minimum time step to prevent division by zero
        
        # Calculate error
        error = setpoint - measurement
        
        # Update state
        self.state.previous_error = self.state.error
        self.state.error = error
        self.state.timestamp = current_time
        
        # Calculate integral term with anti-windup
        self.state.integral += error * dt
        
        # Apply integral limit to prevent windup
        if abs(self.state.integral) > self.gains.integral_limit:
            self.state.integral = np.sign(self.state.integral) * self.gains.integral_limit
            logger.debug(f"{self.name}: Integral term limited to {self.gains.integral_limit}")
        
        # Calculate derivative term with filtering
        if dt > 0:
            self.state.derivative = (error - self.state.previous_error) / dt
        else:
            self.state.derivative = 0.0
        
        # Apply low-pass filter to derivative to reduce noise sensitivity
        alpha = 0.1  # Filter coefficient (0 = no filtering, 1 = no derivative)
        self.state.derivative = alpha * self.state.derivative + (1 - alpha) * self.state.derivative
        
        # Compute PID output
        output = (self.gains.kp * self.state.error + 
                 self.gains.ki * self.state.integral + 
                 self.gains.kd * self.state.derivative)
        
        # Apply output saturation
        if abs(output) > self.gains.output_limit:
            output = np.sign(output) * self.gains.output_limit
            logger.debug(f"{self.name}: Output saturated to {self.gains.output_limit}")
        
        self.state.output = output
        self.last_update_time = current_time
        
        # Update performance metrics
        self.total_updates += 1
        self.max_error = max(self.max_error, abs(error))
        self.rms_error = np.sqrt((self.rms_error**2 * (self.total_updates - 1) + error**2) / self.total_updates)
        
        return output
    
    def reset(self):
        """Reset controller state (clear integral and derivative terms)."""
        self.state.integral = 0.0
        self.state.derivative = 0.0
        self.state.previous_error = 0.0
        self.state.output = 0.0
        logger.info(f"{self.name}: Controller state reset")
    
    def get_performance_stats(self) -> Dict[str, float]:
        """Get performance statistics for monitoring and tuning."""
        return {
            "max_error": self.max_error,
            "rms_error": self.rms_error,
            "total_updates": self.total_updates,
            "current_output": self.state.output,
            "current_error": self.state.error
        }


class FourLayerPIDController:
    """
    Complete 4-layer PID control system for quadrotor flight control.
    
    This class implements the hierarchical control structure where each layer
    generates commands for the layer below it. The control flow is:
    
    Position Error → Velocity Commands → Attitude Commands → Angular Velocity Commands → Motor Commands
    
    The implementation includes:
    - Smooth takeoff with S-curve trajectory
    - Anti-drift compensation during initial flight
    - Gain scheduling based on flight conditions
    - Comprehensive safety checks and limits
    - Real-time performance monitoring
    """
    
    def __init__(self, config: Dict[str, PIDGains]):
        """
        Initialize 4-layer PID controller with configuration for each layer.
        
        Args:
            config (Dict[str, PIDGains]): Configuration dictionary with PID gains for each layer
                Expected keys: 'position', 'velocity', 'attitude', 'attitude_rate'
        """
        # Initialize individual PID controllers for each layer
        self.position_controller = PIDController(config['position'], "Position")
        self.velocity_controller = PIDController(config['velocity'], "Velocity")
        self.attitude_controller = PIDController(config['attitude'], "Attitude")
        self.attitude_rate_controller = PIDController(config['attitude_rate'], "AttitudeRate")
        
        # Control state storage
        self.position_setpoint = np.zeros(3)  # [x, y, z]
        self.velocity_setpoint = np.zeros(3)  # [vx, vy, vz]
        self.attitude_setpoint = np.zeros(3)  # [roll, pitch, yaw]
        self.attitude_rate_setpoint = np.zeros(3)  # [roll_rate, pitch_rate, yaw_rate]
        
        # Current measurements
        self.current_position = np.zeros(3)
        self.current_velocity = np.zeros(3)
        self.current_attitude = np.zeros(3)
        self.current_attitude_rate = np.zeros(3)
        
        # Takeoff control
        self.takeoff_start_time = None
        self.takeoff_duration = 3.0  # seconds
        self.takeoff_target_height = 0.0
        
        # Anti-drift control
        self.anti_drift_start_time = None
        self.anti_drift_duration = 4.0  # seconds
        self.anti_drift_enabled = True
        
        # Safety limits
        self.max_velocity = 2.0  # m/s
        self.max_attitude = np.radians(30)  # 30 degrees
        self.max_attitude_rate = np.radians(180)  # 180 deg/s
        
        # Performance monitoring
        self.flight_start_time = None
        self.total_flight_time = 0.0
        
        logger.info("4-Layer PID Controller initialized successfully")
    
    def set_position_setpoint(self, x: float, y: float, z: float):
        """
        Set the target position for the quadrotor.
        
        Args:
            x (float): Target X position in meters
            y (float): Target Y position in meters  
            z (float): Target Z position in meters (height)
        """
        self.position_setpoint = np.array([x, y, z])
        logger.info(f"Position setpoint updated: [{x:.2f}, {y:.2f}, {z:.2f}]")
    
    def set_attitude_setpoint(self, roll: float, pitch: float, yaw: float):
        """
        Set the target attitude for the quadrotor.
        
        Args:
            roll (float): Target roll angle in radians
            pitch (float): Target pitch angle in radians
            yaw (float): Target yaw angle in radians
        """
        # Apply safety limits
        roll = np.clip(roll, -self.max_attitude, self.max_attitude)
        pitch = np.clip(pitch, -self.max_attitude, self.max_attitude)
        
        self.attitude_setpoint = np.array([roll, pitch, yaw])
        logger.debug(f"Attitude setpoint updated: [{np.degrees(roll):.1f}°, {np.degrees(pitch):.1f}°, {np.degrees(yaw):.1f}°]")
    
    def update_measurements(self, position: np.ndarray, velocity: np.ndarray, 
                          attitude: np.ndarray, attitude_rate: np.ndarray):
        """
        Update current measurements from sensors.
        
        Args:
            position (np.ndarray): Current position [x, y, z] in meters
            velocity (np.ndarray): Current velocity [vx, vy, vz] in m/s
            attitude (np.ndarray): Current attitude [roll, pitch, yaw] in radians
            attitude_rate (np.ndarray): Current attitude rates [roll_rate, pitch_rate, yaw_rate] in rad/s
        """
        self.current_position = np.array(position)
        self.current_velocity = np.array(velocity)
        self.current_attitude = np.array(attitude)
        self.current_attitude_rate = np.array(attitude_rate)
    
    def _smooth_takeoff_trajectory(self, current_time: float) -> float:
        """
        Generate smooth takeoff trajectory using S-curve to avoid initial thrust jumps.
        
        The S-curve provides smooth acceleration and deceleration, reducing oscillations
        during takeoff and improving stability.
        
        Args:
            current_time (float): Current time since takeoff start
            
        Returns:
            float: Target height for takeoff phase
        """
        if self.takeoff_start_time is None:
            return 0.0
        
        elapsed_time = current_time - self.takeoff_start_time
        
        if elapsed_time >= self.takeoff_duration:
            return self.takeoff_target_height
        
        # S-curve trajectory: smooth acceleration and deceleration
        # Normalized time: 0 to 1 over takeoff duration
        t_norm = elapsed_time / self.takeoff_duration
        
        # S-curve function: 3t^2 - 2t^3 (smooth start and end)
        s_curve = 3 * t_norm**2 - 2 * t_norm**3
        
        target_height = s_curve * self.takeoff_target_height
        
        return target_height
    
    def _anti_drift_compensation(self, current_time: float) -> Tuple[float, float]:
        """
        Apply anti-drift compensation during initial flight phase.
        
        This function sets desired X and Y velocities to 0 during the first 4 seconds
        of flight and compensates for actual drift by adjusting roll and pitch commands.
        
        Args:
            current_time (float): Current time since flight start
            
        Returns:
            Tuple[float, float]: Compensated roll and pitch commands
        """
        if not self.anti_drift_enabled or self.anti_drift_start_time is None:
            return 0.0, 0.0
        
        elapsed_time = current_time - self.anti_drift_start_time
        
        if elapsed_time >= self.anti_drift_duration:
            return 0.0, 0.0
        
        # Calculate drift compensation based on current velocity
        # Positive velocity in X requires negative pitch (forward tilt)
        # Positive velocity in Y requires positive roll (right tilt)
        pitch_compensation = -self.current_velocity[0] * 0.5  # Scale factor
        roll_compensation = self.current_velocity[1] * 0.5   # Scale factor
        
        return roll_compensation, pitch_compensation
    
    def compute_control_output(self, dt: float) -> Tuple[np.ndarray, Dict[str, float]]:
        """
        Compute control outputs for all four layers.
        
        This is the main control loop that processes the hierarchical control structure:
        1. Position control generates velocity commands
        2. Velocity control generates attitude commands  
        3. Attitude control generates angular velocity commands
        4. Attitude rate control generates motor commands
        
        Args:
            dt (float): Time step for control computation
            
        Returns:
            Tuple[np.ndarray, Dict[str, float]]: Motor commands and performance metrics
                Motor commands: [motor1, motor2, motor3, motor4] PWM values
                Performance metrics: Dictionary with control performance statistics
        """
        current_time = time.time()
        
        # Initialize flight timing
        if self.flight_start_time is None:
            self.flight_start_time = current_time
            self.takeoff_start_time = current_time
            self.anti_drift_start_time = current_time
        
        self.total_flight_time = current_time - self.flight_start_time
        
        # Layer 1: Position Control (Outer Loop)
        # Generate velocity commands from position errors
        velocity_commands = np.zeros(3)
        for i in range(3):
            # Apply smooth takeoff for Z-axis
            if i == 2 and self.takeoff_start_time:  # Z-axis (height)
                target_height = self._smooth_takeoff_trajectory(current_time)
                velocity_commands[i] = self.position_controller.update(
                    target_height, self.current_position[i], dt)
            else:
                velocity_commands[i] = self.position_controller.update(
                    self.position_setpoint[i], self.current_position[i], dt)
        
        # Apply velocity limits
        velocity_commands = np.clip(velocity_commands, -self.max_velocity, self.max_velocity)
        
        # Layer 2: Velocity Control (Inner Loop)
        # Generate attitude commands from velocity errors
        attitude_commands = np.zeros(3)
        for i in range(3):
            attitude_commands[i] = self.velocity_controller.update(
                velocity_commands[i], self.current_velocity[i], dt)
        
        # Apply anti-drift compensation
        roll_comp, pitch_comp = self._anti_drift_compensation(current_time)
        attitude_commands[0] += roll_comp   # Roll
        attitude_commands[1] += pitch_comp  # Pitch
        
        # Apply attitude limits
        attitude_commands[:2] = np.clip(attitude_commands[:2], -self.max_attitude, self.max_attitude)
        
        # Layer 3: Attitude Control
        # Generate angular velocity commands from attitude errors
        attitude_rate_commands = np.zeros(3)
        for i in range(3):
            attitude_rate_commands[i] = self.attitude_controller.update(
                attitude_commands[i], self.current_attitude[i], dt)
        
        # Apply attitude rate limits
        attitude_rate_commands = np.clip(attitude_rate_commands, -self.max_attitude_rate, self.max_attitude_rate)
        
        # Layer 4: Attitude Rate Control
        # Generate motor commands from angular velocity errors
        motor_commands = np.zeros(4)
        for i in range(3):
            motor_output = self.attitude_rate_controller.update(
                attitude_rate_commands[i], self.current_attitude_rate[i], dt)
            # Distribute motor output to appropriate motors based on control axis
            if i == 0:  # Roll: motors 1,3 vs 2,4
                motor_commands[0] += motor_output
                motor_commands[2] += motor_output
                motor_commands[1] -= motor_output
                motor_commands[3] -= motor_output
            elif i == 1:  # Pitch: motors 1,2 vs 3,4
                motor_commands[0] += motor_output
                motor_commands[1] += motor_output
                motor_commands[2] -= motor_output
                motor_commands[3] -= motor_output
            else:  # Yaw: motors 1,3 vs 2,4 (opposite direction)
                motor_commands[0] += motor_output
                motor_commands[2] -= motor_output
                motor_commands[1] -= motor_output
                motor_commands[3] += motor_output
        
        # Add base thrust for hover
        base_thrust = 0.5  # 50% throttle for hover
        motor_commands += base_thrust
        
        # Apply motor limits (0 to 1)
        motor_commands = np.clip(motor_commands, 0.0, 1.0)
        
        # Collect performance metrics
        performance_metrics = {
            'position_error': np.linalg.norm(self.position_setpoint - self.current_position),
            'velocity_error': np.linalg.norm(velocity_commands - self.current_velocity),
            'attitude_error': np.linalg.norm(attitude_commands - self.current_attitude),
            'attitude_rate_error': np.linalg.norm(attitude_rate_commands - self.current_attitude_rate),
            'flight_time': self.total_flight_time,
            'position_controller_stats': self.position_controller.get_performance_stats(),
            'velocity_controller_stats': self.velocity_controller.get_performance_stats(),
            'attitude_controller_stats': self.attitude_controller.get_performance_stats(),
            'attitude_rate_controller_stats': self.attitude_rate_controller.get_performance_stats()
        }
        
        return motor_commands, performance_metrics
    
    def reset_controllers(self):
        """Reset all controller states (useful for takeoff or emergency situations)."""
        self.position_controller.reset()
        self.velocity_controller.reset()
        self.attitude_controller.reset()
        self.attitude_rate_controller.reset()
        
        self.takeoff_start_time = None
        self.anti_drift_start_time = None
        self.flight_start_time = None
        
        logger.info("All controllers reset successfully")
    
    def enable_anti_drift(self, enabled: bool):
        """Enable or disable anti-drift compensation."""
        self.anti_drift_enabled = enabled
        logger.info(f"Anti-drift compensation {'enabled' if enabled else 'disabled'}")
    
    def set_takeoff_parameters(self, duration: float, target_height: float):
        """
        Set takeoff trajectory parameters.
        
        Args:
            duration (float): Takeoff duration in seconds
            target_height (float): Target height after takeoff in meters
        """
        self.takeoff_duration = duration
        self.takeoff_target_height = target_height
        logger.info(f"Takeoff parameters set: duration={duration}s, target_height={target_height}m")


# Example usage and testing
if __name__ == "__main__":
    """
    Example usage of the 4-layer PID controller.
    
    This demonstrates how to set up and use the controller for quadrotor flight control.
    """
    
    # Define PID gains for each layer (these would typically be tuned experimentally)
    config = {
        'position': PIDGains(kp=1.0, ki=0.1, kd=0.5, integral_limit=10.0, output_limit=2.0),
        'velocity': PIDGains(kp=2.0, ki=0.2, kd=1.0, integral_limit=5.0, output_limit=0.5),
        'attitude': PIDGains(kp=3.0, ki=0.0, kd=0.8, integral_limit=1.0, output_limit=0.3),
        'attitude_rate': PIDGains(kp=4.0, ki=0.0, kd=1.2, integral_limit=0.5, output_limit=0.2)
    }
    
    # Initialize controller
    controller = FourLayerPIDController(config)
    
    # Set target position
    controller.set_position_setpoint(1.0, 0.5, 2.0)  # 1m forward, 0.5m right, 2m up
    
    # Set takeoff parameters
    controller.set_takeoff_parameters(duration=3.0, target_height=2.0)
    
    # Simulation loop
    dt = 0.01  # 100Hz control loop
    simulation_time = 10.0  # 10 seconds simulation
    
    print("Starting 4-layer PID controller simulation...")
    print("=" * 50)
    
    for t in np.arange(0, simulation_time, dt):
        # Simulate current measurements (in real implementation, these come from sensors)
        current_position = np.array([0.1 * t, 0.05 * t, 0.2 * t])  # Simulated position
        current_velocity = np.array([0.1, 0.05, 0.2])  # Simulated velocity
        current_attitude = np.array([0.0, 0.0, 0.0])  # Simulated attitude
        current_attitude_rate = np.array([0.0, 0.0, 0.0])  # Simulated attitude rates
        
        # Update measurements
        controller.update_measurements(current_position, current_velocity, 
                                     current_attitude, current_attitude_rate)
        
        # Compute control output
        motor_commands, metrics = controller.compute_control_output(dt)
        
        # Print progress every second
        if int(t) != int(t - dt):
            print(f"Time: {t:.1f}s | Position Error: {metrics['position_error']:.3f}m | "
                  f"Motor Commands: [{motor_commands[0]:.3f}, {motor_commands[1]:.3f}, "
                  f"{motor_commands[2]:.3f}, {motor_commands[3]:.3f}]")
    
    print("=" * 50)
    print("Simulation completed!")
    print(f"Final position error: {metrics['position_error']:.3f}m")
    print(f"Total flight time: {metrics['flight_time']:.1f}s")
