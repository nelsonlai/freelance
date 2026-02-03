# CrazyFly Quadrotor Control System - Setup Guide
================================================

This guide provides comprehensive instructions for setting up the CrazyFly quadrotor control system, including all software components, hardware requirements, and configuration steps.

## Table of Contents

1. [System Requirements](#system-requirements)
2. [Hardware Setup](#hardware-setup)
3. [Software Installation](#software-installation)
4. [Configuration](#configuration)
5. [Testing](#testing)
6. [Troubleshooting](#troubleshooting)
7. [Advanced Configuration](#advanced-configuration)

---

## System Requirements

### Minimum Requirements
- **Operating System**: Ubuntu 20.04+ / macOS 10.15+ / Windows 10+
- **CPU**: Intel i5 or AMD Ryzen 5 (4+ cores recommended)
- **RAM**: 8GB minimum, 16GB recommended
- **Storage**: 10GB free space
- **Network**: Ethernet connection for real-time control

### Recommended Requirements
- **CPU**: Intel i7 or AMD Ryzen 7 (8+ cores)
- **RAM**: 32GB
- **Storage**: SSD with 50GB free space
- **Network**: Gigabit Ethernet
- **Graphics**: Dedicated GPU for 3D visualization

### Hardware Components
- **Crazyflie 2.1 or Bolt**: Main flight controller
- **Vicon Motion Capture System**: For position tracking
- **Crazyradio PA**: Wireless communication
- **LiPo Battery**: 450mAh 2S (for Crazyflie 2.1) or 850mAh 2S (for Bolt)
- **USB-C Cable**: For firmware flashing and debugging

---

## Hardware Setup

### 1. Crazyflie Assembly

#### For Crazyflie 2.1:
1. **Frame Assembly**:
   - Attach 4 motors to the frame using M2 screws
   - Connect motor wires to the Crazyflie 2.1 board
   - Mount the Crazyflie 2.1 board to the frame
   - Attach propeller guards (optional)

2. **Motor Configuration**:
   ```
   Motor 1 (Front Left):  Clockwise
   Motor 2 (Front Right): Counter-clockwise
   Motor 3 (Back Left):   Counter-clockwise
   Motor 4 (Back Right):  Clockwise
   ```

#### For Crazyflie Bolt:
1. **Frame Assembly**:
   - Mount the Crazyflie Bolt board to the frame
   - Connect brushless motors to the ESC
   - Connect ESC to the Bolt board
   - Attach propellers (3-inch recommended)

2. **ESC Configuration**:
   - Use BLHeli_32 ESCs for best performance
   - Configure for DShot600 protocol
   - Set motor direction as above

### 2. Vicon Motion Capture Setup

1. **Camera Installation**:
   - Mount Vicon cameras around the flight area
   - Ensure overlapping coverage
   - Calibrate camera positions using calibration wand

2. **Marker Placement**:
   - Attach reflective markers to the quadrotor
   - Use 4-6 markers for reliable tracking
   - Ensure markers are visible from multiple cameras

3. **System Calibration**:
   ```bash
   # In Vicon Tracker
   1. Run system calibration
   2. Create rigid body for quadrotor
   3. Test tracking accuracy
   ```

### 3. Communication Setup

1. **Crazyradio PA**:
   - Connect to USB port
   - Install drivers if needed
   - Test connection with Crazyflie client

2. **Network Configuration**:
   ```bash
   # Set up dedicated network for real-time communication
   sudo ip addr add 192.168.1.100/24 dev eth0
   sudo ip route add 192.168.1.0/24 dev eth0
   ```

---

## Software Installation

### 1. Prerequisites

#### Ubuntu/Debian:
```bash
# Update system
sudo apt update && sudo apt upgrade

# Install essential packages
sudo apt install -y build-essential cmake git python3 python3-pip
sudo apt install -y libblas-dev liblapack-dev libatlas-base-dev gfortran
sudo apt install -y libhdf5-dev libhdf5-serial-dev
sudo apt install -y libqt5gui5 libqt5core5a libqt5dbus5
sudo apt install -y libgl1-mesa-glx libglib2.0-0
sudo apt install -y doxygen graphviz
```

#### macOS:
```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install dependencies
brew install cmake python3 git
brew install hdf5 qt5 openblas
brew install doxygen graphviz
```

#### Windows:
1. Install Visual Studio Build Tools 2019 or later
2. Install Python 3.8+ from python.org
3. Install Git for Windows
4. Install CMake from cmake.org

### 2. Clone Repository

```bash
# Clone the repository
git clone https://github.com/your-username/CrazyFly.git
cd CrazyFly

# Initialize submodules (if any)
git submodule update --init --recursive
```

### 3. Python Dependencies

```bash
# Create virtual environment (recommended)
python3 -m venv crazyfly_env
source crazyfly_env/bin/activate  # On Windows: crazyfly_env\Scripts\activate

# Install Python dependencies
pip install -r requirements.txt

# Install additional packages for development
pip install pytest pytest-cov black flake8 mypy
```

### 4. C++ Build

```bash
# Navigate to C++ directory
cd cpp

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
make -j$(nproc)  # Use all available cores

# Install (optional)
sudo make install
```

### 5. MATLAB/Simulink Setup

1. **Install MATLAB R2020a or later**
2. **Add paths**:
   ```matlab
   % In MATLAB
   addpath(genpath('matlab/control_models'));
   addpath(genpath('matlab/simulation'));
   addpath(genpath('matlab/analysis'));
   ```

3. **Install required toolboxes**:
   - Control System Toolbox
   - Simulink
   - Aerospace Toolbox (optional)
   - Robotics System Toolbox (optional)

---

## Configuration

### 1. Control System Configuration

#### PID Controller Tuning:
```python
# Example configuration in python/control_systems/pid_controller.py
config = {
    'position': PIDGains(kp=1.0, ki=0.1, kd=0.5, integral_limit=10.0, output_limit=2.0),
    'velocity': PIDGains(kp=2.0, ki=0.2, kd=1.0, integral_limit=5.0, output_limit=0.5),
    'attitude': PIDGains(kp=3.0, ki=0.0, kd=0.8, integral_limit=1.0, output_limit=0.3),
    'attitude_rate': PIDGains(kp=4.0, ki=0.0, kd=1.2, integral_limit=0.5, output_limit=0.2)
}
```

#### L1 Adaptive Controller:
```python
# Example configuration in python/control_systems/l1_adaptive_controller.py
params = L1Parameters(
    adaptation_rate=100.0,
    filter_bandwidth=10.0,
    prediction_horizon=5
)
```

### 2. Communication Configuration

#### UDP Communication:
```python
# Vicon data reception
VICON_HOST = '192.168.1.100'
VICON_PORT = 8000

# Control data transmission
CONTROL_HOST = '192.168.1.101'
CONTROL_PORT = 8001
```

#### Crazyflie Communication:
```python
# Radio configuration
RADIO_CHANNEL = 80
RADIO_ADDRESS = 0xE7E7E7E7E7
RADIO_DATARATE = 250000
```

### 3. Real-time Configuration

#### Linux Real-time Setup:
```bash
# Install real-time kernel (optional)
sudo apt install linux-image-rt

# Configure real-time priorities
echo '@realtime - rtprio 99' | sudo tee -a /etc/security/limits.conf
echo '@realtime - memlock unlimited' | sudo tee -a /etc/security/limits.conf

# Add user to realtime group
sudo usermod -a -G realtime $USER
```

#### C++ Real-time Configuration:
```cpp
// In cpp/high_freq_control/real_time_controller.cpp
TimingConfig config;
config.control_frequency_hz = 1000.0;  // 1kHz control loop
config.control_period_us = 1000.0;     // 1ms period
config.max_jitter_us = 50.0;           // 50us max jitter
```

---

## Testing

### 1. Unit Tests

```bash
# Run Python tests
cd python
python -m pytest tests/ -v

# Run C++ tests
cd cpp/build
./crazyfly_test
```

### 2. Hardware Tests

#### Crazyflie Connection Test:
```python
# Test script: test_crazyflie_connection.py
from cflib.crazyflie import Crazyflie
from cflib.crazyflie.syncCrazyflie import SyncCrazyflie

def test_connection():
    cf = Crazyflie()
    with SyncCrazyflie(uri, cf) as scf:
        print("Connection successful!")
        # Test basic commands
        scf.cf.commander.send_setpoint(0, 0, 0, 0)
```

#### Vicon Connection Test:
```python
# Test script: test_vicon_connection.py
import socket

def test_vicon():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind(('', 8000))
    
    try:
        data, addr = sock.recvfrom(1024)
        print(f"Received data from {addr}: {data}")
    except socket.timeout:
        print("No data received - check Vicon configuration")
```

### 3. Integration Tests

#### Full System Test:
```bash
# Start all components
python python/gui/flight_control_gui.py &
python python/control_systems/pid_controller.py &
./cpp/build/crazyfly_control &

# Run test flight
python tests/integration_test.py
```

---

## Troubleshooting

### Common Issues

#### 1. Crazyflie Connection Issues
**Problem**: Cannot connect to Crazyflie
**Solution**:
```bash
# Check radio connection
crazyflie-cli-tools scan

# Reset Crazyflie
crazyflie-cli-tools reset

# Check firmware version
crazyflie-cli-tools version
```

#### 2. Vicon Tracking Issues
**Problem**: Poor tracking accuracy
**Solution**:
- Check camera calibration
- Ensure adequate lighting
- Clean reflective markers
- Verify rigid body configuration

#### 3. Real-time Performance Issues
**Problem**: High jitter in control loop
**Solution**:
```bash
# Check system load
htop

# Monitor real-time performance
sudo cyclictest -p 80 -t1 -n -a0 -l 1000000

# Check for IRQ conflicts
cat /proc/interrupts
```

#### 4. Python Import Errors
**Problem**: Module not found errors
**Solution**:
```bash
# Check Python path
python -c "import sys; print(sys.path)"

# Install missing packages
pip install -r requirements.txt

# Check virtual environment
which python
```

### Performance Optimization

#### 1. System Tuning
```bash
# Disable CPU frequency scaling
echo performance | sudo tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor

# Disable power management
sudo cpupower frequency-set -g performance

# Set CPU affinity
taskset -p -c 0 <pid>
```

#### 2. Network Optimization
```bash
# Optimize network settings
sudo sysctl -w net.core.rmem_max=26214400
sudo sysctl -w net.core.wmem_max=26214400
sudo sysctl -w net.ipv4.tcp_rmem="4096 87380 16777216"
sudo sysctl -w net.ipv4.tcp_wmem="4096 65536 16777216"
```

---

## Advanced Configuration

### 1. Custom Firmware

#### Building Custom Firmware:
```bash
# Clone Crazyflie firmware
git clone https://github.com/bitcraze/crazyflie-firmware.git
cd crazyflie-firmware

# Apply custom patches
git apply ../patches/custom_pwm_control.patch

# Build firmware
make clean
make
```

#### Flashing Firmware:
```bash
# Flash to Crazyflie
crazyflie-cli-tools flash firmware/cf2.bin

# Verify firmware
crazyflie-cli-tools version
```

### 2. Multi-Drone Setup

#### Configuration for Multiple Drones:
```python
# Multi-drone configuration
DRONE_CONFIGS = {
    'drone1': {
        'uri': 'radio://0/80/2M/E7E7E7E7E7',
        'position': [0, 0, 0],
        'color': 'red'
    },
    'drone2': {
        'uri': 'radio://0/80/2M/E7E7E7E7E8',
        'position': [1, 0, 0],
        'color': 'blue'
    }
}
```

### 3. Advanced Control Algorithms

#### Model Predictive Control:
```python
# MPC configuration
mpc_config = {
    'horizon': 10,
    'dt': 0.01,
    'Q': np.diag([1.0, 1.0, 1.0, 0.1, 0.1, 0.1]),
    'R': np.diag([0.1, 0.1, 0.1, 0.1])
}
```

#### Reinforcement Learning:
```python
# RL configuration
rl_config = {
    'algorithm': 'PPO',
    'learning_rate': 0.0003,
    'batch_size': 64,
    'gamma': 0.99
}
```

---

## Support and Resources

### Documentation
- [API Reference](api_reference.md)
- [Tutorials](tutorials/)
- [Research Papers](papers/)

### Community
- [GitHub Issues](https://github.com/your-username/CrazyFly/issues)
- [Discord Server](https://discord.gg/crazyfly)
- [Mailing List](mailto:crazyfly@example.com)

### Contributing
- [Contributing Guidelines](CONTRIBUTING.md)
- [Code of Conduct](CODE_OF_CONDUCT.md)
- [Development Setup](DEVELOPMENT.md)

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- [NCKU-Quadrotor-Navigation](https://github.com/Lee-Chun-Yi/NCKU-Quadrotor-Navigation) for the foundation work
- [L1-Crazyflie](https://github.com/cfc-ray/L1-Crazyflie) for L1 adaptive control implementation
- The Crazyflie community for hardware and firmware support
