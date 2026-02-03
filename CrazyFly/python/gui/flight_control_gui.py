"""
Flight Control GUI for Quadrotor Control System
==============================================

This module implements a comprehensive graphical user interface for quadrotor
flight control, providing real-time visualization, parameter tuning, and
data monitoring capabilities.

Features:
- Real-time 3D visualization of quadrotor position and attitude
- Interactive parameter tuning for control algorithms
- Real-time data plotting and monitoring
- Flight mode selection and control
- Emergency stop and safety controls
- Data logging and export functionality
- Performance metrics display

The GUI is designed to work with both the NCKU-Quadrotor-Navigation and
L1-Crazyflie projects, providing a unified interface for different control
algorithms and hardware platforms.

Author: [Your Name]
Date: [Current Date]
License: MIT
"""

import sys
import os
import time
import threading
import numpy as np
from typing import Dict, List, Tuple, Optional, Callable
from dataclasses import dataclass
from enum import Enum
import logging

# GUI Framework
try:
    from PyQt5.QtWidgets import (QApplication, QMainWindow, QWidget, QVBoxLayout, 
                                QHBoxLayout, QGridLayout, QLabel, QPushButton, 
                                QSlider, QSpinBox, QDoubleSpinBox, QComboBox,
                                QCheckBox, QGroupBox, QTabWidget, QTextEdit,
                                QProgressBar, QSplitter, QFrame, QMessageBox,
                                QFileDialog, QTableWidget, QTableWidgetItem)
    from PyQt5.QtCore import Qt, QTimer, pyqtSignal, QThread, QMutex, QWaitCondition
    from PyQt5.QtGui import QFont, QPalette, QColor, QPixmap, QPainter, QPen, QBrush
    PYQT_AVAILABLE = True
except ImportError:
    print("Warning: PyQt5 not available, GUI will not work")
    PYQT_AVAILABLE = False

# Visualization libraries
try:
    import matplotlib.pyplot as plt
    from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
    from matplotlib.figure import Figure
    from matplotlib.animation import FuncAnimation
    import matplotlib.patches as patches
    MATPLOTLIB_AVAILABLE = True
except ImportError:
    print("Warning: matplotlib not available, plotting will not work")
    MATPLOTLIB_AVAILABLE = False

# 3D Visualization
try:
    from mpl_toolkits.mplot3d import Axes3D
    MPL3D_AVAILABLE = True
except ImportError:
    print("Warning: 3D plotting not available")
    MPL3D_AVAILABLE = False

# Configure logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class FlightMode(Enum):
    """Enumeration of available flight modes."""
    MANUAL = "manual"              # Manual control mode
    HOVER = "hover"                # Hover mode
    POSITION_HOLD = "position_hold"  # Position hold mode
    TRAJECTORY = "trajectory"      # Trajectory following mode
    LANDING = "landing"            # Landing mode
    EMERGENCY = "emergency"        # Emergency mode


@dataclass
class ControlParameters:
    """Data structure for control parameters."""
    # Position control gains
    pos_kp: float = 1.0
    pos_ki: float = 0.1
    pos_kd: float = 0.5
    
    # Velocity control gains
    vel_kp: float = 2.0
    vel_ki: float = 0.2
    vel_kd: float = 1.0
    
    # Attitude control gains
    att_kp: float = 3.0
    att_ki: float = 0.0
    att_kd: float = 0.8
    
    # Attitude rate control gains
    rate_kp: float = 4.0
    rate_ki: float = 0.0
    rate_kd: float = 1.2
    
    # L1 adaptive control parameters
    l1_adaptation_rate: float = 100.0
    l1_filter_bandwidth: float = 10.0
    
    # Safety limits
    max_velocity: float = 2.0
    max_attitude: float = 30.0  # degrees
    max_thrust: float = 1.0


@dataclass
class FlightData:
    """Data structure for flight data."""
    # Position and attitude
    position: np.ndarray = None  # [x, y, z]
    velocity: np.ndarray = None  # [vx, vy, vz]
    attitude: np.ndarray = None  # [roll, pitch, yaw]
    angular_rate: np.ndarray = None  # [roll_rate, pitch_rate, yaw_rate]
    
    # Control commands
    motor_commands: np.ndarray = None  # [motor1, motor2, motor3, motor4]
    control_effort: np.ndarray = None  # [roll, pitch, yaw, thrust]
    
    # Performance metrics
    tracking_error: float = 0.0
    control_bandwidth: float = 0.0
    battery_voltage: float = 0.0
    
    # Timing
    timestamp: float = 0.0
    sequence_number: int = 0
    
    def __post_init__(self):
        if self.position is None:
            self.position = np.zeros(3)
        if self.velocity is None:
            self.velocity = np.zeros(3)
        if self.attitude is None:
            self.attitude = np.zeros(3)
        if self.angular_rate is None:
            self.angular_rate = np.zeros(3)
        if self.motor_commands is None:
            self.motor_commands = np.zeros(4)
        if self.control_effort is None:
            self.control_effort = np.zeros(4)


class DataLogger:
    """Data logging utility for flight data."""
    
    def __init__(self, filename: str = None):
        """Initialize data logger."""
        self.filename = filename or f"flight_data_{int(time.time())}.csv"
        self.data_buffer = []
        self.max_buffer_size = 10000
        self.logging_enabled = True
        
        # Create header for CSV file
        self.header = [
            'timestamp', 'sequence_number',
            'pos_x', 'pos_y', 'pos_z',
            'vel_x', 'vel_y', 'vel_z',
            'att_roll', 'att_pitch', 'att_yaw',
            'rate_roll', 'rate_pitch', 'rate_yaw',
            'motor1', 'motor2', 'motor3', 'motor4',
            'control_roll', 'control_pitch', 'control_yaw', 'control_thrust',
            'tracking_error', 'control_bandwidth', 'battery_voltage'
        ]
        
        logger.info(f"Data logger initialized: {self.filename}")
    
    def log_data(self, data: FlightData):
        """Log flight data to buffer."""
        if not self.logging_enabled:
            return
        
        # Convert data to CSV row
        row = [
            data.timestamp, data.sequence_number,
            data.position[0], data.position[1], data.position[2],
            data.velocity[0], data.velocity[1], data.velocity[2],
            data.attitude[0], data.attitude[1], data.attitude[2],
            data.angular_rate[0], data.angular_rate[1], data.angular_rate[2],
            data.motor_commands[0], data.motor_commands[1], 
            data.motor_commands[2], data.motor_commands[3],
            data.control_effort[0], data.control_effort[1],
            data.control_effort[2], data.control_effort[3],
            data.tracking_error, data.control_bandwidth, data.battery_voltage
        ]
        
        self.data_buffer.append(row)
        
        # Limit buffer size
        if len(self.data_buffer) > self.max_buffer_size:
            self.data_buffer.pop(0)
    
    def save_to_file(self):
        """Save logged data to CSV file."""
        if not self.data_buffer:
            logger.warning("No data to save")
            return
        
        try:
            with open(self.filename, 'w') as f:
                # Write header
                f.write(','.join(self.header) + '\n')
                
                # Write data
                for row in self.data_buffer:
                    f.write(','.join(map(str, row)) + '\n')
            
            logger.info(f"Data saved to {self.filename}")
        except Exception as e:
            logger.error(f"Failed to save data: {e}")
    
    def clear_buffer(self):
        """Clear the data buffer."""
        self.data_buffer.clear()
        logger.info("Data buffer cleared")


class RealTimePlotter:
    """Real-time plotting widget for flight data."""
    
    def __init__(self, parent=None):
        """Initialize real-time plotter."""
        if not MATPLOTLIB_AVAILABLE:
            self.canvas = None
            return
        
        # Create figure and canvas
        self.figure = Figure(figsize=(8, 6))
        self.canvas = FigureCanvas(self.figure)
        
        # Create subplots
        self.ax_position = self.figure.add_subplot(2, 2, 1)
        self.ax_attitude = self.figure.add_subplot(2, 2, 2)
        self.ax_motors = self.figure.add_subplot(2, 2, 3)
        self.ax_performance = self.figure.add_subplot(2, 2, 4)
        
        # Initialize data storage
        self.max_points = 1000
        self.time_data = []
        self.position_data = {'x': [], 'y': [], 'z': []}
        self.attitude_data = {'roll': [], 'pitch': [], 'yaw': []}
        self.motor_data = {'m1': [], 'm2': [], 'm3': [], 'm4': []}
        self.performance_data = {'error': [], 'bandwidth': []}
        
        # Setup plots
        self.setup_plots()
        
        # Animation
        self.animation = None
        self.animation_running = False
    
    def setup_plots(self):
        """Setup the plots with proper labels and formatting."""
        # Position plot
        self.ax_position.set_title('Position')
        self.ax_position.set_xlabel('Time (s)')
        self.ax_position.set_ylabel('Position (m)')
        self.ax_position.grid(True)
        
        # Attitude plot
        self.ax_attitude.set_title('Attitude')
        self.ax_attitude.set_xlabel('Time (s)')
        self.ax_attitude.set_ylabel('Angle (rad)')
        self.ax_attitude.grid(True)
        
        # Motor commands plot
        self.ax_motors.set_title('Motor Commands')
        self.ax_motors.set_xlabel('Time (s)')
        self.ax_motors.set_ylabel('PWM Value')
        self.ax_motors.grid(True)
        
        # Performance plot
        self.ax_performance.set_title('Performance Metrics')
        self.ax_performance.set_xlabel('Time (s)')
        self.ax_performance.set_ylabel('Error / Bandwidth')
        self.ax_performance.grid(True)
        
        # Adjust layout
        self.figure.tight_layout()
    
    def update_data(self, data: FlightData):
        """Update plot data with new flight data."""
        if not self.animation_running:
            return
        
        # Add time data
        self.time_data.append(data.timestamp)
        
        # Add position data
        self.position_data['x'].append(data.position[0])
        self.position_data['y'].append(data.position[1])
        self.position_data['z'].append(data.position[2])
        
        # Add attitude data
        self.attitude_data['roll'].append(data.attitude[0])
        self.attitude_data['pitch'].append(data.attitude[1])
        self.attitude_data['yaw'].append(data.attitude[2])
        
        # Add motor data
        self.motor_data['m1'].append(data.motor_commands[0])
        self.motor_data['m2'].append(data.motor_commands[1])
        self.motor_data['m3'].append(data.motor_commands[2])
        self.motor_data['m4'].append(data.motor_commands[3])
        
        # Add performance data
        self.performance_data['error'].append(data.tracking_error)
        self.performance_data['bandwidth'].append(data.control_bandwidth)
        
        # Limit data points
        if len(self.time_data) > self.max_points:
            self.time_data.pop(0)
            for key in self.position_data:
                self.position_data[key].pop(0)
            for key in self.attitude_data:
                self.attitude_data[key].pop(0)
            for key in self.motor_data:
                self.motor_data[key].pop(0)
            for key in self.performance_data:
                self.performance_data[key].pop(0)
    
    def update_plots(self):
        """Update the plots with current data."""
        if not self.animation_running or not self.time_data:
            return
        
        # Clear plots
        self.ax_position.clear()
        self.ax_attitude.clear()
        self.ax_motors.clear()
        self.ax_performance.clear()
        
        # Plot position data
        self.ax_position.plot(self.time_data, self.position_data['x'], 'r-', label='X')
        self.ax_position.plot(self.time_data, self.position_data['y'], 'g-', label='Y')
        self.ax_position.plot(self.time_data, self.position_data['z'], 'b-', label='Z')
        self.ax_position.set_title('Position')
        self.ax_position.set_xlabel('Time (s)')
        self.ax_position.set_ylabel('Position (m)')
        self.ax_position.legend()
        self.ax_position.grid(True)
        
        # Plot attitude data
        self.ax_attitude.plot(self.time_data, self.attitude_data['roll'], 'r-', label='Roll')
        self.ax_attitude.plot(self.time_data, self.attitude_data['pitch'], 'g-', label='Pitch')
        self.ax_attitude.plot(self.time_data, self.attitude_data['yaw'], 'b-', label='Yaw')
        self.ax_attitude.set_title('Attitude')
        self.ax_attitude.set_xlabel('Time (s)')
        self.ax_attitude.set_ylabel('Angle (rad)')
        self.ax_attitude.legend()
        self.ax_attitude.grid(True)
        
        # Plot motor data
        self.ax_motors.plot(self.time_data, self.motor_data['m1'], 'r-', label='Motor 1')
        self.ax_motors.plot(self.time_data, self.motor_data['m2'], 'g-', label='Motor 2')
        self.ax_motors.plot(self.time_data, self.motor_data['m3'], 'b-', label='Motor 3')
        self.ax_motors.plot(self.time_data, self.motor_data['m4'], 'y-', label='Motor 4')
        self.ax_motors.set_title('Motor Commands')
        self.ax_motors.set_xlabel('Time (s)')
        self.ax_motors.set_ylabel('PWM Value')
        self.ax_motors.legend()
        self.ax_motors.grid(True)
        
        # Plot performance data
        self.ax_performance.plot(self.time_data, self.performance_data['error'], 'r-', label='Tracking Error')
        self.ax_performance.plot(self.time_data, self.performance_data['bandwidth'], 'g-', label='Bandwidth')
        self.ax_performance.set_title('Performance Metrics')
        self.ax_performance.set_xlabel('Time (s)')
        self.ax_performance.set_ylabel('Error / Bandwidth')
        self.ax_performance.legend()
        self.ax_performance.grid(True)
        
        # Update canvas
        self.canvas.draw()
    
    def start_animation(self):
        """Start the real-time animation."""
        if not MATPLOTLIB_AVAILABLE:
            return
        
        self.animation_running = True
        self.animation = FuncAnimation(self.figure, lambda x: self.update_plots(), 
                                     interval=100, blit=False)
        logger.info("Real-time plotting animation started")
    
    def stop_animation(self):
        """Stop the real-time animation."""
        self.animation_running = False
        if self.animation:
            self.animation.event_source.stop()
        logger.info("Real-time plotting animation stopped")


class ThreeDVisualizer:
    """3D visualization widget for quadrotor position and attitude."""
    
    def __init__(self, parent=None):
        """Initialize 3D visualizer."""
        if not MPL3D_AVAILABLE:
            self.canvas = None
            return
        
        # Create figure and canvas
        self.figure = Figure(figsize=(8, 6))
        self.canvas = FigureCanvas(self.figure)
        
        # Create 3D axis
        self.ax = self.figure.add_subplot(111, projection='3d')
        
        # Initialize data
        self.position_history = []
        self.max_history = 100
        
        # Setup 3D plot
        self.setup_3d_plot()
        
        # Animation
        self.animation = None
        self.animation_running = False
    
    def setup_3d_plot(self):
        """Setup the 3D plot with proper labels and formatting."""
        self.ax.set_xlabel('X (m)')
        self.ax.set_ylabel('Y (m)')
        self.ax.set_zlabel('Z (m)')
        self.ax.set_title('Quadrotor 3D Position')
        
        # Set axis limits
        self.ax.set_xlim([-5, 5])
        self.ax.set_ylim([-5, 5])
        self.ax.set_zlim([0, 10])
        
        # Add grid
        self.ax.grid(True)
    
    def update_position(self, position: np.ndarray, attitude: np.ndarray):
        """Update the 3D visualization with new position and attitude."""
        if not self.animation_running:
            return
        
        # Add position to history
        self.position_history.append(position.copy())
        
        # Limit history
        if len(self.position_history) > self.max_history:
            self.position_history.pop(0)
        
        # Clear plot
        self.ax.clear()
        
        # Plot position history
        if len(self.position_history) > 1:
            positions = np.array(self.position_history)
            self.ax.plot(positions[:, 0], positions[:, 1], positions[:, 2], 'b-', alpha=0.5)
        
        # Plot current position
        self.ax.scatter(position[0], position[1], position[2], c='red', s=100, marker='o')
        
        # Draw quadrotor body (simplified)
        self.draw_quadrotor_body(position, attitude)
        
        # Update labels and limits
        self.ax.set_xlabel('X (m)')
        self.ax.set_ylabel('Y (m)')
        self.ax.set_zlabel('Z (m)')
        self.ax.set_title('Quadrotor 3D Position')
        self.ax.grid(True)
        
        # Update canvas
        self.canvas.draw()
    
    def draw_quadrotor_body(self, position: np.ndarray, attitude: np.ndarray):
        """Draw a simplified quadrotor body representation."""
        # Body size
        body_size = 0.2
        
        # Create body corners
        corners = np.array([
            [-body_size, -body_size, 0],
            [body_size, -body_size, 0],
            [body_size, body_size, 0],
            [-body_size, body_size, 0],
            [-body_size, -body_size, body_size],
            [body_size, -body_size, body_size],
            [body_size, body_size, body_size],
            [-body_size, body_size, body_size]
        ])
        
        # Apply rotation (simplified)
        # In practice, this would use proper rotation matrices
        rotated_corners = corners + position
        
        # Draw body frame
        for i in range(4):
            # Bottom face
            self.ax.plot([rotated_corners[i, 0], rotated_corners[(i+1)%4, 0]],
                        [rotated_corners[i, 1], rotated_corners[(i+1)%4, 1]],
                        [rotated_corners[i, 2], rotated_corners[(i+1)%4, 2]], 'k-')
            
            # Top face
            self.ax.plot([rotated_corners[i+4, 0], rotated_corners[((i+1)%4)+4, 0]],
                        [rotated_corners[i+4, 1], rotated_corners[((i+1)%4)+4, 1]],
                        [rotated_corners[i+4, 2], rotated_corners[((i+1)%4)+4, 2]], 'k-')
            
            # Vertical edges
            self.ax.plot([rotated_corners[i, 0], rotated_corners[i+4, 0]],
                        [rotated_corners[i, 1], rotated_corners[i+4, 1]],
                        [rotated_corners[i, 2], rotated_corners[i+4, 2]], 'k-')
    
    def start_animation(self):
        """Start the 3D animation."""
        if not MPL3D_AVAILABLE:
            return
        
        self.animation_running = True
        self.animation = FuncAnimation(self.figure, lambda x: None, 
                                     interval=100, blit=False)
        logger.info("3D visualization animation started")
    
    def stop_animation(self):
        """Stop the 3D animation."""
        self.animation_running = False
        if self.animation:
            self.animation.event_source.stop()
        logger.info("3D visualization animation stopped")


class FlightControlGUI(QMainWindow):
    """Main flight control GUI window."""
    
    # Signals for communication with control system
    control_parameters_changed = pyqtSignal(object)  # ControlParameters
    flight_mode_changed = pyqtSignal(object)         # FlightMode
    emergency_stop_signal = pyqtSignal()
    takeoff_signal = pyqtSignal()
    landing_signal = pyqtSignal()
    
    def __init__(self):
        """Initialize the flight control GUI."""
        super().__init__()
        
        if not PYQT_AVAILABLE:
            logger.error("PyQt5 not available, GUI cannot be initialized")
            return
        
        # Initialize data structures
        self.control_params = ControlParameters()
        self.current_flight_mode = FlightMode.MANUAL
        self.data_logger = DataLogger()
        
        # Initialize visualization components
        self.plotter = RealTimePlotter()
        self.visualizer_3d = ThreeDVisualizer()
        
        # Threading
        self.update_timer = QTimer()
        self.update_timer.timeout.connect(self.update_display)
        
        # Setup UI
        self.setup_ui()
        self.setup_connections()
        
        # Start update timer
        self.update_timer.start(100)  # 10Hz update rate
        
        logger.info("Flight control GUI initialized")
    
    def setup_ui(self):
        """Setup the user interface."""
        self.setWindowTitle("CrazyFly Quadrotor Control System")
        self.setGeometry(100, 100, 1400, 900)
        
        # Create central widget
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        
        # Create main layout
        main_layout = QHBoxLayout(central_widget)
        
        # Create left panel (control panel)
        left_panel = self.create_control_panel()
        main_layout.addWidget(left_panel, 1)
        
        # Create right panel (visualization)
        right_panel = self.create_visualization_panel()
        main_layout.addWidget(right_panel, 2)
        
        # Set window properties
        self.setWindowTitle("CrazyFly Quadrotor Control System")
        self.setWindowIcon(self.style().standardIcon(self.style().SP_ComputerIcon))
    
    def create_control_panel(self):
        """Create the control panel widget."""
        panel = QWidget()
        layout = QVBoxLayout(panel)
        
        # Flight mode selection
        mode_group = QGroupBox("Flight Mode")
        mode_layout = QVBoxLayout(mode_group)
        
        self.mode_combo = QComboBox()
        for mode in FlightMode:
            self.mode_combo.addItem(mode.value.replace('_', ' ').title(), mode)
        
        mode_layout.addWidget(self.mode_combo)
        layout.addWidget(mode_group)
        
        # Control buttons
        button_group = QGroupBox("Control")
        button_layout = QGridLayout(button_group)
        
        self.takeoff_btn = QPushButton("Takeoff")
        self.landing_btn = QPushButton("Landing")
        self.emergency_btn = QPushButton("EMERGENCY STOP")
        self.emergency_btn.setStyleSheet("background-color: red; color: white; font-weight: bold;")
        
        button_layout.addWidget(self.takeoff_btn, 0, 0)
        button_layout.addWidget(self.landing_btn, 0, 1)
        button_layout.addWidget(self.emergency_btn, 1, 0, 1, 2)
        
        layout.addWidget(button_group)
        
        # Parameter tuning
        param_group = QGroupBox("Control Parameters")
        param_layout = QGridLayout(param_group)
        
        # Position control gains
        param_layout.addWidget(QLabel("Position Control:"), 0, 0)
        self.pos_kp_spin = QDoubleSpinBox()
        self.pos_kp_spin.setRange(0.0, 10.0)
        self.pos_kp_spin.setValue(self.control_params.pos_kp)
        self.pos_kp_spin.setSingleStep(0.1)
        param_layout.addWidget(QLabel("Kp:"), 1, 0)
        param_layout.addWidget(self.pos_kp_spin, 1, 1)
        
        self.pos_ki_spin = QDoubleSpinBox()
        self.pos_ki_spin.setRange(0.0, 10.0)
        self.pos_ki_spin.setValue(self.control_params.pos_ki)
        self.pos_ki_spin.setSingleStep(0.1)
        param_layout.addWidget(QLabel("Ki:"), 2, 0)
        param_layout.addWidget(self.pos_ki_spin, 2, 1)
        
        self.pos_kd_spin = QDoubleSpinBox()
        self.pos_kd_spin.setRange(0.0, 10.0)
        self.pos_kd_spin.setValue(self.control_params.pos_kd)
        self.pos_kd_spin.setSingleStep(0.1)
        param_layout.addWidget(QLabel("Kd:"), 3, 0)
        param_layout.addWidget(self.pos_kd_spin, 3, 1)
        
        # Velocity control gains
        param_layout.addWidget(QLabel("Velocity Control:"), 4, 0)
        self.vel_kp_spin = QDoubleSpinBox()
        self.vel_kp_spin.setRange(0.0, 10.0)
        self.vel_kp_spin.setValue(self.control_params.vel_kp)
        self.vel_kp_spin.setSingleStep(0.1)
        param_layout.addWidget(QLabel("Kp:"), 5, 0)
        param_layout.addWidget(self.vel_kp_spin, 5, 1)
        
        self.vel_ki_spin = QDoubleSpinBox()
        self.vel_ki_spin.setRange(0.0, 10.0)
        self.vel_ki_spin.setValue(self.control_params.vel_ki)
        self.vel_ki_spin.setSingleStep(0.1)
        param_layout.addWidget(QLabel("Ki:"), 6, 0)
        param_layout.addWidget(self.vel_ki_spin, 6, 1)
        
        self.vel_kd_spin = QDoubleSpinBox()
        self.vel_kd_spin.setRange(0.0, 10.0)
        self.vel_kd_spin.setValue(self.control_params.vel_kd)
        self.vel_kd_spin.setSingleStep(0.1)
        param_layout.addWidget(QLabel("Kd:"), 7, 0)
        param_layout.addWidget(self.vel_kd_spin, 7, 1)
        
        layout.addWidget(param_group)
        
        # Data logging
        logging_group = QGroupBox("Data Logging")
        logging_layout = QVBoxLayout(logging_group)
        
        self.logging_checkbox = QCheckBox("Enable Data Logging")
        self.logging_checkbox.setChecked(True)
        
        self.save_data_btn = QPushButton("Save Data")
        self.clear_data_btn = QPushButton("Clear Data")
        
        logging_layout.addWidget(self.logging_checkbox)
        logging_layout.addWidget(self.save_data_btn)
        logging_layout.addWidget(self.clear_data_btn)
        
        layout.addWidget(logging_group)
        
        # Status display
        status_group = QGroupBox("Status")
        status_layout = QGridLayout(status_group)
        
        self.status_labels = {}
        status_items = ['Flight Mode', 'Battery', 'Connection', 'Control Status']
        
        for i, item in enumerate(status_items):
            status_layout.addWidget(QLabel(f"{item}:"), i, 0)
            self.status_labels[item] = QLabel("Unknown")
            self.status_labels[item].setStyleSheet("background-color: gray; padding: 2px;")
            status_layout.addWidget(self.status_labels[item], i, 1)
        
        layout.addWidget(status_group)
        
        # Add stretch to push everything to the top
        layout.addStretch()
        
        return panel
    
    def create_visualization_panel(self):
        """Create the visualization panel widget."""
        panel = QWidget()
        layout = QVBoxLayout(panel)
        
        # Create tab widget for different visualizations
        tab_widget = QTabWidget()
        
        # Real-time plots tab
        if self.plotter.canvas:
            tab_widget.addTab(self.plotter.canvas, "Real-time Plots")
        
        # 3D visualization tab
        if self.visualizer_3d.canvas:
            tab_widget.addTab(self.visualizer_3d.canvas, "3D Visualization")
        
        # Performance metrics tab
        metrics_widget = self.create_metrics_widget()
        tab_widget.addTab(metrics_widget, "Performance Metrics")
        
        layout.addWidget(tab_widget)
        
        return panel
    
    def create_metrics_widget(self):
        """Create the performance metrics widget."""
        widget = QWidget()
        layout = QVBoxLayout(widget)
        
        # Performance metrics table
        self.metrics_table = QTableWidget()
        self.metrics_table.setColumnCount(2)
        self.metrics_table.setHorizontalHeaderLabels(['Metric', 'Value'])
        
        # Add metrics rows
        metrics = ['Tracking Error', 'Control Bandwidth', 'Position Error', 
                  'Attitude Error', 'Motor Variance', 'Battery Voltage']
        
        self.metrics_table.setRowCount(len(metrics))
        for i, metric in enumerate(metrics):
            self.metrics_table.setItem(i, 0, QTableWidgetItem(metric))
            self.metrics_table.setItem(i, 1, QTableWidgetItem("0.0"))
        
        layout.addWidget(self.metrics_table)
        
        return widget
    
    def setup_connections(self):
        """Setup signal connections."""
        # Flight mode changes
        self.mode_combo.currentIndexChanged.connect(self.on_flight_mode_changed)
        
        # Control buttons
        self.takeoff_btn.clicked.connect(self.on_takeoff_clicked)
        self.landing_btn.clicked.connect(self.on_landing_clicked)
        self.emergency_btn.clicked.connect(self.on_emergency_clicked)
        
        # Parameter changes
        self.pos_kp_spin.valueChanged.connect(self.on_parameter_changed)
        self.pos_ki_spin.valueChanged.connect(self.on_parameter_changed)
        self.pos_kd_spin.valueChanged.connect(self.on_parameter_changed)
        self.vel_kp_spin.valueChanged.connect(self.on_parameter_changed)
        self.vel_ki_spin.valueChanged.connect(self.on_parameter_changed)
        self.vel_kd_spin.valueChanged.connect(self.on_parameter_changed)
        
        # Data logging
        self.logging_checkbox.toggled.connect(self.on_logging_toggled)
        self.save_data_btn.clicked.connect(self.on_save_data_clicked)
        self.clear_data_btn.clicked.connect(self.on_clear_data_clicked)
    
    def on_flight_mode_changed(self):
        """Handle flight mode change."""
        mode = self.mode_combo.currentData()
        self.current_flight_mode = mode
        self.flight_mode_changed.emit(mode)
        
        # Update status
        self.status_labels['Flight Mode'].setText(mode.value.replace('_', ' ').title())
        self.status_labels['Flight Mode'].setStyleSheet("background-color: green; color: white; padding: 2px;")
        
        logger.info(f"Flight mode changed to: {mode.value}")
    
    def on_takeoff_clicked(self):
        """Handle takeoff button click."""
        self.takeoff_signal.emit()
        logger.info("Takeoff signal sent")
    
    def on_landing_clicked(self):
        """Handle landing button click."""
        self.landing_signal.emit()
        logger.info("Landing signal sent")
    
    def on_emergency_clicked(self):
        """Handle emergency stop button click."""
        reply = QMessageBox.question(self, 'Emergency Stop', 
                                   'Are you sure you want to emergency stop?',
                                   QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
        
        if reply == QMessageBox.Yes:
            self.emergency_stop_signal.emit()
            self.status_labels['Control Status'].setText("EMERGENCY STOP")
            self.status_labels['Control Status'].setStyleSheet("background-color: red; color: white; padding: 2px;")
            logger.warning("Emergency stop activated")
    
    def on_parameter_changed(self):
        """Handle parameter changes."""
        # Update control parameters
        self.control_params.pos_kp = self.pos_kp_spin.value()
        self.control_params.pos_ki = self.pos_ki_spin.value()
        self.control_params.pos_kd = self.pos_kd_spin.value()
        self.control_params.vel_kp = self.vel_kp_spin.value()
        self.control_params.vel_ki = self.vel_ki_spin.value()
        self.control_params.vel_kd = self.vel_kd_spin.value()
        
        # Emit signal
        self.control_parameters_changed.emit(self.control_params)
        
        logger.debug("Control parameters updated")
    
    def on_logging_toggled(self, enabled):
        """Handle logging toggle."""
        self.data_logger.logging_enabled = enabled
        logger.info(f"Data logging {'enabled' if enabled else 'disabled'}")
    
    def on_save_data_clicked(self):
        """Handle save data button click."""
        filename, _ = QFileDialog.getSaveFileName(self, "Save Flight Data", 
                                                f"flight_data_{int(time.time())}.csv",
                                                "CSV Files (*.csv)")
        if filename:
            self.data_logger.filename = filename
            self.data_logger.save_to_file()
    
    def on_clear_data_clicked(self):
        """Handle clear data button click."""
        self.data_logger.clear_buffer()
        logger.info("Flight data cleared")
    
    def update_flight_data(self, data: FlightData):
        """Update the GUI with new flight data."""
        # Update visualizations
        if self.plotter:
            self.plotter.update_data(data)
        
        if self.visualizer_3d:
            self.visualizer_3d.update_position(data.position, data.attitude)
        
        # Log data
        self.data_logger.log_data(data)
        
        # Update status
        self.status_labels['Battery'].setText(f"{data.battery_voltage:.1f}V")
        self.status_labels['Connection'].setText("Connected")
        self.status_labels['Connection'].setStyleSheet("background-color: green; color: white; padding: 2px;")
        
        # Update metrics table
        if self.metrics_table:
            self.metrics_table.setItem(0, 1, QTableWidgetItem(f"{data.tracking_error:.3f}"))
            self.metrics_table.setItem(1, 1, QTableWidgetItem(f"{data.control_bandwidth:.1f}"))
            
            # Calculate position error
            pos_error = np.linalg.norm(data.position)
            self.metrics_table.setItem(2, 1, QTableWidgetItem(f"{pos_error:.3f}"))
            
            # Calculate attitude error
            att_error = np.linalg.norm(data.attitude)
            self.metrics_table.setItem(3, 1, QTableWidgetItem(f"{att_error:.3f}"))
            
            # Calculate motor variance
            motor_variance = np.var(data.motor_commands)
            self.metrics_table.setItem(4, 1, QTableWidgetItem(f"{motor_variance:.3f}"))
            
            # Battery voltage
            self.metrics_table.setItem(5, 1, QTableWidgetItem(f"{data.battery_voltage:.1f}"))
    
    def update_display(self):
        """Update the display (called by timer)."""
        # This method is called periodically to update the display
        # In practice, this would be connected to the control system
        pass
    
    def start_visualization(self):
        """Start the visualization animations."""
        if self.plotter:
            self.plotter.start_animation()
        
        if self.visualizer_3d:
            self.visualizer_3d.start_animation()
        
        logger.info("Visualization animations started")
    
    def stop_visualization(self):
        """Stop the visualization animations."""
        if self.plotter:
            self.plotter.stop_animation()
        
        if self.visualizer_3d:
            self.visualizer_3d.stop_animation()
        
        logger.info("Visualization animations stopped")
    
    def closeEvent(self, event):
        """Handle window close event."""
        self.stop_visualization()
        self.update_timer.stop()
        event.accept()


# Example usage
if __name__ == "__main__":
    if not PYQT_AVAILABLE:
        print("PyQt5 not available, cannot run GUI")
        sys.exit(1)
    
    app = QApplication(sys.argv)
    
    # Create and show the GUI
    gui = FlightControlGUI()
    gui.show()
    
    # Start visualization
    gui.start_visualization()
    
    # Simulate some flight data updates
    def simulate_data():
        """Simulate flight data for demonstration."""
        import time
        
        start_time = time.time()
        while True:
            # Create simulated flight data
            data = FlightData()
            data.timestamp = time.time() - start_time
            data.sequence_number += 1
            
            # Simulate position (circular motion)
            t = data.timestamp
            data.position = np.array([2 * np.cos(t), 2 * np.sin(t), 1.0 + 0.5 * np.sin(2*t)])
            data.velocity = np.array([-2 * np.sin(t), 2 * np.cos(t), np.cos(2*t)])
            data.attitude = np.array([0.1 * np.sin(t), 0.1 * np.cos(t), t % (2*np.pi)])
            data.angular_rate = np.array([0.1 * np.cos(t), -0.1 * np.sin(t), 1.0])
            
            # Simulate motor commands
            data.motor_commands = np.array([0.5, 0.5, 0.5, 0.5]) + 0.1 * np.random.randn(4)
            data.motor_commands = np.clip(data.motor_commands, 0.0, 1.0)
            
            # Simulate control effort
            data.control_effort = np.array([0.1, 0.1, 0.1, 0.5])
            
            # Simulate performance metrics
            data.tracking_error = 0.1 + 0.05 * np.sin(t)
            data.control_bandwidth = 10.0 + 2.0 * np.sin(t/10)
            data.battery_voltage = 12.0 - 0.1 * t
            
            # Update GUI
            gui.update_flight_data(data)
            
            time.sleep(0.1)  # 10Hz update rate
    
    # Start data simulation in a separate thread
    import threading
    data_thread = threading.Thread(target=simulate_data, daemon=True)
    data_thread.start()
    
    # Run the application
    sys.exit(app.exec_())
