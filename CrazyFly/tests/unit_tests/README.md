# Unit Tests

This directory contains unit tests for the CrazyFly quadrotor control system.

## Test Structure

- `test_control_systems/` - Tests for control algorithms
- `test_interfaces/` - Tests for hardware interfaces
- `test_utils/` - Tests for utility functions

## Running Tests

```bash
# Run all unit tests
python -m pytest tests/unit_tests/

# Run specific test category
python -m pytest tests/unit_tests/test_control_systems/
```

## Test Coverage

- Control system algorithms (PID, L1 Adaptive, MPC)
- Hardware interfaces (Vicon, Crazyflie)
- Utility functions (data logging, configuration)
- Performance monitoring
