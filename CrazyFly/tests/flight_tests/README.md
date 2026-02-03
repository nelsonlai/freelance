# Flight Tests

This directory contains flight validation tests for the CrazyFly quadrotor control system.

## Test Structure

- `test_hover/` - Hover stability tests
- `test_trajectory/` - Trajectory tracking tests
- `test_disturbance/` - Disturbance rejection tests
- `test_safety/` - Safety system tests

## Running Tests

```bash
# Run all flight tests (requires hardware)
python -m pytest tests/flight_tests/

# Run specific flight test
python -m pytest tests/flight_tests/test_hover/
```

## Test Coverage

- Hover stability and accuracy
- Trajectory tracking performance
- Disturbance rejection capabilities
- Safety system functionality
- Emergency procedures
