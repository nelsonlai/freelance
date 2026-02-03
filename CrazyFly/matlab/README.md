# MATLAB Scripts for CrazyFly Quadrotor Control System

This directory contains MATLAB scripts and Simulink models for the CrazyFly quadrotor control system. These scripts provide comprehensive simulation, analysis, and optimization capabilities for quadrotor control algorithms.

## Overview

The MATLAB components include:
- **Simulink Models**: Complete control system models for different control strategies
- **Parameter Optimization**: Advanced optimization algorithms for controller tuning
- **Performance Analysis**: Comprehensive analysis tools for control system evaluation
- **Dynamics Simulation**: Detailed quadrotor dynamics models

## Files Description

### Simulink Model Generators

#### `four_layer_pid.m`
- **Purpose**: Generates a 4-layer PID control system Simulink model
- **Features**:
  - Position, velocity, attitude, and attitude-rate control layers
  - Anti-windup and output saturation
  - Derivative filtering and smooth takeoff
  - Anti-drift compensation
- **Output**: `four_layer_pid.slx`
- **Usage**: Run the script to create and open the Simulink model

#### `l1_adaptive_model.m`
- **Purpose**: Generates an L1 adaptive control system Simulink model
- **Features**:
  - State predictor with adaptive law
  - L1 filter for robust performance
  - Control law implementation
  - Plant model integration
- **Output**: `l1_adaptive_model.slx`
- **Usage**: Run the script to create and open the Simulink model

#### `hybrid_controller.m`
- **Purpose**: Generates a hybrid control system Simulink model
- **Features**:
  - Integration of PID, L1 Adaptive, and MPC controllers
  - Intelligent switching logic
  - Performance evaluation subsystem
  - Multi-controller comparison
- **Output**: `hybrid_controller.slx`
- **Usage**: Run the script to create and open the Simulink model

#### `quadrotor_dynamics.m`
- **Purpose**: Generates a comprehensive quadrotor dynamics Simulink model
- **Features**:
  - 6-DOF rigid body dynamics
  - Motor dynamics and thrust generation
  - Aerodynamic effects (drag, ground effect)
  - Environmental forces and sensor models
- **Output**: `quadrotor_dynamics.slx`
- **Usage**: Run the script to create and open the Simulink model

### Analysis and Optimization Tools

#### `parameter_optimizer.m`
- **Purpose**: Advanced parameter optimization for control systems
- **Features**:
  - Multiple optimization algorithms (Genetic, Particle Swarm, Bayesian, Gradient Descent)
  - Multi-objective optimization
  - Parameter bounds and constraints
  - Performance visualization and reporting
- **Usage**:
  ```matlab
  optimizer = ParameterOptimizer();
  optimizer.set_controller_type('pid');
  optimizer.set_optimization_algorithm('genetic');
  optimizer.optimize_parameters();
  optimizer.plot_optimization_results();
  ```

#### `performance_analyzer.m`
- **Purpose**: Comprehensive performance analysis of control systems
- **Features**:
  - Time-domain analysis (RMSE, settling time, overshoot)
  - Frequency response analysis
  - Stability analysis (Lyapunov, BIBO, asymptotic)
  - Robustness evaluation
  - Performance reporting and visualization
- **Usage**:
  ```matlab
  analyzer = PerformanceAnalyzer();
  analyzer.load_controller_data(data);
  analyzer.load_reference_data(reference);
  analyzer.analyze_performance();
  analyzer.plot_performance_analysis();
  ```

## Installation and Setup

### Prerequisites
- MATLAB R2018b or later
- Simulink
- Control System Toolbox
- Optimization Toolbox (for parameter optimization)
- Signal Processing Toolbox (for frequency analysis)

### Installation Steps
1. Ensure all prerequisites are installed
2. Add the MATLAB directory to your MATLAB path:
   ```matlab
   addpath('path/to/CrazyFly/matlab');
   ```
3. Run the demo scripts to verify installation:
   ```matlab
   demo_parameter_optimizer();
   demo_performance_analyzer();
   ```

## Usage Examples

### Creating a 4-Layer PID Controller Model
```matlab
% Generate the Simulink model
four_layer_pid;

% The model will be created and opened automatically
% You can then modify parameters and run simulations
```

### Optimizing PID Parameters
```matlab
% Create optimizer instance
optimizer = ParameterOptimizer();

% Configure for PID optimization
optimizer.set_controller_type('pid');
optimizer.set_optimization_algorithm('genetic');
optimizer.set_objective_function('multi_objective');

% Run optimization
optimizer.optimize_parameters();

% View results
optimizer.plot_optimization_results();
optimizer.export_optimization_results('pid_optimization.mat');
```

### Analyzing Control System Performance
```matlab
% Create analyzer instance
analyzer = PerformanceAnalyzer();

% Load simulation data
analyzer.load_controller_data('simulation_results.mat');
analyzer.load_reference_data('reference_trajectory.mat');

% Run comprehensive analysis
analyzer.set_analysis_type('comprehensive');
analyzer.analyze_performance();

% Generate plots and reports
analyzer.plot_performance_analysis();
analyzer.export_analysis_results();
```

### Creating a Hybrid Control System
```matlab
% Generate hybrid controller model
hybrid_controller;

% The model includes PID, L1 Adaptive, and MPC controllers
% with intelligent switching logic
```

## Model Features

### Control System Models
- **Four-Layer PID**: Complete cascaded control structure
- **L1 Adaptive**: Robust adaptive control implementation
- **MPC**: Model predictive control with constraints
- **Hybrid**: Intelligent switching between controllers

### Analysis Capabilities
- **Time-Domain**: Tracking error, settling time, overshoot analysis
- **Frequency-Domain**: Bode plots, bandwidth, phase margin
- **Stability**: Lyapunov, BIBO, and asymptotic stability
- **Robustness**: Parameter variations, disturbance rejection

### Optimization Features
- **Multiple Algorithms**: Genetic, Particle Swarm, Bayesian, Gradient Descent
- **Multi-Objective**: Trade-off between performance and energy
- **Constraints**: Parameter bounds and physical limitations
- **Visualization**: Convergence plots and parameter evolution

## Output Files

### Generated Simulink Models
- `four_layer_pid.slx`: 4-layer PID control system
- `l1_adaptive_model.slx`: L1 adaptive control system
- `hybrid_controller.slx`: Hybrid control system
- `quadrotor_dynamics.slx`: Complete quadrotor dynamics

### Analysis Results
- `performance_analysis/`: Directory containing analysis results
- `optimization_results.mat`: Parameter optimization results
- `analysis_results.mat`: Performance analysis results
- `comprehensive_performance_report.txt`: Detailed analysis report

### Plots and Visualizations
- Performance analysis plots (PNG format)
- Optimization convergence plots
- Frequency response plots
- Time-domain response plots

## Troubleshooting

### Common Issues

1. **Simulink Model Not Opening**
   - Ensure Simulink is installed and licensed
   - Check MATLAB version compatibility
   - Verify file permissions

2. **Optimization Not Converging**
   - Adjust population size and iteration limits
   - Check parameter bounds for feasibility
   - Try different optimization algorithms

3. **Analysis Errors**
   - Verify data format and dimensions
   - Check for NaN or Inf values in data
   - Ensure reference and response data are aligned

### Performance Tips

1. **For Large Simulations**
   - Use parallel computing for optimization
   - Reduce simulation time for initial testing
   - Use simplified models for quick iterations

2. **For Parameter Optimization**
   - Start with smaller population sizes
   - Use appropriate parameter bounds
   - Monitor convergence plots

3. **For Performance Analysis**
   - Use appropriate sampling rates
   - Filter noisy data before analysis
   - Consider multiple performance metrics

## Contributing

When adding new MATLAB scripts:

1. Follow the existing naming conventions
2. Include comprehensive documentation
3. Add demo functions for testing
4. Ensure compatibility with different MATLAB versions
5. Include error handling and validation

## License

This MATLAB code is part of the CrazyFly project and is licensed under the MIT License.

## Support

For issues and questions:
1. Check the troubleshooting section
2. Review the demo scripts for examples
3. Consult the main project documentation
4. Report bugs through the project repository

---

**Note**: These MATLAB scripts are designed to work with the Python components of the CrazyFly system. For complete system integration, refer to the main project documentation.
