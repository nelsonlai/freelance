"""
Particle Filter Implementation for Quadrotor State Estimation
===========================================================

This module implements a Particle Filter (PF) for recursive state estimation
in quadrotor control systems, providing robust estimation capabilities for
non-Gaussian noise scenarios and multi-modal distributions.

Key Features:
- Sequential Monte Carlo estimation
- Non-Gaussian noise handling
- Multi-modal state estimation
- Adaptive resampling strategies
- Effective sample size monitoring
- Performance optimization techniques

The Particle Filter is particularly useful for scenarios with:
- Non-Gaussian process or measurement noise
- Multi-modal probability distributions
- Nonlinear dynamics with high uncertainty
- Robust estimation in challenging environments

Author: [Your Name]
Date: [Current Date]
License: MIT
"""

import numpy as np
import time
import threading
from typing import Dict, List, Tuple, Optional, Callable, Any
from dataclasses import dataclass
from enum import Enum
import logging
from scipy.stats import multivariate_normal
import warnings

# Import base classes
from .recursive_estimator import (
    RecursiveEstimatorBase, EstimatorConfig, SensorMeasurement, 
    StateEstimate, SensorType, EstimatorType
)

# Configure logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class ResamplingStrategy(Enum):
    """Enumeration of resampling strategies."""
    SYSTEMATIC = "systematic"
    MULTINOMIAL = "multinomial"
    RESIDUAL = "residual"
    STRATIFIED = "stratified"


@dataclass
class ParticleFilterConfig(EstimatorConfig):
    """
    Configuration for Particle Filter.
    
    Attributes:
        num_particles (int): Number of particles
        resampling_strategy (ResamplingStrategy): Resampling strategy
        resampling_threshold (float): Effective sample size threshold for resampling
        process_noise_scale (float): Scale factor for process noise
        measurement_noise_scale (float): Scale factor for measurement noise
        enable_adaptive_resampling (bool): Enable adaptive resampling
        enable_regularization (bool): Enable particle regularization
        regularization_strength (float): Regularization strength
    """
    num_particles: int = 1000
    resampling_strategy: ResamplingStrategy = ResamplingStrategy.SYSTEMATIC
    resampling_threshold: float = 0.5
    process_noise_scale: float = 1.0
    measurement_noise_scale: float = 1.0
    enable_adaptive_resampling: bool = True
    enable_regularization: bool = True
    regularization_strength: float = 0.1


class Particle:
    """
    Individual particle in the particle filter.
    
    Attributes:
        state (np.ndarray): Particle state
        weight (float): Particle weight
        timestamp (float): Particle timestamp
    """
    
    def __init__(self, state: np.ndarray, weight: float = 1.0, timestamp: float = 0.0):
        """
        Initialize particle.
        
        Args:
            state (np.ndarray): Particle state
            weight (float): Particle weight
            timestamp (float): Particle timestamp
        """
        self.state = state.copy()
        self.weight = weight
        self.timestamp = timestamp


class ParticleFilter(RecursiveEstimatorBase):
    """
    Particle Filter implementation for recursive state estimation.
    
    The Particle Filter uses sequential Monte Carlo methods to estimate
    the state of a system by maintaining a set of weighted particles
    that represent the posterior probability distribution.
    """
    
    def __init__(self, config: ParticleFilterConfig):
        """
        Initialize Particle Filter.
        
        Args:
            config (ParticleFilterConfig): Particle Filter configuration
        """
        # Initialize base class with modified config
        base_config = EstimatorConfig(
            estimator_type=EstimatorType.PARTICLE,
            state_dimension=config.state_dimension,
            process_noise_covariance=config.process_noise_covariance,
            initial_state=config.initial_state,
            initial_covariance=config.initial_covariance,
            sensor_configs=config.sensor_configs,
            update_rate=config.update_rate,
            enable_adaptive_noise=config.enable_adaptive_noise,
            enable_outlier_detection=config.enable_outlier_detection,
            outlier_threshold=config.outlier_threshold
        )
        
        super().__init__(base_config)
        
        # Particle Filter specific configuration
        self.pf_config = config
        self.num_particles = config.num_particles
        
        # Initialize particles
        self.particles: List[Particle] = []
        self._initialize_particles()
        
        # Resampling parameters
        self.resampling_strategy = config.resampling_strategy
        self.resampling_threshold = config.resampling_threshold
        self.enable_adaptive_resampling = config.enable_adaptive_resampling
        self.enable_regularization = config.enable_regularization
        self.regularization_strength = config.regularization_strength
        
        # Performance monitoring
        self.effective_sample_sizes = []
        self.resampling_counts = []
        self.last_resample_time = time.time()
        
        logger.info(f"Particle Filter initialized: {self.num_particles} particles")
    
    def _initialize_particles(self):
        """Initialize particles from initial distribution."""
        self.particles = []
        
        # Generate particles from initial distribution
        if self.config.initial_covariance is not None:
            # Use initial covariance for particle distribution
            try:
                # Generate particles from multivariate normal distribution
                initial_particles = np.random.multivariate_normal(
                    self.config.initial_state, 
                    self.config.initial_covariance, 
                    self.num_particles
                )
            except np.linalg.LinAlgError:
                # Fallback to uniform distribution if covariance is not positive definite
                logger.warning("Initial covariance not positive definite, using uniform distribution")
                initial_particles = np.random.uniform(
                    self.config.initial_state - 1.0,
                    self.config.initial_state + 1.0,
                    (self.num_particles, self.state_dim)
                )
        else:
            # Use uniform distribution around initial state
            initial_particles = np.random.uniform(
                self.config.initial_state - 1.0,
                self.config.initial_state + 1.0,
                (self.num_particles, self.state_dim)
            )
        
        # Create particle objects
        initial_weight = 1.0 / self.num_particles
        for i in range(self.num_particles):
            particle = Particle(
                state=initial_particles[i],
                weight=initial_weight,
                timestamp=time.time()
            )
            self.particles.append(particle)
        
        logger.info(f"Initialized {len(self.particles)} particles")
    
    def predict(self, dt: float, control_input: Optional[np.ndarray] = None) -> StateEstimate:
        """
        Predict state forward using particle filter prediction step.
        
        Args:
            dt (float): Time step
            control_input (Optional[np.ndarray]): Control input
            
        Returns:
            StateEstimate: Predicted state estimate
        """
        with self.lock:
            # Predict each particle forward
            for particle in self.particles:
                # Add process noise
                process_noise = self._generate_process_noise(dt)
                
                # Apply state transition
                particle.state = self._state_transition(particle.state, dt, control_input) + process_noise
                particle.timestamp = time.time()
            
            # Compute state estimate from particles
            self.state, self.covariance = self._compute_state_estimate()
            
            # Create estimate
            estimate = StateEstimate(
                state=self.state.copy(),
                covariance=self.covariance.copy(),
                timestamp=time.time(),
                confidence=self._compute_confidence()
            )
            
            return estimate
    
    def update(self, measurement: SensorMeasurement) -> StateEstimate:
        """
        Update state estimate using particle filter update step.
        
        Args:
            measurement (SensorMeasurement): Sensor measurement
            
        Returns:
            StateEstimate: Updated state estimate
        """
        with self.lock:
            # Update particle weights based on measurement likelihood
            self._update_particle_weights(measurement)
            
            # Normalize weights
            self._normalize_weights()
            
            # Check if resampling is needed
            effective_sample_size = self._compute_effective_sample_size()
            self.effective_sample_sizes.append(effective_sample_size)
            
            if self._should_resample(effective_sample_size):
                self._resample_particles()
                self.resampling_counts.append(time.time())
            
            # Regularize particles if enabled
            if self.enable_regularization:
                self._regularize_particles()
            
            # Compute state estimate from particles
            self.state, self.covariance = self._compute_state_estimate()
            
            # Create estimate
            estimate = StateEstimate(
                state=self.state.copy(),
                covariance=self.covariance.copy(),
                timestamp=time.time(),
                confidence=self._compute_confidence()
            )
            
            return estimate
    
    def _generate_process_noise(self, dt: float) -> np.ndarray:
        """
        Generate process noise for particle prediction.
        
        Args:
            dt (float): Time step
            
        Returns:
            np.ndarray: Process noise vector
        """
        # Scale process noise by time step and configuration
        scaled_noise = self.process_noise * dt * self.pf_config.process_noise_scale
        
        # Generate noise from multivariate normal distribution
        try:
            noise = np.random.multivariate_normal(np.zeros(self.state_dim), scaled_noise)
        except np.linalg.LinAlgError:
            # Fallback to independent Gaussian noise
            logger.warning("Process noise covariance not positive definite, using independent noise")
            noise = np.random.normal(0, np.sqrt(np.diag(scaled_noise)), self.state_dim)
        
        return noise
    
    def _state_transition(self, state: np.ndarray, dt: float, control_input: Optional[np.ndarray] = None) -> np.ndarray:
        """
        State transition function for quadrotor dynamics.
        
        Args:
            state (np.ndarray): Current state
            dt (float): Time step
            control_input (Optional[np.ndarray]): Control input
            
        Returns:
            np.ndarray: Next state
        """
        # Same as EKF/UKF implementation
        next_state = state.copy()
        
        # Position update
        next_state[0:3] = state[0:3] + state[3:6] * dt
        
        # Velocity update (simplified)
        if control_input is not None and len(control_input) >= 4:
            thrust = np.sum(control_input)
            gravity = 9.81
            
            next_state[3] = state[3] + (thrust * np.sin(state[7]) * np.cos(state[8])) * dt
            next_state[4] = state[4] + (-thrust * np.sin(state[8])) * dt
            next_state[5] = state[5] + (thrust * np.cos(state[7]) * np.cos(state[8]) - gravity) * dt
        else:
            next_state[3:6] = state[3:6]
        
        # Attitude update
        next_state[6:9] = state[6:9] + state[9:12] * dt
        
        # Angular velocity update
        next_state[9:12] = state[9:12]
        
        return next_state
    
    def _update_particle_weights(self, measurement: SensorMeasurement):
        """
        Update particle weights based on measurement likelihood.
        
        Args:
            measurement (SensorMeasurement): Sensor measurement
        """
        # Compute measurement likelihood for each particle
        for particle in self.particles:
            # Predict measurement for this particle
            predicted_measurement = self._predict_measurement(measurement.sensor_type, particle.state)
            
            # Compute innovation
            innovation = measurement.data - predicted_measurement
            
            # Compute likelihood
            likelihood = self._compute_measurement_likelihood(
                innovation, 
                measurement.covariance * self.pf_config.measurement_noise_scale
            )
            
            # Update particle weight
            particle.weight *= likelihood
        
        # Handle numerical issues
        self._handle_numerical_issues()
    
    def _compute_measurement_likelihood(self, innovation: np.ndarray, measurement_covariance: np.ndarray) -> float:
        """
        Compute measurement likelihood.
        
        Args:
            innovation (np.ndarray): Innovation vector
            measurement_covariance (np.ndarray): Measurement noise covariance
            
        Returns:
            float: Measurement likelihood
        """
        try:
            # Use multivariate normal distribution
            likelihood = multivariate_normal.pdf(innovation, mean=np.zeros_like(innovation), cov=measurement_covariance)
            
            # Handle numerical issues
            if np.isnan(likelihood) or np.isinf(likelihood):
                likelihood = 1e-10
            
            return max(likelihood, 1e-10)  # Ensure minimum likelihood
            
        except np.linalg.LinAlgError:
            # Fallback to independent Gaussian likelihood
            logger.warning("Measurement covariance not positive definite, using independent likelihood")
            likelihood = 1.0
            for i in range(len(innovation)):
                var = measurement_covariance[i, i] if measurement_covariance.ndim > 1 else measurement_covariance[i]
                likelihood *= np.exp(-0.5 * innovation[i]**2 / var) / np.sqrt(2 * np.pi * var)
            
            return max(likelihood, 1e-10)
    
    def _normalize_weights(self):
        """Normalize particle weights."""
        total_weight = sum(particle.weight for particle in self.particles)
        
        if total_weight > 0:
            for particle in self.particles:
                particle.weight /= total_weight
        else:
            # Reset weights if total weight is zero
            logger.warning("Total particle weight is zero, resetting weights")
            uniform_weight = 1.0 / len(self.particles)
            for particle in self.particles:
                particle.weight = uniform_weight
    
    def _compute_effective_sample_size(self) -> float:
        """
        Compute effective sample size.
        
        Returns:
            float: Effective sample size
        """
        weights = np.array([particle.weight for particle in self.particles])
        return 1.0 / np.sum(weights**2)
    
    def _should_resample(self, effective_sample_size: float) -> bool:
        """
        Determine if resampling should be performed.
        
        Args:
            effective_sample_size (float): Current effective sample size
            
        Returns:
            bool: True if resampling should be performed
        """
        if not self.enable_adaptive_resampling:
            return False
        
        threshold = self.resampling_threshold * self.num_particles
        return effective_sample_size < threshold
    
    def _resample_particles(self):
        """Resample particles based on their weights."""
        # Extract weights
        weights = np.array([particle.weight for particle in self.particles])
        
        # Generate new particle indices
        if self.resampling_strategy == ResamplingStrategy.SYSTEMATIC:
            indices = self._systematic_resampling(weights)
        elif self.resampling_strategy == ResamplingStrategy.MULTINOMIAL:
            indices = self._multinomial_resampling(weights)
        elif self.resampling_strategy == ResamplingStrategy.RESIDUAL:
            indices = self._residual_resampling(weights)
        elif self.resampling_strategy == ResamplingStrategy.STRATIFIED:
            indices = self._stratified_resampling(weights)
        else:
            raise ValueError(f"Unknown resampling strategy: {self.resampling_strategy}")
        
        # Create new particles
        new_particles = []
        uniform_weight = 1.0 / self.num_particles
        
        for i in range(self.num_particles):
            # Copy selected particle
            selected_particle = self.particles[indices[i]]
            new_particle = Particle(
                state=selected_particle.state.copy(),
                weight=uniform_weight,
                timestamp=time.time()
            )
            new_particles.append(new_particle)
        
        # Replace particles
        self.particles = new_particles
        self.last_resample_time = time.time()
        
        logger.debug(f"Resampled particles using {self.resampling_strategy.value} strategy")
    
    def _systematic_resampling(self, weights: np.ndarray) -> np.ndarray:
        """
        Systematic resampling.
        
        Args:
            weights (np.ndarray): Particle weights
            
        Returns:
            np.ndarray: Resampled particle indices
        """
        n = len(weights)
        cumulative_weights = np.cumsum(weights)
        
        # Generate systematic samples
        u = np.random.uniform(0, 1/n)
        indices = np.zeros(n, dtype=int)
        
        j = 0
        for i in range(n):
            while u > cumulative_weights[j]:
                j += 1
            indices[i] = j
            u += 1/n
        
        return indices
    
    def _multinomial_resampling(self, weights: np.ndarray) -> np.ndarray:
        """
        Multinomial resampling.
        
        Args:
            weights (np.ndarray): Particle weights
            
        Returns:
            np.ndarray: Resampled particle indices
        """
        return np.random.choice(len(weights), size=len(weights), p=weights, replace=True)
    
    def _residual_resampling(self, weights: np.ndarray) -> np.ndarray:
        """
        Residual resampling.
        
        Args:
            weights (np.ndarray): Particle weights
            
        Returns:
            np.ndarray: Resampled particle indices
        """
        n = len(weights)
        indices = []
        
        # Deterministic part
        for i in range(n):
            count = int(n * weights[i])
            indices.extend([i] * count)
        
        # Stochastic part
        residual_weights = n * weights - np.floor(n * weights)
        residual_weights /= np.sum(residual_weights)
        
        remaining = n - len(indices)
        if remaining > 0:
            stochastic_indices = np.random.choice(n, size=remaining, p=residual_weights, replace=True)
            indices.extend(stochastic_indices)
        
        return np.array(indices)
    
    def _stratified_resampling(self, weights: np.ndarray) -> np.ndarray:
        """
        Stratified resampling.
        
        Args:
            weights (np.ndarray): Particle weights
            
        Returns:
            np.ndarray: Resampled particle indices
        """
        n = len(weights)
        cumulative_weights = np.cumsum(weights)
        indices = np.zeros(n, dtype=int)
        
        for i in range(n):
            u = np.random.uniform(i/n, (i+1)/n)
            j = 0
            while u > cumulative_weights[j]:
                j += 1
            indices[i] = j
        
        return indices
    
    def _regularize_particles(self):
        """Regularize particles to prevent degeneracy."""
        if len(self.particles) == 0:
            return
        
        # Compute current state estimate
        current_state, current_covariance = self._compute_state_estimate()
        
        # Add small amount of noise to each particle
        regularization_noise = self.regularization_strength * current_covariance
        
        for particle in self.particles:
            try:
                noise = np.random.multivariate_normal(np.zeros(self.state_dim), regularization_noise)
                particle.state += noise
            except np.linalg.LinAlgError:
                # Fallback to independent noise
                noise = np.random.normal(0, np.sqrt(np.diag(regularization_noise)), self.state_dim)
                particle.state += noise
    
    def _compute_state_estimate(self) -> Tuple[np.ndarray, np.ndarray]:
        """
        Compute state estimate from particles.
        
        Returns:
            Tuple[np.ndarray, np.ndarray]: State estimate and covariance
        """
        if len(self.particles) == 0:
            return self.state.copy(), self.covariance.copy()
        
        # Compute weighted mean
        state_estimate = np.zeros(self.state_dim)
        for particle in self.particles:
            state_estimate += particle.weight * particle.state
        
        # Compute weighted covariance
        covariance_estimate = np.zeros((self.state_dim, self.state_dim))
        for particle in self.particles:
            diff = particle.state - state_estimate
            covariance_estimate += particle.weight * np.outer(diff, diff)
        
        return state_estimate, covariance_estimate
    
    def _handle_numerical_issues(self):
        """Handle numerical issues with particle weights."""
        # Check for NaN or infinite weights
        for particle in self.particles:
            if np.isnan(particle.weight) or np.isinf(particle.weight):
                particle.weight = 1e-10
        
        # Check if all weights are zero
        total_weight = sum(particle.weight for particle in self.particles)
        if total_weight == 0:
            logger.warning("All particle weights are zero, resetting to uniform")
            uniform_weight = 1.0 / len(self.particles)
            for particle in self.particles:
                particle.weight = uniform_weight
    
    def _compute_confidence(self) -> float:
        """
        Compute estimate confidence based on effective sample size.
        
        Returns:
            float: Confidence value (0-1)
        """
        if len(self.effective_sample_sizes) == 0:
            return 1.0
        
        # Use effective sample size as confidence measure
        effective_sample_size = self.effective_sample_sizes[-1]
        confidence = effective_sample_size / self.num_particles
        
        return min(max(confidence, 0.0), 1.0)
    
    def get_particle_statistics(self) -> Dict[str, float]:
        """
        Get particle filter statistics.
        
        Returns:
            Dict[str, float]: Particle filter statistics
        """
        if len(self.particles) == 0:
            return {}
        
        weights = np.array([particle.weight for particle in self.particles])
        
        return {
            'num_particles': len(self.particles),
            'effective_sample_size': self._compute_effective_sample_size(),
            'weight_variance': np.var(weights),
            'weight_entropy': -np.sum(weights * np.log(weights + 1e-10)),
            'resampling_count': len(self.resampling_counts),
            'last_resample_time': self.last_resample_time
        }
    
    def get_particle_cloud(self) -> np.ndarray:
        """
        Get current particle cloud.
        
        Returns:
            np.ndarray: Particle states matrix
        """
        if len(self.particles) == 0:
            return np.array([])
        
        return np.array([particle.state for particle in self.particles])
    
    def get_particle_weights(self) -> np.ndarray:
        """
        Get current particle weights.
        
        Returns:
            np.ndarray: Particle weights array
        """
        if len(self.particles) == 0:
            return np.array([])
        
        return np.array([particle.weight for particle in self.particles])
    
    def reset(self):
        """Reset particle filter state."""
        with self.lock:
            # Reset base class
            super().reset()
            
            # Reset particles
            self._initialize_particles()
            
            # Reset particle filter specific variables
            self.effective_sample_sizes.clear()
            self.resampling_counts.clear()
            self.last_resample_time = time.time()
            
            logger.info("Particle filter reset")


# Example usage and testing
if __name__ == "__main__":
    """
    Example usage of the Particle Filter.
    
    This demonstrates how to set up and use the Particle Filter for
    quadrotor state estimation with non-Gaussian noise.
    """
    
    # Initialize configuration
    config = ParticleFilterConfig(
        num_particles=1000,
        resampling_strategy=ResamplingStrategy.SYSTEMATIC,
        resampling_threshold=0.5,
        state_dimension=12,
        process_noise_covariance=np.eye(12) * 0.01,
        initial_state=np.zeros(12),
        initial_covariance=np.eye(12) * 0.1,
        update_rate=100.0,
        enable_adaptive_resampling=True,
        enable_regularization=True,
        regularization_strength=0.1
    )
    
    # Create particle filter
    particle_filter = ParticleFilter(config)
    
    # Add callbacks
    def estimate_callback(estimate):
        """Callback for state estimates."""
        print(f"State estimate: {estimate.state[:3]}, confidence: {estimate.confidence:.3f}")
    
    def error_callback(error):
        """Callback for errors."""
        print(f"Estimation error: {error}")
    
    particle_filter.add_estimate_callback(estimate_callback)
    particle_filter.add_error_callback(error_callback)
    
    # Simulate measurements with non-Gaussian noise
    print("Particle Filter Simulation")
    print("=" * 40)
    
    # Simulate IMU measurements with heavy-tailed noise
    for i in range(10):
        # Generate heavy-tailed noise (mixture of Gaussians)
        if np.random.random() < 0.1:  # 10% chance of outlier
            noise = np.random.normal(0, 1.0, 6)  # Large noise
        else:
            noise = np.random.normal(0, 0.1, 6)  # Small noise
        
        imu_measurement = SensorMeasurement(
            sensor_type=SensorType.IMU,
            data=np.array([0.1, 0.2, 0.3, 0.01, 0.02, 0.03]) + noise,
            timestamp=time.time(),
            covariance=np.eye(6) * 0.01,
            quality=0.9
        )
        
        particle_filter.add_measurement(imu_measurement)
        time.sleep(0.01)  # 100Hz
    
    # Print final statistics
    print("\n" + "=" * 40)
    print("Particle Filter Results:")
    
    stats = particle_filter.get_performance_stats()
    for key, value in stats.items():
        print(f"  {key}: {value:.3f}")
    
    pf_stats = particle_filter.get_particle_statistics()
    for key, value in pf_stats.items():
        print(f"  {key}: {value:.3f}")
    
    latest_estimate = particle_filter.get_latest_estimate()
    if latest_estimate:
        print(f"  Final state: {latest_estimate.state[:3]}")
        print(f"  Final confidence: {latest_estimate.confidence:.3f}")
    
    print(f"  Total updates: {particle_filter.update_count}")
    print(f"  Average estimation time: {np.mean(particle_filter.estimation_times):.3f}s")
