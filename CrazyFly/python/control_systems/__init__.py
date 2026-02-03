"""
Control Systems Package for CrazyFly Quadrotor Control System
===========================================================

This package contains control system implementations for the quadrotor,
including PID controllers, adaptive control, and model predictive control.

Modules:
- pid_controller: Enhanced PID control system
- l1_adaptive_controller: L1 adaptive control implementation
- kalman_filter: Advanced Kalman filtering
- mpc_controller: Model Predictive Control

Author: [Your Name]
Date: [Current Date]
License: MIT
"""

from .pid_controller import FourLayerPIDController
from .l1_adaptive_controller import L1AdaptiveController
from .kalman_filter import AdaptiveKalmanFilter
from .mpc_controller import MPCController

__version__ = "1.0.0"
__author__ = "[Your Name]"
__email__ = "[your.email@example.com]"

__all__ = [
    'FourLayerPIDController',
    'L1AdaptiveController',
    'AdaptiveKalmanFilter',
    'MPCController'
]
