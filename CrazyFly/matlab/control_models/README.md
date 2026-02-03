# Control Models

This directory contains Simulink control system models for the CrazyFly quadrotor.

## Models

- `four_layer_pid.slx` - 4-layer PID control system
- `l1_adaptive_model.slx` - L1 adaptive control model
- `hybrid_controller.slx` - Hybrid control system

## Usage

```matlab
% Open a model
open_system('four_layer_pid.slx');

% Run simulation
sim('four_layer_pid.slx');
```

## Features

- Complete control system implementations
- Real-time simulation capabilities
- Performance analysis tools
- Parameter tuning interfaces
