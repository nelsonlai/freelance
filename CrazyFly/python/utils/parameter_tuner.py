"""
Parameter Tuner for Quadrotor Control System
===========================================

This module provides a comprehensive parameter tuning interface for real-time
adjustment of control parameters with visualization and optimization capabilities.

Key Features:
- Real-time parameter adjustment with immediate feedback
- Parameter optimization using various algorithms
- Parameter validation and safety limits
- Parameter history tracking and analysis
- Export/import of parameter configurations
- Integration with control systems and estimators

The parameter tuner enables fine-tuning of control algorithms during
development and testing phases.

Author: [Your Name]
Date: [Current Date]
License: MIT
"""

import numpy as np
import time
import json
import threading
from typing import Dict, List, Tuple, Optional, Callable, Any, Union
from dataclasses import dataclass
from enum import Enum
import logging
from queue import Queue
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import tkinter as tk
from tkinter import ttk, messagebox, filedialog
import pickle

# Configure logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class ParameterType(Enum):
    """Enumeration of parameter types."""
    PID_GAIN = "pid_gain"
    L1_PARAMETER = "l1_parameter"
    MPC_PARAMETER = "mpc_parameter"
    ESTIMATION_PARAMETER = "estimation_parameter"
    SENSOR_PARAMETER = "sensor_parameter"
    SYSTEM_PARAMETER = "system_parameter"


class OptimizationAlgorithm(Enum):
    """Enumeration of optimization algorithms."""
    GRADIENT_DESCENT = "gradient_descent"
    GENETIC_ALGORITHM = "genetic_algorithm"
    PARTICLE_SWARM = "particle_swarm"
    BAYESIAN_OPTIMIZATION = "bayesian_optimization"
    RANDOM_SEARCH = "random_search"


@dataclass
class ParameterDefinition:
    """
    Definition of a tunable parameter.
    
    Attributes:
        name (str): Parameter name
        parameter_type (ParameterType): Type of parameter
        value (float): Current parameter value
        min_value (float): Minimum allowed value
        max_value (float): Maximum allowed value
        default_value (float): Default parameter value
        step_size (float): Step size for adjustment
        description (str): Parameter description
        unit (str): Parameter unit
        category (str): Parameter category
    """
    name: str
    parameter_type: ParameterType
    value: float
    min_value: float
    max_value: float
    default_value: float
    step_size: float
    description: str = ""
    unit: str = ""
    category: str = ""


@dataclass
class ParameterSet:
    """
    Collection of related parameters.
    
    Attributes:
        name (str): Parameter set name
        parameters (Dict[str, ParameterDefinition]): Dictionary of parameters
        description (str): Parameter set description
        timestamp (float): Creation timestamp
    """
    name: str
    parameters: Dict[str, ParameterDefinition]
    description: str = ""
    timestamp: float = 0.0


class ParameterValidator:
    """
    Parameter validation and safety checking.
    
    This class provides validation functions to ensure parameter values
    are within safe bounds and don't cause system instability.
    """
    
    def __init__(self):
        """Initialize parameter validator."""
        self.validation_rules = {}
        self.safety_limits = {}
        
        # Define default validation rules
        self._setup_default_rules()
        
        logger.info("Parameter validator initialized")
    
    def _setup_default_rules(self):
        """Setup default validation rules."""
        # PID gains
        self.validation_rules['pid_gain'] = {
            'kp': {'min': 0.0, 'max': 100.0, 'type': 'positive'},
            'ki': {'min': 0.0, 'max': 50.0, 'type': 'positive'},
            'kd': {'min': 0.0, 'max': 20.0, 'type': 'positive'}
        }
        
        # L1 parameters
        self.validation_rules['l1_parameter'] = {
            'gamma': {'min': 0.1, 'max': 1000.0, 'type': 'positive'},
            'omega': {'min': 0.1, 'max': 100.0, 'type': 'positive'},
            'tau': {'min': 0.001, 'max': 1.0, 'type': 'positive'}
        }
        
        # MPC parameters
        self.validation_rules['mpc_parameter'] = {
            'horizon': {'min': 1, 'max': 50, 'type': 'integer'},
            'dt': {'min': 0.001, 'max': 1.0, 'type': 'positive'},
            'Q_weight': {'min': 0.0, 'max': 1000.0, 'type': 'positive'},
            'R_weight': {'min': 0.0, 'max': 1000.0, 'type': 'positive'}
        }
        
        # Estimation parameters
        self.validation_rules['estimation_parameter'] = {
            'process_noise': {'min': 0.0, 'max': 10.0, 'type': 'positive'},
            'measurement_noise': {'min': 0.0, 'max': 10.0, 'type': 'positive'},
            'num_particles': {'min': 10, 'max': 10000, 'type': 'integer'}
        }
    
    def validate_parameter(self, parameter: ParameterDefinition) -> Tuple[bool, str]:
        """
        Validate a parameter value.
        
        Args:
            parameter (ParameterDefinition): Parameter to validate
            
        Returns:
            Tuple[bool, str]: (is_valid, error_message)
        """
        # Check basic bounds
        if parameter.value < parameter.min_value:
            return False, f"Value {parameter.value} below minimum {parameter.min_value}"
        
        if parameter.value > parameter.max_value:
            return False, f"Value {parameter.value} above maximum {parameter.max_value}"
        
        # Check type-specific rules
        if parameter.parameter_type.value in self.validation_rules:
            rules = self.validation_rules[parameter.parameter_type.value]
            
            # Extract parameter name (remove category prefix if present)
            param_name = parameter.name.split('.')[-1] if '.' in parameter.name else parameter.name
            
            if param_name in rules:
                rule = rules[param_name]
                
                # Check type-specific validation
                if rule['type'] == 'positive' and parameter.value <= 0:
                    return False, f"Parameter {param_name} must be positive"
                
                elif rule['type'] == 'integer' and not isinstance(parameter.value, (int, np.integer)):
                    return False, f"Parameter {param_name} must be integer"
        
        return True, ""
    
    def validate_parameter_set(self, parameter_set: ParameterSet) -> Dict[str, Tuple[bool, str]]:
        """
        Validate all parameters in a parameter set.
        
        Args:
            parameter_set (ParameterSet): Parameter set to validate
            
        Returns:
            Dict[str, Tuple[bool, str]]: Validation results for each parameter
        """
        results = {}
        
        for param_name, parameter in parameter_set.parameters.items():
            is_valid, error_msg = self.validate_parameter(parameter)
            results[param_name] = (is_valid, error_msg)
        
        return results
    
    def check_stability(self, parameter_set: ParameterSet) -> Tuple[bool, str]:
        """
        Check if parameter set maintains system stability.
        
        Args:
            parameter_set (ParameterSet): Parameter set to check
            
        Returns:
            Tuple[bool, str]: (is_stable, warning_message)
        """
        warnings = []
        
        # Check PID stability conditions
        pid_params = {name: param for name, param in parameter_set.parameters.items() 
                     if param.parameter_type == ParameterType.PID_GAIN}
        
        for param_name, param in pid_params.items():
            if 'kp' in param_name.lower() and param.value > 50:
                warnings.append(f"High proportional gain {param_name}={param.value} may cause oscillations")
            
            if 'ki' in param_name.lower() and param.value > 20:
                warnings.append(f"High integral gain {param_name}={param.value} may cause overshoot")
            
            if 'kd' in param_name.lower() and param.value > 10:
                warnings.append(f"High derivative gain {param_name}={param.value} may amplify noise")
        
        # Check L1 stability conditions
        l1_params = {name: param for name, param in parameter_set.parameters.items() 
                    if param.parameter_type == ParameterType.L1_PARAMETER}
        
        for param_name, param in l1_params.items():
            if 'gamma' in param_name.lower() and param.value > 500:
                warnings.append(f"High adaptation rate {param_name}={param.value} may cause instability")
        
        is_stable = len(warnings) == 0
        warning_msg = "; ".join(warnings) if warnings else "System appears stable"
        
        return is_stable, warning_msg


class ParameterOptimizer:
    """
    Parameter optimization using various algorithms.
    
    This class provides optimization capabilities for automatically tuning
    parameters based on performance metrics.
    """
    
    def __init__(self, algorithm: OptimizationAlgorithm = OptimizationAlgorithm.GRADIENT_DESCENT):
        """
        Initialize parameter optimizer.
        
        Args:
            algorithm (OptimizationAlgorithm): Optimization algorithm to use
        """
        self.algorithm = algorithm
        self.optimization_history = []
        self.current_iteration = 0
        self.max_iterations = 100
        self.convergence_threshold = 1e-6
        
        logger.info(f"Parameter optimizer initialized: {algorithm.value}")
    
    def optimize_parameters(self, parameter_set: ParameterSet, 
                          objective_function: Callable[[ParameterSet], float],
                          constraints: Optional[List[Callable]] = None) -> ParameterSet:
        """
        Optimize parameters using the selected algorithm.
        
        Args:
            parameter_set (ParameterSet): Initial parameter set
            objective_function (Callable): Function to minimize
            constraints (Optional[List[Callable]]): Constraint functions
            
        Returns:
            ParameterSet: Optimized parameter set
        """
        if self.algorithm == OptimizationAlgorithm.GRADIENT_DESCENT:
            return self._gradient_descent_optimization(parameter_set, objective_function, constraints)
        elif self.algorithm == OptimizationAlgorithm.GENETIC_ALGORITHM:
            return self._genetic_algorithm_optimization(parameter_set, objective_function, constraints)
        elif self.algorithm == OptimizationAlgorithm.PARTICLE_SWARM:
            return self._particle_swarm_optimization(parameter_set, objective_function, constraints)
        elif self.algorithm == OptimizationAlgorithm.RANDOM_SEARCH:
            return self._random_search_optimization(parameter_set, objective_function, constraints)
        else:
            raise ValueError(f"Unsupported optimization algorithm: {self.algorithm}")
    
    def _gradient_descent_optimization(self, parameter_set: ParameterSet,
                                     objective_function: Callable[[ParameterSet], float],
                                     constraints: Optional[List[Callable]] = None) -> ParameterSet:
        """
        Gradient descent optimization.
        
        Args:
            parameter_set (ParameterSet): Initial parameter set
            objective_function (Callable): Function to minimize
            constraints (Optional[List[Callable]]): Constraint functions
            
        Returns:
            ParameterSet: Optimized parameter set
        """
        current_set = parameter_set
        learning_rate = 0.01
        
        for iteration in range(self.max_iterations):
            # Compute gradient
            gradient = self._compute_gradient(current_set, objective_function)
            
            # Update parameters
            new_set = self._update_parameters(current_set, gradient, learning_rate)
            
            # Apply constraints
            if constraints:
                for constraint in constraints:
                    new_set = constraint(new_set)
            
            # Check convergence
            current_value = objective_function(current_set)
            new_value = objective_function(new_set)
            
            if abs(new_value - current_value) < self.convergence_threshold:
                logger.info(f"Gradient descent converged after {iteration} iterations")
                break
            
            current_set = new_set
            self.optimization_history.append((iteration, new_value))
        
        return current_set
    
    def _compute_gradient(self, parameter_set: ParameterSet,
                         objective_function: Callable[[ParameterSet], float]) -> Dict[str, float]:
        """
        Compute gradient of objective function with respect to parameters.
        
        Args:
            parameter_set (ParameterSet): Current parameter set
            objective_function (Callable): Objective function
            
        Returns:
            Dict[str, float]: Gradient for each parameter
        """
        gradient = {}
        epsilon = 1e-6
        
        for param_name, parameter in parameter_set.parameters.items():
            # Compute finite difference
            original_value = parameter.value
            
            # Forward difference
            parameter.value = original_value + epsilon
            forward_value = objective_function(parameter_set)
            
            # Backward difference
            parameter.value = original_value - epsilon
            backward_value = objective_function(parameter_set)
            
            # Restore original value
            parameter.value = original_value
            
            # Compute gradient
            gradient[param_name] = (forward_value - backward_value) / (2 * epsilon)
        
        return gradient
    
    def _update_parameters(self, parameter_set: ParameterSet, 
                          gradient: Dict[str, float], learning_rate: float) -> ParameterSet:
        """
        Update parameters using gradient descent.
        
        Args:
            parameter_set (ParameterSet): Current parameter set
            gradient (Dict[str, float]): Gradient for each parameter
            learning_rate (float): Learning rate
            
        Returns:
            ParameterSet: Updated parameter set
        """
        new_parameters = {}
        
        for param_name, parameter in parameter_set.parameters.items():
            if param_name in gradient:
                # Update parameter value
                new_value = parameter.value - learning_rate * gradient[param_name]
                
                # Ensure bounds
                new_value = max(parameter.min_value, min(parameter.max_value, new_value))
                
                # Create new parameter definition
                new_param = ParameterDefinition(
                    name=parameter.name,
                    parameter_type=parameter.parameter_type,
                    value=new_value,
                    min_value=parameter.min_value,
                    max_value=parameter.max_value,
                    default_value=parameter.default_value,
                    step_size=parameter.step_size,
                    description=parameter.description,
                    unit=parameter.unit,
                    category=parameter.category
                )
                
                new_parameters[param_name] = new_param
        
        return ParameterSet(
            name=parameter_set.name,
            parameters=new_parameters,
            description=parameter_set.description,
            timestamp=time.time()
        )
    
    def _genetic_algorithm_optimization(self, parameter_set: ParameterSet,
                                      objective_function: Callable[[ParameterSet], float],
                                      constraints: Optional[List[Callable]] = None) -> ParameterSet:
        """
        Genetic algorithm optimization.
        
        Args:
            parameter_set (ParameterSet): Initial parameter set
            objective_function (Callable): Function to minimize
            constraints (Optional[List[Callable]]): Constraint functions
            
        Returns:
            ParameterSet: Optimized parameter set
        """
        # Simplified genetic algorithm implementation
        population_size = 20
        generations = 50
        mutation_rate = 0.1
        
        # Initialize population
        population = [self._create_random_parameter_set(parameter_set) for _ in range(population_size)]
        
        best_set = parameter_set
        best_fitness = objective_function(parameter_set)
        
        for generation in range(generations):
            # Evaluate fitness
            fitness_scores = []
            for individual in population:
                fitness = objective_function(individual)
                fitness_scores.append(fitness)
                
                if fitness < best_fitness:
                    best_fitness = fitness
                    best_set = individual
            
            # Selection and crossover
            new_population = []
            for _ in range(population_size):
                parent1 = self._tournament_selection(population, fitness_scores)
                parent2 = self._tournament_selection(population, fitness_scores)
                child = self._crossover(parent1, parent2)
                
                # Mutation
                if np.random.random() < mutation_rate:
                    child = self._mutate(child)
                
                new_population.append(child)
            
            population = new_population
            self.optimization_history.append((generation, best_fitness))
        
        return best_set
    
    def _create_random_parameter_set(self, template_set: ParameterSet) -> ParameterSet:
        """Create a random parameter set based on template."""
        random_parameters = {}
        
        for param_name, parameter in template_set.parameters.items():
            random_value = np.random.uniform(parameter.min_value, parameter.max_value)
            
            random_param = ParameterDefinition(
                name=parameter.name,
                parameter_type=parameter.parameter_type,
                value=random_value,
                min_value=parameter.min_value,
                max_value=parameter.max_value,
                default_value=parameter.default_value,
                step_size=parameter.step_size,
                description=parameter.description,
                unit=parameter.unit,
                category=parameter.category
            )
            
            random_parameters[param_name] = random_param
        
        return ParameterSet(
            name=template_set.name,
            parameters=random_parameters,
            description=template_set.description,
            timestamp=time.time()
        )
    
    def _tournament_selection(self, population: List[ParameterSet], 
                            fitness_scores: List[float]) -> ParameterSet:
        """Tournament selection for genetic algorithm."""
        tournament_size = 3
        tournament_indices = np.random.choice(len(population), tournament_size, replace=False)
        tournament_fitness = [fitness_scores[i] for i in tournament_indices]
        
        winner_index = tournament_indices[np.argmin(tournament_fitness)]
        return population[winner_index]
    
    def _crossover(self, parent1: ParameterSet, parent2: ParameterSet) -> ParameterSet:
        """Crossover operation for genetic algorithm."""
        crossover_rate = 0.5
        child_parameters = {}
        
        for param_name in parent1.parameters.keys():
            if np.random.random() < crossover_rate:
                child_parameters[param_name] = parent1.parameters[param_name]
            else:
                child_parameters[param_name] = parent2.parameters[param_name]
        
        return ParameterSet(
            name=parent1.name,
            parameters=child_parameters,
            description=parent1.description,
            timestamp=time.time()
        )
    
    def _mutate(self, parameter_set: ParameterSet) -> ParameterSet:
        """Mutation operation for genetic algorithm."""
        mutation_strength = 0.1
        mutated_parameters = {}
        
        for param_name, parameter in parameter_set.parameters.items():
            # Add random noise
            noise = np.random.normal(0, mutation_strength * (parameter.max_value - parameter.min_value))
            new_value = parameter.value + noise
            
            # Ensure bounds
            new_value = max(parameter.min_value, min(parameter.max_value, new_value))
            
            mutated_param = ParameterDefinition(
                name=parameter.name,
                parameter_type=parameter.parameter_type,
                value=new_value,
                min_value=parameter.min_value,
                max_value=parameter.max_value,
                default_value=parameter.default_value,
                step_size=parameter.step_size,
                description=parameter.description,
                unit=parameter.unit,
                category=parameter.category
            )
            
            mutated_parameters[param_name] = mutated_param
        
        return ParameterSet(
            name=parameter_set.name,
            parameters=mutated_parameters,
            description=parameter_set.description,
            timestamp=time.time()
        )
    
    def _particle_swarm_optimization(self, parameter_set: ParameterSet,
                                   objective_function: Callable[[ParameterSet], float],
                                   constraints: Optional[List[Callable]] = None) -> ParameterSet:
        """
        Particle swarm optimization.
        
        Args:
            parameter_set (ParameterSet): Initial parameter set
            objective_function (Callable): Function to minimize
            constraints (Optional[List[Callable]]): Constraint functions
            
        Returns:
            ParameterSet: Optimized parameter set
        """
        # Simplified PSO implementation
        num_particles = 20
        max_iterations = 50
        
        # Initialize particles
        particles = [self._create_random_parameter_set(parameter_set) for _ in range(num_particles)]
        velocities = [np.zeros(len(parameter_set.parameters)) for _ in range(num_particles)]
        
        # Initialize best positions
        personal_best = particles.copy()
        personal_best_fitness = [objective_function(p) for p in particles]
        
        global_best = personal_best[np.argmin(personal_best_fitness)]
        global_best_fitness = min(personal_best_fitness)
        
        # PSO parameters
        w = 0.7  # inertia weight
        c1 = 1.5  # cognitive coefficient
        c2 = 1.5  # social coefficient
        
        for iteration in range(max_iterations):
            for i, particle in enumerate(particles):
                # Update velocity
                for j, param_name in enumerate(particle.parameters.keys()):
                    r1, r2 = np.random.random(2)
                    
                    cognitive_velocity = c1 * r1 * (personal_best[i].parameters[param_name].value - 
                                                   particle.parameters[param_name].value)
                    social_velocity = c2 * r2 * (global_best.parameters[param_name].value - 
                                              particle.parameters[param_name].value)
                    
                    velocities[i][j] = w * velocities[i][j] + cognitive_velocity + social_velocity
                
                # Update position
                for j, param_name in enumerate(particle.parameters.keys()):
                    new_value = particle.parameters[param_name].value + velocities[i][j]
                    
                    # Ensure bounds
                    param = particle.parameters[param_name]
                    new_value = max(param.min_value, min(param.max_value, new_value))
                    
                    particle.parameters[param_name].value = new_value
                
                # Evaluate fitness
                fitness = objective_function(particle)
                
                # Update personal best
                if fitness < personal_best_fitness[i]:
                    personal_best[i] = particle
                    personal_best_fitness[i] = fitness
                
                # Update global best
                if fitness < global_best_fitness:
                    global_best = particle
                    global_best_fitness = fitness
            
            self.optimization_history.append((iteration, global_best_fitness))
        
        return global_best
    
    def _random_search_optimization(self, parameter_set: ParameterSet,
                                  objective_function: Callable[[ParameterSet], float],
                                  constraints: Optional[List[Callable]] = None) -> ParameterSet:
        """
        Random search optimization.
        
        Args:
            parameter_set (ParameterSet): Initial parameter set
            objective_function (Callable): Function to minimize
            constraints (Optional[List[Callable]]): Constraint functions
            
        Returns:
            ParameterSet: Optimized parameter set
        """
        best_set = parameter_set
        best_fitness = objective_function(parameter_set)
        
        for iteration in range(self.max_iterations):
            # Generate random parameter set
            random_set = self._create_random_parameter_set(parameter_set)
            
            # Apply constraints
            if constraints:
                for constraint in constraints:
                    random_set = constraint(random_set)
            
            # Evaluate fitness
            fitness = objective_function(random_set)
            
            # Update best if better
            if fitness < best_fitness:
                best_set = random_set
                best_fitness = fitness
            
            self.optimization_history.append((iteration, best_fitness))
        
        return best_set
    
    def get_optimization_history(self) -> List[Tuple[int, float]]:
        """
        Get optimization history.
        
        Returns:
            List[Tuple[int, float]]: List of (iteration, objective_value) pairs
        """
        return self.optimization_history.copy()
    
    def plot_optimization_progress(self):
        """Plot optimization progress."""
        if not self.optimization_history:
            logger.warning("No optimization history to plot")
            return
        
        iterations, values = zip(*self.optimization_history)
        
        plt.figure(figsize=(10, 6))
        plt.plot(iterations, values, 'b-', linewidth=2)
        plt.xlabel('Iteration')
        plt.ylabel('Objective Value')
        plt.title(f'Optimization Progress - {self.algorithm.value}')
        plt.grid(True)
        plt.show()


class ParameterTunerGUI:
    """
    Graphical user interface for parameter tuning.
    
    This class provides a comprehensive GUI for real-time parameter
    adjustment with visualization and optimization capabilities.
    """
    
    def __init__(self, parameter_set: ParameterSet):
        """
        Initialize parameter tuner GUI.
        
        Args:
            parameter_set (ParameterSet): Initial parameter set
        """
        self.parameter_set = parameter_set
        self.parameter_history = []
        self.optimizer = ParameterOptimizer()
        self.validator = ParameterValidator()
        
        # GUI components
        self.root = None
        self.parameter_widgets = {}
        self.history_plot = None
        self.optimization_plot = None
        
        # Callbacks
        self.parameter_change_callbacks = []
        self.optimization_callbacks = []
        
        logger.info("Parameter tuner GUI initialized")
    
    def show(self):
        """Show the parameter tuner GUI."""
        self.root = tk.Tk()
        self.root.title("Parameter Tuner - Quadrotor Control System")
        self.root.geometry("1200x800")
        
        # Create main frame
        main_frame = ttk.Frame(self.root, padding="10")
        main_frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
        
        # Configure grid weights
        self.root.columnconfigure(0, weight=1)
        self.root.rowconfigure(0, weight=1)
        main_frame.columnconfigure(1, weight=1)
        main_frame.rowconfigure(0, weight=1)
        
        # Create parameter panel
        self._create_parameter_panel(main_frame)
        
        # Create visualization panel
        self._create_visualization_panel(main_frame)
        
        # Create control panel
        self._create_control_panel(main_frame)
        
        # Start GUI
        self.root.mainloop()
    
    def _create_parameter_panel(self, parent):
        """Create parameter adjustment panel."""
        # Parameter frame
        param_frame = ttk.LabelFrame(parent, text="Parameters", padding="5")
        param_frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S), padx=(0, 10))
        
        # Create parameter widgets
        row = 0
        for param_name, parameter in self.parameter_set.parameters.items():
            # Parameter label
            label = ttk.Label(param_frame, text=f"{param_name}:")
            label.grid(row=row, column=0, sticky=tk.W, pady=2)
            
            # Parameter value entry
            value_var = tk.DoubleVar(value=parameter.value)
            value_entry = ttk.Entry(param_frame, textvariable=value_var, width=10)
            value_entry.grid(row=row, column=1, padx=5, pady=2)
            
            # Parameter slider
            slider = ttk.Scale(param_frame, from_=parameter.min_value, to=parameter.max_value,
                             orient=tk.HORIZONTAL, variable=value_var, length=200)
            slider.grid(row=row, column=2, padx=5, pady=2)
            
            # Unit label
            if parameter.unit:
                unit_label = ttk.Label(param_frame, text=parameter.unit)
                unit_label.grid(row=row, column=3, padx=5, pady=2)
            
            # Store widgets
            self.parameter_widgets[param_name] = {
                'value_var': value_var,
                'entry': value_entry,
                'slider': slider
            }
            
            # Bind change event
            value_var.trace('w', lambda *args, name=param_name: self._on_parameter_change(name))
            
            row += 1
        
        # Configure grid weights
        param_frame.columnconfigure(2, weight=1)
    
    def _create_visualization_panel(self, parent):
        """Create visualization panel."""
        # Visualization frame
        viz_frame = ttk.LabelFrame(parent, text="Visualization", padding="5")
        viz_frame.grid(row=0, column=1, sticky=(tk.W, tk.E, tk.N, tk.S))
        
        # Create matplotlib figure
        fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(8, 6))
        
        # Parameter history plot
        self.history_plot = ax1
        self.history_plot.set_title("Parameter History")
        self.history_plot.set_xlabel("Time")
        self.history_plot.set_ylabel("Parameter Value")
        self.history_plot.grid(True)
        
        # Optimization progress plot
        self.optimization_plot = ax2
        self.optimization_plot.set_title("Optimization Progress")
        self.optimization_plot.set_xlabel("Iteration")
        self.optimization_plot.set_ylabel("Objective Value")
        self.optimization_plot.grid(True)
        
        # Embed matplotlib figure in tkinter
        from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
        canvas = FigureCanvasTkAgg(fig, viz_frame)
        canvas.draw()
        canvas.get_tk_widget().pack(fill=tk.BOTH, expand=True)
    
    def _create_control_panel(self, parent):
        """Create control panel."""
        # Control frame
        control_frame = ttk.LabelFrame(parent, text="Controls", padding="5")
        control_frame.grid(row=1, column=0, columnspan=2, sticky=(tk.W, tk.E), pady=(10, 0))
        
        # Buttons
        ttk.Button(control_frame, text="Reset to Defaults", 
                  command=self._reset_to_defaults).grid(row=0, column=0, padx=5, pady=5)
        
        ttk.Button(control_frame, text="Validate Parameters", 
                  command=self._validate_parameters).grid(row=0, column=1, padx=5, pady=5)
        
        ttk.Button(control_frame, text="Start Optimization", 
                  command=self._start_optimization).grid(row=0, column=2, padx=5, pady=5)
        
        ttk.Button(control_frame, text="Save Parameters", 
                  command=self._save_parameters).grid(row=0, column=3, padx=5, pady=5)
        
        ttk.Button(control_frame, text="Load Parameters", 
                  command=self._load_parameters).grid(row=0, column=4, padx=5, pady=5)
        
        # Status label
        self.status_label = ttk.Label(control_frame, text="Ready")
        self.status_label.grid(row=1, column=0, columnspan=5, pady=5)
    
    def _on_parameter_change(self, param_name: str):
        """Handle parameter change event."""
        # Update parameter value
        value_var = self.parameter_widgets[param_name]['value_var']
        self.parameter_set.parameters[param_name].value = value_var.get()
        
        # Add to history
        self.parameter_history.append({
            'timestamp': time.time(),
            'parameter': param_name,
            'value': value_var.get()
        })
        
        # Update visualization
        self._update_visualization()
        
        # Call callbacks
        for callback in self.parameter_change_callbacks:
            try:
                callback(param_name, value_var.get())
            except Exception as e:
                logger.error(f"Error in parameter change callback: {e}")
    
    def _update_visualization(self):
        """Update visualization plots."""
        if not self.parameter_history:
            return
        
        # Update parameter history plot
        self.history_plot.clear()
        
        # Plot last 100 history entries
        recent_history = self.parameter_history[-100:]
        timestamps = [entry['timestamp'] for entry in recent_history]
        values = [entry['value'] for entry in recent_history]
        
        self.history_plot.plot(timestamps, values, 'b-', linewidth=2)
        self.history_plot.set_title("Parameter History")
        self.history_plot.set_xlabel("Time")
        self.history_plot.set_ylabel("Parameter Value")
        self.history_plot.grid(True)
        
        # Update optimization plot if available
        if self.optimizer.optimization_history:
            self.optimization_plot.clear()
            iterations, values = zip(*self.optimizer.optimization_history)
            self.optimization_plot.plot(iterations, values, 'r-', linewidth=2)
            self.optimization_plot.set_title("Optimization Progress")
            self.optimization_plot.set_xlabel("Iteration")
            self.optimization_plot.set_ylabel("Objective Value")
            self.optimization_plot.grid(True)
        
        # Redraw
        self.history_plot.figure.canvas.draw()
    
    def _reset_to_defaults(self):
        """Reset parameters to default values."""
        for param_name, parameter in self.parameter_set.parameters.items():
            parameter.value = parameter.default_value
            self.parameter_widgets[param_name]['value_var'].set(parameter.default_value)
        
        self.status_label.config(text="Parameters reset to defaults")
    
    def _validate_parameters(self):
        """Validate current parameters."""
        is_valid, error_msg = self.validator.validate_parameter_set(self.parameter_set)
        is_stable, warning_msg = self.validator.check_stability(self.parameter_set)
        
        if is_valid and is_stable:
            self.status_label.config(text="Parameters are valid and stable")
        else:
            message = f"Validation failed: {error_msg}; Stability: {warning_msg}"
            self.status_label.config(text=message)
            messagebox.showwarning("Parameter Validation", message)
    
    def _start_optimization(self):
        """Start parameter optimization."""
        # Simple objective function (minimize sum of parameter values)
        def objective_function(param_set):
            return sum(param.value for param in param_set.parameters.values())
        
        # Run optimization in separate thread
        def optimize():
            try:
                self.status_label.config(text="Optimizing parameters...")
                
                optimized_set = self.optimizer.optimize_parameters(
                    self.parameter_set, objective_function
                )
                
                # Update GUI with optimized parameters
                for param_name, parameter in optimized_set.parameters.items():
                    self.parameter_set.parameters[param_name].value = parameter.value
                    self.parameter_widgets[param_name]['value_var'].set(parameter.value)
                
                self.status_label.config(text="Optimization completed")
                self._update_visualization()
                
            except Exception as e:
                self.status_label.config(text=f"Optimization failed: {e}")
                logger.error(f"Optimization error: {e}")
        
        import threading
        optimization_thread = threading.Thread(target=optimize)
        optimization_thread.daemon = True
        optimization_thread.start()
    
    def _save_parameters(self):
        """Save parameters to file."""
        filename = filedialog.asksaveasfilename(
            defaultextension=".json",
            filetypes=[("JSON files", "*.json"), ("All files", "*.*")]
        )
        
        if filename:
            try:
                # Convert parameter set to dictionary
                data = {
                    'name': self.parameter_set.name,
                    'description': self.parameter_set.description,
                    'timestamp': self.parameter_set.timestamp,
                    'parameters': {}
                }
                
                for param_name, parameter in self.parameter_set.parameters.items():
                    data['parameters'][param_name] = {
                        'name': parameter.name,
                        'parameter_type': parameter.parameter_type.value,
                        'value': parameter.value,
                        'min_value': parameter.min_value,
                        'max_value': parameter.max_value,
                        'default_value': parameter.default_value,
                        'step_size': parameter.step_size,
                        'description': parameter.description,
                        'unit': parameter.unit,
                        'category': parameter.category
                    }
                
                with open(filename, 'w') as f:
                    json.dump(data, f, indent=2)
                
                self.status_label.config(text=f"Parameters saved to {filename}")
                
            except Exception as e:
                self.status_label.config(text=f"Save failed: {e}")
                logger.error(f"Save error: {e}")
    
    def _load_parameters(self):
        """Load parameters from file."""
        filename = filedialog.askopenfilename(
            filetypes=[("JSON files", "*.json"), ("All files", "*.*")]
        )
        
        if filename:
            try:
                with open(filename, 'r') as f:
                    data = json.load(f)
                
                # Update parameter set
                self.parameter_set.name = data['name']
                self.parameter_set.description = data['description']
                self.parameter_set.timestamp = data['timestamp']
                
                for param_name, param_data in data['parameters'].items():
                    if param_name in self.parameter_set.parameters:
                        parameter = self.parameter_set.parameters[param_name]
                        parameter.value = param_data['value']
                        self.parameter_widgets[param_name]['value_var'].set(param_data['value'])
                
                self.status_label.config(text=f"Parameters loaded from {filename}")
                
            except Exception as e:
                self.status_label.config(text=f"Load failed: {e}")
                logger.error(f"Load error: {e}")
    
    def add_parameter_change_callback(self, callback: Callable):
        """
        Add callback for parameter changes.
        
        Args:
            callback (Callable): Function to call when parameter changes
        """
        self.parameter_change_callbacks.append(callback)
    
    def add_optimization_callback(self, callback: Callable):
        """
        Add callback for optimization events.
        
        Args:
            callback (Callable): Function to call during optimization
        """
        self.optimization_callbacks.append(callback)


# Example usage and testing
if __name__ == "__main__":
    """
    Example usage of the parameter tuner.
    
    This demonstrates how to set up and use the parameter tuner for
    real-time parameter adjustment and optimization.
    """
    
    # Create example parameter set
    parameters = {
        'pid_position.kp': ParameterDefinition(
            name='pid_position.kp',
            parameter_type=ParameterType.PID_GAIN,
            value=2.0,
            min_value=0.0,
            max_value=10.0,
            default_value=2.0,
            step_size=0.1,
            description="Position PID proportional gain",
            unit="",
            category="PID"
        ),
        'pid_position.ki': ParameterDefinition(
            name='pid_position.ki',
            parameter_type=ParameterType.PID_GAIN,
            value=0.1,
            min_value=0.0,
            max_value=5.0,
            default_value=0.1,
            step_size=0.01,
            description="Position PID integral gain",
            unit="",
            category="PID"
        ),
        'pid_position.kd': ParameterDefinition(
            name='pid_position.kd',
            parameter_type=ParameterType.PID_GAIN,
            value=0.5,
            min_value=0.0,
            max_value=2.0,
            default_value=0.5,
            step_size=0.05,
            description="Position PID derivative gain",
            unit="",
            category="PID"
        ),
        'l1_adaptive.gamma': ParameterDefinition(
            name='l1_adaptive.gamma',
            parameter_type=ParameterType.L1_PARAMETER,
            value=100.0,
            min_value=1.0,
            max_value=1000.0,
            default_value=100.0,
            step_size=10.0,
            description="L1 adaptive adaptation rate",
            unit="",
            category="L1"
        )
    }
    
    parameter_set = ParameterSet(
        name="Quadrotor Control Parameters",
        parameters=parameters,
        description="Example parameter set for quadrotor control",
        timestamp=time.time()
    )
    
    # Create parameter tuner GUI
    tuner = ParameterTunerGUI(parameter_set)
    
    # Add callbacks
    def parameter_change_callback(param_name, value):
        """Callback for parameter changes."""
        print(f"Parameter {param_name} changed to {value}")
    
    tuner.add_parameter_change_callback(parameter_change_callback)
    
    # Show GUI
    print("Starting Parameter Tuner GUI...")
    tuner.show()
