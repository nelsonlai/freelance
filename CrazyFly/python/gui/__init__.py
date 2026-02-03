"""
GUI Package for CrazyFly Quadrotor Control System
================================================

This package contains GUI modules for the quadrotor control system,
including flight control interfaces, parameter tuning, and visualization.

Modules:
- flight_control_gui: Main flight control GUI
- parameter_tuner: Parameter tuning interface
- visualization: 3D visualization tools

Author: [Your Name]
Date: [Current Date]
License: MIT
"""

from .flight_control_gui import FlightControlGUI
from .parameter_tuner import ParameterTunerGUI, ParameterOptimizer, ParameterType, OptimizationAlgorithm
from .visualization import RealTimeVisualizer, QuadrotorVisualizer, VisualizationMode, CameraMode

__version__ = "1.0.0"
__author__ = "[Your Name]"
__email__ = "[your.email@example.com]"

__all__ = [
    # Flight Control GUI
    'FlightControlGUI',
    
    # Parameter Tuner
    'ParameterTunerGUI',
    'ParameterOptimizer',
    'ParameterType',
    'OptimizationAlgorithm',
    
    # Visualization
    'RealTimeVisualizer',
    'QuadrotorVisualizer',
    'VisualizationMode',
    'CameraMode'
]
