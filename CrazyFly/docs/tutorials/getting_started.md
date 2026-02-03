# Getting Started with CrazyFly

## Overview

This tutorial will guide you through setting up and using the CrazyFly quadrotor control system. By the end of this tutorial, you'll have a working system that can control a quadrotor using various control algorithms.

## Prerequisites

### Hardware Requirements

- **Crazyflie 2.1** quadrotor
- **Crazyradio PA** for communication
- **Vicon Motion Capture System** (optional, for position feedback)
- **Computer** with Python 3.8+ support

### Software Requirements

- Python 3.8 or higher
- Required Python packages (see `requirements.txt`)
- Git for version control

## Installation

### 1. Clone the Repository

```bash
git clone https://github.com/your-username/CrazyFly.git
cd CrazyFly
```

### 2. Install Python Dependencies

```bash
pip install -r requirements.txt
```

### 3. Install Additional Dependencies

#### For GUI Support
```bash
pip install PyQt5 matplotlib
```

#### For Performance Monitoring
```bash
pip install psutil
```

#### For Data Logging
```bash
pip install h5py
```

### 4. Verify Installation

```bash
python -c "import python; print('CrazyFly installed successfully!')"
```

## Basic Setup

### 1. Hardware Connection

#### Connect Crazyflie
1. Insert the Crazyradio PA into your computer
2. Turn on the Crazyflie 2.1
3. Verify the connection:
```python
from python.interfaces import CrazyflieInterface

crazyflie = CrazyflieInterface("radio://0/80/2M/E7E7E7E7E7")
if crazyflie.connect():
    print("Connected to Crazyflie!")
else:
    print("Failed to connect to Crazyflie")
```

#### Connect Vicon (Optional)
```python
from python.interfaces import ViconInterface

vicon = ViconInterface("192.168.1.100", 801)
if vicon.connect():
    print("Connected to Vicon!")
else:
    print("Failed to connect to Vicon")
```

### 2. Configuration Setup

Create a basic configuration:

```python
from python.utils import ConfigurationManager, ConfigSection, ConfigFormat

# Create configuration manager
config_manager = ConfigurationManager("config")
config_manager.set_config_format(ConfigFormat.JSON)

# Set basic control parameters
config_manager.set_config(ConfigSection.CONTROL, "control_mode", "PID")
config_manager.set_config(ConfigSection.CONTROL, "position_kp", 2.0)
config_manager.set_config(ConfigSection.CONTROL, "position_ki", 0.1)
config_manager.set_config(ConfigSection.CONTROL, "position_kd", 1.0)

# Set communication parameters
config_manager.set_config(ConfigSection.COMMUNICATION, "crazyflie_enabled", True)
config_manager.set_config(ConfigSection.COMMUNICATION, "crazyflie_address", "radio://0/80/2M/E7E7E7E7E7")

# Save configuration
config_manager.save_config(ConfigSection.CONTROL)
config_manager.save_config(ConfigSection.COMMUNICATION)
```

## Your First Flight

### 1. Basic PID Control

Create a simple PID controller:

```python
import numpy as np
import time
from python.control_systems import FourLayerPIDController
from python.interfaces import CrazyflieInterface
from python.utils import DataLogger

# Initialize components
pid_controller = FourLayerPIDController()
crazyflie = CrazyflieInterface("radio://0/80/2M/E7E7E7E7E7")
logger = DataLogger()

# Connect to hardware
if not crazyflie.connect():
    print("Failed to connect to Crazyflie")
    exit(1)

# Start logging
logger.start()

# Set PID gains
pid_controller.set_gains("position", {"kp": 2.0, "ki": 0.1, "kd": 1.0})
pid_controller.set_gains("velocity", {"kp": 1.5, "ki": 0.05, "kd": 0.8})
pid_controller.set_gains("attitude", {"kp": 3.0, "ki": 0.2, "kd": 1.5})

# Control loop
try:
    print("Starting control loop...")
    
    # Takeoff
    crazyflie.takeoff(0.5)
    time.sleep(3)  # Wait for takeoff
    
    # Simple hover control
    reference_position = np.array([0.0, 0.0, 0.5])  # Hover at 0.5m height
    
    for i in range(100):  # 10 seconds at 10Hz
        # Get current state (simplified - in practice, get from sensors)
        current_position = np.array([0.0, 0.0, 0.5])  # Assume current position
        current_velocity = np.array([0.0, 0.0, 0.0])  # Assume current velocity
        current_attitude = np.array([0.0, 0.0, 0.0])  # Assume current attitude
        
        current_state = np.concatenate([current_position, current_velocity, current_attitude])
        
        # Calculate control commands
        control_commands = pid_controller.update(reference_position, current_state, 0.1)
        
        # Send commands to Crazyflie
        crazyflie.send_control_commands(control_commands)
        
        # Log data
        logger.log_position(current_position)
        logger.log_attitude(current_attitude)
        
        time.sleep(0.1)  # 10Hz control loop
    
    # Land
    crazyflie.land()
    
except KeyboardInterrupt:
    print("Emergency stop!")
    crazyflie.emergency_stop()

finally:
    # Cleanup
    logger.stop()
    crazyflie.disconnect()
    print("Flight completed!")
```

### 2. Using the GUI

Launch the flight control GUI:

```python
from python.gui import FlightControlGUI, ParameterTunerGUI, RealTimeVisualizer

# Create GUI components
flight_gui = FlightControlGUI()
param_tuner = ParameterTunerGUI()
visualizer = RealTimeVisualizer()

# Show GUIs
flight_gui.show()
param_tuner.show()
visualizer.show()

# The GUIs will handle the control loop automatically
```

## Advanced Features

### 1. State Estimation

Use the recursive estimators for better state estimation:

```python
from python.estimation import ExtendedKalmanFilter
import numpy as np

# Initialize EKF
initial_state = np.zeros(12)  # [position, velocity, attitude, angular_velocity]
initial_covariance = np.eye(12) * 0.1

ekf = ExtendedKalmanFilter(initial_state, initial_covariance)

# In your control loop
for i in range(100):
    # Prediction step
    predicted_state = ekf.predict(0.1)
    
    # Get measurement (from Vicon or other sensors)
    measurement = np.array([0.0, 0.0, 0.5, 0.0, 0.0, 0.0])  # Position and velocity
    measurement_covariance = np.eye(6) * 0.01
    
    # Update step
    updated_state = ekf.update(measurement, measurement_covariance)
    
    # Use updated state for control
    current_state = updated_state
    control_commands = pid_controller.update(reference_position, current_state, 0.1)
```

### 2. Performance Monitoring

Monitor system performance in real-time:

```python
from python.utils import PerformanceMonitor, PerformanceConfig

# Create performance monitor
config = PerformanceConfig(
    update_interval=1.0,
    enable_cpu_monitoring=True,
    enable_memory_monitoring=True,
    alert_thresholds={
        'cpu_cpu_percent': 80.0,
        'memory_memory_percent': 85.0
    }
)

monitor = PerformanceMonitor(config)

# Add alert callback
def alert_callback(alert):
    print(f"Performance alert: {alert.message}")

monitor.add_alert_callback(alert_callback)

# Start monitoring
monitor.start_monitoring()

# Your control loop here...

# Get performance report
report = monitor.get_performance_report()
print(f"Performance summary: {report['summary']}")

# Stop monitoring
monitor.stop_monitoring()
```

### 3. Data Logging

Comprehensive data logging for analysis:

```python
from python.utils import DataLogger, LoggerConfig, DataFormat

# Create data logger
config = LoggerConfig(
    output_directory="flight_logs",
    data_format=DataFormat.HDF5,
    compression_enabled=True,
    max_file_size=50 * 1024 * 1024  # 50MB
)

logger = DataLogger(config)

# Start logging
logger.start()

# In your control loop
for i in range(100):
    # Log various data types
    logger.log_position(current_position, "drone_1")
    logger.log_attitude(current_attitude, "drone_1")
    logger.log_velocity(current_velocity, "drone_1")
    logger.log_control_commands(control_commands, "drone_1")
    
    # Log performance metrics
    performance = {
        'position_error': np.linalg.norm(reference_position - current_position),
        'control_effort': np.linalg.norm(control_commands)
    }
    logger.log_performance_metrics(performance)
    
    # Log system events
    if i % 10 == 0:
        logger.log_system_event("Checkpoint", {"iteration": i})

# Stop logging
logger.stop()

# Export data
logger.export_data(DataFormat.JSON, "flight_data.json")
```

## Troubleshooting

### Common Issues

#### 1. Connection Issues

**Problem:** Cannot connect to Crazyflie
```bash
# Check if Crazyradio PA is recognized
lsusb | grep Crazyradio

# Check Crazyflie address
# Try different addresses: radio://0/80/2M/E7E7E7E7E7, radio://0/80/2M/E7E7E7E7E8
```

**Solution:**
- Ensure Crazyradio PA is properly inserted
- Check Crazyflie battery level
- Verify the correct radio address
- Try different radio channels

#### 2. Performance Issues

**Problem:** Control loop running too slowly
```python
# Check system performance
from python.utils import PerformanceMonitor
monitor = PerformanceMonitor()
monitor.start_monitoring()

# Get current metrics
metrics = monitor.get_current_metrics()
print(f"CPU Usage: {metrics.get('cpu_cpu_percent', 0):.1f}%")
print(f"Memory Usage: {metrics.get('memory_memory_percent', 0):.1f}%")
```

**Solution:**
- Reduce control loop frequency
- Optimize data processing
- Close unnecessary applications
- Use more efficient data structures

#### 3. GUI Issues

**Problem:** GUI not displaying properly
```bash
# Check PyQt5 installation
python -c "from PyQt5.QtWidgets import QApplication; print('PyQt5 OK')"

# Check display settings
echo $DISPLAY
```

**Solution:**
- Reinstall PyQt5: `pip install --force-reinstall PyQt5`
- Check display settings
- Use different backend: `export QT_QPA_PLATFORM=offscreen`

### Debug Mode

Enable debug mode for detailed logging:

```python
import logging
logging.basicConfig(level=logging.DEBUG)

# Or set in configuration
config_manager.set_config(ConfigSection.SYSTEM, "debug_mode", True)
config_manager.set_config(ConfigSection.SYSTEM, "log_level", "DEBUG")
```

## Next Steps

### 1. Advanced Control Algorithms

- **L1 Adaptive Control**: Implement robust adaptive control
- **Model Predictive Control**: Use MPC for trajectory tracking
- **Hybrid Control**: Combine multiple control strategies

### 2. Multi-Drone Control

- Extend the system for multiple quadrotors
- Implement formation control
- Add collision avoidance

### 3. Machine Learning Integration

- Implement reinforcement learning for control
- Use neural networks for state estimation
- Add adaptive parameter tuning

### 4. Simulation Environment

- Set up simulation environment for testing
- Implement hardware-in-the-loop simulation
- Add virtual sensor models

## Resources

### Documentation
- [API Reference](api_reference.md)
- [Setup Guide](setup_guide.md)
- [Configuration Guide](configuration.md)

### Examples
- Check the `python/examples/` directory for more examples
- Review the test files for usage patterns

### Community
- GitHub Issues: Report bugs and request features
- Discussions: Ask questions and share experiences
- Wiki: Community-contributed documentation

## Support

If you encounter issues:

1. **Check the documentation** for solutions
2. **Search existing issues** on GitHub
3. **Create a new issue** with detailed information
4. **Join the community** discussions

---

*Happy flying! 🚁*
