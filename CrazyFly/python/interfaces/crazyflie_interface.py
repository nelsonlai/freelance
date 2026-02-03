"""
Crazyflie Interface for Quadrotor Control
=========================================

This module provides a comprehensive interface to the Crazyflie 2.1 quadrotor,
enabling direct communication, parameter management, logging, and control.

Key Features:
- Direct Crazyflie 2.1 communication via Crazyradio PA
- Parameter reading and writing
- Real-time data logging
- Motor control and thrust commands
- Firmware parameter management
- Connection management and error handling
- Performance monitoring

The Crazyflie 2.1 is a small, open-source quadrotor platform ideal for
research and development in aerial robotics.

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
from queue import Queue
import struct

# Crazyflie imports
try:
    import cflib.crtp
    from cflib.crazyflie import Crazyflie
    from cflib.crazyflie.log import LogConfig
    from cflib.crazyflie.mem import MemoryElement
    from cflib.crazyflie.mem import Poly4D
    from cflib.crazyflie.syncCrazyflie import SyncCrazyflie
    from cflib.utils import uri_helper
    CRAZYFLIE_AVAILABLE = True
except ImportError:
    CRAZYFLIE_AVAILABLE = False
    logging.warning("Crazyflie library not available. Install with: pip install cflib")

# Configure logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class FlightMode(Enum):
    """Enumeration of Crazyflie flight modes."""
    IDLE = "idle"
    TAKEOFF = "takeoff"
    HOVER = "hover"
    LAND = "land"
    MANUAL = "manual"
    AUTONOMOUS = "autonomous"


class LogDataType(Enum):
    """Enumeration of log data types."""
    POSITION = "position"
    VELOCITY = "velocity"
    ATTITUDE = "attitude"
    MOTORS = "motors"
    BATTERY = "battery"
    SENSORS = "sensors"
    ALL = "all"


@dataclass
class CrazyflieState:
    """
    Data structure for Crazyflie state information.
    
    Attributes:
        position (np.ndarray): 3D position [x, y, z] in meters
        velocity (np.ndarray): Linear velocity [vx, vy, vz] in m/s
        attitude (np.ndarray): Attitude as quaternion [w, x, y, z]
        angular_velocity (np.ndarray): Angular velocity [wx, wy, wz] in rad/s
        battery_level (float): Battery level (0-1)
        battery_voltage (float): Battery voltage in volts
        motor_thrust (np.ndarray): Motor thrust values [0-1]
        flight_mode (FlightMode): Current flight mode
        timestamp (float): State timestamp
        connected (bool): Connection status
    """
    position: np.ndarray = None
    velocity: np.ndarray = None
    attitude: np.ndarray = None
    angular_velocity: np.ndarray = None
    battery_level: float = 0.0
    battery_voltage: float = 0.0
    motor_thrust: np.ndarray = None
    flight_mode: FlightMode = FlightMode.IDLE
    timestamp: float = 0.0
    connected: bool = False


@dataclass
class CrazyflieConfig:
    """
    Configuration for Crazyflie interface.
    
    Attributes:
        uri (str): Crazyflie URI (e.g., "radio://0/80/2M/E7E7E7E7E7")
        update_rate (int): Data update rate in Hz
        log_enabled (bool): Enable data logging
        log_data_types (List[LogDataType]): Types of data to log
        auto_reconnect (bool): Enable automatic reconnection
        timeout (float): Connection timeout in seconds
        max_thrust (float): Maximum thrust per motor (0-1)
        emergency_stop_thrust (float): Emergency stop thrust value
    """
    uri: str = "radio://0/80/2M/E7E7E7E7E7"
    update_rate: int = 100
    log_enabled: bool = True
    log_data_types: List[LogDataType] = None
    auto_reconnect: bool = True
    timeout: float = 5.0
    max_thrust: float = 0.7
    emergency_stop_thrust: float = 0.0


class CrazyflieLogger:
    """
    Data logging system for Crazyflie.
    
    This class handles real-time data logging from the Crazyflie,
    including position, velocity, attitude, and sensor data.
    """
    
    def __init__(self, crazyflie: 'Crazyflie', config: CrazyflieConfig):
        """
        Initialize Crazyflie logger.
        
        Args:
            crazyflie (Crazyflie): Crazyflie instance
            config (CrazyflieConfig): Configuration
        """
        self.crazyflie = crazyflie
        self.config = config
        self.log_configs: Dict[str, LogConfig] = {}
        self.log_data: Dict[str, List[Any]] = {}
        self.log_timestamps: List[float] = []
        
        # Initialize log data types
        if config.log_data_types is None:
            config.log_data_types = [LogDataType.ALL]
        
        # Setup logging
        self._setup_logging()
        
        logger.info("Crazyflie logger initialized")
    
    def _setup_logging(self):
        """Setup logging configurations."""
        # Position logging
        if LogDataType.POSITION in self.config.log_data_types or LogDataType.ALL in self.config.log_data_types:
            self._setup_position_logging()
        
        # Velocity logging
        if LogDataType.VELOCITY in self.config.log_data_types or LogDataType.ALL in self.config.log_data_types:
            self._setup_velocity_logging()
        
        # Attitude logging
        if LogDataType.ATTITUDE in self.config.log_data_types or LogDataType.ALL in self.config.log_data_types:
            self._setup_attitude_logging()
        
        # Motor logging
        if LogDataType.MOTORS in self.config.log_data_types or LogDataType.ALL in self.config.log_data_types:
            self._setup_motor_logging()
        
        # Battery logging
        if LogDataType.BATTERY in self.config.log_data_types or LogDataType.ALL in self.config.log_data_types:
            self._setup_battery_logging()
        
        # Sensor logging
        if LogDataType.SENSORS in self.config.log_data_types or LogDataType.ALL in self.config.log_data_types:
            self._setup_sensor_logging()
    
    def _setup_position_logging(self):
        """Setup position logging."""
        log_config = LogConfig(name="Position", period_in_ms=10)
        log_config.add_variable("kalman.stateX", "float")
        log_config.add_variable("kalman.stateY", "float")
        log_config.add_variable("kalman.stateZ", "float")
        
        self.log_configs["position"] = log_config
        self.log_data["position"] = []
        
        # Add callback
        self.crazyflie.log.add_config(log_config)
        log_config.data_received_cb.add_callback(self._position_log_callback)
        log_config.error_cb.add_callback(self._log_error_callback)
        
        logger.debug("Position logging configured")
    
    def _setup_velocity_logging(self):
        """Setup velocity logging."""
        log_config = LogConfig(name="Velocity", period_in_ms=10)
        log_config.add_variable("kalman.statePX", "float")
        log_config.add_variable("kalman.statePY", "float")
        log_config.add_variable("kalman.statePZ", "float")
        
        self.log_configs["velocity"] = log_config
        self.log_data["velocity"] = []
        
        # Add callback
        self.crazyflie.log.add_config(log_config)
        log_config.data_received_cb.add_callback(self._velocity_log_callback)
        log_config.error_cb.add_callback(self._log_error_callback)
        
        logger.debug("Velocity logging configured")
    
    def _setup_attitude_logging(self):
        """Setup attitude logging."""
        log_config = LogConfig(name="Attitude", period_in_ms=10)
        log_config.add_variable("stabilizer.roll", "float")
        log_config.add_variable("stabilizer.pitch", "float")
        log_config.add_variable("stabilizer.yaw", "float")
        log_config.add_variable("gyro.x", "float")
        log_config.add_variable("gyro.y", "float")
        log_config.add_variable("gyro.z", "float")
        
        self.log_configs["attitude"] = log_config
        self.log_data["attitude"] = []
        
        # Add callback
        self.crazyflie.log.add_config(log_config)
        log_config.data_received_cb.add_callback(self._attitude_log_callback)
        log_config.error_cb.add_callback(self._log_error_callback)
        
        logger.debug("Attitude logging configured")
    
    def _setup_motor_logging(self):
        """Setup motor logging."""
        log_config = LogConfig(name="Motors", period_in_ms=10)
        log_config.add_variable("motor.m1", "uint16_t")
        log_config.add_variable("motor.m2", "uint16_t")
        log_config.add_variable("motor.m3", "uint16_t")
        log_config.add_variable("motor.m4", "uint16_t")
        
        self.log_configs["motors"] = log_config
        self.log_data["motors"] = []
        
        # Add callback
        self.crazyflie.log.add_config(log_config)
        log_config.data_received_cb.add_callback(self._motor_log_callback)
        log_config.error_cb.add_callback(self._log_error_callback)
        
        logger.debug("Motor logging configured")
    
    def _setup_battery_logging(self):
        """Setup battery logging."""
        log_config = LogConfig(name="Battery", period_in_ms=100)
        log_config.add_variable("pm.vbat", "float")
        log_config.add_variable("pm.batteryLevel", "uint8_t")
        
        self.log_configs["battery"] = log_config
        self.log_data["battery"] = []
        
        # Add callback
        self.crazyflie.log.add_config(log_config)
        log_config.data_received_cb.add_callback(self._battery_log_callback)
        log_config.error_cb.add_callback(self._log_error_callback)
        
        logger.debug("Battery logging configured")
    
    def _setup_sensor_logging(self):
        """Setup sensor logging."""
        log_config = LogConfig(name="Sensors", period_in_ms=10)
        log_config.add_variable("acc.x", "float")
        log_config.add_variable("acc.y", "float")
        log_config.add_variable("acc.z", "float")
        log_config.add_variable("mag.x", "float")
        log_config.add_variable("mag.y", "float")
        log_config.add_variable("mag.z", "float")
        
        self.log_configs["sensors"] = log_config
        self.log_data["sensors"] = []
        
        # Add callback
        self.crazyflie.log.add_config(log_config)
        log_config.data_received_cb.add_callback(self._sensor_log_callback)
        log_config.error_cb.add_callback(self._log_error_callback)
        
        logger.debug("Sensor logging configured")
    
    def _position_log_callback(self, timestamp, data, logconf):
        """Callback for position log data."""
        position = np.array([
            data["kalman.stateX"],
            data["kalman.stateY"],
            data["kalman.stateZ"]
        ])
        
        self.log_data["position"].append({
            'timestamp': timestamp,
            'position': position
        })
        
        # Keep data size manageable
        if len(self.log_data["position"]) > 1000:
            self.log_data["position"].pop(0)
    
    def _velocity_log_callback(self, timestamp, data, logconf):
        """Callback for velocity log data."""
        velocity = np.array([
            data["kalman.statePX"],
            data["kalman.statePY"],
            data["kalman.statePZ"]
        ])
        
        self.log_data["velocity"].append({
            'timestamp': timestamp,
            'velocity': velocity
        })
        
        # Keep data size manageable
        if len(self.log_data["velocity"]) > 1000:
            self.log_data["velocity"].pop(0)
    
    def _attitude_log_callback(self, timestamp, data, logconf):
        """Callback for attitude log data."""
        attitude = np.array([
            data["stabilizer.roll"],
            data["stabilizer.pitch"],
            data["stabilizer.yaw"]
        ])
        
        angular_velocity = np.array([
            data["gyro.x"],
            data["gyro.y"],
            data["gyro.z"]
        ])
        
        self.log_data["attitude"].append({
            'timestamp': timestamp,
            'attitude': attitude,
            'angular_velocity': angular_velocity
        })
        
        # Keep data size manageable
        if len(self.log_data["attitude"]) > 1000:
            self.log_data["attitude"].pop(0)
    
    def _motor_log_callback(self, timestamp, data, logconf):
        """Callback for motor log data."""
        motor_thrust = np.array([
            data["motor.m1"],
            data["motor.m2"],
            data["motor.m3"],
            data["motor.m4"]
        ]) / 65535.0  # Normalize to 0-1
        
        self.log_data["motors"].append({
            'timestamp': timestamp,
            'motor_thrust': motor_thrust
        })
        
        # Keep data size manageable
        if len(self.log_data["motors"]) > 1000:
            self.log_data["motors"].pop(0)
    
    def _battery_log_callback(self, timestamp, data, logconf):
        """Callback for battery log data."""
        battery_data = {
            'timestamp': timestamp,
            'voltage': data["pm.vbat"],
            'level': data["pm.batteryLevel"] / 100.0  # Normalize to 0-1
        }
        
        self.log_data["battery"].append(battery_data)
        
        # Keep data size manageable
        if len(self.log_data["battery"]) > 100:
            self.log_data["battery"].pop(0)
    
    def _sensor_log_callback(self, timestamp, data, logconf):
        """Callback for sensor log data."""
        accelerometer = np.array([
            data["acc.x"],
            data["acc.y"],
            data["acc.z"]
        ])
        
        magnetometer = np.array([
            data["mag.x"],
            data["mag.y"],
            data["mag.z"]
        ])
        
        self.log_data["sensors"].append({
            'timestamp': timestamp,
            'accelerometer': accelerometer,
            'magnetometer': magnetometer
        })
        
        # Keep data size manageable
        if len(self.log_data["sensors"]) > 1000:
            self.log_data["sensors"].pop(0)
    
    def _log_error_callback(self, logconf, msg):
        """Callback for log errors."""
        logger.error(f"Log error in {logconf.name}: {msg}")
    
    def start_logging(self):
        """Start all logging configurations."""
        for name, log_config in self.log_configs.items():
            try:
                log_config.start()
                logger.info(f"Started {name} logging")
            except Exception as e:
                logger.error(f"Failed to start {name} logging: {e}")
    
    def stop_logging(self):
        """Stop all logging configurations."""
        for name, log_config in self.log_configs.items():
            try:
                log_config.stop()
                logger.info(f"Stopped {name} logging")
            except Exception as e:
                logger.error(f"Failed to stop {name} logging: {e}")
    
    def get_latest_data(self, data_type: str) -> Optional[Dict]:
        """
        Get latest data for a specific type.
        
        Args:
            data_type (str): Type of data to retrieve
            
        Returns:
            Optional[Dict]: Latest data or None if not available
        """
        if data_type in self.log_data and self.log_data[data_type]:
            return self.log_data[data_type][-1]
        return None
    
    def get_all_data(self, data_type: str) -> List[Dict]:
        """
        Get all data for a specific type.
        
        Args:
            data_type (str): Type of data to retrieve
            
        Returns:
            List[Dict]: All data for the specified type
        """
        return self.log_data.get(data_type, []).copy()
    
    def clear_data(self):
        """Clear all logged data."""
        for data_type in self.log_data:
            self.log_data[data_type].clear()
        self.log_timestamps.clear()
        logger.info("Cleared all logged data")


class CrazyflieParameterManager:
    """
    Parameter management for Crazyflie.
    
    This class handles reading and writing of Crazyflie firmware parameters,
    including control gains, sensor calibration, and system settings.
    """
    
    def __init__(self, crazyflie: 'Crazyflie'):
        """
        Initialize parameter manager.
        
        Args:
            crazyflie (Crazyflie): Crazyflie instance
        """
        self.crazyflie = crazyflie
        self.parameters: Dict[str, Any] = {}
        self.parameter_callbacks: Dict[str, List[Callable]] = {}
        
        # Common parameter groups
        self.param_groups = {
            'pid': ['pid_attitude.pitch_kp', 'pid_attitude.pitch_ki', 'pid_attitude.pitch_kd',
                   'pid_attitude.roll_kp', 'pid_attitude.roll_ki', 'pid_attitude.roll_kd',
                   'pid_attitude.yaw_kp', 'pid_attitude.yaw_ki', 'pid_attitude.yaw_kd',
                   'pid_rate.pitch_kp', 'pid_rate.pitch_ki', 'pid_rate.pitch_kd',
                   'pid_rate.roll_kp', 'pid_rate.roll_ki', 'pid_rate.roll_kd',
                   'pid_rate.yaw_kp', 'pid_rate.yaw_ki', 'pid_rate.yaw_kd'],
            'kalman': ['kalman.initialX', 'kalman.initialY', 'kalman.initialZ',
                      'kalman.processNoiseStdDevX', 'kalman.processNoiseStdDevY', 'kalman.processNoiseStdDevZ'],
            'system': ['system.forceArm', 'system.forceDisarm', 'system.emergencyStop'],
            'sensors': ['gyro.x', 'gyro.y', 'gyro.z', 'acc.x', 'acc.y', 'acc.z']
        }
        
        logger.info("Crazyflie parameter manager initialized")
    
    def add_parameter_callback(self, param_name: str, callback: Callable):
        """
        Add callback for parameter updates.
        
        Args:
            param_name (str): Parameter name
            callback (Callable): Callback function
        """
        if param_name not in self.parameter_callbacks:
            self.parameter_callbacks[param_name] = []
        self.parameter_callbacks[param_name].append(callback)
    
    def _parameter_callback(self, name: str, value: Any):
        """Generic parameter callback."""
        self.parameters[name] = value
        
        # Call registered callbacks
        if name in self.parameter_callbacks:
            for callback in self.parameter_callbacks[name]:
                try:
                    callback(name, value)
                except Exception as e:
                    logger.error(f"Error in parameter callback for {name}: {e}")
    
    def read_parameter(self, param_name: str) -> Optional[Any]:
        """
        Read a single parameter.
        
        Args:
            param_name (str): Parameter name
            
        Returns:
            Optional[Any]: Parameter value or None if failed
        """
        try:
            self.crazyflie.param.add_update_callback(group="", name=param_name,
                                                   cb=self._parameter_callback)
            return self.parameters.get(param_name)
        except Exception as e:
            logger.error(f"Failed to read parameter {param_name}: {e}")
            return None
    
    def write_parameter(self, param_name: str, value: Any) -> bool:
        """
        Write a single parameter.
        
        Args:
            param_name (str): Parameter name
            value (Any): Parameter value
            
        Returns:
            bool: True if successful
        """
        try:
            self.crazyflie.param.set_value(param_name, value)
            logger.debug(f"Set parameter {param_name} = {value}")
            return True
        except Exception as e:
            logger.error(f"Failed to write parameter {param_name}: {e}")
            return False
    
    def read_parameter_group(self, group_name: str) -> Dict[str, Any]:
        """
        Read all parameters in a group.
        
        Args:
            group_name (str): Parameter group name
            
        Returns:
            Dict[str, Any]: Dictionary of parameter values
        """
        if group_name not in self.param_groups:
            logger.warning(f"Unknown parameter group: {group_name}")
            return {}
        
        group_params = {}
        for param_name in self.param_groups[group_name]:
            value = self.read_parameter(param_name)
            if value is not None:
                group_params[param_name] = value
        
        logger.info(f"Read {len(group_params)} parameters from group {group_name}")
        return group_params
    
    def write_parameter_group(self, group_name: str, values: Dict[str, Any]) -> bool:
        """
        Write parameters in a group.
        
        Args:
            group_name (str): Parameter group name
            values (Dict[str, Any]): Parameter values
            
        Returns:
            bool: True if all successful
        """
        if group_name not in self.param_groups:
            logger.warning(f"Unknown parameter group: {group_name}")
            return False
        
        success_count = 0
        for param_name, value in values.items():
            if param_name in self.param_groups[group_name]:
                if self.write_parameter(param_name, value):
                    success_count += 1
        
        logger.info(f"Wrote {success_count}/{len(values)} parameters in group {group_name}")
        return success_count == len(values)
    
    def get_pid_gains(self) -> Dict[str, Dict[str, float]]:
        """
        Get current PID gains.
        
        Returns:
            Dict[str, Dict[str, float]]: PID gains organized by controller
        """
        pid_gains = {
            'attitude': {},
            'rate': {}
        }
        
        # Read attitude PID gains
        for axis in ['pitch', 'roll', 'yaw']:
            for gain in ['kp', 'ki', 'kd']:
                param_name = f"pid_attitude.{axis}_{gain}"
                value = self.read_parameter(param_name)
                if value is not None:
                    if 'attitude' not in pid_gains:
                        pid_gains['attitude'] = {}
                    pid_gains['attitude'][f"{axis}_{gain}"] = value
        
        # Read rate PID gains
        for axis in ['pitch', 'roll', 'yaw']:
            for gain in ['kp', 'ki', 'kd']:
                param_name = f"pid_rate.{axis}_{gain}"
                value = self.read_parameter(param_name)
                if value is not None:
                    if 'rate' not in pid_gains:
                        pid_gains['rate'] = {}
                    pid_gains['rate'][f"{axis}_{gain}"] = value
        
        return pid_gains
    
    def set_pid_gains(self, pid_gains: Dict[str, Dict[str, float]]) -> bool:
        """
        Set PID gains.
        
        Args:
            pid_gains (Dict[str, Dict[str, float]]): PID gains to set
            
        Returns:
            bool: True if successful
        """
        success = True
        
        # Set attitude PID gains
        if 'attitude' in pid_gains:
            for param_name, value in pid_gains['attitude'].items():
                if not self.write_parameter(f"pid_attitude.{param_name}", value):
                    success = False
        
        # Set rate PID gains
        if 'rate' in pid_gains:
            for param_name, value in pid_gains['rate'].items():
                if not self.write_parameter(f"pid_rate.{param_name}", value):
                    success = False
        
        return success


class CrazyflieInterface:
    """
    Main Crazyflie interface for quadrotor control system.
    
    This class provides a high-level interface to the Crazyflie 2.1,
    handling communication, control, logging, and parameter management.
    """
    
    def __init__(self, config: CrazyflieConfig):
        """
        Initialize Crazyflie interface.
        
        Args:
            config (CrazyflieConfig): Crazyflie configuration
        """
        if not CRAZYFLIE_AVAILABLE:
            raise ImportError("Crazyflie library not available. Install with: pip install cflib")
        
        self.config = config
        self.crazyflie = None
        self.sync_crazyflie = None
        self.connected = False
        
        # Initialize components
        self.logger = None
        self.param_manager = None
        
        # State management
        self.current_state = CrazyflieState()
        self.flight_mode = FlightMode.IDLE
        
        # Callbacks
        self.state_callbacks: List[Callable] = []
        self.connection_callbacks: List[Callable] = []
        self.error_callbacks: List[Callable] = []
        
        # Performance monitoring
        self.last_update_time = time.time()
        self.update_count = 0
        self.error_count = 0
        
        # Initialize Crazyflie library
        cflib.crtp.init_drivers()
        
        logger.info(f"Crazyflie interface initialized: {config.uri}")
    
    def connect(self) -> bool:
        """
        Connect to Crazyflie.
        
        Returns:
            bool: True if connection successful
        """
        try:
            # Create Crazyflie instance
            self.crazyflie = Crazyflie(rw_cache="./cache")
            
            # Add connection callbacks
            self.crazyflie.connected.add_callback(self._connected_callback)
            self.crazyflie.disconnected.add_callback(self._disconnected_callback)
            self.crazyflie.connection_failed.add_callback(self._connection_failed_callback)
            
            # Connect
            self.crazyflie.open_link(self.config.uri)
            
            # Wait for connection
            timeout = time.time() + self.config.timeout
            while not self.connected and time.time() < timeout:
                time.sleep(0.1)
            
            if self.connected:
                # Initialize components
                self.logger = CrazyflieLogger(self.crazyflie, self.config)
                self.param_manager = CrazyflieParameterManager(self.crazyflie)
                
                # Start logging if enabled
                if self.config.log_enabled:
                    self.logger.start_logging()
                
                logger.info("Crazyflie connected successfully")
                return True
            else:
                logger.error("Failed to connect to Crazyflie")
                return False
                
        except Exception as e:
            logger.error(f"Error connecting to Crazyflie: {e}")
            return False
    
    def disconnect(self):
        """Disconnect from Crazyflie."""
        if self.logger:
            self.logger.stop_logging()
        
        if self.crazyflie:
            self.crazyflie.close_link()
        
        self.connected = False
        logger.info("Crazyflie disconnected")
    
    def _connected_callback(self, uri):
        """Callback for successful connection."""
        self.connected = True
        self.current_state.connected = True
        
        # Call connection callbacks
        for callback in self.connection_callbacks:
            try:
                callback(True, uri)
            except Exception as e:
                logger.error(f"Error in connection callback: {e}")
        
        logger.info(f"Connected to Crazyflie: {uri}")
    
    def _disconnected_callback(self, uri):
        """Callback for disconnection."""
        self.connected = False
        self.current_state.connected = False
        
        # Call connection callbacks
        for callback in self.connection_callbacks:
            try:
                callback(False, uri)
            except Exception as e:
                logger.error(f"Error in connection callback: {e}")
        
        logger.info(f"Disconnected from Crazyflie: {uri}")
    
    def _connection_failed_callback(self, uri, msg):
        """Callback for connection failure."""
        self.connected = False
        self.current_state.connected = False
        
        # Call error callbacks
        for callback in self.error_callbacks:
            try:
                callback(f"Connection failed: {msg}")
            except Exception as e:
                logger.error(f"Error in error callback: {e}")
        
        logger.error(f"Connection failed to Crazyflie {uri}: {msg}")
    
    def update(self):
        """Update Crazyflie state and data."""
        if not self.connected:
            return
        
        try:
            # Update state from logging data
            self._update_state_from_logs()
            
            # Update performance stats
            self.update_count += 1
            self.last_update_time = time.time()
            
            # Call state callbacks
            for callback in self.state_callbacks:
                try:
                    callback(self.current_state)
                except Exception as e:
                    logger.error(f"Error in state callback: {e}")
            
        except Exception as e:
            logger.error(f"Error updating Crazyflie state: {e}")
            self.error_count += 1
    
    def _update_state_from_logs(self):
        """Update state from logged data."""
        if not self.logger:
            return
        
        # Update position
        position_data = self.logger.get_latest_data("position")
        if position_data:
            self.current_state.position = position_data['position']
            self.current_state.timestamp = position_data['timestamp']
        
        # Update velocity
        velocity_data = self.logger.get_latest_data("velocity")
        if velocity_data:
            self.current_state.velocity = velocity_data['velocity']
        
        # Update attitude
        attitude_data = self.logger.get_latest_data("attitude")
        if attitude_data:
            # Convert Euler angles to quaternion
            roll, pitch, yaw = attitude_data['attitude']
            self.current_state.attitude = self._euler_to_quaternion(roll, pitch, yaw)
            self.current_state.angular_velocity = attitude_data['angular_velocity']
        
        # Update motor thrust
        motor_data = self.logger.get_latest_data("motors")
        if motor_data:
            self.current_state.motor_thrust = motor_data['motor_thrust']
        
        # Update battery
        battery_data = self.logger.get_latest_data("battery")
        if battery_data:
            self.current_state.battery_voltage = battery_data['voltage']
            self.current_state.battery_level = battery_data['level']
    
    def _euler_to_quaternion(self, roll: float, pitch: float, yaw: float) -> np.ndarray:
        """Convert Euler angles to quaternion."""
        # Convert to radians
        roll = np.radians(roll)
        pitch = np.radians(pitch)
        yaw = np.radians(yaw)
        
        # Quaternion components
        cy = np.cos(yaw * 0.5)
        sy = np.sin(yaw * 0.5)
        cp = np.cos(pitch * 0.5)
        sp = np.sin(pitch * 0.5)
        cr = np.cos(roll * 0.5)
        sr = np.sin(roll * 0.5)
        
        w = cr * cp * cy + sr * sp * sy
        x = sr * cp * cy - cr * sp * sy
        y = cr * sp * cy + sr * cp * sy
        z = cr * cp * sy - sr * sp * cy
        
        return np.array([w, x, y, z])
    
    def send_thrust_setpoint(self, thrust: np.ndarray):
        """
        Send thrust setpoint to motors.
        
        Args:
            thrust (np.ndarray): Thrust values [0-1] for each motor
        """
        if not self.connected:
            logger.warning("Cannot send thrust setpoint: not connected")
            return
        
        # Validate thrust values
        thrust = np.clip(thrust, 0.0, self.config.max_thrust)
        
        try:
            # Send thrust commands
            self.crazyflie.commander.send_setpoint(
                roll=0, pitch=0, yawrate=0, thrust=thrust[0]
            )
            
            logger.debug(f"Sent thrust setpoint: {thrust}")
            
        except Exception as e:
            logger.error(f"Failed to send thrust setpoint: {e}")
    
    def send_position_setpoint(self, position: np.ndarray, yaw: float = 0.0):
        """
        Send position setpoint.
        
        Args:
            position (np.ndarray): Target position [x, y, z]
            yaw (float): Target yaw angle in degrees
        """
        if not self.connected:
            logger.warning("Cannot send position setpoint: not connected")
            return
        
        try:
            # Convert to Crazyflie coordinate system if needed
            x, y, z = position
            
            # Send position setpoint
            self.crazyflie.commander.send_position_setpoint(x, y, z, yaw)
            
            logger.debug(f"Sent position setpoint: pos={position}, yaw={yaw}")
            
        except Exception as e:
            logger.error(f"Failed to send position setpoint: {e}")
    
    def emergency_stop(self):
        """Send emergency stop command."""
        if self.connected:
            try:
                # Send zero thrust
                self.send_thrust_setpoint(np.array([self.config.emergency_stop_thrust] * 4))
                
                # Set flight mode to idle
                self.flight_mode = FlightMode.IDLE
                self.current_state.flight_mode = FlightMode.IDLE
                
                logger.warning("Emergency stop executed")
                
            except Exception as e:
                logger.error(f"Failed to execute emergency stop: {e}")
    
    def takeoff(self, height: float = 0.5, duration: float = 2.0):
        """
        Execute takeoff maneuver.
        
        Args:
            height (float): Takeoff height in meters
            duration (float): Takeoff duration in seconds
        """
        if not self.connected:
            logger.warning("Cannot takeoff: not connected")
            return
        
        try:
            # Set flight mode
            self.flight_mode = FlightMode.TAKEOFF
            self.current_state.flight_mode = FlightMode.TAKEOFF
            
            # Execute takeoff
            self.crazyflie.commander.takeoff(height, duration)
            
            logger.info(f"Takeoff initiated: height={height}m, duration={duration}s")
            
        except Exception as e:
            logger.error(f"Failed to execute takeoff: {e}")
    
    def land(self, duration: float = 2.0):
        """
        Execute landing maneuver.
        
        Args:
            duration (float): Landing duration in seconds
        """
        if not self.connected:
            logger.warning("Cannot land: not connected")
            return
        
        try:
            # Set flight mode
            self.flight_mode = FlightMode.LAND
            self.current_state.flight_mode = FlightMode.LAND
            
            # Execute landing
            self.crazyflie.commander.land(0.0, duration)
            
            logger.info(f"Landing initiated: duration={duration}s")
            
        except Exception as e:
            logger.error(f"Failed to execute landing: {e}")
    
    def get_state(self) -> CrazyflieState:
        """
        Get current Crazyflie state.
        
        Returns:
            CrazyflieState: Current state
        """
        return self.current_state
    
    def add_state_callback(self, callback: Callable):
        """
        Add callback for state updates.
        
        Args:
            callback (Callable): Function to call when state is updated
        """
        self.state_callbacks.append(callback)
    
    def add_connection_callback(self, callback: Callable):
        """
        Add callback for connection events.
        
        Args:
            callback (Callable): Function to call on connection events
        """
        self.connection_callbacks.append(callback)
    
    def add_error_callback(self, callback: Callable):
        """
        Add callback for error events.
        
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
            'error_rate': self.error_count / max(self.update_count, 1.0),
            'connected': self.connected
        }
    
    def reset(self):
        """Reset interface state."""
        self.current_state = CrazyflieState()
        self.flight_mode = FlightMode.IDLE
        self.update_count = 0
        self.error_count = 0
        self.last_update_time = time.time()
        
        if self.logger:
            self.logger.clear_data()
        
        logger.info("Crazyflie interface reset")


# Example usage and testing
if __name__ == "__main__":
    """
    Example usage of the Crazyflie interface.
    
    This demonstrates how to set up and use the Crazyflie interface for
    quadrotor control and monitoring.
    """
    
    # Initialize configuration
    config = CrazyflieConfig(
        uri="radio://0/80/2M/E7E7E7E7E7",  # Replace with your Crazyflie URI
        update_rate=100,
        log_enabled=True,
        log_data_types=[LogDataType.ALL],
        auto_reconnect=True,
        max_thrust=0.7
    )
    
    # Initialize Crazyflie interface
    crazyflie = CrazyflieInterface(config)
    
    # Add callbacks
    def state_callback(state):
        """Callback for state updates."""
        if state.connected:
            print(f"Position: {state.position}, Battery: {state.battery_level:.2f}")
    
    def connection_callback(connected, uri):
        """Callback for connection events."""
        status = "connected" if connected else "disconnected"
        print(f"Crazyflie {status}: {uri}")
    
    def error_callback(error):
        """Callback for errors."""
        print(f"Crazyflie error: {error}")
    
    crazyflie.add_state_callback(state_callback)
    crazyflie.add_connection_callback(connection_callback)
    crazyflie.add_error_callback(error_callback)
    
    # Connect to Crazyflie
    if crazyflie.connect():
        print("Connected to Crazyflie")
        
        try:
            # Main loop
            print("Monitoring Crazyflie...")
            print("Press Ctrl+C to stop")
            
            while True:
                # Update Crazyflie state
                crazyflie.update()
                
                # Get performance stats every 10 seconds
                if crazyflie.update_count % 1000 == 0:
                    stats = crazyflie.get_performance_stats()
                    print(f"Performance: {stats}")
                
                time.sleep(0.01)  # 100Hz update rate
                
        except KeyboardInterrupt:
            print("\nStopping Crazyflie interface...")
        
        finally:
            crazyflie.disconnect()
            print("Crazyflie interface stopped")
    
    else:
        print("Failed to connect to Crazyflie")
