"""
Utilities Package for CrazyFly Quadrotor Control System
======================================================

This package contains utility modules for the quadrotor control system,
including data logging, configuration management, and performance monitoring.

Modules:
- data_logger: Comprehensive data logging utilities
- config_manager: Configuration management system
- performance_monitor: Performance monitoring and analysis

Author: [Your Name]
Date: [Current Date]
License: MIT
"""

from .data_logger import DataLogger, LoggerConfig, LogLevel, DataFormat, LogEntry
from .config_manager import ConfigurationManager, ConfigFormat, ConfigSection, ConfigSchema
from .performance_monitor import PerformanceMonitor, PerformanceConfig, PerformanceMetric, MetricType

__version__ = "1.0.0"
__author__ = "[Your Name]"
__email__ = "[your.email@example.com]"

__all__ = [
    # Data Logger
    'DataLogger',
    'LoggerConfig', 
    'LogLevel',
    'DataFormat',
    'LogEntry',
    
    # Configuration Manager
    'ConfigurationManager',
    'ConfigFormat',
    'ConfigSection',
    'ConfigSchema',
    
    # Performance Monitor
    'PerformanceMonitor',
    'PerformanceConfig',
    'PerformanceMetric',
    'MetricType'
]
