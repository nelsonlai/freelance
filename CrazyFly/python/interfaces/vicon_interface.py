"""
Vicon Motion Capture System Interface
====================================

This module provides a comprehensive interface to the Vicon motion capture system
for real-time tracking of quadrotor position and orientation. It supports multiple
subjects, data streaming, and integration with the control system.

Key Features:
- Real-time position and orientation tracking
- Multiple subject support (for multi-drone scenarios)
- Data filtering and smoothing
- Coordinate system transformations
- Automatic reconnection and error handling
- Performance monitoring and logging

The Vicon system provides high-precision optical tracking using retroreflective
markers, making it ideal for indoor quadrotor control and research.

Author: [Your Name]
Date: [Current Date]
License: MIT
"""

import numpy as np
import time
import threading
import socket
import struct
import json
from typing import Dict, List, Tuple, Optional, Callable
from dataclasses import dataclass
from enum import Enum
import logging
from queue import Queue
import cv2
from scipy.spatial.transform import Rotation
from scipy.signal import butter, filtfilt

# Configure logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class ViconDataFormat(Enum):
    """Enumeration of Vicon data formats."""
    CSV = "csv"
    JSON = "json"
    BINARY = "binary"
    UDP = "udp"


@dataclass
class ViconSubject:
    """
    Data structure for Vicon subject information.
    
    Attributes:
        name (str): Subject name/ID
        position (np.ndarray): 3D position [x, y, z] in meters
        orientation (np.ndarray): Orientation as quaternion [w, x, y, z]
        velocity (np.ndarray): Linear velocity [vx, vy, vz] in m/s
        angular_velocity (np.ndarray): Angular velocity [wx, wy, wz] in rad/s
        quality (float): Tracking quality (0-1)
        timestamp (float): Data timestamp
        visible (bool): Whether subject is currently visible
    """
    name: str
    position: np.ndarray = None
    orientation: np.ndarray = None
    velocity: np.ndarray = None
    angular_velocity: np.ndarray = None
    quality: float = 0.0
    timestamp: float = 0.0
    visible: bool = False


@dataclass
class ViconConfig:
    """
    Configuration for Vicon interface.
    
    Attributes:
        host (str): Vicon server hostname/IP
        port (int): Vicon server port
        data_format (ViconDataFormat): Data format for communication
        update_rate (int): Data update rate in Hz
        buffer_size (int): Data buffer size
        coordinate_system (str): Coordinate system transformation
        filter_enabled (bool): Enable data filtering
        filter_cutoff (float): Filter cutoff frequency
        auto_reconnect (bool): Enable automatic reconnection
        timeout (float): Connection timeout in seconds
    """
    host: str = "localhost"
    port: int = 800
    data_format: ViconDataFormat = ViconDataFormat.UDP
    update_rate: int = 100
    buffer_size: int = 1000
    coordinate_system: str = "vicon_to_ned"  # Coordinate transformation
    filter_enabled: bool = True
    filter_cutoff: float = 10.0  # Hz
    auto_reconnect: bool = True
    timeout: float = 5.0


class ViconDataFilter:
    """
    Data filtering and smoothing for Vicon measurements.
    
    This class implements various filtering techniques to improve
    the quality of Vicon position and orientation data.
    """
    
    def __init__(self, config: ViconConfig):
        """
        Initialize Vicon data filter.
        
        Args:
            config (ViconConfig): Vicon configuration
        """
        self.config = config
        self.filter_enabled = config.filter_enabled
        self.cutoff_freq = config.filter_cutoff
        self.sample_rate = config.update_rate
        
        # Filter coefficients
        self.position_filter = None
        self.orientation_filter = None
        self.velocity_filter = None
        
        # Data buffers
        self.position_buffer = []
        self.orientation_buffer = []
        self.velocity_buffer = []
        
        # Initialize filters
        if self.filter_enabled:
            self._initialize_filters()
        
        logger.info(f"Vicon data filter initialized: cutoff={self.cutoff_freq}Hz, sample_rate={self.sample_rate}Hz")
    
    def _initialize_filters(self):
        """Initialize Butterworth filters for different data types."""
        # Normalize cutoff frequency
        nyquist = self.sample_rate / 2
        normalized_cutoff = self.cutoff_freq / nyquist
        
        # Ensure cutoff is within valid range
        normalized_cutoff = min(max(normalized_cutoff, 0.001), 0.999)
        
        # Design Butterworth filter
        b, a = butter(2, normalized_cutoff, btype='low')
        
        # Store filter coefficients
        self.position_filter = (b, a)
        self.orientation_filter = (b, a)
        self.velocity_filter = (b, a)
        
        logger.debug(f"Filters initialized: normalized_cutoff={normalized_cutoff}")
    
    def filter_position(self, position: np.ndarray) -> np.ndarray:
        """
        Filter position data.
        
        Args:
            position (np.ndarray): Raw position data [x, y, z]
            
        Returns:
            np.ndarray: Filtered position data
        """
        if not self.filter_enabled or self.position_filter is None:
            return position
        
        # Add to buffer
        self.position_buffer.append(position)
        
        # Keep buffer size manageable
        if len(self.position_buffer) > 100:
            self.position_buffer.pop(0)
        
        # Apply filter if enough data
        if len(self.position_buffer) >= 10:
            b, a = self.position_filter
            data = np.array(self.position_buffer)
            
            # Apply filter to each dimension
            filtered_data = np.zeros_like(data)
            for i in range(3):
                filtered_data[:, i] = filtfilt(b, a, data[:, i])
            
            return filtered_data[-1]  # Return latest filtered value
        
        return position
    
    def filter_orientation(self, orientation: np.ndarray) -> np.ndarray:
        """
        Filter orientation data (quaternion).
        
        Args:
            orientation (np.ndarray): Raw orientation as quaternion [w, x, y, z]
            
        Returns:
            np.ndarray: Filtered orientation quaternion
        """
        if not self.filter_enabled or self.orientation_filter is None:
            return orientation
        
        # Add to buffer
        self.orientation_buffer.append(orientation)
        
        # Keep buffer size manageable
        if len(self.orientation_buffer) > 100:
            self.orientation_buffer.pop(0)
        
        # Apply filter if enough data
        if len(self.orientation_buffer) >= 10:
            b, a = self.orientation_filter
            data = np.array(self.orientation_buffer)
            
            # Apply filter to each quaternion component
            filtered_data = np.zeros_like(data)
            for i in range(4):
                filtered_data[:, i] = filtfilt(b, a, data[:, i])
            
            # Normalize quaternion
            filtered_quat = filtered_data[-1]
            filtered_quat = filtered_quat / np.linalg.norm(filtered_quat)
            
            return filtered_quat
        
        return orientation
    
    def filter_velocity(self, velocity: np.ndarray) -> np.ndarray:
        """
        Filter velocity data.
        
        Args:
            velocity (np.ndarray): Raw velocity data [vx, vy, vz]
            
        Returns:
            np.ndarray: Filtered velocity data
        """
        if not self.filter_enabled or self.velocity_filter is None:
            return velocity
        
        # Add to buffer
        self.velocity_buffer.append(velocity)
        
        # Keep buffer size manageable
        if len(self.velocity_buffer) > 100:
            self.velocity_buffer.pop(0)
        
        # Apply filter if enough data
        if len(self.velocity_buffer) >= 10:
            b, a = self.velocity_filter
            data = np.array(self.velocity_buffer)
            
            # Apply filter to each dimension
            filtered_data = np.zeros_like(data)
            for i in range(3):
                filtered_data[:, i] = filtfilt(b, a, data[:, i])
            
            return filtered_data[-1]  # Return latest filtered value
        
        return velocity
    
    def compute_velocity(self, position_history: List[np.ndarray], 
                        timestamps: List[float]) -> np.ndarray:
        """
        Compute velocity from position history.
        
        Args:
            position_history (List[np.ndarray]): Recent position measurements
            timestamps (List[float]): Corresponding timestamps
            
        Returns:
            np.ndarray: Computed velocity [vx, vy, vz]
        """
        if len(position_history) < 2:
            return np.zeros(3)
        
        # Use last two measurements for velocity estimation
        pos1 = position_history[-2]
        pos2 = position_history[-1]
        dt = timestamps[-1] - timestamps[-2]
        
        if dt <= 0:
            return np.zeros(3)
        
        velocity = (pos2 - pos1) / dt
        
        # Filter velocity
        return self.filter_velocity(velocity)
    
    def compute_angular_velocity(self, orientation_history: List[np.ndarray],
                                timestamps: List[float]) -> np.ndarray:
        """
        Compute angular velocity from orientation history.
        
        Args:
            orientation_history (List[np.ndarray]): Recent orientation measurements
            timestamps (List[float]): Corresponding timestamps
            
        Returns:
            np.ndarray: Computed angular velocity [wx, wy, wz]
        """
        if len(orientation_history) < 2:
            return np.zeros(3)
        
        # Use last two measurements for angular velocity estimation
        quat1 = orientation_history[-2]
        quat2 = orientation_history[-1]
        dt = timestamps[-1] - timestamps[-2]
        
        if dt <= 0:
            return np.zeros(3)
        
        # Compute relative rotation
        quat_rel = self._quaternion_multiply(quat2, self._quaternion_conjugate(quat1))
        
        # Convert to angular velocity (simplified)
        # For small rotations: ω ≈ 2 * q_xyz / dt
        angular_velocity = 2.0 * quat_rel[1:4] / dt
        
        return angular_velocity
    
    def _quaternion_multiply(self, q1: np.ndarray, q2: np.ndarray) -> np.ndarray:
        """Multiply two quaternions."""
        w1, x1, y1, z1 = q1
        w2, x2, y2, z2 = q2
        
        w = w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2
        x = w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2
        y = w1 * y2 - x1 * z2 + y1 * w2 + z1 * x2
        z = w1 * z2 + x1 * y2 - y1 * x2 + z1 * w2
        
        return np.array([w, x, y, z])
    
    def _quaternion_conjugate(self, q: np.ndarray) -> np.ndarray:
        """Compute quaternion conjugate."""
        return np.array([q[0], -q[1], -q[2], -q[3]])


class ViconUDPClient:
    """
    UDP client for receiving Vicon data.
    
    This class handles the low-level UDP communication with the Vicon
    system for real-time data streaming.
    """
    
    def __init__(self, config: ViconConfig):
        """
        Initialize Vicon UDP client.
        
        Args:
            config (ViconConfig): Vicon configuration
        """
        self.config = config
        self.socket = None
        self.connected = False
        self.data_queue = Queue(maxsize=config.buffer_size)
        
        # Threading
        self.receive_thread = None
        self.running = False
        
        logger.info(f"Vicon UDP client initialized: {config.host}:{config.port}")
    
    def connect(self) -> bool:
        """
        Connect to Vicon system.
        
        Returns:
            bool: True if connection successful
        """
        try:
            # Create UDP socket
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            self.socket.settimeout(self.config.timeout)
            
            # Bind to receive data
            self.socket.bind((self.config.host, self.config.port))
            
            self.connected = True
            logger.info(f"Connected to Vicon system at {self.config.host}:{self.config.port}")
            
            # Start receive thread
            self.running = True
            self.receive_thread = threading.Thread(target=self._receive_loop)
            self.receive_thread.daemon = True
            self.receive_thread.start()
            
            return True
            
        except Exception as e:
            logger.error(f"Failed to connect to Vicon: {e}")
            self.connected = False
            return False
    
    def disconnect(self):
        """Disconnect from Vicon system."""
        self.running = False
        
        if self.receive_thread:
            self.receive_thread.join(timeout=1.0)
        
        if self.socket:
            self.socket.close()
            self.socket = None
        
        self.connected = False
        logger.info("Disconnected from Vicon system")
    
    def _receive_loop(self):
        """Main receive loop for UDP data."""
        while self.running:
            try:
                # Receive data
                data, addr = self.socket.recvfrom(4096)
                
                # Parse data based on format
                if self.config.data_format == ViconDataFormat.JSON:
                    parsed_data = self._parse_json_data(data)
                elif self.config.data_format == ViconDataFormat.BINARY:
                    parsed_data = self._parse_binary_data(data)
                else:
                    parsed_data = self._parse_csv_data(data)
                
                # Add to queue (non-blocking)
                try:
                    self.data_queue.put_nowait(parsed_data)
                except:
                    # Queue full, remove oldest item
                    try:
                        self.data_queue.get_nowait()
                        self.data_queue.put_nowait(parsed_data)
                    except:
                        pass
                
            except socket.timeout:
                continue
            except Exception as e:
                logger.error(f"Error in receive loop: {e}")
                break
        
        logger.debug("Receive loop terminated")
    
    def _parse_json_data(self, data: bytes) -> Dict:
        """Parse JSON-formatted Vicon data."""
        try:
            json_str = data.decode('utf-8')
            return json.loads(json_str)
        except Exception as e:
            logger.error(f"Failed to parse JSON data: {e}")
            return {}
    
    def _parse_binary_data(self, data: bytes) -> Dict:
        """Parse binary-formatted Vicon data."""
        try:
            # Example binary format: [timestamp][num_subjects][subject_data...]
            offset = 0
            
            # Read timestamp (double)
            timestamp = struct.unpack('d', data[offset:offset+8])[0]
            offset += 8
            
            # Read number of subjects (int)
            num_subjects = struct.unpack('i', data[offset:offset+4])[0]
            offset += 4
            
            subjects = {}
            
            for i in range(num_subjects):
                # Read subject name length (int)
                name_len = struct.unpack('i', data[offset:offset+4])[0]
                offset += 4
                
                # Read subject name
                name = data[offset:offset+name_len].decode('utf-8')
                offset += name_len
                
                # Read position (3 doubles)
                position = struct.unpack('ddd', data[offset:offset+24])
                offset += 24
                
                # Read orientation (4 doubles)
                orientation = struct.unpack('dddd', data[offset:offset+32])
                offset += 32
                
                # Read quality (double)
                quality = struct.unpack('d', data[offset:offset+8])[0]
                offset += 8
                
                subjects[name] = {
                    'position': np.array(position),
                    'orientation': np.array(orientation),
                    'quality': quality,
                    'timestamp': timestamp
                }
            
            return {
                'timestamp': timestamp,
                'subjects': subjects
            }
            
        except Exception as e:
            logger.error(f"Failed to parse binary data: {e}")
            return {}
    
    def _parse_csv_data(self, data: bytes) -> Dict:
        """Parse CSV-formatted Vicon data."""
        try:
            csv_str = data.decode('utf-8')
            lines = csv_str.strip().split('\n')
            
            subjects = {}
            timestamp = time.time()
            
            for line in lines:
                if line.startswith('#'):
                    continue
                
                parts = line.split(',')
                if len(parts) >= 8:  # name, x, y, z, qw, qx, qy, qz, quality
                    name = parts[0]
                    position = np.array([float(parts[1]), float(parts[2]), float(parts[3])])
                    orientation = np.array([float(parts[4]), float(parts[5]), float(parts[6]), float(parts[7])])
                    quality = float(parts[8]) if len(parts) > 8 else 1.0
                    
                    subjects[name] = {
                        'position': position,
                        'orientation': orientation,
                        'quality': quality,
                        'timestamp': timestamp
                    }
            
            return {
                'timestamp': timestamp,
                'subjects': subjects
            }
            
        except Exception as e:
            logger.error(f"Failed to parse CSV data: {e}")
            return {}
    
    def get_latest_data(self) -> Optional[Dict]:
        """
        Get latest data from queue.
        
        Returns:
            Optional[Dict]: Latest data or None if queue empty
        """
        try:
            return self.data_queue.get_nowait()
        except:
            return None


class ViconInterface:
    """
    Main Vicon interface for quadrotor control system.
    
    This class provides a high-level interface to the Vicon motion capture
    system, handling data processing, filtering, and coordinate transformations.
    """
    
    def __init__(self, config: ViconConfig):
        """
        Initialize Vicon interface.
        
        Args:
            config (ViconConfig): Vicon configuration
        """
        self.config = config
        
        # Initialize components
        self.udp_client = ViconUDPClient(config)
        self.data_filter = ViconDataFilter(config)
        
        # Data storage
        self.subjects: Dict[str, ViconSubject] = {}
        self.position_history: Dict[str, List[np.ndarray]] = {}
        self.orientation_history: Dict[str, List[np.ndarray]] = {}
        self.timestamp_history: Dict[str, List[float]] = {}
        
        # Callbacks
        self.data_callbacks: List[Callable] = []
        self.error_callbacks: List[Callable] = []
        
        # Performance monitoring
        self.last_update_time = time.time()
        self.update_count = 0
        self.error_count = 0
        
        # Coordinate transformation matrices
        self._setup_coordinate_transforms()
        
        logger.info("Vicon interface initialized")
    
    def _setup_coordinate_transforms(self):
        """Setup coordinate system transformations."""
        # Vicon to NED (North-East-Down) transformation
        # Vicon: X-forward, Y-left, Z-up
        # NED: X-north, Y-east, Z-down
        self.vicon_to_ned = np.array([
            [0, -1, 0],   # X_ned = -Y_vicon
            [1, 0, 0],    # Y_ned = X_vicon
            [0, 0, -1]    # Z_ned = -Z_vicon
        ])
        
        # NED to Vicon transformation
        self.ned_to_vicon = self.vicon_to_ned.T
        
        logger.debug("Coordinate transformations initialized")
    
    def connect(self) -> bool:
        """
        Connect to Vicon system.
        
        Returns:
            bool: True if connection successful
        """
        success = self.udp_client.connect()
        
        if success:
            logger.info("Vicon interface connected")
        else:
            logger.error("Failed to connect Vicon interface")
        
        return success
    
    def disconnect(self):
        """Disconnect from Vicon system."""
        self.udp_client.disconnect()
        logger.info("Vicon interface disconnected")
    
    def update(self):
        """Update Vicon data and process subjects."""
        # Get latest data
        data = self.udp_client.get_latest_data()
        if data is None:
            return
        
        try:
            timestamp = data.get('timestamp', time.time())
            subjects_data = data.get('subjects', {})
            
            # Process each subject
            for subject_name, subject_data in subjects_data.items():
                self._process_subject(subject_name, subject_data, timestamp)
            
            # Update performance stats
            self.update_count += 1
            self.last_update_time = timestamp
            
            # Call data callbacks
            for callback in self.data_callbacks:
                try:
                    callback(self.subjects)
                except Exception as e:
                    logger.error(f"Error in data callback: {e}")
            
        except Exception as e:
            logger.error(f"Error updating Vicon data: {e}")
            self.error_count += 1
            
            # Call error callbacks
            for callback in self.error_callbacks:
                try:
                    callback(e)
                except Exception as callback_error:
                    logger.error(f"Error in error callback: {callback_error}")
    
    def _process_subject(self, subject_name: str, subject_data: Dict, timestamp: float):
        """
        Process data for a single subject.
        
        Args:
            subject_name (str): Subject name
            subject_data (Dict): Raw subject data
            timestamp (float): Data timestamp
        """
        # Extract raw data
        raw_position = subject_data.get('position', np.zeros(3))
        raw_orientation = subject_data.get('orientation', np.array([1, 0, 0, 0]))
        quality = subject_data.get('quality', 0.0)
        
        # Apply coordinate transformation
        position = self._transform_position(raw_position)
        orientation = self._transform_orientation(raw_orientation)
        
        # Apply filtering
        filtered_position = self.data_filter.filter_position(position)
        filtered_orientation = self.data_filter.filter_orientation(orientation)
        
        # Initialize history if needed
        if subject_name not in self.position_history:
            self.position_history[subject_name] = []
            self.orientation_history[subject_name] = []
            self.timestamp_history[subject_name] = []
        
        # Add to history
        self.position_history[subject_name].append(filtered_position)
        self.orientation_history[subject_name].append(filtered_orientation)
        self.timestamp_history[subject_name].append(timestamp)
        
        # Keep history size manageable
        max_history = 100
        if len(self.position_history[subject_name]) > max_history:
            self.position_history[subject_name].pop(0)
            self.orientation_history[subject_name].pop(0)
            self.timestamp_history[subject_name].pop(0)
        
        # Compute velocity and angular velocity
        velocity = self.data_filter.compute_velocity(
            self.position_history[subject_name],
            self.timestamp_history[subject_name]
        )
        
        angular_velocity = self.data_filter.compute_angular_velocity(
            self.orientation_history[subject_name],
            self.timestamp_history[subject_name]
        )
        
        # Update subject
        self.subjects[subject_name] = ViconSubject(
            name=subject_name,
            position=filtered_position,
            orientation=filtered_orientation,
            velocity=velocity,
            angular_velocity=angular_velocity,
            quality=quality,
            timestamp=timestamp,
            visible=quality > 0.1  # Consider visible if quality > 10%
        )
    
    def _transform_position(self, position: np.ndarray) -> np.ndarray:
        """
        Transform position from Vicon to NED coordinates.
        
        Args:
            position (np.ndarray): Position in Vicon coordinates
            
        Returns:
            np.ndarray: Position in NED coordinates
        """
        if self.config.coordinate_system == "vicon_to_ned":
            return self.vicon_to_ned @ position
        else:
            return position
    
    def _transform_orientation(self, orientation: np.ndarray) -> np.ndarray:
        """
        Transform orientation from Vicon to NED coordinates.
        
        Args:
            orientation (np.ndarray): Orientation quaternion in Vicon coordinates
            
        Returns:
            np.ndarray: Orientation quaternion in NED coordinates
        """
        if self.config.coordinate_system == "vicon_to_ned":
            # Create rotation matrix from quaternion
            w, x, y, z = orientation
            R_vicon = np.array([
                [1-2*y*y-2*z*z, 2*x*y-2*w*z, 2*x*z+2*w*y],
                [2*x*y+2*w*z, 1-2*x*x-2*z*z, 2*y*z-2*w*x],
                [2*x*z-2*w*y, 2*y*z+2*w*x, 1-2*x*x-2*y*y]
            ])
            
            # Transform rotation matrix
            R_ned = self.vicon_to_ned @ R_vicon @ self.ned_to_vicon
            
            # Convert back to quaternion
            return self._rotation_matrix_to_quaternion(R_ned)
        else:
            return orientation
    
    def _rotation_matrix_to_quaternion(self, R: np.ndarray) -> np.ndarray:
        """Convert rotation matrix to quaternion."""
        trace = np.trace(R)
        
        if trace > 0:
            S = np.sqrt(trace + 1.0) * 2
            w = 0.25 * S
            x = (R[2, 1] - R[1, 2]) / S
            y = (R[0, 2] - R[2, 0]) / S
            z = (R[1, 0] - R[0, 1]) / S
        elif R[0, 0] > R[1, 1] and R[0, 0] > R[2, 2]:
            S = np.sqrt(1.0 + R[0, 0] - R[1, 1] - R[2, 2]) * 2
            w = (R[2, 1] - R[1, 2]) / S
            x = 0.25 * S
            y = (R[0, 1] + R[1, 0]) / S
            z = (R[0, 2] + R[2, 0]) / S
        elif R[1, 1] > R[2, 2]:
            S = np.sqrt(1.0 + R[1, 1] - R[0, 0] - R[2, 2]) * 2
            w = (R[0, 2] - R[2, 0]) / S
            x = (R[0, 1] + R[1, 0]) / S
            y = 0.25 * S
            z = (R[1, 2] + R[2, 1]) / S
        else:
            S = np.sqrt(1.0 + R[2, 2] - R[0, 0] - R[1, 1]) * 2
            w = (R[1, 0] - R[0, 1]) / S
            x = (R[0, 2] + R[2, 0]) / S
            y = (R[1, 2] + R[2, 1]) / S
            z = 0.25 * S
        
        return np.array([w, x, y, z])
    
    def get_subject(self, subject_name: str) -> Optional[ViconSubject]:
        """
        Get data for a specific subject.
        
        Args:
            subject_name (str): Subject name
            
        Returns:
            Optional[ViconSubject]: Subject data or None if not found
        """
        return self.subjects.get(subject_name)
    
    def get_all_subjects(self) -> Dict[str, ViconSubject]:
        """
        Get data for all subjects.
        
        Returns:
            Dict[str, ViconSubject]: Dictionary of all subjects
        """
        return self.subjects.copy()
    
    def get_visible_subjects(self) -> Dict[str, ViconSubject]:
        """
        Get data for all visible subjects.
        
        Returns:
            Dict[str, ViconSubject]: Dictionary of visible subjects
        """
        return {name: subject for name, subject in self.subjects.items() if subject.visible}
    
    def add_data_callback(self, callback: Callable):
        """
        Add callback function for data updates.
        
        Args:
            callback (Callable): Function to call when data is updated
        """
        self.data_callbacks.append(callback)
    
    def add_error_callback(self, callback: Callable):
        """
        Add callback function for error handling.
        
        Args:
            callback (Callable): Function to call when errors occur
        """
        self.error_callbacks.append(callback)
    
    def get_performance_stats(self) -> Dict[str, float]:
        """
        Get performance statistics.
        
        Returns:
            Dict[str, float]: Performance statistics
        """
        current_time = time.time()
        time_since_update = current_time - self.last_update_time
        
        return {
            'update_count': self.update_count,
            'error_count': self.error_count,
            'time_since_update': time_since_update,
            'update_rate': self.update_count / max(time_since_update, 1.0),
            'error_rate': self.error_count / max(self.update_count, 1.0)
        }
    
    def reset(self):
        """Reset interface state."""
        self.subjects.clear()
        self.position_history.clear()
        self.orientation_history.clear()
        self.timestamp_history.clear()
        self.update_count = 0
        self.error_count = 0
        self.last_update_time = time.time()
        
        logger.info("Vicon interface reset")


# Example usage and testing
if __name__ == "__main__":
    """
    Example usage of the Vicon interface.
    
    This demonstrates how to set up and use the Vicon interface for
    quadrotor position and orientation tracking.
    """
    
    # Initialize configuration
    config = ViconConfig(
        host="192.168.1.100",  # Vicon server IP
        port=800,
        data_format=ViconDataFormat.UDP,
        update_rate=100,
        filter_enabled=True,
        filter_cutoff=10.0,
        auto_reconnect=True
    )
    
    # Initialize Vicon interface
    vicon = ViconInterface(config)
    
    # Add data callback
    def data_callback(subjects):
        """Callback function for data updates."""
        for name, subject in subjects.items():
            if subject.visible:
                print(f"{name}: pos={subject.position}, vel={subject.velocity}, quality={subject.quality:.2f}")
    
    vicon.add_data_callback(data_callback)
    
    # Add error callback
    def error_callback(error):
        """Callback function for errors."""
        print(f"Vicon error: {error}")
    
    vicon.add_error_callback(error_callback)
    
    # Connect to Vicon system
    if vicon.connect():
        print("Connected to Vicon system")
        
        try:
            # Main loop
            print("Receiving Vicon data...")
            print("Press Ctrl+C to stop")
            
            while True:
                # Update Vicon data
                vicon.update()
                
                # Get performance stats every 10 seconds
                if vicon.update_count % 1000 == 0:
                    stats = vicon.get_performance_stats()
                    print(f"Performance: {stats}")
                
                time.sleep(0.01)  # 100Hz update rate
                
        except KeyboardInterrupt:
            print("\nStopping Vicon interface...")
        
        finally:
            vicon.disconnect()
            print("Vicon interface stopped")
    
    else:
        print("Failed to connect to Vicon system")
