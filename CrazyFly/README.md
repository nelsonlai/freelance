# CrazyFly: Advanced Quadrotor Control System

[![Python](https://img.shields.io/badge/Python-3.8+-blue.svg)](https://www.python.org/)
[![MATLAB](https://img.shields.io/badge/MATLAB-R2020a+-orange.svg)](https://www.mathworks.com/)
[![C++](https://img.shields.io/badge/C++-17-green.svg)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

A comprehensive quadrotor control system implementation featuring advanced control algorithms, real-time performance optimization, and multi-language support for research and educational purposes.

## 🚁 Overview

CrazyFly is a complete quadrotor control system that implements state-of-the-art control algorithms including 4-layer PID control, L1 adaptive control, and Model Predictive Control (MPC). The system is designed for research, education, and practical applications with support for Crazyflie 2.1 hardware and Vicon motion capture systems.

### Key Features

- **Advanced Control Algorithms**: 4-layer PID, L1 Adaptive Control, MPC, Hybrid Control
- **Real-Time Performance**: 1000Hz control loops with optimized C++ implementation
- **Multi-Language Support**: Python, MATLAB/Simulink, C++
- **Comprehensive GUI**: Real-time 3D visualization and parameter tuning
- **Robust State Estimation**: Kalman filtering, sensor fusion, adaptive estimation
- **Hardware Integration**: Crazyflie 2.1, Vicon motion capture, custom firmware
- **Simulation Environment**: Complete MATLAB/Simulink simulation framework

## 📁 Project Structure

```
CrazyFly/
├── README.md                           # This file
├── NextSteps.md                        # Contribution roadmap and future plans
├── PROJECT_SUMMARY.md                  # Detailed project summary
├── requirements.txt                    # Python dependencies
├── python/                             # Python implementations
│   ├── __init__.py                     # Main package initialization
│   ├── control_systems/                # Control algorithms
│   │   ├── pid_controller.py          # 4-layer PID controller
│   │   ├── l1_adaptive_controller.py  # L1 adaptive control
│   │   ├── kalman_filter.py           # Advanced Kalman filtering
│   │   └── mpc_controller.py          # Model Predictive Control
│   ├── interfaces/                     # Hardware interfaces
│   │   ├── vicon_interface.py         # Vicon motion capture
│   │   ├── crazyflie_interface.py     # Crazyflie communication
│   │   └── udp_handler.py             # UDP communication
│   ├── gui/                           # User interfaces
│   │   ├── flight_control_gui.py      # Main flight control GUI
│   │   ├── parameter_tuner.py         # Parameter tuning interface
│   │   └── visualization.py           # 3D visualization tools
│   ├── estimation/                     # State estimation
│   │   ├── recursive_estimator.py     # Base estimator class
│   │   ├── particle_filter.py         # Particle filter implementation
│   │   └── sensor_fusion_manager.py   # Multi-sensor fusion
│   ├── utils/                         # Utility functions
│   │   ├── data_logger.py             # Data logging utilities
│   │   ├── config_manager.py          # Configuration management
│   │   └── performance_monitor.py     # Performance monitoring
│   └── examples/                      # Usage examples
│       └── recursive_estimator_example.py
├── cpp/                               # C++ implementations
│   ├── CMakeLists.txt                 # CMake build configuration
│   ├── high_freq_control/             # High-frequency control
│   │   └── real_time_controller.cpp   # Real-time control loop
│   ├── firmware/                      # Custom firmware components
│   │   ├── pwm_controller.cpp         # PWM motor control
│   │   ├── safety_system.cpp          # Safety systems
│   │   └── sensor_interface.cpp       # Sensor interfaces
│   └── utils/                         # C++ utilities
│       ├── memory_manager.cpp         # Memory management
│       ├── thread_pool.cpp            # Multi-threading
│       └── performance_optimizer.cpp   # Performance optimization
├── matlab/                            # MATLAB/Simulink implementations
│   ├── README.md                      # MATLAB documentation
│   ├── control_models/                # Control system models
│   │   ├── four_layer_pid.slx         # 4-layer PID control
│   │   ├── l1_adaptive_model.slx      # L1 adaptive control
│   │   └── hybrid_controller.slx      # Hybrid control system
│   ├── simulation/                    # Simulation environment
│   │   ├── quadrotor_dynamics.slx     # Quadrotor dynamics
│   │   ├── vicon_simulation.slx       # Vicon simulation
│   │   └── environment_model.slx      # Environmental factors
│   └── analysis/                      # Analysis tools
│       ├── parameter_optimizer.m      # Parameter optimization
│       ├── performance_analyzer.m     # Performance analysis
│       └── four_layer_pid.m           # Model generators
├── tests/                             # Testing framework
│   ├── unit_tests/                    # Unit tests
│   ├── integration_tests/            # Integration tests
│   └── flight_tests/                 # Flight validation tests
└── docs/                              # Documentation
    ├── setup_guide.md                 # Setup instructions
    ├── api_reference.md               # API documentation
    └── tutorials/                     # Tutorial guides
```

## 🚀 Quick Start

### Prerequisites

- **Python 3.8+** with pip
- **MATLAB R2020a+** with Simulink
- **C++17** compiler (GCC/Clang)
- **Crazyflie SDK** and tools
- **Vicon Tracker** (for motion capture)

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/your-username/CrazyFly.git
   cd CrazyFly
   ```

2. **Install Python dependencies**
   ```bash
   pip install -r requirements.txt
   ```

3. **Set up MATLAB paths**
   ```matlab
   addpath(genpath('matlab'));
   savepath;
   ```

4. **Build C++ components**
   ```bash
   cd cpp
   mkdir build && cd build
   cmake ..
   make
   ```

### Basic Usage

1. **Run Python control system**
   ```python
   from python.control_systems import FourLayerPIDController
   from python.interfaces import CrazyflieInterface
   
   # Initialize controller
   controller = FourLayerPIDController()
   
   # Connect to Crazyflie
   crazyflie = CrazyflieInterface("radio://0/80/2M/E7E7E7E7E7")
   crazyflie.connect()
   
   # Start control loop
   controller.start_control_loop()
   ```

2. **Open MATLAB simulation**
   ```matlab
   % Generate and open 4-layer PID model
   four_layer_pid;
   
   % Run simulation
   sim('four_layer_pid.slx');
   ```

3. **Launch GUI**
   ```python
   from python.gui import FlightControlGUI
   
   gui = FlightControlGUI()
   gui.show()
   ```

## 🎯 Control Algorithms

### 4-Layer PID Controller
Complete cascaded control structure with position, velocity, attitude, and attitude-rate control layers.

```python
from python.control_systems import FourLayerPIDController

controller = FourLayerPIDController()
controller.set_gains("position", {"kp": 2.0, "ki": 0.1, "kd": 1.0})
controller.set_gains("velocity", {"kp": 1.5, "ki": 0.05, "kd": 0.8})
controller.set_gains("attitude", {"kp": 3.0, "ki": 0.2, "kd": 1.5})
```

### L1 Adaptive Control
Robust adaptive control with fast adaptation and stability guarantees.

```python
from python.control_systems import L1AdaptiveController

l1_controller = L1AdaptiveController()
l1_controller.set_adaptation_rate(10.0)
l1_controller.set_filter_bandwidth(5.0)
```

### Model Predictive Control
Advanced trajectory tracking with constraint handling.

```python
from python.control_systems import MPCController

mpc_controller = MPCController()
mpc_controller.set_horizon_length(20)
mpc_controller.set_constraints(position_limits=[-2, 2])
```

## 🔧 Hardware Integration

### Crazyflie 2.1 Interface
Direct communication with Crazyflie hardware via Crazyradio PA.

```python
from python.interfaces import CrazyflieInterface

crazyflie = CrazyflieInterface("radio://0/80/2M/E7E7E7E7E7")
crazyflie.connect()
crazyflie.takeoff(0.5)
crazyflie.send_control_commands(commands)
```

### Vicon Motion Capture
Real-time position and orientation tracking.

```python
from python.interfaces import ViconInterface

vicon = ViconInterface("192.168.1.100", 801)
vicon.connect()
position = vicon.get_subject_data("quadrotor")
```

## 📊 Performance Monitoring

### Real-Time Metrics
Monitor system performance with comprehensive metrics.

```python
from python.utils import PerformanceMonitor

monitor = PerformanceMonitor()
monitor.start_monitoring()
metrics = monitor.get_current_metrics()
```

### Data Logging
Comprehensive flight data recording and analysis.

```python
from python.utils import DataLogger

logger = DataLogger()
logger.start()
logger.log_position(position, "drone_1")
logger.log_attitude(attitude, "drone_1")
logger.export_data("flight_data.h5")
```

## 🧪 Testing Framework

### Unit Tests
```bash
python -m pytest tests/unit_tests/
```

### Integration Tests
```bash
python -m pytest tests/integration_tests/
```

### Flight Tests
```bash
python -m pytest tests/flight_tests/
```

## 📚 Documentation

- **[Setup Guide](docs/setup_guide.md)**: Detailed installation and configuration
- **[API Reference](docs/api_reference.md)**: Complete API documentation
- **[Tutorials](docs/tutorials/)**: Step-by-step guides
- **[Next Steps](NextSteps.md)**: Contribution roadmap and future plans

## 🤝 Contributing

We welcome contributions! Please see our [Contributing Guidelines](CONTRIBUTING.md) for details.

### High-Priority Areas
- Advanced control algorithm implementations
- Real-time performance optimization
- Hardware integration improvements
- Simulation environment enhancements
- Documentation and tutorials

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- [NCKU-Quadrotor-Navigation](https://github.com/Lee-Chun-Yi/NCKU-Quadrotor-Navigation) for foundational work
- [L1-Crazyflie](https://github.com/cfc-ray/L1-Crazyflie) for L1 adaptive control implementation
- The Crazyflie community for hardware and firmware support

## 📞 Support

- **Issues**: [GitHub Issues](https://github.com/your-username/CrazyFly/issues)
- **Discussions**: [GitHub Discussions](https://github.com/your-username/CrazyFly/discussions)
- **Documentation**: [Wiki](https://github.com/your-username/CrazyFly/wiki)

---

**CrazyFly** - Advancing quadrotor control technology through open-source innovation.
