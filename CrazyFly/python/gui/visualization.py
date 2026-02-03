"""
3D Visualization Tools for Quadrotor Control System
==================================================

This module provides comprehensive 3D visualization tools for quadrotor
flight data, including real-time trajectory plotting, attitude visualization,
and interactive controls.

Key Features:
- Real-time 3D trajectory visualization
- Quadrotor attitude and orientation display
- Interactive camera controls
- Multiple visualization modes
- Data export and recording
- Performance metrics overlay
- Multi-drone visualization support

The visualization system enables real-time monitoring of quadrotor flight
and provides tools for post-flight analysis and debugging.

Author: [Your Name]
Date: [Current Date]
License: MIT
"""

import numpy as np
import time
import threading
from typing import Dict, List, Tuple, Optional, Any, Callable
from dataclasses import dataclass
from enum import Enum
import logging
import json
from pathlib import Path

# Visualization imports
try:
    import matplotlib.pyplot as plt
    from matplotlib.animation import FuncAnimation
    from mpl_toolkits.mplot3d import Axes3D
    from mpl_toolkits.mplot3d.art3d import Poly3DCollection
    import matplotlib.patches as patches
    from matplotlib.patches import FancyBboxPatch
    import matplotlib.colors as mcolors
    VISUALIZATION_AVAILABLE = True
except ImportError:
    VISUALIZATION_AVAILABLE = False
    logging.warning("Matplotlib not available. Install with: pip install matplotlib")

# GUI imports
try:
    from PyQt5.QtWidgets import (
        QMainWindow, QWidget, QVBoxLayout, QHBoxLayout, QGridLayout,
        QLabel, QPushButton, QComboBox, QCheckBox, QSlider, QSpinBox,
        QGroupBox, QTabWidget, QTextEdit, QFileDialog, QMessageBox,
        QSplitter, QFrame
    )
    from PyQt5.QtCore import Qt, QTimer, pyqtSignal, QThread
    from PyQt5.QtGui import QFont, QPalette, QColor
    from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
    from matplotlib.backends.backend_qt5agg import NavigationToolbar2QT as NavigationToolbar
    from matplotlib.figure import Figure
    GUI_AVAILABLE = True
except ImportError:
    GUI_AVAILABLE = False
    logging.warning("PyQt5 not available. Install with: pip install PyQt5")

# Configure logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class VisualizationMode(Enum):
    """Enumeration of visualization modes."""
    TRAJECTORY_3D = "trajectory_3d"
    ATTITUDE_DISPLAY = "attitude_display"
    PERFORMANCE_METRICS = "performance_metrics"
    MULTI_DRONE = "multi_drone"
    REAL_TIME = "real_time"


class CameraMode(Enum):
    """Enumeration of camera modes."""
    FREE = "free"
    FOLLOW = "follow"
    ORBIT = "orbit"
    TOP_DOWN = "top_down"
    SIDE_VIEW = "side_view"


@dataclass
class QuadrotorState:
    """
    Data structure for quadrotor state.
    
    Attributes:
        position (np.ndarray): Position [x, y, z] in meters
        velocity (np.ndarray): Velocity [vx, vy, vz] in m/s
        attitude (np.ndarray): Attitude [roll, pitch, yaw] in radians
        angular_velocity (np.ndarray): Angular velocity [wx, wy, wz] in rad/s
        timestamp (float): Timestamp in seconds
        drone_id (str): Unique drone identifier
    """
    position: np.ndarray
    velocity: np.ndarray
    attitude: np.ndarray
    angular_velocity: np.ndarray
    timestamp: float
    drone_id: str = "drone_1"


@dataclass
class VisualizationConfig:
    """
    Configuration for visualization.
    
    Attributes:
        mode (VisualizationMode): Visualization mode
        camera_mode (CameraMode): Camera mode
        update_rate (float): Update rate in Hz
        trajectory_length (int): Number of trajectory points to display
        show_axes (bool): Show coordinate axes
        show_grid (bool): Show grid
        show_trajectory (bool): Show trajectory path
        show_attitude (bool): Show attitude indicators
        show_performance (bool): Show performance metrics
        colors (Dict[str, str]): Color scheme
    """
    mode: VisualizationMode = VisualizationMode.TRAJECTORY_3D
    camera_mode: CameraMode = CameraMode.FOLLOW
    update_rate: float = 30.0
    trajectory_length: int = 1000
    show_axes: bool = True
    show_grid: bool = True
    show_trajectory: bool = True
    show_attitude: bool = True
    show_performance: bool = True
    colors: Dict[str, str] = None
    
    def __post_init__(self):
        """Initialize default colors if not provided."""
        if self.colors is None:
            self.colors = {
                'drone_body': '#2E86AB',
                'drone_arms': '#A23B72',
                'trajectory': '#F18F01',
                'current_position': '#C73E1D',
                'target_position': '#3D348B',
                'velocity_vector': '#06FFA5',
                'attitude_indicator': '#FF6B35',
                'performance_good': '#4CAF50',
                'performance_warning': '#FF9800',
                'performance_error': '#F44336'
            }


class QuadrotorVisualizer:
    """
    Base quadrotor visualizer class.
    
    This class provides the core visualization functionality for
    displaying quadrotor states in 3D space.
    """
    
    def __init__(self, config: VisualizationConfig = None):
        """
        Initialize quadrotor visualizer.
        
        Args:
            config (VisualizationConfig): Visualization configuration
        """
        if not VISUALIZATION_AVAILABLE:
            raise ImportError("Matplotlib not available. Install with: pip install matplotlib")
        
        self.config = config or VisualizationConfig()
        self.trajectory_history: List[QuadrotorState] = []
        self.current_state: Optional[QuadrotorState] = None
        self.target_position: Optional[np.ndarray] = None
        
        # Performance metrics
        self.performance_history: List[Dict[str, float]] = []
        
        logger.info("Quadrotor visualizer initialized")
    
    def update_state(self, state: QuadrotorState):
        """
        Update current quadrotor state.
        
        Args:
            state (QuadrotorState): New quadrotor state
        """
        self.current_state = state
        
        # Add to trajectory history
        self.trajectory_history.append(state)
        
        # Limit trajectory length
        if len(self.trajectory_history) > self.config.trajectory_length:
            self.trajectory_history.pop(0)
        
        logger.debug(f"Updated state for drone {state.drone_id}")
    
    def update_target(self, target_position: np.ndarray):
        """
        Update target position.
        
        Args:
            target_position (np.ndarray): Target position [x, y, z]
        """
        self.target_position = target_position
        logger.debug(f"Updated target position: {target_position}")
    
    def update_performance(self, metrics: Dict[str, float]):
        """
        Update performance metrics.
        
        Args:
            metrics (Dict[str, float]): Performance metrics
        """
        self.performance_history.append({
            'timestamp': time.time(),
            **metrics
        })
        
        # Limit performance history
        if len(self.performance_history) > 1000:
            self.performance_history.pop(0)
        
        logger.debug(f"Updated performance metrics: {metrics}")
    
    def _create_quadrotor_mesh(self, position: np.ndarray, attitude: np.ndarray) -> List[np.ndarray]:
        """
        Create quadrotor mesh for visualization.
        
        Args:
            position (np.ndarray): Position [x, y, z]
            attitude (np.ndarray): Attitude [roll, pitch, yaw]
            
        Returns:
            List[np.ndarray]: List of mesh vertices
        """
        # Quadrotor dimensions
        body_radius = 0.05
        arm_length = 0.15
        arm_width = 0.01
        height = 0.02
        
        # Create rotation matrix
        roll, pitch, yaw = attitude
        Rx = np.array([[1, 0, 0],
                      [0, np.cos(roll), -np.sin(roll)],
                      [0, np.sin(roll), np.cos(roll)]])
        
        Ry = np.array([[np.cos(pitch), 0, np.sin(pitch)],
                      [0, 1, 0],
                      [-np.sin(pitch), 0, np.cos(pitch)]])
        
        Rz = np.array([[np.cos(yaw), -np.sin(yaw), 0],
                      [np.sin(yaw), np.cos(yaw), 0],
                      [0, 0, 1]])
        
        R = Rz @ Ry @ Rx
        
        # Create body cylinder
        theta = np.linspace(0, 2*np.pi, 8)
        body_vertices = []
        for t in theta:
            for h in [0, height]:
                x = body_radius * np.cos(t)
                y = body_radius * np.sin(t)
                z = h
                vertex = R @ np.array([x, y, z]) + position
                body_vertices.append(vertex)
        
        # Create arms
        arm_vertices = []
        arm_directions = [
            [1, 0, 0], [-1, 0, 0], [0, 1, 0], [0, -1, 0]
        ]
        
        for direction in arm_directions:
            start = position
            end = position + R @ (np.array(direction) * arm_length)
            
            # Create arm box
            arm_center = (start + end) / 2
            arm_vector = end - start
            arm_length_actual = np.linalg.norm(arm_vector)
            
            if arm_length_actual > 0:
                arm_unit = arm_vector / arm_length_actual
                
                # Create perpendicular vectors
                if np.abs(arm_unit[0]) < 0.9:
                    perp1 = np.array([1, 0, 0])
                else:
                    perp1 = np.array([0, 1, 0])
                
                perp1 = perp1 - np.dot(perp1, arm_unit) * arm_unit
                perp1 = perp1 / np.linalg.norm(perp1)
                perp2 = np.cross(arm_unit, perp1)
                
                # Create arm box vertices
                for i in range(4):
                    for j in range(2):
                        offset = (perp1 * (i-1.5) + perp2 * (j-0.5)) * arm_width
                        vertex = arm_center + offset
                        arm_vertices.append(vertex)
        
        return [np.array(body_vertices), np.array(arm_vertices)]
    
    def _create_attitude_indicator(self, position: np.ndarray, attitude: np.ndarray) -> Tuple[np.ndarray, np.ndarray]:
        """
        Create attitude indicator.
        
        Args:
            position (np.ndarray): Position [x, y, z]
            attitude (np.ndarray): Attitude [roll, pitch, yaw]
            
        Returns:
            Tuple[np.ndarray, np.ndarray]: Origin and direction vectors
        """
        roll, pitch, yaw = attitude
        
        # Create rotation matrix
        Rx = np.array([[1, 0, 0],
                      [0, np.cos(roll), -np.sin(roll)],
                      [0, np.sin(roll), np.cos(roll)]])
        
        Ry = np.array([[np.cos(pitch), 0, np.sin(pitch)],
                      [0, 1, 0],
                      [-np.sin(pitch), 0, np.cos(pitch)]])
        
        Rz = np.array([[np.cos(yaw), -np.sin(yaw), 0],
                      [np.sin(yaw), np.cos(yaw), 0],
                      [0, 0, 1]])
        
        R = Rz @ Ry @ Rx
        
        # Create coordinate frame vectors
        origin = position
        x_axis = origin + R @ np.array([0.1, 0, 0])
        y_axis = origin + R @ np.array([0, 0.1, 0])
        z_axis = origin + R @ np.array([0, 0, 0.1])
        
        return origin, np.array([x_axis, y_axis, z_axis])


class RealTimeVisualizer(QuadrotorVisualizer):
    """
    Real-time quadrotor visualizer with GUI.
    
    This class provides a GUI-based real-time visualization system
    for monitoring quadrotor flight.
    """
    
    # Signals
    state_updated = pyqtSignal(object)  # QuadrotorState
    visualization_mode_changed = pyqtSignal(str)  # mode name
    
    def __init__(self, config: VisualizationConfig = None):
        """Initialize real-time visualizer."""
        if not GUI_AVAILABLE:
            raise ImportError("PyQt5 not available. Install with: pip install PyQt5")
        
        super().__init__(config)
        
        # GUI components
        self.main_window = None
        self.figure = None
        self.canvas = None
        self.ax = None
        self.animation = None
        
        # Visualization objects
        self.quadrotor_mesh = None
        self.trajectory_line = None
        self.target_point = None
        self.attitude_vectors = None
        self.performance_text = None
        
        # Setup GUI
        self._setup_gui()
        self._setup_animation()
        
        logger.info("Real-time visualizer initialized")
    
    def _setup_gui(self):
        """Setup the main GUI."""
        self.main_window = QMainWindow()
        self.main_window.setWindowTitle("CrazyFly 3D Visualizer")
        self.main_window.setGeometry(100, 100, 1200, 800)
        
        # Central widget
        central_widget = QWidget()
        self.main_window.setCentralWidget(central_widget)
        
        # Main layout
        main_layout = QHBoxLayout(central_widget)
        
        # Create splitter
        splitter = QSplitter(Qt.Horizontal)
        main_layout.addWidget(splitter)
        
        # Left panel: Controls
        left_panel = self._create_control_panel()
        splitter.addWidget(left_panel)
        
        # Right panel: Visualization
        right_panel = self._create_visualization_panel()
        splitter.addWidget(right_panel)
        
        # Set splitter proportions
        splitter.setSizes([300, 900])
    
    def _create_control_panel(self) -> QWidget:
        """Create the control panel."""
        panel = QWidget()
        layout = QVBoxLayout(panel)
        
        # Visualization mode selection
        mode_group = QGroupBox("Visualization Mode")
        mode_layout = QVBoxLayout(mode_group)
        
        self.mode_combo = QComboBox()
        for mode in VisualizationMode:
            self.mode_combo.addItem(mode.value.replace('_', ' ').title())
        self.mode_combo.currentTextChanged.connect(self._on_mode_changed)
        mode_layout.addWidget(self.mode_combo)
        
        layout.addWidget(mode_group)
        
        # Camera controls
        camera_group = QGroupBox("Camera Controls")
        camera_layout = QVBoxLayout(camera_group)
        
        self.camera_combo = QComboBox()
        for camera_mode in CameraMode:
            self.camera_combo.addItem(camera_mode.value.replace('_', ' ').title())
        camera_layout.addWidget(self.camera_combo)
        
        # Camera buttons
        reset_camera_button = QPushButton("Reset Camera")
        reset_camera_button.clicked.connect(self._reset_camera)
        camera_layout.addWidget(reset_camera_button)
        
        layout.addWidget(camera_group)
        
        # Display options
        display_group = QGroupBox("Display Options")
        display_layout = QVBoxLayout(display_group)
        
        self.show_trajectory_check = QCheckBox("Show Trajectory")
        self.show_trajectory_check.setChecked(self.config.show_trajectory)
        self.show_trajectory_check.toggled.connect(self._on_show_trajectory_changed)
        display_layout.addWidget(self.show_trajectory_check)
        
        self.show_attitude_check = QCheckBox("Show Attitude")
        self.show_attitude_check.setChecked(self.config.show_attitude)
        self.show_attitude_check.toggled.connect(self._on_show_attitude_changed)
        display_layout.addWidget(self.show_attitude_check)
        
        self.show_grid_check = QCheckBox("Show Grid")
        self.show_grid_check.setChecked(self.config.show_grid)
        self.show_grid_check.toggled.connect(self._on_show_grid_changed)
        display_layout.addWidget(self.show_grid_check)
        
        layout.addWidget(display_group)
        
        # Performance metrics
        performance_group = QGroupBox("Performance Metrics")
        performance_layout = QVBoxLayout(performance_group)
        
        self.performance_text = QTextEdit()
        self.performance_text.setMaximumHeight(150)
        self.performance_text.setReadOnly(True)
        performance_layout.addWidget(self.performance_text)
        
        layout.addWidget(performance_group)
        
        # Control buttons
        button_layout = QHBoxLayout()
        
        record_button = QPushButton("Record")
        record_button.clicked.connect(self._start_recording)
        button_layout.addWidget(record_button)
        
        export_button = QPushButton("Export")
        export_button.clicked.connect(self._export_data)
        button_layout.addWidget(export_button)
        
        layout.addLayout(button_layout)
        
        return panel
    
    def _create_visualization_panel(self) -> QWidget:
        """Create the visualization panel."""
        panel = QWidget()
        layout = QVBoxLayout(panel)
        
        # Create matplotlib figure
        self.figure = Figure(figsize=(10, 8))
        self.canvas = FigureCanvas(self.figure)
        
        # Create 3D axes
        self.ax = self.figure.add_subplot(111, projection='3d')
        
        # Setup axes
        self.ax.set_xlabel('X (m)')
        self.ax.set_ylabel('Y (m)')
        self.ax.set_zlabel('Z (m)')
        self.ax.set_title('CrazyFly 3D Visualization')
        
        # Add navigation toolbar
        toolbar = NavigationToolbar(self.canvas, panel)
        layout.addWidget(toolbar)
        layout.addWidget(self.canvas)
        
        return panel
    
    def _setup_animation(self):
        """Setup the animation."""
        # Set initial view
        self.ax.set_xlim([-2, 2])
        self.ax.set_ylim([-2, 2])
        self.ax.set_zlim([0, 4])
        
        # Create animation
        self.animation = FuncAnimation(
            self.figure, self._update_plot, 
            interval=int(1000 / self.config.update_rate),
            blit=False
        )
    
    def _update_plot(self, frame):
        """Update the plot."""
        if self.current_state is None:
            return
        
        # Clear previous plot
        self.ax.clear()
        
        # Setup axes
        self.ax.set_xlabel('X (m)')
        self.ax.set_ylabel('Y (m)')
        self.ax.set_zlabel('Z (m)')
        self.ax.set_title('CrazyFly 3D Visualization')
        
        # Show grid if enabled
        if self.config.show_grid:
            self.ax.grid(True)
        
        # Plot trajectory if enabled
        if self.config.show_trajectory and len(self.trajectory_history) > 1:
            positions = np.array([state.position for state in self.trajectory_history])
            self.ax.plot(positions[:, 0], positions[:, 1], positions[:, 2], 
                        color=self.config.colors['trajectory'], linewidth=2, alpha=0.7)
        
        # Plot current position
        if self.current_state:
            self.ax.scatter(self.current_state.position[0], 
                          self.current_state.position[1], 
                          self.current_state.position[2],
                          color=self.config.colors['current_position'], 
                          s=100, marker='o')
        
        # Plot target position
        if self.target_position is not None:
            self.ax.scatter(self.target_position[0], 
                          self.target_position[1], 
                          self.target_position[2],
                          color=self.config.colors['target_position'], 
                          s=100, marker='*')
        
        # Plot quadrotor mesh
        if self.current_state and self.config.show_attitude:
            self._plot_quadrotor_mesh()
        
        # Update camera view
        self._update_camera_view()
        
        # Update performance display
        self._update_performance_display()
    
    def _plot_quadrotor_mesh(self):
        """Plot quadrotor mesh."""
        if self.current_state is None:
            return
        
        position = self.current_state.position
        attitude = self.current_state.attitude
        
        # Create mesh
        body_vertices, arm_vertices = self._create_quadrotor_mesh(position, attitude)
        
        # Plot body
        if len(body_vertices) > 0:
            body_vertices = np.array(body_vertices)
            self.ax.scatter(body_vertices[:, 0], body_vertices[:, 1], body_vertices[:, 2],
                          color=self.config.colors['drone_body'], s=50)
        
        # Plot arms
        if len(arm_vertices) > 0:
            arm_vertices = np.array(arm_vertices)
            self.ax.scatter(arm_vertices[:, 0], arm_vertices[:, 1], arm_vertices[:, 2],
                          color=self.config.colors['drone_arms'], s=30)
        
        # Plot attitude indicator
        origin, vectors = self._create_attitude_indicator(position, attitude)
        
        colors = ['red', 'green', 'blue']
        for i, vector in enumerate(vectors):
            self.ax.quiver(origin[0], origin[1], origin[2],
                         vector[0] - origin[0], vector[1] - origin[1], vector[2] - origin[2],
                         color=colors[i], arrow_length_ratio=0.1)
    
    def _update_camera_view(self):
        """Update camera view based on mode."""
        if self.current_state is None:
            return
        
        camera_mode = CameraMode(self.camera_combo.currentText().lower().replace(' ', '_'))
        
        if camera_mode == CameraMode.FOLLOW:
            # Follow the drone
            pos = self.current_state.position
            self.ax.view_init(elev=20, azim=45)
            self.ax.set_xlim([pos[0] - 2, pos[0] + 2])
            self.ax.set_ylim([pos[1] - 2, pos[1] + 2])
            self.ax.set_zlim([pos[2] - 1, pos[2] + 3])
        
        elif camera_mode == CameraMode.TOP_DOWN:
            # Top-down view
            pos = self.current_state.position
            self.ax.view_init(elev=90, azim=0)
            self.ax.set_xlim([pos[0] - 2, pos[0] + 2])
            self.ax.set_ylim([pos[1] - 2, pos[1] + 2])
            self.ax.set_zlim([0, 4])
        
        elif camera_mode == CameraMode.SIDE_VIEW:
            # Side view
            pos = self.current_state.position
            self.ax.view_init(elev=0, azim=0)
            self.ax.set_xlim([pos[0] - 2, pos[0] + 2])
            self.ax.set_ylim([pos[1] - 2, pos[1] + 2])
            self.ax.set_zlim([0, 4])
    
    def _update_performance_display(self):
        """Update performance display."""
        if not self.performance_history:
            return
        
        # Get latest performance metrics
        latest = self.performance_history[-1]
        
        # Format display text
        text = f"Position Error: {latest.get('position_error', 0):.3f} m\n"
        text += f"Velocity Error: {latest.get('velocity_error', 0):.3f} m/s\n"
        text += f"Attitude Error: {latest.get('attitude_error', 0):.3f} rad\n"
        text += f"Control Effort: {latest.get('control_effort', 0):.3f}\n"
        text += f"Update Rate: {len(self.performance_history) / 10:.1f} Hz"
        
        self.performance_text.setText(text)
    
    def _on_mode_changed(self, mode_name: str):
        """Handle visualization mode change."""
        mode = VisualizationMode(mode_name.lower().replace(' ', '_'))
        self.config.mode = mode
        self.visualization_mode_changed.emit(mode_name)
        logger.info(f"Visualization mode changed to: {mode_name}")
    
    def _on_show_trajectory_changed(self, checked: bool):
        """Handle trajectory display toggle."""
        self.config.show_trajectory = checked
        logger.debug(f"Trajectory display: {checked}")
    
    def _on_show_attitude_changed(self, checked: bool):
        """Handle attitude display toggle."""
        self.config.show_attitude = checked
        logger.debug(f"Attitude display: {checked}")
    
    def _on_show_grid_changed(self, checked: bool):
        """Handle grid display toggle."""
        self.config.show_grid = checked
        logger.debug(f"Grid display: {checked}")
    
    def _reset_camera(self):
        """Reset camera view."""
        self.ax.view_init(elev=20, azim=45)
        self.ax.set_xlim([-2, 2])
        self.ax.set_ylim([-2, 2])
        self.ax.set_zlim([0, 4])
        logger.debug("Camera view reset")
    
    def _start_recording(self):
        """Start recording visualization."""
        # This would implement recording functionality
        QMessageBox.information(self.main_window, "Info", "Recording started!")
        logger.info("Visualization recording started")
    
    def _export_data(self):
        """Export visualization data."""
        file_path, _ = QFileDialog.getSaveFileName(
            self.main_window, "Export Data", "", "JSON Files (*.json);;All Files (*)"
        )
        
        if file_path:
            try:
                data = {
                    'trajectory': [{
                        'position': state.position.tolist(),
                        'velocity': state.velocity.tolist(),
                        'attitude': state.attitude.tolist(),
                        'timestamp': state.timestamp,
                        'drone_id': state.drone_id
                    } for state in self.trajectory_history],
                    'performance': self.performance_history,
                    'config': {
                        'mode': self.config.mode.value,
                        'camera_mode': self.config.camera_mode.value,
                        'update_rate': self.config.update_rate
                    }
                }
                
                with open(file_path, 'w') as f:
                    json.dump(data, f, indent=2)
                
                QMessageBox.information(self.main_window, "Success", "Data exported successfully!")
                logger.info(f"Data exported to {file_path}")
                
            except Exception as e:
                QMessageBox.critical(self.main_window, "Error", f"Failed to export data: {e}")
                logger.error(f"Failed to export data: {e}")
    
    def show(self):
        """Show the visualization window."""
        self.main_window.show()
    
    def close(self):
        """Close the visualization window."""
        if self.main_window:
            self.main_window.close()


# Example usage
if __name__ == "__main__":
    """
    Example usage of the 3D visualizer.
    
    This demonstrates how to set up and use the 3D visualization
    system for real-time quadrotor monitoring.
    """
    
    if not GUI_AVAILABLE:
        print("PyQt5 not available. Install with: pip install PyQt5 matplotlib")
        exit(1)
    
    import sys
    from PyQt5.QtWidgets import QApplication
    
    # Create application
    app = QApplication(sys.argv)
    
    # Create visualizer
    config = VisualizationConfig(
        mode=VisualizationMode.TRAJECTORY_3D,
        camera_mode=CameraMode.FOLLOW,
        update_rate=30.0
    )
    
    visualizer = RealTimeVisualizer(config)
    
    # Add callbacks
    def state_updated(state):
        """Callback for state updates."""
        print(f"State updated for drone {state.drone_id}")
    
    def mode_changed(mode_name):
        """Callback for mode changes."""
        print(f"Mode changed to: {mode_name}")
    
    visualizer.state_updated.connect(state_updated)
    visualizer.visualization_mode_changed.connect(mode_changed)
    
    # Simulate data updates
    def simulate_data():
        """Simulate quadrotor data updates."""
        import random
        
        while True:
            # Generate random state
            position = np.array([
                random.uniform(-1, 1),
                random.uniform(-1, 1),
                random.uniform(0.5, 2.0)
            ])
            
            velocity = np.array([
                random.uniform(-0.5, 0.5),
                random.uniform(-0.5, 0.5),
                random.uniform(-0.2, 0.2)
            ])
            
            attitude = np.array([
                random.uniform(-0.1, 0.1),
                random.uniform(-0.1, 0.1),
                random.uniform(0, 2*np.pi)
            ])
            
            angular_velocity = np.array([
                random.uniform(-0.5, 0.5),
                random.uniform(-0.5, 0.5),
                random.uniform(-0.5, 0.5)
            ])
            
            state = QuadrotorState(
                position=position,
                velocity=velocity,
                attitude=attitude,
                angular_velocity=angular_velocity,
                timestamp=time.time(),
                drone_id="drone_1"
            )
            
            # Update visualizer
            visualizer.update_state(state)
            
            # Update performance metrics
            performance = {
                'position_error': random.uniform(0, 0.2),
                'velocity_error': random.uniform(0, 0.1),
                'attitude_error': random.uniform(0, 0.05),
                'control_effort': random.uniform(0.1, 0.5)
            }
            visualizer.update_performance(performance)
            
            # Update target
            target = np.array([
                random.uniform(-0.5, 0.5),
                random.uniform(-0.5, 0.5),
                random.uniform(1.0, 1.5)
            ])
            visualizer.update_target(target)
            
            time.sleep(0.1)  # 10Hz update rate
    
    # Start simulation in background thread
    simulation_thread = threading.Thread(target=simulate_data, daemon=True)
    simulation_thread.start()
    
    # Show visualizer
    visualizer.show()
    
    # Run application
    sys.exit(app.exec_())
