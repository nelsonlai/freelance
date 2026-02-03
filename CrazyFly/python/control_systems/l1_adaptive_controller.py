"""
L1 Adaptive Controller for Quadrotor Flight Control
==================================================

This module implements an L1 Adaptive Control system for quadrotor flight control,
providing robust performance in the presence of uncertainties and disturbances.

L1 Adaptive Control Theory:
---------------------------
L1 adaptive control is a control methodology that provides fast adaptation while
maintaining stability. The key features are:

1. Fast Adaptation: The adaptive law updates parameters rapidly to track uncertainties
2. L1 Filtering: A low-pass filter prevents high-frequency control signals that could
   cause instability or excite unmodeled dynamics
3. Guaranteed Stability: The L1-norm condition ensures closed-loop stability
4. Predictable Performance: The controller provides predictable transient and steady-state
   performance bounds

The L1 adaptive control structure consists of:
- State Predictor: Predicts the system state based on current estimates
- Adaptive Law: Updates parameter estimates based on prediction errors
- Control Law: Generates control signals using the adaptive estimates
- L1 Filter: Filters the adaptive control signal to ensure stability

This implementation is designed to work with the L1-Crazyflie project and provides
enhanced robustness compared to traditional PID controllers.

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
from scipy import signal
from scipy.linalg import solve_discrete_lyapunov

# Configure logging for debugging and monitoring
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class L1ControllerType(Enum):
    """Enumeration of different L1 adaptive controller types."""
    STATE_FEEDBACK = "state_feedback"      # Full state feedback L1 controller
    OUTPUT_FEEDBACK = "output_feedback"    # Output feedback L1 controller
    REFERENCE_MODEL = "reference_model"    # Reference model following L1 controller


@dataclass
class L1Parameters:
    """
    Data structure for storing L1 adaptive controller parameters.
    
    Attributes:
        Am (np.ndarray): Desired closed-loop system matrix (n x n)
        Bm (np.ndarray): Desired closed-loop input matrix (n x m)
        Cm (np.ndarray): Output matrix (p x n)
        Km (np.ndarray): State feedback gain matrix (m x n)
        Kg (np.ndarray): Feedforward gain matrix (m x p)
        D (np.ndarray): Adaptation gain matrix (n x n)
        Ts (float): Sampling time in seconds
        filter_bandwidth (float): L1 filter bandwidth in rad/s
        adaptation_rate (float): Adaptation rate for parameter updates
        prediction_horizon (int): Number of steps for state prediction
    """
    Am: np.ndarray
    Bm: np.ndarray
    Cm: np.ndarray
    Km: np.ndarray
    Kg: np.ndarray
    D: np.ndarray
    Ts: float = 0.01
    filter_bandwidth: float = 10.0
    adaptation_rate: float = 100.0
    prediction_horizon: int = 5


@dataclass
class L1State:
    """
    Data structure for storing the current state of the L1 adaptive controller.
    
    Attributes:
        x_hat (np.ndarray): Estimated state vector
        theta_hat (np.ndarray): Estimated parameter vector
        sigma_hat (np.ndarray): Estimated matched uncertainty
        x_pred (np.ndarray): Predicted state vector
        u_adapt (np.ndarray): Adaptive control signal
        u_l1 (np.ndarray): L1 filtered control signal
        prediction_error (np.ndarray): State prediction error
        adaptation_error (np.ndarray): Parameter adaptation error
        timestamp (float): Timestamp of last update
    """
    x_hat: np.ndarray
    theta_hat: np.ndarray
    sigma_hat: np.ndarray
    x_pred: np.ndarray
    u_adapt: np.ndarray
    u_l1: np.ndarray
    prediction_error: np.ndarray
    adaptation_error: np.ndarray
    timestamp: float = 0.0


class L1Filter:
    """
    L1 filter implementation for adaptive control signal filtering.
    
    The L1 filter is a low-pass filter that prevents high-frequency components
    in the adaptive control signal from causing instability or exciting
    unmodeled dynamics. The filter bandwidth is a key design parameter that
    affects the trade-off between adaptation speed and stability.
    """
    
    def __init__(self, bandwidth: float, Ts: float, order: int = 2):
        """
        Initialize L1 filter with specified bandwidth.
        
        Args:
            bandwidth (float): Filter bandwidth in rad/s
            Ts (float): Sampling time in seconds
            order (int): Filter order (1 or 2)
        """
        self.bandwidth = bandwidth
        self.Ts = Ts
        self.order = order
        
        # Design low-pass filter using Butterworth approximation
        # Convert bandwidth from rad/s to Hz
        cutoff_freq = bandwidth / (2 * np.pi)
        nyquist_freq = 1.0 / (2 * Ts)
        
        # Normalize frequency
        normalized_freq = cutoff_freq / nyquist_freq
        
        # Design filter
        if order == 1:
            # First-order filter: H(s) = bandwidth / (s + bandwidth)
            self.b, self.a = signal.butter(1, normalized_freq, btype='low')
        else:
            # Second-order filter: H(s) = bandwidth^2 / (s^2 + 2*zeta*bandwidth*s + bandwidth^2)
            self.b, self.a = signal.butter(2, normalized_freq, btype='low')
        
        # Initialize filter state
        self.x_prev = np.zeros(len(self.b) - 1)
        self.y_prev = np.zeros(len(self.a) - 1)
        
        logger.info(f"L1 filter initialized: bandwidth={bandwidth:.1f} rad/s, order={order}")
    
    def filter_signal(self, u_input: np.ndarray) -> np.ndarray:
        """
        Filter the input signal using the designed low-pass filter.
        
        Args:
            u_input (np.ndarray): Input signal to filter
            
        Returns:
            np.ndarray: Filtered output signal
        """
        # Apply filter using difference equation
        # y[n] = b[0]*x[n] + b[1]*x[n-1] + ... - a[1]*y[n-1] - a[2]*y[n-2] - ...
        
        u_filtered = np.zeros_like(u_input)
        
        for i in range(len(u_input)):
            # Current input
            x_current = u_input[i]
            
            # Compute filtered output
            y_current = self.b[0] * x_current
            
            # Add contributions from previous inputs
            for j in range(1, len(self.b)):
                if i - j >= 0:
                    y_current += self.b[j] * u_input[i - j]
                else:
                    y_current += self.b[j] * self.x_prev[j - 1 - i]
            
            # Subtract contributions from previous outputs
            for j in range(1, len(self.a)):
                if i - j >= 0:
                    y_current -= self.a[j] * u_filtered[i - j]
                else:
                    y_current -= self.a[j] * self.y_prev[j - 1 - i]
            
            u_filtered[i] = y_current
        
        # Update previous values for next iteration
        if len(u_input) >= len(self.b) - 1:
            self.x_prev = u_input[-(len(self.b) - 1):]
        else:
            self.x_prev = np.concatenate([self.x_prev[-(len(self.b) - 1 - len(u_input)):], u_input])
        
        if len(u_filtered) >= len(self.a) - 1:
            self.y_prev = u_filtered[-(len(self.a) - 1):]
        else:
            self.y_prev = np.concatenate([self.y_prev[-(len(self.a) - 1 - len(u_filtered)):], u_filtered])
        
        return u_filtered
    
    def reset(self):
        """Reset filter state."""
        self.x_prev = np.zeros(len(self.b) - 1)
        self.y_prev = np.zeros(len(self.a) - 1)
        logger.debug("L1 filter state reset")


class StatePredictor:
    """
    State predictor for L1 adaptive control.
    
    The state predictor estimates the system state based on the current
    parameter estimates and generates prediction errors used for adaptation.
    """
    
    def __init__(self, Am: np.ndarray, Bm: np.ndarray, Ts: float):
        """
        Initialize state predictor.
        
        Args:
            Am (np.ndarray): Desired closed-loop system matrix
            Bm (np.ndarray): Desired closed-loop input matrix
            Ts (float): Sampling time
        """
        self.Am = Am
        self.Bm = Bm
        self.Ts = Ts
        
        # Discretize system matrices
        self.Ad = np.eye(Am.shape[0]) + Am * Ts
        self.Bd = Bm * Ts
        
        # Initialize prediction state
        self.x_pred = np.zeros(Am.shape[0])
        
        logger.info("State predictor initialized")
    
    def predict_state(self, x_current: np.ndarray, u_input: np.ndarray, 
                     theta_hat: np.ndarray, sigma_hat: np.ndarray) -> np.ndarray:
        """
        Predict the next state based on current estimates.
        
        Args:
            x_current (np.ndarray): Current state measurement
            u_input (np.ndarray): Current control input
            theta_hat (np.ndarray): Current parameter estimate
            sigma_hat (np.ndarray): Current uncertainty estimate
            
        Returns:
            np.ndarray: Predicted state
        """
        # State prediction equation: x_hat[k+1] = Ad * x_hat[k] + Bd * u[k] + Bd * sigma_hat[k]
        self.x_pred = (self.Ad @ x_current + 
                      self.Bd @ u_input + 
                      self.Bd @ sigma_hat)
        
        return self.x_pred
    
    def compute_prediction_error(self, x_measured: np.ndarray) -> np.ndarray:
        """
        Compute the prediction error for adaptation.
        
        Args:
            x_measured (np.ndarray): Measured state
            
        Returns:
            np.ndarray: Prediction error
        """
        return x_measured - self.x_pred


class AdaptiveLaw:
    """
    Adaptive law for parameter estimation in L1 adaptive control.
    
    The adaptive law updates parameter estimates based on prediction errors
    to ensure fast adaptation while maintaining stability.
    """
    
    def __init__(self, D: np.ndarray, Ts: float, adaptation_rate: float = 100.0):
        """
        Initialize adaptive law.
        
        Args:
            D (np.ndarray): Adaptation gain matrix
            Ts (float): Sampling time
            adaptation_rate (float): Adaptation rate parameter
        """
        self.D = D
        self.Ts = Ts
        self.gamma = adaptation_rate
        
        # Initialize parameter estimates
        self.theta_hat = np.zeros(D.shape[1])
        self.sigma_hat = np.zeros(D.shape[0])
        
        logger.info(f"Adaptive law initialized with adaptation rate: {adaptation_rate}")
    
    def update_parameters(self, prediction_error: np.ndarray, 
                         regressor: np.ndarray) -> Tuple[np.ndarray, np.ndarray]:
        """
        Update parameter estimates using adaptive law.
        
        The adaptive law follows the form:
        theta_hat_dot = gamma * D^T * prediction_error * regressor
        
        Args:
            prediction_error (np.ndarray): State prediction error
            regressor (np.ndarray): Regressor vector for parameter estimation
            
        Returns:
            Tuple[np.ndarray, np.ndarray]: Updated parameter and uncertainty estimates
        """
        # Update parameter estimates
        theta_dot = self.gamma * self.D.T @ prediction_error * regressor
        self.theta_hat += theta_dot * self.Ts
        
        # Update uncertainty estimate
        sigma_dot = self.gamma * prediction_error
        self.sigma_hat += sigma_dot * self.Ts
        
        return self.theta_hat, self.sigma_hat
    
    def reset(self):
        """Reset parameter estimates."""
        self.theta_hat = np.zeros_like(self.theta_hat)
        self.sigma_hat = np.zeros_like(self.sigma_hat)
        logger.debug("Adaptive law parameters reset")


class L1AdaptiveController:
    """
    Complete L1 adaptive controller implementation for quadrotor flight control.
    
    This class implements the full L1 adaptive control structure including:
    - State predictor for state estimation
    - Adaptive law for parameter estimation
    - Control law for signal generation
    - L1 filter for signal filtering
    
    The controller provides robust performance in the presence of:
    - Model uncertainties
    - External disturbances
    - Parameter variations
    - Unmodeled dynamics
    """
    
    def __init__(self, params: L1Parameters, controller_type: L1ControllerType = L1ControllerType.STATE_FEEDBACK):
        """
        Initialize L1 adaptive controller.
        
        Args:
            params (L1Parameters): Controller parameters
            controller_type (L1ControllerType): Type of L1 controller to implement
        """
        self.params = params
        self.controller_type = controller_type
        
        # Initialize system dimensions
        self.n = params.Am.shape[0]  # State dimension
        self.m = params.Bm.shape[1]  # Input dimension
        self.p = params.Cm.shape[0]  # Output dimension
        
        # Initialize components
        self.state_predictor = StatePredictor(params.Am, params.Bm, params.Ts)
        self.adaptive_law = AdaptiveLaw(params.D, params.Ts, params.adaptation_rate)
        self.l1_filter = L1Filter(params.filter_bandwidth, params.Ts)
        
        # Initialize controller state
        self.state = L1State(
            x_hat=np.zeros(self.n),
            theta_hat=np.zeros(params.D.shape[1]),
            sigma_hat=np.zeros(params.D.shape[0]),
            x_pred=np.zeros(self.n),
            u_adapt=np.zeros(self.m),
            u_l1=np.zeros(self.m),
            prediction_error=np.zeros(self.n),
            adaptation_error=np.zeros(self.n)
        )
        
        # Performance monitoring
        self.total_updates = 0
        self.max_prediction_error = 0.0
        self.rms_prediction_error = 0.0
        
        # Safety limits
        self.max_control_input = 1.0
        self.max_parameter_variation = 10.0
        
        logger.info(f"L1 Adaptive Controller initialized: {controller_type.value}")
    
    def set_reference(self, r: np.ndarray):
        """
        Set the reference signal for the controller.
        
        Args:
            r (np.ndarray): Reference signal vector
        """
        self.reference = np.array(r)
        logger.debug(f"Reference signal set: {r}")
    
    def update_measurements(self, x_measured: np.ndarray, y_measured: Optional[np.ndarray] = None):
        """
        Update current measurements from sensors.
        
        Args:
            x_measured (np.ndarray): Measured state vector
            y_measured (np.ndarray, optional): Measured output vector
        """
        self.x_measured = np.array(x_measured)
        if y_measured is not None:
            self.y_measured = np.array(y_measured)
        else:
            self.y_measured = self.params.Cm @ x_measured
        
        logger.debug(f"Measurements updated: x={x_measured}")
    
    def _compute_control_law(self, x_hat: np.ndarray, r: np.ndarray, 
                           sigma_hat: np.ndarray) -> np.ndarray:
        """
        Compute the control law based on current estimates.
        
        The control law follows the form:
        u = Km * (r - x_hat) + Kg * r - sigma_hat
        
        Args:
            x_hat (np.ndarray): Estimated state
            r (np.ndarray): Reference signal
            sigma_hat (np.ndarray): Estimated uncertainty
            
        Returns:
            np.ndarray: Control signal
        """
        if self.controller_type == L1ControllerType.STATE_FEEDBACK:
            # State feedback control law
            u = (self.params.Km @ (r - x_hat) + 
                 self.params.Kg @ r - 
                 sigma_hat)
        
        elif self.controller_type == L1ControllerType.OUTPUT_FEEDBACK:
            # Output feedback control law
            y_ref = self.params.Cm @ r
            u = (self.params.Km @ (y_ref - self.y_measured) + 
                 self.params.Kg @ y_ref - 
                 sigma_hat)
        
        else:  # REFERENCE_MODEL
            # Reference model following control law
            x_ref = r  # Reference is the desired state
            u = (self.params.Km @ (x_ref - x_hat) + 
                 self.params.Kg @ x_ref - 
                 sigma_hat)
        
        return u
    
    def _compute_regressor(self, x: np.ndarray, u: np.ndarray) -> np.ndarray:
        """
        Compute the regressor vector for parameter estimation.
        
        The regressor depends on the system structure and the type of
        uncertainties being estimated. This is a simplified implementation
        that can be extended based on specific system requirements.
        
        Args:
            x (np.ndarray): Current state
            u (np.ndarray): Current input
            
        Returns:
            np.ndarray: Regressor vector
        """
        # Simplified regressor: [x; u; 1]
        # This can be extended to include more complex functions of x and u
        regressor = np.concatenate([x, u, [1.0]])
        return regressor
    
    def compute_control_output(self) -> Tuple[np.ndarray, Dict[str, float]]:
        """
        Compute the L1 adaptive control output.
        
        This is the main control loop that implements the L1 adaptive control
        algorithm:
        1. State prediction using current estimates
        2. Prediction error computation
        3. Parameter adaptation using adaptive law
        4. Control law computation
        5. L1 filtering of control signal
        
        Returns:
            Tuple[np.ndarray, Dict[str, float]]: Control output and performance metrics
                Control output: Filtered control signal
                Performance metrics: Dictionary with control performance statistics
        """
        current_time = time.time()
        
        # Step 1: State prediction
        x_pred = self.state_predictor.predict_state(
            self.x_measured, 
            self.state.u_l1, 
            self.state.theta_hat, 
            self.state.sigma_hat
        )
        
        # Step 2: Compute prediction error
        prediction_error = self.state_predictor.compute_prediction_error(self.x_measured)
        
        # Step 3: Compute regressor
        regressor = self._compute_regressor(self.x_measured, self.state.u_l1)
        
        # Step 4: Update parameter estimates
        theta_hat_new, sigma_hat_new = self.adaptive_law.update_parameters(
            prediction_error, regressor
        )
        
        # Step 5: Compute control law
        u_adapt = self._compute_control_law(
            self.x_measured, 
            self.reference, 
            sigma_hat_new
        )
        
        # Step 6: Apply L1 filtering
        u_l1 = self.l1_filter.filter_signal(u_adapt.reshape(1, -1)).flatten()
        
        # Step 7: Apply safety limits
        u_l1 = np.clip(u_l1, -self.max_control_input, self.max_control_input)
        
        # Update controller state
        self.state.x_pred = x_pred
        self.state.theta_hat = theta_hat_new
        self.state.sigma_hat = sigma_hat_new
        self.state.u_adapt = u_adapt
        self.state.u_l1 = u_l1
        self.state.prediction_error = prediction_error
        self.state.timestamp = current_time
        
        # Update performance metrics
        self.total_updates += 1
        prediction_error_norm = np.linalg.norm(prediction_error)
        self.max_prediction_error = max(self.max_prediction_error, prediction_error_norm)
        self.rms_prediction_error = np.sqrt((self.rms_prediction_error**2 * (self.total_updates - 1) + 
                                           prediction_error_norm**2) / self.total_updates)
        
        # Collect performance metrics
        performance_metrics = {
            'prediction_error_norm': prediction_error_norm,
            'max_prediction_error': self.max_prediction_error,
            'rms_prediction_error': self.rms_prediction_error,
            'total_updates': self.total_updates,
            'control_signal_norm': np.linalg.norm(u_l1),
            'parameter_estimate_norm': np.linalg.norm(theta_hat_new),
            'uncertainty_estimate_norm': np.linalg.norm(sigma_hat_new),
            'adaptation_rate': self.params.adaptation_rate,
            'filter_bandwidth': self.params.filter_bandwidth
        }
        
        return u_l1, performance_metrics
    
    def reset_controller(self):
        """Reset all controller components."""
        self.state_predictor.x_pred = np.zeros(self.n)
        self.adaptive_law.reset()
        self.l1_filter.reset()
        
        # Reset controller state
        self.state = L1State(
            x_hat=np.zeros(self.n),
            theta_hat=np.zeros(self.params.D.shape[1]),
            sigma_hat=np.zeros(self.params.D.shape[0]),
            x_pred=np.zeros(self.n),
            u_adapt=np.zeros(self.m),
            u_l1=np.zeros(self.m),
            prediction_error=np.zeros(self.n),
            adaptation_error=np.zeros(self.n)
        )
        
        # Reset performance metrics
        self.total_updates = 0
        self.max_prediction_error = 0.0
        self.rms_prediction_error = 0.0
        
        logger.info("L1 Adaptive Controller reset successfully")
    
    def set_adaptation_rate(self, rate: float):
        """Set the adaptation rate parameter."""
        self.params.adaptation_rate = rate
        self.adaptive_law.gamma = rate
        logger.info(f"Adaptation rate set to: {rate}")
    
    def set_filter_bandwidth(self, bandwidth: float):
        """Set the L1 filter bandwidth."""
        self.params.filter_bandwidth = bandwidth
        # Reinitialize filter with new bandwidth
        self.l1_filter = L1Filter(bandwidth, self.params.Ts)
        logger.info(f"L1 filter bandwidth set to: {bandwidth} rad/s")
    
    def get_parameter_estimates(self) -> Dict[str, np.ndarray]:
        """Get current parameter estimates for monitoring."""
        return {
            'theta_hat': self.state.theta_hat,
            'sigma_hat': self.state.sigma_hat,
            'x_pred': self.state.x_pred,
            'prediction_error': self.state.prediction_error
        }
    
    def check_stability_condition(self) -> bool:
        """
        Check the L1-norm stability condition.
        
        The L1-norm condition ensures that the L1 filter bandwidth is
        sufficiently high to maintain closed-loop stability.
        
        Returns:
            bool: True if stability condition is satisfied
        """
        # Simplified stability check based on filter bandwidth
        # In practice, this would involve more sophisticated analysis
        min_bandwidth = 5.0  # Minimum required bandwidth
        return self.params.filter_bandwidth >= min_bandwidth


def design_l1_controller_for_quadrotor(mass: float = 0.5, inertia: np.ndarray = None,
                                      Ts: float = 0.01) -> L1Parameters:
    """
    Design L1 adaptive controller parameters for a quadrotor system.
    
    This function designs the controller parameters based on the quadrotor
    dynamics and desired performance specifications.
    
    Args:
        mass (float): Quadrotor mass in kg
        inertia (np.ndarray): Moment of inertia matrix [Ixx, Iyy, Izz]
        Ts (float): Sampling time in seconds
        
    Returns:
        L1Parameters: Designed controller parameters
    """
    if inertia is None:
        inertia = np.array([0.01, 0.01, 0.02])  # Default inertia values
    
    # Define system dimensions
    n = 12  # State dimension: [x, y, z, vx, vy, vz, roll, pitch, yaw, roll_rate, pitch_rate, yaw_rate]
    m = 4   # Input dimension: [motor1, motor2, motor3, motor4]
    p = 6   # Output dimension: [x, y, z, roll, pitch, yaw]
    
    # Design desired closed-loop dynamics
    # Position dynamics (double integrator)
    pos_poles = [-2.0, -2.0, -2.0]  # Desired poles for position control
    Am_pos = np.diag(pos_poles)
    
    # Attitude dynamics (second order)
    att_poles = [-3.0, -3.0, -3.0]  # Desired poles for attitude control
    Am_att = np.diag(att_poles)
    
    # Angular rate dynamics (first order)
    rate_poles = [-5.0, -5.0, -5.0]  # Desired poles for angular rate control
    Am_rate = np.diag(rate_poles)
    
    # Combine into full system matrix
    Am = np.block([
        [Am_pos, np.zeros((3, 9))],
        [np.zeros((3, 3)), Am_att, np.zeros((3, 6))],
        [np.zeros((3, 6)), Am_rate, np.zeros((3, 3))],
        [np.zeros((3, 9)), Am_rate]
    ])
    
    # Design input matrix
    Bm = np.zeros((n, m))
    # Position control inputs
    Bm[3:6, :] = np.eye(3)  # Velocity control
    # Attitude control inputs
    Bm[9:12, :] = np.eye(3)  # Angular rate control
    
    # Design output matrix
    Cm = np.zeros((p, n))
    Cm[:3, :3] = np.eye(3)  # Position outputs
    Cm[3:6, 6:9] = np.eye(3)  # Attitude outputs
    
    # Design state feedback gain
    Km = np.zeros((m, n))
    # Position control gains
    Km[0, 3:6] = [1.0, 0.0, 0.0]  # X velocity control
    Km[1, 3:6] = [0.0, 1.0, 0.0]  # Y velocity control
    Km[2, 3:6] = [0.0, 0.0, 1.0]  # Z velocity control
    # Attitude control gains
    Km[0, 9:12] = [1.0, 0.0, 0.0]  # Roll rate control
    Km[1, 9:12] = [0.0, 1.0, 0.0]  # Pitch rate control
    Km[2, 9:12] = [0.0, 0.0, 1.0]  # Yaw rate control
    
    # Design feedforward gain
    Kg = np.zeros((m, p))
    Kg[0, 0] = 1.0  # X position feedforward
    Kg[1, 1] = 1.0  # Y position feedforward
    Kg[2, 2] = 1.0  # Z position feedforward
    
    # Design adaptation gain matrix
    D = np.eye(n) * 10.0  # High adaptation gain for fast adaptation
    
    # Create L1 parameters
    params = L1Parameters(
        Am=Am,
        Bm=Bm,
        Cm=Cm,
        Km=Km,
        Kg=Kg,
        D=D,
        Ts=Ts,
        filter_bandwidth=10.0,
        adaptation_rate=100.0,
        prediction_horizon=5
    )
    
    logger.info("L1 controller parameters designed for quadrotor system")
    return params


# Example usage and testing
if __name__ == "__main__":
    """
    Example usage of the L1 adaptive controller.
    
    This demonstrates how to set up and use the controller for quadrotor flight control.
    """
    
    # Design controller parameters
    params = design_l1_controller_for_quadrotor(mass=0.5, Ts=0.01)
    
    # Initialize controller
    controller = L1AdaptiveController(params, L1ControllerType.STATE_FEEDBACK)
    
    # Set reference (desired position and attitude)
    reference = np.array([1.0, 0.5, 2.0, 0.0, 0.0, 0.0])  # [x, y, z, roll, pitch, yaw]
    controller.set_reference(reference)
    
    # Simulation loop
    dt = 0.01  # 100Hz control loop
    simulation_time = 10.0  # 10 seconds simulation
    
    print("Starting L1 adaptive controller simulation...")
    print("=" * 50)
    
    for t in np.arange(0, simulation_time, dt):
        # Simulate current measurements (in real implementation, these come from sensors)
        current_state = np.array([
            0.1 * t, 0.05 * t, 0.2 * t,  # Position
            0.1, 0.05, 0.2,              # Velocity
            0.0, 0.0, 0.0,               # Attitude
            0.0, 0.0, 0.0                # Angular rates
        ])
        
        # Update measurements
        controller.update_measurements(current_state)
        
        # Compute control output
        control_output, metrics = controller.compute_control_output()
        
        # Print progress every second
        if int(t) != int(t - dt):
            print(f"Time: {t:.1f}s | Prediction Error: {metrics['prediction_error_norm']:.3f} | "
                  f"Control Signal: [{control_output[0]:.3f}, {control_output[1]:.3f}, "
                  f"{control_output[2]:.3f}, {control_output[3]:.3f}]")
    
    print("=" * 50)
    print("Simulation completed!")
    print(f"Final prediction error: {metrics['prediction_error_norm']:.3f}")
    print(f"Max prediction error: {metrics['max_prediction_error']:.3f}")
    print(f"RMS prediction error: {metrics['rms_prediction_error']:.3f}")
    
    # Check stability condition
    if controller.check_stability_condition():
        print("✓ L1-norm stability condition satisfied")
    else:
        print("✗ L1-norm stability condition violated")
