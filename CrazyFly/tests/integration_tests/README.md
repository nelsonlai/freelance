# Integration Tests

This directory contains integration tests for the CrazyFly quadrotor control system.

## Test Structure

- `test_hardware_integration/` - Tests for hardware interfaces
- `test_control_integration/` - Tests for control system integration
- `test_communication/` - Tests for communication protocols

## Running Tests

```bash
# Run all integration tests
python -m pytest tests/integration_tests/

# Run hardware integration tests
python -m pytest tests/integration_tests/test_hardware_integration/
```

## Test Coverage

- Hardware interface integration (Vicon + Crazyflie)
- Control system pipeline (sensor → estimator → controller → actuator)
- Communication protocols (UDP, serial, wireless)
- Multi-component system behavior
