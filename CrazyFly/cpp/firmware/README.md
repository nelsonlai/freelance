# Firmware Components

This directory contains custom firmware components for the CrazyFly quadrotor control system.

## Components

- `pwm_controller.cpp` - PWM motor control implementation
- `safety_system.cpp` - Safety and emergency systems
- `sensor_interface.cpp` - Sensor interface implementation

## Building Firmware

```bash
cd cpp/firmware
make clean
make
```

## Features

- Real-time motor control
- Safety monitoring and emergency procedures
- Sensor data acquisition and processing
- Communication protocol implementation
