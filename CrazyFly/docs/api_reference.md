# CrazyFly API Reference

## Overview

This document provides a comprehensive API reference for the CrazyFly quadrotor control system. The system is organized into several packages, each containing specialized modules for different aspects of quadrotor control.

## Package Structure

```
python/
├── control_systems/     # Control algorithms
├── interfaces/          # Hardware interfaces
├── gui/                # User interfaces
├── utils/              # Utility functions
└── estimation/         # State estimation
```

## Control Systems

### FourLayerPIDController

A comprehensive 4-layer PID control system for quadrotor flight control.

**Location:** `python/control_systems/pid_controller.py`

**Class:** `FourLayerPIDController`

#### Constructor
```python
def __init__(self, config: PIDConfig = None)
```

#### Methods

##### `update(reference: np.ndarray, current_state: np.ndarray, dt: float) -> np.ndarray`
Update the controller with new reference and current state.

**Parameters:**
- `reference`: Target position/velocity/attitude
- `current_state`: Current measured state
- `dt`: Time step

**Returns:** Control commands

##### `set_gains(layer: str, gains: Dict[str, float])`
Set PID gains for a specific control layer.

**Parameters:**
- `layer`: Control layer ('position', 'velocity', 'attitude', 'attitude_rate')
- `gains`: Dictionary of gains {'kp', 'ki', 'kd'}

##### `reset()`
Reset all integrators and previous errors.

##### `get_performance_metrics() -> Dict[str, float]`
Get current performance metrics.

### L1AdaptiveController

L1 adaptive control implementation for robust quadrotor control.

**Location:** `python/control_systems/l1_adaptive_controller.py`

**Class:** `L1AdaptiveController`

#### Constructor
```python
def __init__(self, config: L1Config = None)
```

#### Methods

##### `update(reference: np.ndarray, current_state: np.ndarray, dt: float) -> np.ndarray`
Update the L1 adaptive controller.

##### `set_adaptation_rate(rate: float)`
Set the adaptation rate.

##### `get_adaptive_parameters() -> Dict[str, np.ndarray]`
Get current adaptive parameter estimates.

### MPCController

Model Predictive Control implementation for trajectory tracking.

**Location:** `python/control_systems/mpc_controller.py`

**Class:** `MPCController`

#### Constructor
```python
def __init__(self, config: MPCConfig = None)
```

#### Methods

##### `solve_optimization(current_state: np.ndarray, reference_trajectory: np.ndarray) -> np.ndarray`
Solve the MPC optimization problem.

##### `set_horizon_length(length: int)`
Set the prediction horizon length.

##### `get_optimization_status() -> Dict[str, Any]`
Get optimization solver status.

## Interfaces

### ViconInterface

Interface to Vicon motion capture system.

**Location:** `python/interfaces/vicon_interface.py`

**Class:** `ViconInterface`

#### Constructor
```python
def __init__(self, host: str = "192.168.1.100", port: int = 801)
```

#### Methods

##### `connect() -> bool`
Connect to Vicon system.

##### `disconnect()`
Disconnect from Vicon system.

##### `get_subject_data(subject_name: str) -> Optional[Dict[str, Any]]`
Get data for a specific subject.

##### `get_all_subjects() -> List[str]`
Get list of all tracked subjects.

### CrazyflieInterface

Interface to Crazyflie 2.1 quadrotor.

**Location:** `python/interfaces/crazyflie_interface.py`

**Class:** `CrazyflieInterface`

#### Constructor
```python
def __init__(self, address: str = "radio://0/80/2M/E7E7E7E7E7")
```

#### Methods

##### `connect() -> bool`
Connect to Crazyflie.

##### `disconnect()`
Disconnect from Crazyflie.

##### `takeoff(height: float = 0.5) -> bool`
Execute takeoff maneuver.

##### `land() -> bool`
Execute landing maneuver.

##### `send_control_commands(commands: np.ndarray)`
Send motor control commands.

##### `get_state() -> Dict[str, Any]`
Get current quadrotor state.

### UDPHandler

UDP communication handler for real-time data transmission.

**Location:** `python/interfaces/udp_handler.py`

**Class:** `UDPHandler`

#### Constructor
```python
def __init__(self, host: str = "127.0.0.1", port: int = 8080)
```

#### Methods

##### `start()`
Start UDP communication.

##### `stop()`
Stop UDP communication.

##### `send_data(data: Any, format: DataFormat = DataFormat.JSON)`
Send data over UDP.

##### `receive_data() -> Optional[Any]`
Receive data from UDP.

## GUI Components

### FlightControlGUI

Main flight control GUI window.

**Location:** `python/gui/flight_control_gui.py`

**Class:** `FlightControlGUI`

#### Constructor
```python
def __init__(self)
```

#### Methods

##### `show()`
Display the GUI window.

##### `close()`
Close the GUI window.

##### `update_flight_data(data: Dict[str, Any])`
Update flight data display.

##### `set_control_mode(mode: str)`
Set the control mode.

### ParameterTunerGUI

Parameter tuning interface with real-time visualization.

**Location:** `python/gui/parameter_tuner.py`

**Class:** `ParameterTunerGUI`

#### Constructor
```python
def __init__(self)
```

#### Methods

##### `add_parameter_set(parameter_set: ParameterSet)`
Add a parameter set to the tuner.

##### `update_parameter_value(set_name: str, param_name: str, value: float)`
Update a parameter value.

##### `start_optimization(algorithm: OptimizationAlgorithm)`
Start parameter optimization.

### RealTimeVisualizer

3D visualization system for quadrotor flight.

**Location:** `python/gui/visualization.py`

**Class:** `RealTimeVisualizer`

#### Constructor
```python
def __init__(self, config: VisualizationConfig = None)
```

#### Methods

##### `update_state(state: QuadrotorState)`
Update quadrotor state for visualization.

##### `update_target(target_position: np.ndarray)`
Update target position.

##### `show()`
Display the visualization window.

## Utilities

### DataLogger

Comprehensive data logging system.

**Location:** `python/utils/data_logger.py`

**Class:** `DataLogger`

#### Constructor
```python
def __init__(self, config: LoggerConfig = None)
```

#### Methods

##### `start()`
Start data logging.

##### `stop()`
Stop data logging.

##### `log_data(data_type: str, data: Any, metadata: Dict[str, Any] = None)`
Log data with metadata.

##### `log_position(position: np.ndarray, drone_id: str = "drone_1")`
Log position data.

##### `log_attitude(attitude: np.ndarray, drone_id: str = "drone_1")`
Log attitude data.

##### `export_data(file_path: str = None) -> bool`
Export logged data to file.

### ConfigurationManager

Configuration management system with validation and hot-reloading.

**Location:** `python/utils/config_manager.py`

**Class:** `ConfigurationManager`

#### Constructor
```python
def __init__(self, config_dir: str = "config", encryption_key: str = None)
```

#### Methods

##### `load_config(section: ConfigSection, file_path: str = None) -> bool`
Load configuration from file.

##### `save_config(section: ConfigSection, file_path: str = None) -> bool`
Save configuration to file.

##### `get_config(section: ConfigSection, key: str = None, default: Any = None) -> Any`
Get configuration value.

##### `set_config(section: ConfigSection, key: str, value: Any, encrypt: bool = False) -> bool`
Set configuration value.

##### `start_watching()`
Start watching for configuration changes.

##### `add_change_callback(callback: Callable)`
Add callback for configuration changes.

### PerformanceMonitor

Performance monitoring and analysis system.

**Location:** `python/utils/performance_monitor.py`

**Class:** `PerformanceMonitor`

#### Constructor
```python
def __init__(self, config: PerformanceConfig = None)
```

#### Methods

##### `start_monitoring()`
Start performance monitoring.

##### `stop_monitoring()`
Stop performance monitoring.

##### `get_current_metrics() -> Dict[str, float]`
Get current metric values.

##### `get_performance_report() -> Dict[str, Any]`
Get comprehensive performance report.

##### `add_alert_callback(callback: Callable)`
Add callback for performance alerts.

##### `plot_metrics(metric_names: List[str] = None, save_path: str = None)`
Plot performance metrics.

## Estimation

### RecursiveEstimatorBase

Base class for recursive state estimators.

**Location:** `python/estimation/recursive_estimator.py`

**Class:** `RecursiveEstimatorBase`

#### Constructor
```python
def __init__(self, initial_state: np.ndarray, initial_covariance: np.ndarray)
```

#### Methods

##### `predict(dt: float) -> np.ndarray`
Predict next state estimate.

##### `update(measurement: np.ndarray, measurement_covariance: np.ndarray) -> np.ndarray`
Update state estimate with measurement.

##### `get_state() -> np.ndarray`
Get current state estimate.

##### `get_covariance() -> np.ndarray`
Get current state covariance.

### ExtendedKalmanFilter

Extended Kalman Filter implementation.

**Location:** `python/estimation/recursive_estimator.py`

**Class:** `ExtendedKalmanFilter`

#### Constructor
```python
def __init__(self, initial_state: np.ndarray, initial_covariance: np.ndarray)
```

#### Methods

##### `predict(dt: float) -> np.ndarray`
EKF prediction step.

##### `update(measurement: np.ndarray, measurement_covariance: np.ndarray) -> np.ndarray`
EKF update step.

### UnscentedKalmanFilter

Unscented Kalman Filter implementation.

**Location:** `python/estimation/recursive_estimator.py`

**Class:** `UnscentedKalmanFilter`

#### Constructor
```python
def __init__(self, initial_state: np.ndarray, initial_covariance: np.ndarray)
```

#### Methods

##### `predict(dt: float) -> np.ndarray`
UKF prediction step.

##### `update(measurement: np.ndarray, measurement_covariance: np.ndarray) -> np.ndarray`
UKF update step.

### ParticleFilter

Particle Filter implementation.

**Location:** `python/estimation/particle_filter.py`

**Class:** `ParticleFilter`

#### Constructor
```python
def __init__(self, initial_state: np.ndarray, num_particles: int = 1000)
```

#### Methods

##### `predict(dt: float)`
PF prediction step.

##### `update(measurement: np.ndarray, measurement_covariance: np.ndarray)`
PF update step.

##### `resample()`
Resample particles.

### SensorFusionManager

Multi-sensor data fusion manager.

**Location:** `python/estimation/sensor_fusion_manager.py`

**Class:** `SensorFusionManager`

#### Constructor
```python
def __init__(self, config: FusionConfig = None)
```

#### Methods

##### `add_sensor(sensor_id: str, sensor_type: SensorType, update_rate: float)`
Add a sensor to the fusion system.

##### `update_sensor_data(sensor_id: str, data: Dict[str, Any])`
Update sensor data.

##### `get_fused_state() -> np.ndarray`
Get fused state estimate.

##### `start_fusion()`
Start sensor fusion.

##### `stop_fusion()`
Stop sensor fusion.

## Data Structures

### PIDConfig
Configuration for PID controller.

**Fields:**
- `position_gains`: Position control gains
- `velocity_gains`: Velocity control gains
- `attitude_gains`: Attitude control gains
- `attitude_rate_gains`: Attitude rate control gains

### L1Config
Configuration for L1 adaptive controller.

**Fields:**
- `adaptation_rate`: Adaptation rate
- `filter_bandwidth`: L1 filter bandwidth
- `prediction_horizon`: Prediction horizon

### MPCConfig
Configuration for MPC controller.

**Fields:**
- `horizon_length`: Prediction horizon length
- `position_weight`: Position tracking weight
- `control_weight`: Control effort weight
- `max_iterations`: Maximum optimization iterations

### LoggerConfig
Configuration for data logger.

**Fields:**
- `output_directory`: Output directory
- `data_format`: Data format
- `compression_enabled`: Enable compression
- `max_file_size`: Maximum file size
- `flush_interval`: Flush interval

### PerformanceConfig
Configuration for performance monitor.

**Fields:**
- `update_interval`: Update interval
- `history_length`: History length
- `enable_cpu_monitoring`: Enable CPU monitoring
- `enable_memory_monitoring`: Enable memory monitoring
- `alert_thresholds`: Alert thresholds

## Enums

### LogLevel
- `DEBUG`
- `INFO`
- `WARNING`
- `ERROR`
- `CRITICAL`

### DataFormat
- `JSON`
- `CSV`
- `HDF5`
- `BINARY`
- `PICKLE`
- `COMPRESSED`

### ConfigFormat
- `JSON`
- `YAML`
- `INI`
- `TOML`

### ConfigSection
- `SYSTEM`
- `CONTROL`
- `SENSORS`
- `COMMUNICATION`
- `GUI`
- `LOGGING`
- `SAFETY`
- `PERFORMANCE`

### MetricType
- `CPU_USAGE`
- `MEMORY_USAGE`
- `NETWORK_IO`
- `DISK_IO`
- `CONTROL_LATENCY`
- `SENSOR_LATENCY`
- `COMMUNICATION_LATENCY`
- `THREAD_COUNT`
- `PROCESS_COUNT`
- `TEMPERATURE`
- `BATTERY_LEVEL`
- `CUSTOM`

### AlertLevel
- `INFO`
- `WARNING`
- `ERROR`
- `CRITICAL`

### VisualizationMode
- `TRAJECTORY_3D`
- `ATTITUDE_DISPLAY`
- `PERFORMANCE_METRICS`
- `MULTI_DRONE`
- `REAL_TIME`

### CameraMode
- `FREE`
- `FOLLOW`
- `ORBIT`
- `TOP_DOWN`
- `SIDE_VIEW`

### ParameterType
- `PID`
- `L1_ADAPTIVE`
- `MPC`
- `KALMAN_FILTER`
- `SENSOR_FUSION`
- `SYSTEM`

### OptimizationAlgorithm
- `GRADIENT_DESCENT`
- `GENETIC_ALGORITHM`
- `PARTICLE_SWARM`
- `BAYESIAN_OPTIMIZATION`
- `MANUAL`

## Usage Examples

### Basic Control System Setup

```python
from python.control_systems import FourLayerPIDController
from python.interfaces import ViconInterface, CrazyflieInterface
from python.utils import DataLogger, ConfigurationManager

# Initialize components
pid_controller = FourLayerPIDController()
vicon = ViconInterface("192.168.1.100")
crazyflie = CrazyflieInterface("radio://0/80/2M/E7E7E7E7E7")
logger = DataLogger()
config = ConfigurationManager()

# Connect to hardware
vicon.connect()
crazyflie.connect()

# Start logging
logger.start()

# Control loop
while True:
    # Get current state from Vicon
    state = vicon.get_subject_data("drone_1")
    
    # Calculate control commands
    commands = pid_controller.update(reference, state, dt)
    
    # Send commands to Crazyflie
    crazyflie.send_control_commands(commands)
    
    # Log data
    logger.log_position(state['position'])
    logger.log_attitude(state['attitude'])
```

### GUI Usage

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
```

### Performance Monitoring

```python
from python.utils import PerformanceMonitor

# Create performance monitor
monitor = PerformanceMonitor()

# Add alert callback
def alert_callback(alert):
    print(f"Performance alert: {alert.message}")

monitor.add_alert_callback(alert_callback)

# Start monitoring
monitor.start_monitoring()

# Get performance report
report = monitor.get_performance_report()
print(f"Performance summary: {report['summary']}")
```

## Error Handling

All classes include comprehensive error handling and logging. Errors are logged using Python's `logging` module and can be configured to output to files or console.

## Threading and Concurrency

Many components use threading for real-time operation:

- **Data Logger**: Asynchronous logging with queue-based buffering
- **Performance Monitor**: Background monitoring thread
- **Configuration Manager**: Hot-reloading with file watching
- **GUI Components**: Separate threads for UI updates

## Performance Considerations

- Use appropriate buffer sizes for data logging
- Configure update rates based on system capabilities
- Monitor memory usage with large data histories
- Use compression for long-term data storage
- Consider using HDF5 format for large datasets

## Security

- Configuration encryption for sensitive data
- Input validation for all parameters
- Secure communication protocols
- Access control for configuration changes
