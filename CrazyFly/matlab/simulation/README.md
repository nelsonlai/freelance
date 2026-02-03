# Simulation Environment

This directory contains simulation models for the CrazyFly quadrotor system.

## Models

- `quadrotor_dynamics.slx` - Quadrotor dynamics simulation
- `vicon_simulation.slx` - Vicon motion capture simulation
- `environment_model.slx` - Environmental factors simulation

## Usage

```matlab
% Open simulation model
open_system('quadrotor_dynamics.slx');

% Run simulation with parameters
sim('quadrotor_dynamics.slx', 'StopTime', '10');
```

## Features

- Realistic quadrotor dynamics
- Motion capture system simulation
- Environmental disturbance modeling
- Hardware-in-the-loop testing
