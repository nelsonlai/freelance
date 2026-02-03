"""
Interfaces Package for CrazyFly Quadrotor Control System
=======================================================

This package contains interface modules for the quadrotor control system,
including hardware interfaces and communication protocols.

Modules:
- vicon_interface: Vicon motion capture system interface
- crazyflie_interface: Crazyflie quadrotor communication interface
- udp_handler: UDP communication utilities

Author: [Your Name]
Date: [Current Date]
License: MIT
"""

from .vicon_interface import ViconInterface
from .crazyflie_interface import CrazyflieInterface
from .udp_handler import UDPHandler

__version__ = "1.0.0"
__author__ = "[Your Name]"
__email__ = "[your.email@example.com]"

__all__ = [
    'ViconInterface',
    'CrazyflieInterface', 
    'UDPHandler'
]
