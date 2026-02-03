# L1 Adaptive Control Model Generator

## Problem Fixed

The original issue was that the file `four_layer_pid_l1_adapter.slx` was actually a MATLAB script (`.m` file) but had a `.slx` extension, which caused MATLAB to try to open it as a Simulink model file, resulting in the error:

```
'four_layer_pid_l1_adapter.slx' is not a valid Simulink model file: Could not open source package
```

## Solution

1. **Renamed the file**: `four_layer_pid_l1_adapter.slx` → `four_layer_pid_l1_adapter.m`
2. **Created a runner script**: `run_l1_adapter.m` to easily generate the Simulink model
3. **Fixed model naming**: The script now generates a proper `.slx` file

## How to Use

### Method 1: Ultra-Simple Script (Recommended)

1. Open MATLAB R2025a
2. Navigate to the `matlab/control_models/` directory
3. Run the ultra-simple script:
   ```matlab
   simple_l1_model
   ```

### Method 2: Full-Featured Script

1. Open MATLAB R2025a
2. Navigate to the `matlab/control_models/` directory
3. Run the full script:
   ```matlab
   generate_l1_model
   ```

### Method 3: Using the Runner Script

1. Open MATLAB R2025a
2. Navigate to the `matlab/control_models/` directory
3. Run the script:
   ```matlab
   run_l1_adapter
   ```

### Method 4: Direct Execution

1. Open MATLAB R2025a
2. Navigate to the `matlab/control_models/` directory
3. Run the main script:
   ```matlab
   four_layer_pid_l1_adapter
   ```

### Method 5: Function Call

1. Open MATLAB R2025a
2. Navigate to the `matlab/control_models/` directory
3. Call the function directly:
   ```matlab
   create_four_layer_pid_model()
   ```

## What Happens

1. The script generates a new Simulink model called `four_layer_pid_l1_adapter.slx`
2. The model includes both PID and L1 adaptive control systems
3. You can switch between control modes using the `Control_Mode` constant
4. The model opens automatically in Simulink

## Model Features

- **Hybrid Control**: Both PID and L1 adaptive control
- **4 Control Layers**: Position, Velocity, Attitude, Attitude Rate
- **Real-time Switching**: Switch between control methods during simulation
- **Monitoring**: Scopes to monitor L1 adaptation behavior
- **Parameter Tuning**: Easy parameter adjustment

## Control Mode Selection

- **Control_Mode = 1**: PID Control (default)
- **Control_Mode = 0**: L1 Adaptive Control

## Simulation

After the model is generated:

```matlab
% Run simulation
sim('four_layer_pid_l1_adapter');

% Or open the model first
open_system('four_layer_pid_l1_adapter');
% Then click the "Run" button in Simulink
```

## Troubleshooting

If you encounter any issues:

1. **Clear workspace**: `clear all; close all; clc;`
2. **Check MATLAB path**: Make sure you're in the correct directory
3. **Check Simulink**: Ensure Simulink is properly installed
4. **Run the runner script**: Use `run_l1_adapter` for error handling

## Files Created

- `four_layer_pid_l1_adapter.m` - Main model generator script
- `run_l1_adapter.m` - Easy-to-use runner script
- `four_layer_pid_l1_adapter.slx` - Generated Simulink model (after running the script)
- `L1_ADAPTIVE_INTEGRATION.md` - Detailed documentation

## Next Steps

1. Run the model generator
2. Explore the Simulink model
3. Try switching between PID and L1 adaptive control
4. Monitor the adaptation behavior
5. Tune parameters for your specific application
