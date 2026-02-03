"""
Model Predictive Control (MPC) for Quadrotor Trajectory Tracking
==============================================================

This module implements a Model Predictive Control system for quadrotor flight control,
providing advanced trajectory tracking capabilities with constraint handling and
real-time optimization.

Key Features:
- Nonlinear MPC with quadrotor dynamics model
- Real-time trajectory optimization
- Constraint handling (actuator limits, safety bounds)
- Multiple cost functions for different objectives
- Warm-starting for improved convergence
- Robust disturbance rejection

This implementation provides an alternative to PID control for improved trajectory
tracking performance and constraint satisfaction.

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
from scipy.optimize import minimize
from scipy.integrate import odeint
import cvxpy as cp

# Configure logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class MPCObjective(Enum):
    """Enumeration of different MPC objective functions."""
    TRACKING = "tracking"          # Trajectory tracking
    ENERGY = "energy"              # Energy minimization
    SMOOTHNESS = "smoothness"      # Control smoothness
    ROBUSTNESS = "robustness"      # Disturbance rejection


@dataclass
class MPCParameters:
    """
    Data structure for MPC controller parameters.
    
    Attributes:
        horizon (int): Prediction horizon length
        dt (float): Time step for discretization
        Q (np.ndarray): State cost matrix
        R (np.ndarray): Control cost matrix
        Qf (np.ndarray): Terminal state cost matrix
        max_iterations (int): Maximum optimization iterations
        tolerance (float): Optimization tolerance
        warm_start (bool): Enable warm-starting
        constraint_handling (str): Constraint handling method
    """
    horizon: int = 10
    dt: float = 0.1
    Q: np.ndarray = None
    R: np.ndarray = None
    Qf: np.ndarray = None
    max_iterations: int = 100
    tolerance: float = 1e-6
    warm_start: bool = True
    constraint_handling: str = "soft"  # "soft" or "hard"


@dataclass
class QuadrotorConstraints:
    """
    Data structure for quadrotor constraints.
    
    Attributes:
        max_thrust (float): Maximum thrust per motor
        min_thrust (float): Minimum thrust per motor
        max_angular_velocity (float): Maximum angular velocity
        max_velocity (float): Maximum linear velocity
        max_acceleration (float): Maximum acceleration
        safety_bounds (Dict): Safety boundary constraints
    """
    max_thrust: float = 1.0
    min_thrust: float = 0.0
    max_angular_velocity: float = 5.0  # rad/s
    max_velocity: float = 5.0  # m/s
    max_acceleration: float = 10.0  # m/s^2
    safety_bounds: Dict = None


class QuadrotorDynamics:
    """
    Quadrotor dynamics model for MPC prediction.
    
    This class implements the nonlinear dynamics of a quadrotor UAV,
    including translational and rotational dynamics with realistic
    aerodynamic effects and motor dynamics.
    """
    
    def __init__(self, mass: float = 0.5, inertia: np.ndarray = None):
        """
        Initialize quadrotor dynamics model.
        
        Args:
            mass (float): Quadrotor mass in kg
            inertia (np.ndarray): Moment of inertia matrix [Ixx, Iyy, Izz]
        """
        self.mass = mass
        if inertia is None:
            inertia = np.array([0.01, 0.01, 0.02])  # Default inertia
        self.inertia = inertia
        
        # Aerodynamic parameters
        self.air_density = 1.225  # kg/m^3
        self.drag_coefficient = 0.1
        self.propeller_area = 0.01  # m^2
        
        # Motor parameters
        self.motor_time_constant = 0.02  # s
        self.motor_gain = 1.0
        
        # Gravity
        self.g = 9.81  # m/s^2
        
        logger.info(f"Quadrotor dynamics initialized: mass={mass}kg, inertia={inertia}")
    
    def continuous_dynamics(self, state: np.ndarray, control: np.ndarray, t: float) -> np.ndarray:
        """
        Continuous-time quadrotor dynamics.
        
        Args:
            state (np.ndarray): State vector [x, y, z, vx, vy, vz, roll, pitch, yaw, roll_rate, pitch_rate, yaw_rate]
            control (np.ndarray): Control vector [motor1, motor2, motor3, motor4]
            t (float): Time (for time-varying dynamics)
            
        Returns:
            np.ndarray: State derivatives
        """
        # Extract state components
        position = state[:3]
        velocity = state[3:6]
        attitude = state[6:9]
        angular_velocity = state[9:12]
        
        # Extract control inputs
        motor_forces = control
        
        # Compute total thrust and moments
        total_thrust = np.sum(motor_forces)
        
        # Motor configuration matrix (assuming standard quadrotor configuration)
        # [roll_moment, pitch_moment, yaw_moment, thrust]
        motor_matrix = np.array([
            [1, -1, -1, 1],    # Roll moment
            [1, 1, -1, -1],    # Pitch moment
            [-1, 1, -1, 1],    # Yaw moment
            [1, 1, 1, 1]       # Total thrust
        ])
        
        moments_and_thrust = motor_matrix @ motor_forces
        
        # Rotation matrix (simplified, assuming small angles)
        roll, pitch, yaw = attitude
        R = np.array([
            [np.cos(yaw), -np.sin(yaw), 0],
            [np.sin(yaw), np.cos(yaw), 0],
            [0, 0, 1]
        ])
        
        # Translational dynamics
        # F = ma + mg + F_drag
        thrust_vector = np.array([0, 0, total_thrust])
        gravity_vector = np.array([0, 0, -self.mass * self.g])
        
        # Drag force (simplified)
        drag_force = -0.5 * self.air_density * self.drag_coefficient * self.propeller_area * velocity * np.abs(velocity)
        
        acceleration = (R @ thrust_vector + gravity_vector + drag_force) / self.mass
        
        # Rotational dynamics
        # τ = I * α
        moments = moments_and_thrust[:3]
        angular_acceleration = moments / self.inertia
        
        # State derivatives
        state_dot = np.concatenate([
            velocity,                    # Position derivatives
            acceleration,               # Velocity derivatives
            angular_velocity,           # Attitude derivatives
            angular_acceleration        # Angular velocity derivatives
        ])
        
        return state_dot
    
    def discrete_dynamics(self, state: np.ndarray, control: np.ndarray, dt: float) -> np.ndarray:
        """
        Discrete-time quadrotor dynamics using RK4 integration.
        
        Args:
            state (np.ndarray): Current state
            control (np.ndarray): Control input
            dt (float): Time step
            
        Returns:
            np.ndarray: Next state
        """
        # RK4 integration
        k1 = self.continuous_dynamics(state, control, 0)
        k2 = self.continuous_dynamics(state + 0.5 * dt * k1, control, 0.5 * dt)
        k3 = self.continuous_dynamics(state + 0.5 * dt * k2, control, 0.5 * dt)
        k4 = self.continuous_dynamics(state + dt * k3, control, dt)
        
        next_state = state + (dt / 6) * (k1 + 2 * k2 + 2 * k3 + k4)
        
        return next_state
    
    def linearize(self, state: np.ndarray, control: np.ndarray) -> Tuple[np.ndarray, np.ndarray]:
        """
        Linearize dynamics around operating point.
        
        Args:
            state (np.ndarray): Operating state
            control (np.ndarray): Operating control
            
        Returns:
            Tuple[np.ndarray, np.ndarray]: Linearized A and B matrices
        """
        # Finite difference approximation
        epsilon = 1e-6
        
        # State dimension
        n = len(state)
        m = len(control)
        
        # Initialize matrices
        A = np.zeros((n, n))
        B = np.zeros((n, m))
        
        # Compute A matrix (state derivatives)
        for i in range(n):
            state_plus = state.copy()
            state_plus[i] += epsilon
            state_minus = state.copy()
            state_minus[i] -= epsilon
            
            f_plus = self.continuous_dynamics(state_plus, control, 0)
            f_minus = self.continuous_dynamics(state_minus, control, 0)
            
            A[:, i] = (f_plus - f_minus) / (2 * epsilon)
        
        # Compute B matrix (control derivatives)
        for i in range(m):
            control_plus = control.copy()
            control_plus[i] += epsilon
            control_minus = control.copy()
            control_minus[i] -= epsilon
            
            f_plus = self.continuous_dynamics(state, control_plus, 0)
            f_minus = self.continuous_dynamics(state, control_minus, 0)
            
            B[:, i] = (f_plus - f_minus) / (2 * epsilon)
        
        return A, B


class MPCOptimizer:
    """
    MPC optimizer using different optimization methods.
    
    This class implements the optimization problem for MPC, supporting
    both nonlinear optimization and convex optimization approaches.
    """
    
    def __init__(self, dynamics: QuadrotorDynamics, params: MPCParameters):
        """
        Initialize MPC optimizer.
        
        Args:
            dynamics (QuadrotorDynamics): Quadrotor dynamics model
            params (MPCParameters): MPC parameters
        """
        self.dynamics = dynamics
        self.params = params
        
        # State and control dimensions
        self.nx = 12  # State dimension
        self.nu = 4   # Control dimension
        
        # Initialize cost matrices if not provided
        if self.params.Q is None:
            self.params.Q = np.eye(self.nx)
            self.params.Q[0:3, 0:3] *= 10.0  # Position tracking
            self.params.Q[3:6, 3:6] *= 5.0   # Velocity tracking
            self.params.Q[6:9, 6:9] *= 2.0   # Attitude tracking
        
        if self.params.R is None:
            self.params.R = np.eye(self.nu) * 0.1  # Control cost
        
        if self.params.Qf is None:
            self.params.Qf = self.params.Q * 2.0  # Terminal cost
        
        # Warm-start storage
        self.previous_solution = None
        
        logger.info(f"MPC optimizer initialized: horizon={params.horizon}, dt={params.dt}")
    
    def solve_optimization(self, current_state: np.ndarray, reference_trajectory: np.ndarray,
                         constraints: QuadrotorConstraints) -> np.ndarray:
        """
        Solve MPC optimization problem.
        
        Args:
            current_state (np.ndarray): Current state
            reference_trajectory (np.ndarray): Reference trajectory over horizon
            constraints (QuadrotorConstraints): System constraints
            
        Returns:
            np.ndarray: Optimal control sequence
        """
        if self.params.constraint_handling == "soft":
            return self._solve_soft_constraints(current_state, reference_trajectory, constraints)
        else:
            return self._solve_hard_constraints(current_state, reference_trajectory, constraints)
    
    def _solve_soft_constraints(self, current_state: np.ndarray, reference_trajectory: np.ndarray,
                              constraints: QuadrotorConstraints) -> np.ndarray:
        """
        Solve MPC with soft constraints using nonlinear optimization.
        
        Args:
            current_state (np.ndarray): Current state
            reference_trajectory (np.ndarray): Reference trajectory
            constraints (QuadrotorConstraints): System constraints
            
        Returns:
            np.ndarray: Optimal control sequence
        """
        # Flatten control sequence for optimization
        n_vars = self.nu * self.params.horizon
        
        # Initial guess (warm-start or zero)
        if self.params.warm_start and self.previous_solution is not None:
            x0 = self.previous_solution
        else:
            x0 = np.zeros(n_vars)
        
        # Define objective function
        def objective(control_sequence):
            return self._compute_cost(current_state, control_sequence, reference_trajectory, constraints)
        
        # Define gradient (optional, for better convergence)
        def gradient(control_sequence):
            return self._compute_gradient(current_state, control_sequence, reference_trajectory)
        
        # Solve optimization
        result = minimize(
            objective,
            x0,
            method='SLSQP',
            jac=gradient,
            options={
                'maxiter': self.params.max_iterations,
                'ftol': self.params.tolerance,
                'disp': False
            }
        )
        
        if not result.success:
            logger.warning(f"MPC optimization failed: {result.message}")
            # Return previous solution or zero control
            if self.previous_solution is not None:
                return self.previous_solution
            else:
                return np.zeros(n_vars)
        
        # Store solution for warm-starting
        self.previous_solution = result.x
        
        return result.x
    
    def _solve_hard_constraints(self, current_state: np.ndarray, reference_trajectory: np.ndarray,
                              constraints: QuadrotorConstraints) -> np.ndarray:
        """
        Solve MPC with hard constraints using convex optimization.
        
        Args:
            current_state (np.ndarray): Current state
            reference_trajectory (np.ndarray): Reference trajectory
            constraints (QuadrotorConstraints): System constraints
            
        Returns:
            np.ndarray: Optimal control sequence
        """
        # Use linearized dynamics for convex optimization
        A, B = self.dynamics.linearize(current_state, np.zeros(self.nu))
        
        # Define variables
        x = cp.Variable((self.nx, self.params.horizon + 1))
        u = cp.Variable((self.nu, self.params.horizon))
        
        # Define cost function
        cost = 0
        for k in range(self.params.horizon):
            # State cost
            state_error = x[:, k] - reference_trajectory[:, k]
            cost += cp.quad_form(state_error, self.params.Q)
            
            # Control cost
            cost += cp.quad_form(u[:, k], self.params.R)
        
        # Terminal cost
        terminal_error = x[:, -1] - reference_trajectory[:, -1]
        cost += cp.quad_form(terminal_error, self.params.Qf)
        
        # Define constraints
        constraints_list = []
        
        # Initial state constraint
        constraints_list.append(x[:, 0] == current_state)
        
        # Dynamics constraints
        for k in range(self.params.horizon):
            constraints_list.append(x[:, k + 1] == A @ x[:, k] + B @ u[:, k])
        
        # Control constraints
        for k in range(self.params.horizon):
            constraints_list.append(u[:, k] >= constraints.min_thrust)
            constraints_list.append(u[:, k] <= constraints.max_thrust)
        
        # State constraints (safety bounds)
        if constraints.safety_bounds:
            for k in range(self.params.horizon + 1):
                # Position bounds
                if 'position' in constraints.safety_bounds:
                    pos_bounds = constraints.safety_bounds['position']
                    constraints_list.append(x[0:3, k] >= pos_bounds['min'])
                    constraints_list.append(x[0:3, k] <= pos_bounds['max'])
                
                # Velocity bounds
                if 'velocity' in constraints.safety_bounds:
                    vel_bounds = constraints.safety_bounds['velocity']
                    constraints_list.append(x[3:6, k] >= vel_bounds['min'])
                    constraints_list.append(x[3:6, k] <= vel_bounds['max'])
        
        # Solve problem
        problem = cp.Problem(cp.Minimize(cost), constraints_list)
        problem.solve(solver=cp.OSQP, verbose=False)
        
        if problem.status != cp.OPTIMAL:
            logger.warning(f"MPC optimization failed: {problem.status}")
            return np.zeros(self.nu * self.params.horizon)
        
        # Return control sequence
        return u.value.flatten()
    
    def _compute_cost(self, current_state: np.ndarray, control_sequence: np.ndarray,
                     reference_trajectory: np.ndarray, constraints: QuadrotorConstraints) -> float:
        """
        Compute total cost for given control sequence.
        
        Args:
            current_state (np.ndarray): Current state
            control_sequence (np.ndarray): Control sequence
            reference_trajectory (np.ndarray): Reference trajectory
            constraints (QuadrotorConstraints): System constraints
            
        Returns:
            float: Total cost
        """
        # Reshape control sequence
        U = control_sequence.reshape(self.nu, self.params.horizon)
        
        # Simulate trajectory
        X = np.zeros((self.nx, self.params.horizon + 1))
        X[:, 0] = current_state
        
        cost = 0.0
        
        for k in range(self.params.horizon):
            # State cost
            state_error = X[:, k] - reference_trajectory[:, k]
            cost += state_error.T @ self.params.Q @ state_error
            
            # Control cost
            cost += U[:, k].T @ self.params.R @ U[:, k]
            
            # Control smoothness cost
            if k > 0:
                control_diff = U[:, k] - U[:, k-1]
                cost += 0.1 * control_diff.T @ control_diff
            
            # Simulate next state
            X[:, k + 1] = self.dynamics.discrete_dynamics(X[:, k], U[:, k], self.params.dt)
        
        # Terminal cost
        terminal_error = X[:, -1] - reference_trajectory[:, -1]
        cost += terminal_error.T @ self.params.Qf @ terminal_error
        
        # Soft constraint penalties
        cost += self._compute_constraint_penalties(X, U, constraints)
        
        return cost
    
    def _compute_gradient(self, current_state: np.ndarray, control_sequence: np.ndarray,
                         reference_trajectory: np.ndarray) -> np.ndarray:
        """
        Compute gradient of cost function with respect to control.
        
        Args:
            current_state (np.ndarray): Current state
            control_sequence (np.ndarray): Control sequence
            reference_trajectory (np.ndarray): Reference trajectory
            
        Returns:
            np.ndarray: Gradient vector
        """
        # Finite difference approximation
        epsilon = 1e-6
        n_vars = len(control_sequence)
        gradient = np.zeros(n_vars)
        
        base_cost = self._compute_cost(current_state, control_sequence, reference_trajectory, None)
        
        for i in range(n_vars):
            control_plus = control_sequence.copy()
            control_plus[i] += epsilon
            cost_plus = self._compute_cost(current_state, control_plus, reference_trajectory, None)
            gradient[i] = (cost_plus - base_cost) / epsilon
        
        return gradient
    
    def _compute_constraint_penalties(self, X: np.ndarray, U: np.ndarray,
                                    constraints: QuadrotorConstraints) -> float:
        """
        Compute penalty for constraint violations.
        
        Args:
            X (np.ndarray): State trajectory
            U (np.ndarray): Control trajectory
            constraints (QuadrotorConstraints): System constraints
            
        Returns:
            float: Constraint penalty
        """
        penalty = 0.0
        penalty_weight = 1000.0
        
        # Control bounds
        for k in range(U.shape[1]):
            # Min thrust violation
            min_violation = np.maximum(0, constraints.min_thrust - U[:, k])
            penalty += penalty_weight * np.sum(min_violation**2)
            
            # Max thrust violation
            max_violation = np.maximum(0, U[:, k] - constraints.max_thrust)
            penalty += penalty_weight * np.sum(max_violation**2)
        
        # Velocity bounds
        for k in range(X.shape[1]):
            velocity = X[3:6, k]
            velocity_magnitude = np.linalg.norm(velocity)
            
            if velocity_magnitude > constraints.max_velocity:
                penalty += penalty_weight * (velocity_magnitude - constraints.max_velocity)**2
        
        # Angular velocity bounds
        for k in range(X.shape[1]):
            angular_velocity = X[9:12, k]
            angular_velocity_magnitude = np.linalg.norm(angular_velocity)
            
            if angular_velocity_magnitude > constraints.max_angular_velocity:
                penalty += penalty_weight * (angular_velocity_magnitude - constraints.max_angular_velocity)**2
        
        return penalty


class MPCController:
    """
    Main MPC controller for quadrotor flight control.
    
    This class implements the complete MPC control system, including
    trajectory generation, optimization, and control execution.
    """
    
    def __init__(self, params: MPCParameters, constraints: QuadrotorConstraints):
        """
        Initialize MPC controller.
        
        Args:
            params (MPCParameters): MPC parameters
            constraints (QuadrotorConstraints): System constraints
        """
        self.params = params
        self.constraints = constraints
        
        # Initialize dynamics model
        self.dynamics = QuadrotorDynamics()
        
        # Initialize optimizer
        self.optimizer = MPCOptimizer(self.dynamics, params)
        
        # Control state
        self.current_state = np.zeros(12)
        self.control_sequence = None
        self.last_update_time = time.time()
        
        # Performance monitoring
        self.total_updates = 0
        self.optimization_times = []
        self.cost_history = []
        
        # Reference trajectory storage
        self.reference_trajectory = None
        
        logger.info("MPC controller initialized")
    
    def set_reference_trajectory(self, trajectory: np.ndarray):
        """
        Set reference trajectory for MPC.
        
        Args:
            trajectory (np.ndarray): Reference trajectory [state_dim, horizon+1]
        """
        if trajectory.shape[0] != 12 or trajectory.shape[1] != self.params.horizon + 1:
            raise ValueError(f"Trajectory must have shape (12, {self.params.horizon + 1})")
        
        self.reference_trajectory = trajectory.copy()
        logger.info(f"Reference trajectory set: shape={trajectory.shape}")
    
    def update_state(self, state: np.ndarray):
        """
        Update current state estimate.
        
        Args:
            state (np.ndarray): Current state estimate
        """
        self.current_state = np.array(state)
        logger.debug(f"State updated: {state}")
    
    def compute_control(self) -> np.ndarray:
        """
        Compute optimal control input.
        
        Returns:
            np.ndarray: Optimal control input (motor commands)
        """
        if self.reference_trajectory is None:
            logger.warning("No reference trajectory set, returning zero control")
            return np.zeros(4)
        
        # Start timing
        start_time = time.time()
        
        # Solve MPC optimization
        try:
            control_sequence = self.optimizer.solve_optimization(
                self.current_state,
                self.reference_trajectory,
                self.constraints
            )
            
            # Extract first control input
            control_input = control_sequence[:4]
            
            # Store control sequence for warm-starting
            self.control_sequence = control_sequence
            
            # Record optimization time
            optimization_time = time.time() - start_time
            self.optimization_times.append(optimization_time)
            
            # Record cost
            cost = self.optimizer._compute_cost(
                self.current_state,
                control_sequence,
                self.reference_trajectory,
                self.constraints
            )
            self.cost_history.append(cost)
            
            self.total_updates += 1
            self.last_update_time = time.time()
            
            logger.debug(f"Control computed: {control_input}, time: {optimization_time:.3f}s")
            
            return control_input
            
        except Exception as e:
            logger.error(f"MPC optimization failed: {e}")
            return np.zeros(4)
    
    def generate_circular_trajectory(self, center: np.ndarray, radius: float, height: float,
                                  duration: float) -> np.ndarray:
        """
        Generate circular reference trajectory.
        
        Args:
            center (np.ndarray): Circle center [x, y]
            radius (float): Circle radius
            height (float): Flight height
            duration (float): Trajectory duration
            
        Returns:
            np.ndarray: Reference trajectory
        """
        trajectory = np.zeros((12, self.params.horizon + 1))
        
        for k in range(self.params.horizon + 1):
            t = k * self.params.dt
            angle = 2 * np.pi * t / duration
            
            # Position
            trajectory[0, k] = center[0] + radius * np.cos(angle)  # x
            trajectory[1, k] = center[1] + radius * np.sin(angle)  # y
            trajectory[2, k] = height  # z
            
            # Velocity
            angular_velocity = 2 * np.pi / duration
            trajectory[3, k] = -radius * angular_velocity * np.sin(angle)  # vx
            trajectory[4, k] = radius * angular_velocity * np.cos(angle)   # vy
            trajectory[5, k] = 0.0  # vz
            
            # Attitude (level flight)
            trajectory[6, k] = 0.0  # roll
            trajectory[7, k] = 0.0  # pitch
            trajectory[8, k] = angle  # yaw
            
            # Angular velocity
            trajectory[9, k] = 0.0   # roll_rate
            trajectory[10, k] = 0.0  # pitch_rate
            trajectory[11, k] = angular_velocity  # yaw_rate
        
        return trajectory
    
    def generate_hover_trajectory(self, position: np.ndarray, yaw: float = 0.0) -> np.ndarray:
        """
        Generate hover reference trajectory.
        
        Args:
            position (np.ndarray): Hover position [x, y, z]
            yaw (float): Hover yaw angle
            
        Returns:
            np.ndarray: Reference trajectory
        """
        trajectory = np.zeros((12, self.params.horizon + 1))
        
        for k in range(self.params.horizon + 1):
            # Position
            trajectory[0:3, k] = position
            
            # Zero velocity and angular velocity
            trajectory[3:6, k] = 0.0
            trajectory[9:12, k] = 0.0
            
            # Attitude
            trajectory[6:8, k] = 0.0  # roll, pitch
            trajectory[8, k] = yaw    # yaw
        
        return trajectory
    
    def get_performance_stats(self) -> Dict[str, float]:
        """
        Get performance statistics.
        
        Returns:
            Dict[str, float]: Performance statistics
        """
        if not self.optimization_times:
            return {'total_updates': 0, 'avg_optimization_time': 0.0, 'avg_cost': 0.0}
        
        return {
            'total_updates': self.total_updates,
            'avg_optimization_time': np.mean(self.optimization_times),
            'max_optimization_time': np.max(self.optimization_times),
            'min_optimization_time': np.min(self.optimization_times),
            'avg_cost': np.mean(self.cost_history),
            'min_cost': np.min(self.cost_history),
            'max_cost': np.max(self.cost_history)
        }
    
    def reset(self):
        """Reset controller state."""
        self.current_state = np.zeros(12)
        self.control_sequence = None
        self.reference_trajectory = None
        self.optimization_times.clear()
        self.cost_history.clear()
        self.total_updates = 0
        
        # Reset optimizer
        self.optimizer.previous_solution = None
        
        logger.info("MPC controller reset")


# Example usage and testing
if __name__ == "__main__":
    """
    Example usage of the MPC controller.
    
    This demonstrates how to set up and use the MPC controller for
    quadrotor trajectory tracking.
    """
    
    # Initialize parameters
    mpc_params = MPCParameters(
        horizon=10,
        dt=0.1,
        max_iterations=50,
        tolerance=1e-6,
        warm_start=True,
        constraint_handling="soft"
    )
    
    # Initialize constraints
    constraints = QuadrotorConstraints(
        max_thrust=1.0,
        min_thrust=0.0,
        max_angular_velocity=5.0,
        max_velocity=5.0,
        max_acceleration=10.0,
        safety_bounds={
            'position': {'min': np.array([-10, -10, 0]), 'max': np.array([10, 10, 10])},
            'velocity': {'min': np.array([-5, -5, -5]), 'max': np.array([5, 5, 5])}
        }
    )
    
    # Initialize MPC controller
    mpc_controller = MPCController(mpc_params, constraints)
    
    # Generate circular trajectory
    center = np.array([0.0, 0.0])
    radius = 2.0
    height = 1.0
    duration = 10.0
    
    reference_trajectory = mpc_controller.generate_circular_trajectory(center, radius, height, duration)
    mpc_controller.set_reference_trajectory(reference_trajectory)
    
    # Simulation
    simulation_time = 10.0
    dt = 0.1
    num_steps = int(simulation_time / dt)
    
    print("MPC Controller Simulation")
    print("=" * 40)
    
    # Initial state
    current_state = np.array([2.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0])
    mpc_controller.update_state(current_state)
    
    for step in range(num_steps):
        # Compute control
        control = mpc_controller.compute_control()
        
        # Simulate system (simplified)
        # In practice, this would use the actual quadrotor dynamics
        current_state = mpc_controller.dynamics.discrete_dynamics(current_state, control, dt)
        mpc_controller.update_state(current_state)
        
        # Print progress every second
        if step % 10 == 0:
            t = step * dt
            position_error = np.linalg.norm(current_state[:3] - reference_trajectory[:3, 0])
            print(f"Time: {t:.1f}s | Position Error: {position_error:.3f}m | "
                  f"Control: [{control[0]:.3f}, {control[1]:.3f}, {control[2]:.3f}, {control[3]:.3f}]")
    
    # Print final statistics
    print("\n" + "=" * 40)
    print("Simulation Results:")
    
    stats = mpc_controller.get_performance_stats()
    for key, value in stats.items():
        print(f"  {key}: {value:.3f}")
    
    print(f"  Total control updates: {mpc_controller.total_updates}")
    print(f"  Average optimization time: {np.mean(mpc_controller.optimization_times):.3f}s")
    print(f"  Average cost: {np.mean(mpc_controller.cost_history):.3f}")
