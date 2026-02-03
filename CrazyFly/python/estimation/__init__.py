"""
Estimation Module for Quadrotor Control System
=============================================

This module provides comprehensive state estimation capabilities for quadrotor
control systems, including multiple estimation algorithms and sensor fusion.

Key Components:
- RecursiveEstimatorBase: Abstract base class for all estimators
- ExtendedKalmanFilter: EKF implementation for nonlinear systems
- UnscentedKalmanFilter: UKF implementation for better nonlinear handling
- ParticleFilter: Particle filter for non-Gaussian noise scenarios
- SensorFusionManager: Multi-sensor fusion and coordination
- RecursiveEstimatorFactory: Factory for creating estimators

The estimation module provides the foundation for accurate state estimation
required by advanced control algorithms like MPC and L1 adaptive control.

Author: [Your Name]
Date: [Current Date]
License: MIT
"""

from .recursive_estimator import (
    RecursiveEstimatorBase,
    ExtendedKalmanFilter,
    UnscentedKalmanFilter,
    RecursiveEstimatorFactory,
    EstimatorConfig,
    EstimatorType,
    SensorMeasurement,
    StateEstimate,
    SensorType
)

from .particle_filter import (
    ParticleFilter,
    ParticleFilterConfig,
    Particle,
    ResamplingStrategy
)

from .sensor_fusion_manager import (
    SensorFusionManager,
    SensorFusionConfig,
    SensorInfo,
    SensorStatus,
    FusionStrategy
)

__all__ = [
    # Base classes
    'RecursiveEstimatorBase',
    'EstimatorConfig',
    'EstimatorType',
    'SensorMeasurement',
    'StateEstimate',
    'SensorType',
    
    # Estimators
    'ExtendedKalmanFilter',
    'UnscentedKalmanFilter',
    'ParticleFilter',
    'RecursiveEstimatorFactory',
    
    # Particle Filter
    'ParticleFilterConfig',
    'Particle',
    'ResamplingStrategy',
    
    # Sensor Fusion
    'SensorFusionManager',
    'SensorFusionConfig',
    'SensorInfo',
    'SensorStatus',
    'FusionStrategy'
]

__version__ = "1.0.0"
__author__ = "[Your Name]"
__email__ = "[your.email@example.com]"
