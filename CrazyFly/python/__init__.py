"""
CrazyFly Quadrotor Control System - Python Package
==================================================

A comprehensive quadrotor control system implementation with advanced
control algorithms, real-time performance, and user-friendly interfaces.

Key Features:
- Advanced control systems (PID, L1 Adaptive, MPC)
- Real-time state estimation and sensor fusion
- Comprehensive GUI interfaces
- Performance monitoring and optimization
- Multi-format data logging
- Configuration management
- Hardware interfaces (Vicon, Crazyflie)

Author: [Your Name]
Date: [Current Date]
License: MIT
"""

# Import main components
from .control_systems import (
    FourLayerPIDController,
    L1AdaptiveController,
    AdaptiveKalmanFilter,
    MPCController
)

from .interfaces import (
    ViconInterface,
    CrazyflieInterface,
    UDPHandler
)

from .gui import (
    FlightControlGUI,
    ParameterTunerGUI,
    RealTimeVisualizer
)

from .utils import (
    DataLogger,
    ConfigurationManager,
    PerformanceMonitor
)

from .estimation import (
    RecursiveEstimatorBase,
    ExtendedKalmanFilter,
    UnscentedKalmanFilter,
    ParticleFilter,
    SensorFusionManager
)

__version__ = "1.0.0"
__author__ = "[Your Name]"
__email__ = "[your.email@example.com]"

__all__ = [
    # Control Systems
    'FourLayerPIDController',
    'L1AdaptiveController', 
    'AdaptiveKalmanFilter',
    'MPCController',
    
    # Interfaces
    'ViconInterface',
    'CrazyflieInterface',
    'UDPHandler',
    
    # GUI
    'FlightControlGUI',
    'ParameterTunerGUI',
    'RealTimeVisualizer',
    
    # Utilities
    'DataLogger',
    'ConfigurationManager',
    'PerformanceMonitor',
    
    # Estimation
    'RecursiveEstimatorBase',
    'ExtendedKalmanFilter',
    'UnscentedKalmanFilter',
    'ParticleFilter',
    'SensorFusionManager'
]
