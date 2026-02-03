"""
Visualization Module for Quadrotor Control System
================================================

This module provides comprehensive visualization capabilities for the
quadrotor control system, including 3D visualization, real-time plotting,
and data analysis tools.

Key Features:
- 3D quadrotor visualization with real-time state updates
- Multi-sensor data plotting and analysis
- Trajectory visualization and comparison
- Performance metrics visualization
- Interactive parameter tuning visualization
- Export capabilities for reports and presentations

The visualization module enables real-time monitoring and analysis of
quadrotor performance during flight and testing.

Author: [Your Name]
Date: [Current Date]
License: MIT
"""

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from mpl_toolkits.mplot3d import Axes3D
import time
import threading
from typing import Dict, List, Tuple, Optional, Callable, Any, Union
from dataclasses import dataclass
from enum import Enum
import logging
from queue import Queue
import json
import os

# Configure logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class VisualizationType(Enum):
    """Enumeration of visualization types."""
    QUADROTOR_3D = "quadrotor_3d"
    TRAJECTORY_3D = "trajectory_3d"
    SENSOR_DATA = "sensor_data"
    CONTROL_SIGNALS = "control_signals"
    PERFORMANCE_METRICS = "performance_metrics"
    PARAMETER_HISTORY = "parameter_history"


@dataclass
class VisualizationConfig:
    """
    Configuration for visualization components.
    
    Attributes:
        update_rate (float): Visualization update rate in Hz
        enable_3d_visualization (bool): Enable 3D quadrotor visualization
        enable_real_time_plotting (bool): Enable real-time data plotting
        enable_trajectory_visualization (bool): Enable trajectory visualization
        enable_performance_monitoring (bool): Enable performance monitoring
        figure_size (Tuple[int, int]): Figure size for plots
        dpi (int): DPI for high-quality plots
        save_format (str): Format for saving plots
    """
    update_rate: float = 30.0
    enable_3d_visualization: bool = True
    enable_real_time_plotting: bool = True
    enable_trajectory_visualization: bool = True
    enable_performance_monitoring: bool = True
    figure_size: Tuple[int, int] = (12, 8)
    dpi: int = 100
    save_format: str = "png"


class Quadrotor3DVisualizer:
    """
    3D visualization of quadrotor state and dynamics.
    
    This class provides real-time 3D visualization of the quadrotor,
    including position, orientation, and motor states.
    """
    
    def __init__(self, config: VisualizationConfig):
        """
        Initialize 3D quadrotor visualizer.
        
        Args:
            config (VisualizationConfig): Visualization configuration
        """
        self.config = config
        
        # 3D figure and axes
        self.fig = None
        self.ax = None
        
        # Quadrotor geometry
        self.arm_length = 0.046  # meters
        self.body_radius = 0.02  # meters
        self.propeller_radius = 0.015  # meters
        
        # Visualization objects
        self.body = None
        self.arms = []
        self.propellers = []
        self.trajectory_line = None
        self.reference_trajectory = None
        
        # Data storage
        self.position_history = []
        self.orientation_history = []
        self.trajectory_data = []
        
        # Animation
        self.animation = None
        self.is_running = False
        
        logger.info("3D quadrotor visualizer initialized")
    
    def setup_visualization(self):
        """Setup 3D visualization environment."""
        # Create figure and 3D axes
        self.fig = plt.figure(figsize=self.config.figure_size, dpi=self.config.dpi)
        self.ax = self.fig.add_subplot(111, projection='3d')
        
        # Set axis labels and title
        self.ax.set_xlabel('X (m)')
        self.ax.set_ylabel('Y (m)')
        self.ax.set_zlabel('Z (m)')
        self.ax.set_title('Quadrotor 3D Visualization')
        
        # Set axis limits
        self.ax.set_xlim([-2, 2])
        self.ax.set_ylim([-2, 2])
        self.ax.set_zlim([0, 4])
        
        # Create quadrotor geometry
        self._create_quadrotor_geometry()
        
        # Create trajectory line
        self.trajectory_line, = self.ax.plot([], [], [], 'b-', linewidth=2, alpha=0.7)
        
        logger.info("3D visualization environment setup complete")
    
    def _create_quadrotor_geometry(self):
        """Create quadrotor geometric elements."""
        # Create body (central sphere)
        u = np.linspace(0, 2 * np.pi, 20)
        v = np.linspace(0, np.pi, 20)
        x = self.body_radius * np.outer(np.cos(u), np.sin(v))
        y = self.body_radius * np.outer(np.sin(u), np.sin(v))
        z = self.body_radius * np.outer(np.ones(np.size(u)), np.cos(v))
        
        self.body = self.ax.plot_surface(x, y, z, color='gray', alpha=0.8)
        
        # Create arms (lines from center to propellers)
        arm_positions = [
            [self.arm_length, 0, 0],    # Front
            [-self.arm_length, 0, 0],   # Back
            [0, self.arm_length, 0],    # Right
            [0, -self.arm_length, 0]    # Left
        ]
        
        for pos in arm_positions:
            arm, = self.ax.plot([0, pos[0]], [0, pos[1]], [0, pos[2]], 'k-', linewidth=3)
            self.arms.append(arm)
        
        # Create propellers (circles at arm ends)
        for pos in arm_positions:
            theta = np.linspace(0, 2 * np.pi, 20)
            x_prop = pos[0] + self.propeller_radius * np.cos(theta)
            y_prop = pos[1] + self.propeller_radius * np.sin(theta)
            z_prop = pos[2] * np.ones_like(theta)
            
            prop, = self.ax.plot(x_prop, y_prop, z_prop, 'r-', linewidth=2)
            self.propellers.append(prop)
    
    def update_quadrotor_state(self, position: np.ndarray, orientation: np.ndarray, 
                              motor_speeds: Optional[np.ndarray] = None):
        """
        Update quadrotor state in visualization.
        
        Args:
            position (np.ndarray): Position [x, y, z]
            orientation (np.ndarray): Orientation [roll, pitch, yaw]
            motor_speeds (Optional[np.ndarray]): Motor speeds [m1, m2, m3, m4]
        """
        # Store history
        self.position_history.append(position.copy())
        self.orientation_history.append(orientation.copy())
        
        # Keep history size manageable
        max_history = 1000
        if len(self.position_history) > max_history:
            self.position_history.pop(0)
            self.orientation_history.pop(0)
        
        # Update trajectory line
        if len(self.position_history) > 1:
            positions = np.array(self.position_history)
            self.trajectory_line.set_data(positions[:, 0], positions[:, 1])
            self.trajectory_line.set_3d_properties(positions[:, 2])
        
        # Update quadrotor position and orientation
        self._update_quadrotor_geometry(position, orientation)
        
        # Update motor visualization if speeds provided
        if motor_speeds is not None:
            self._update_motor_visualization(motor_speeds)
    
    def _update_quadrotor_geometry(self, position: np.ndarray, orientation: np.ndarray):
        """Update quadrotor geometric elements with new state."""
        # Extract orientation angles
        roll, pitch, yaw = orientation
        
        # Create rotation matrices
        Rx = np.array([[1, 0, 0],
                      [0, np.cos(roll), -np.sin(roll)],
                      [0, np.sin(roll), np.cos(roll)]])
        
        Ry = np.array([[np.cos(pitch), 0, np.sin(pitch)],
                      [0, 1, 0],
                      [-np.sin(pitch), 0, np.cos(pitch)]])
        
        Rz = np.array([[np.cos(yaw), -np.sin(yaw), 0],
                      [np.sin(yaw), np.cos(yaw), 0],
                      [0, 0, 1]])
        
        # Combined rotation matrix
        R = Rz @ Ry @ Rx
        
        # Update body position
        self.ax.view_init(elev=20, azim=45)  # Set viewing angle
        
        # Update arms
        arm_positions = [
            [self.arm_length, 0, 0],    # Front
            [-self.arm_length, 0, 0],   # Back
            [0, self.arm_length, 0],    # Right
            [0, -self.arm_length, 0]    # Left
        ]
        
        for i, pos in enumerate(arm_positions):
            # Rotate arm position
            rotated_pos = R @ np.array(pos)
            translated_pos = rotated_pos + position
            
            # Update arm line
            self.arms[i].set_data([position[0], translated_pos[0]], 
                                 [position[1], translated_pos[1]])
            self.arms[i].set_3d_properties([position[2], translated_pos[2]])
            
            # Update propeller
            theta = np.linspace(0, 2 * np.pi, 20)
            x_prop = translated_pos[0] + self.propeller_radius * np.cos(theta)
            y_prop = translated_pos[1] + self.propeller_radius * np.sin(theta)
            z_prop = translated_pos[2] * np.ones_like(theta)
            
            self.propellers[i].set_data(x_prop, y_prop)
            self.propellers[i].set_3d_properties(z_prop)
    
    def _update_motor_visualization(self, motor_speeds: np.ndarray):
        """Update motor visualization based on speeds."""
        # Normalize motor speeds for visualization
        max_speed = np.max(motor_speeds) if np.max(motor_speeds) > 0 else 1.0
        normalized_speeds = motor_speeds / max_speed
        
        # Update propeller colors based on speed
        colors = ['red', 'blue', 'green', 'orange']
        for i, (prop, speed) in enumerate(zip(self.propellers, normalized_speeds)):
            alpha = 0.3 + 0.7 * speed  # Vary transparency with speed
            prop.set_color(colors[i])
            prop.set_alpha(alpha)
    
    def set_reference_trajectory(self, trajectory: np.ndarray):
        """
        Set reference trajectory for visualization.
        
        Args:
            trajectory (np.ndarray): Reference trajectory points [N, 3]
        """
        self.reference_trajectory = trajectory
        
        # Plot reference trajectory
        if self.reference_trajectory is not None:
            self.ax.plot(trajectory[:, 0], trajectory[:, 1], trajectory[:, 2], 
                        'g--', linewidth=2, alpha=0.5, label='Reference')
            self.ax.legend()
    
    def start_animation(self):
        """Start real-time animation."""
        if self.is_running:
            logger.warning("Animation already running")
            return
        
        self.is_running = True
        
        # Create animation
        self.animation = FuncAnimation(
            self.fig, self._animation_update, 
            interval=1000/self.config.update_rate,  # milliseconds
            blit=False
        )
        
        plt.show()
        
        logger.info("3D animation started")
    
    def _animation_update(self, frame):
        """Animation update function."""
        # This function is called by FuncAnimation
        # The actual state updates are handled by update_quadrotor_state
        return []
    
    def stop_animation(self):
        """Stop real-time animation."""
        self.is_running = False
        
        if self.animation:
            self.animation.event_source.stop()
        
        logger.info("3D animation stopped")
    
    def save_visualization(self, filename: str):
        """
        Save current visualization to file.
        
        Args:
            filename (str): Output filename
        """
        if self.fig:
            self.fig.savefig(filename, dpi=self.config.dpi, bbox_inches='tight')
            logger.info(f"Visualization saved to {filename}")
    
    def clear_trajectory(self):
        """Clear trajectory history."""
        self.position_history.clear()
        self.orientation_history.clear()
        
        if self.trajectory_line:
            self.trajectory_line.set_data([], [])
            self.trajectory_line.set_3d_properties([])
        
        logger.info("Trajectory history cleared")


class DataVisualizer:
    """
    Real-time data visualization and plotting.
    
    This class provides comprehensive plotting capabilities for sensor data,
    control signals, and performance metrics.
    """
    
    def __init__(self, config: VisualizationConfig):
        """
        Initialize data visualizer.
        
        Args:
            config (VisualizationConfig): Visualization configuration
        """
        self.config = config
        
        # Figure and subplots
        self.fig = None
        self.axes = {}
        
        # Data storage
        self.data_queues = {}
        self.time_data = []
        
        # Plotting objects
        self.plot_lines = {}
        self.plot_objects = {}
        
        # Animation
        self.animation = None
        self.is_running = False
        
        # Callbacks
        self.update_callbacks = []
        
        logger.info("Data visualizer initialized")
    
    def setup_plots(self, plot_configs: Dict[str, Dict]):
        """
        Setup plotting environment.
        
        Args:
            plot_configs (Dict[str, Dict]): Configuration for each plot
        """
        # Create figure with subplots
        num_plots = len(plot_configs)
        self.fig, axes = plt.subplots(num_plots, 1, figsize=self.config.figure_size, dpi=self.config.dpi)
        
        if num_plots == 1:
            axes = [axes]
        
        # Setup each plot
        for i, (plot_name, config) in enumerate(plot_configs.items()):
            ax = axes[i]
            self.axes[plot_name] = ax
            
            # Configure plot
            ax.set_title(config.get('title', plot_name))
            ax.set_xlabel(config.get('xlabel', 'Time (s)'))
            ax.set_ylabel(config.get('ylabel', 'Value'))
            ax.grid(True)
            
            # Initialize data queues
            self.data_queues[plot_name] = Queue()
            
            # Initialize plot lines
            self.plot_lines[plot_name] = []
            for j, label in enumerate(config.get('data_labels', ['Data'])):
                line, = ax.plot([], [], label=label, linewidth=2)
                self.plot_lines[plot_name].append(line)
            
            # Add legend if multiple data series
            if len(config.get('data_labels', ['Data'])) > 1:
                ax.legend()
        
        plt.tight_layout()
        logger.info(f"Setup {num_plots} plots: {list(plot_configs.keys())}")
    
    def add_data(self, plot_name: str, data: np.ndarray, timestamp: float = None):
        """
        Add data to a specific plot.
        
        Args:
            plot_name (str): Name of the plot
            data (np.ndarray): Data to add
            timestamp (float): Timestamp for the data
        """
        if plot_name not in self.data_queues:
            logger.warning(f"Plot '{plot_name}' not found")
            return
        
        if timestamp is None:
            timestamp = time.time()
        
        # Add data to queue
        self.data_queues[plot_name].put((timestamp, data))
        
        # Store time data
        self.time_data.append(timestamp)
        
        # Keep time data manageable
        max_history = 1000
        if len(self.time_data) > max_history:
            self.time_data.pop(0)
    
    def start_real_time_plotting(self):
        """Start real-time plotting animation."""
        if self.is_running:
            logger.warning("Real-time plotting already running")
            return
        
        self.is_running = True
        
        # Create animation
        self.animation = FuncAnimation(
            self.fig, self._plot_update,
            interval=1000/self.config.update_rate,  # milliseconds
            blit=False
        )
        
        plt.show()
        
        logger.info("Real-time plotting started")
    
    def _plot_update(self, frame):
        """Plot update function for animation."""
        # Update each plot
        for plot_name, ax in self.axes.items():
            if plot_name in self.data_queues:
                # Get data from queue
                data_points = []
                while not self.data_queues[plot_name].empty():
                    try:
                        timestamp, data = self.data_queues[plot_name].get_nowait()
                        data_points.append((timestamp, data))
                    except:
                        break
                
                if data_points:
                    # Update plot data
                    timestamps = [point[0] for point in data_points]
                    data_values = [point[1] for point in data_points]
                    
                    # Update each line in the plot
                    for i, line in enumerate(self.plot_lines[plot_name]):
                        if i < len(data_values[0]):
                            line_data = [data[i] for data in data_values]
                            line.set_data(timestamps, line_data)
                    
                    # Update axis limits
                    ax.relim()
                    ax.autoscale_view()
        
        return []
    
    def stop_real_time_plotting(self):
        """Stop real-time plotting."""
        self.is_running = False
        
        if self.animation:
            self.animation.event_source.stop()
        
        logger.info("Real-time plotting stopped")
    
    def create_performance_plot(self, performance_data: Dict[str, List[float]]):
        """
        Create performance metrics visualization.
        
        Args:
            performance_data (Dict[str, List[float]]): Performance data
        """
        if not performance_data:
            return
        
        # Create subplots for different metrics
        num_metrics = len(performance_data)
        fig, axes = plt.subplots(num_metrics, 1, figsize=self.config.figure_size, dpi=self.config.dpi)
        
        if num_metrics == 1:
            axes = [axes]
        
        for i, (metric_name, values) in enumerate(performance_data.items()):
            ax = axes[i]
            
            # Plot metric
            time_points = np.arange(len(values))
            ax.plot(time_points, values, 'b-', linewidth=2)
            ax.set_title(f'{metric_name} Performance')
            ax.set_xlabel('Time Steps')
            ax.set_ylabel(metric_name)
            ax.grid(True)
            
            # Add statistics
            mean_val = np.mean(values)
            std_val = np.std(values)
            ax.axhline(y=mean_val, color='r', linestyle='--', alpha=0.7, 
                      label=f'Mean: {mean_val:.3f}')
            ax.fill_between(time_points, mean_val - std_val, mean_val + std_val, 
                           alpha=0.2, color='r', label=f'±1σ: {std_val:.3f}')
            ax.legend()
        
        plt.tight_layout()
        plt.show()
        
        logger.info(f"Performance plot created for {num_metrics} metrics")
    
    def create_trajectory_comparison(self, actual_trajectory: np.ndarray, 
                                   reference_trajectory: np.ndarray,
                                   labels: List[str] = None):
        """
        Create trajectory comparison visualization.
        
        Args:
            actual_trajectory (np.ndarray): Actual trajectory [N, 3]
            reference_trajectory (np.ndarray): Reference trajectory [N, 3]
            labels (List[str]): Labels for the trajectories
        """
        if labels is None:
            labels = ['Actual', 'Reference']
        
        # Create 3D plot
        fig = plt.figure(figsize=self.config.figure_size, dpi=self.config.dpi)
        ax = fig.add_subplot(111, projection='3d')
        
        # Plot trajectories
        ax.plot(actual_trajectory[:, 0], actual_trajectory[:, 1], actual_trajectory[:, 2], 
                'b-', linewidth=2, label=labels[0])
        ax.plot(reference_trajectory[:, 0], reference_trajectory[:, 1], reference_trajectory[:, 2], 
                'r--', linewidth=2, label=labels[1])
        
        # Configure plot
        ax.set_xlabel('X (m)')
        ax.set_ylabel('Y (m)')
        ax.set_zlabel('Z (m)')
        ax.set_title('Trajectory Comparison')
        ax.legend()
        ax.grid(True)
        
        plt.show()
        
        logger.info("Trajectory comparison plot created")
    
    def save_plots(self, filename: str):
        """
        Save current plots to file.
        
        Args:
            filename (str): Output filename
        """
        if self.fig:
            self.fig.savefig(filename, dpi=self.config.dpi, bbox_inches='tight')
            logger.info(f"Plots saved to {filename}")
    
    def add_update_callback(self, callback: Callable):
        """
        Add callback for plot updates.
        
        Args:
            callback (Callable): Function to call on plot updates
        """
        self.update_callbacks.append(callback)


class VisualizationManager:
    """
    Main visualization manager for coordinating all visualization components.
    
    This class provides a unified interface for all visualization capabilities
    and manages the coordination between different visualization components.
    """
    
    def __init__(self, config: VisualizationConfig):
        """
        Initialize visualization manager.
        
        Args:
            config (VisualizationConfig): Visualization configuration
        """
        self.config = config
        
        # Visualization components
        self.quadrotor_visualizer = None
        self.data_visualizer = None
        
        # Data storage
        self.visualization_data = {}
        self.performance_metrics = {}
        
        # Threading
        self.visualization_thread = None
        self.is_running = False
        
        # Callbacks
        self.data_callbacks = []
        self.error_callbacks = []
        
        logger.info("Visualization manager initialized")
    
    def setup_visualization(self):
        """Setup all visualization components."""
        # Setup 3D quadrotor visualization
        if self.config.enable_3d_visualization:
            self.quadrotor_visualizer = Quadrotor3DVisualizer(self.config)
            self.quadrotor_visualizer.setup_visualization()
        
        # Setup data visualization
        if self.config.enable_real_time_plotting:
            self.data_visualizer = DataVisualizer(self.config)
            
            # Define plot configurations
            plot_configs = {
                'position': {
                    'title': 'Position',
                    'xlabel': 'Time (s)',
                    'ylabel': 'Position (m)',
                    'data_labels': ['X', 'Y', 'Z']
                },
                'velocity': {
                    'title': 'Velocity',
                    'xlabel': 'Time (s)',
                    'ylabel': 'Velocity (m/s)',
                    'data_labels': ['Vx', 'Vy', 'Vz']
                },
                'attitude': {
                    'title': 'Attitude',
                    'xlabel': 'Time (s)',
                    'ylabel': 'Angle (rad)',
                    'data_labels': ['Roll', 'Pitch', 'Yaw']
                },
                'control_signals': {
                    'title': 'Control Signals',
                    'xlabel': 'Time (s)',
                    'ylabel': 'Signal',
                    'data_labels': ['Motor 1', 'Motor 2', 'Motor 3', 'Motor 4']
                }
            }
            
            self.data_visualizer.setup_plots(plot_configs)
        
        logger.info("Visualization setup complete")
    
    def start_visualization(self):
        """Start all visualization components."""
        if self.is_running:
            logger.warning("Visualization already running")
            return
        
        self.is_running = True
        
        # Start visualization thread
        self.visualization_thread = threading.Thread(target=self._visualization_loop, daemon=True)
        self.visualization_thread.start()
        
        # Start 3D visualization
        if self.quadrotor_visualizer:
            self.quadrotor_visualizer.start_animation()
        
        # Start data visualization
        if self.data_visualizer:
            self.data_visualizer.start_real_time_plotting()
        
        logger.info("Visualization started")
    
    def stop_visualization(self):
        """Stop all visualization components."""
        self.is_running = False
        
        # Stop 3D visualization
        if self.quadrotor_visualizer:
            self.quadrotor_visualizer.stop_animation()
        
        # Stop data visualization
        if self.data_visualizer:
            self.data_visualizer.stop_real_time_plotting()
        
        logger.info("Visualization stopped")
    
    def _visualization_loop(self):
        """Main visualization loop."""
        while self.is_running:
            try:
                # Process visualization data
                self._process_visualization_data()
                
                # Sleep to maintain update rate
                time.sleep(1.0 / self.config.update_rate)
                
            except Exception as e:
                logger.error(f"Error in visualization loop: {e}")
                # Call error callbacks
                for callback in self.error_callbacks:
                    try:
                        callback(e)
                    except Exception as callback_error:
                        logger.error(f"Error in error callback: {callback_error}")
    
    def _process_visualization_data(self):
        """Process and update visualization data."""
        # This function would process data from queues and update visualizations
        # Implementation depends on data sources and requirements
        pass
    
    def update_quadrotor_state(self, position: np.ndarray, orientation: np.ndarray, 
                              motor_speeds: Optional[np.ndarray] = None):
        """
        Update quadrotor state in visualization.
        
        Args:
            position (np.ndarray): Position [x, y, z]
            orientation (np.ndarray): Orientation [roll, pitch, yaw]
            motor_speeds (Optional[np.ndarray]): Motor speeds [m1, m2, m3, m4]
        """
        if self.quadrotor_visualizer:
            self.quadrotor_visualizer.update_quadrotor_state(position, orientation, motor_speeds)
        
        # Update data visualizer
        if self.data_visualizer:
            timestamp = time.time()
            self.data_visualizer.add_data('position', position, timestamp)
            self.data_visualizer.add_data('attitude', orientation, timestamp)
            
            if motor_speeds is not None:
                self.data_visualizer.add_data('control_signals', motor_speeds, timestamp)
    
    def update_sensor_data(self, sensor_name: str, data: np.ndarray):
        """
        Update sensor data in visualization.
        
        Args:
            sensor_name (str): Name of the sensor
            data (np.ndarray): Sensor data
        """
        if self.data_visualizer:
            timestamp = time.time()
            self.data_visualizer.add_data(sensor_name, data, timestamp)
    
    def update_performance_metrics(self, metrics: Dict[str, float]):
        """
        Update performance metrics.
        
        Args:
            metrics (Dict[str, float]): Performance metrics
        """
        timestamp = time.time()
        
        for metric_name, value in metrics.items():
            if metric_name not in self.performance_metrics:
                self.performance_metrics[metric_name] = []
            
            self.performance_metrics[metric_name].append(value)
            
            # Keep history manageable
            max_history = 1000
            if len(self.performance_metrics[metric_name]) > max_history:
                self.performance_metrics[metric_name].pop(0)
    
    def create_performance_report(self, output_dir: str = "reports"):
        """
        Create comprehensive performance report.
        
        Args:
            output_dir (str): Output directory for reports
        """
        if not os.path.exists(output_dir):
            os.makedirs(output_dir)
        
        # Create performance plots
        if self.performance_metrics:
            self.data_visualizer.create_performance_plot(self.performance_metrics)
            
            # Save performance data
            performance_file = os.path.join(output_dir, "performance_data.json")
            with open(performance_file, 'w') as f:
                json.dump(self.performance_metrics, f, indent=2)
        
        # Save visualization screenshots
        if self.quadrotor_visualizer:
            screenshot_file = os.path.join(output_dir, "quadrotor_visualization.png")
            self.quadrotor_visualizer.save_visualization(screenshot_file)
        
        if self.data_visualizer:
            plots_file = os.path.join(output_dir, "data_plots.png")
            self.data_visualizer.save_plots(plots_file)
        
        logger.info(f"Performance report created in {output_dir}")
    
    def add_data_callback(self, callback: Callable):
        """
        Add callback for data updates.
        
        Args:
            callback (Callable): Function to call on data updates
        """
        self.data_callbacks.append(callback)
    
    def add_error_callback(self, callback: Callable):
        """
        Add callback for errors.
        
        Args:
            callback (Callable): Function to call on errors
        """
        self.error_callbacks.append(callback)


# Example usage and testing
if __name__ == "__main__":
    """
    Example usage of the visualization module.
    
    This demonstrates how to set up and use the visualization components
    for quadrotor monitoring and analysis.
    """
    
    # Create visualization configuration
    config = VisualizationConfig(
        update_rate=30.0,
        enable_3d_visualization=True,
        enable_real_time_plotting=True,
        enable_trajectory_visualization=True,
        enable_performance_monitoring=True,
        figure_size=(12, 8),
        dpi=100
    )
    
    # Create visualization manager
    viz_manager = VisualizationManager(config)
    
    # Setup visualization
    viz_manager.setup_visualization()
    
    # Add callbacks
    def data_callback(data):
        """Callback for data updates."""
        print(f"Data updated: {data}")
    
    def error_callback(error):
        """Callback for errors."""
        print(f"Visualization error: {error}")
    
    viz_manager.add_data_callback(data_callback)
    viz_manager.add_error_callback(error_callback)
    
    # Start visualization
    viz_manager.start_visualization()
    
    # Simulate quadrotor data
    print("Visualization Demo")
    print("=" * 30)
    
    try:
        # Simulate flight data
        for i in range(100):
            # Generate simulated data
            time_val = i * 0.1
            position = np.array([np.sin(time_val), np.cos(time_val), 1.0 + 0.5 * np.sin(time_val)])
            orientation = np.array([0.1 * np.sin(time_val), 0.1 * np.cos(time_val), time_val])
            motor_speeds = np.array([0.25 + 0.1 * np.sin(time_val), 
                                   0.25 + 0.1 * np.cos(time_val),
                                   0.25 + 0.1 * np.sin(time_val + np.pi/2),
                                   0.25 + 0.1 * np.cos(time_val + np.pi/2)])
            
            # Update visualization
            viz_manager.update_quadrotor_state(position, orientation, motor_speeds)
            
            # Update performance metrics
            metrics = {
                'position_error': np.random.normal(0, 0.1),
                'velocity_error': np.random.normal(0, 0.05),
                'control_effort': np.sum(motor_speeds)
            }
            viz_manager.update_performance_metrics(metrics)
            
            time.sleep(0.1)  # 10Hz update rate
        
        # Create performance report
        viz_manager.create_performance_report()
        
    except KeyboardInterrupt:
        print("\nVisualization demo interrupted")
    
    finally:
        # Stop visualization
        viz_manager.stop_visualization()
        print("Visualization stopped")
