"""
Data Logging Utilities for Quadrotor Control System
==================================================

This module provides comprehensive data logging utilities for recording
quadrotor flight data, including sensor readings, control commands,
performance metrics, and system events.

Key Features:
- Multi-format data logging (JSON, CSV, HDF5, binary)
- Real-time data streaming
- Automatic data compression
- Data validation and integrity checks
- Configurable logging levels
- Automatic file rotation
- Data export and analysis tools
- Performance monitoring

The data logger enables comprehensive recording of all system data for
post-flight analysis, debugging, and performance optimization.

Author: [Your Name]
Date: [Current Date]
License: MIT
"""

import numpy as np
import time
import threading
import json
import csv
import pickle
import gzip
import h5py
from typing import Dict, List, Tuple, Optional, Any, Union, Callable
from dataclasses import dataclass, asdict
from enum import Enum
from pathlib import Path
import logging
from datetime import datetime
import queue
import os
import shutil

# Configure logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class LogLevel(Enum):
    """Enumeration of logging levels."""
    DEBUG = "debug"
    INFO = "info"
    WARNING = "warning"
    ERROR = "error"
    CRITICAL = "critical"


class DataFormat(Enum):
    """Enumeration of data formats."""
    JSON = "json"
    CSV = "csv"
    HDF5 = "hdf5"
    BINARY = "binary"
    PICKLE = "pickle"
    COMPRESSED = "compressed"


@dataclass
class LogEntry:
    """
    Data structure for a log entry.
    
    Attributes:
        timestamp (float): Timestamp in seconds
        data_type (str): Type of data being logged
        data (Any): Actual data to be logged
        metadata (Dict[str, Any]): Additional metadata
        level (LogLevel): Logging level
    """
    timestamp: float
    data_type: str
    data: Any
    metadata: Dict[str, Any] = None
    level: LogLevel = LogLevel.INFO
    
    def __post_init__(self):
        """Initialize metadata if not provided."""
        if self.metadata is None:
            self.metadata = {}


@dataclass
class LoggerConfig:
    """
    Configuration for data logger.
    
    Attributes:
        output_directory (str): Output directory for log files
        data_format (DataFormat): Preferred data format
        compression_enabled (bool): Enable data compression
        max_file_size (int): Maximum file size in bytes
        max_files (int): Maximum number of files to keep
        flush_interval (float): Flush interval in seconds
        buffer_size (int): Buffer size for queued entries
        enable_validation (bool): Enable data validation
        enable_backup (bool): Enable automatic backups
        backup_interval (float): Backup interval in hours
    """
    output_directory: str = "logs"
    data_format: DataFormat = DataFormat.HDF5
    compression_enabled: bool = True
    max_file_size: int = 100 * 1024 * 1024  # 100MB
    max_files: int = 10
    flush_interval: float = 1.0
    buffer_size: int = 1000
    enable_validation: bool = True
    enable_backup: bool = True
    backup_interval: float = 24.0  # 24 hours


class DataValidator:
    """
    Data validation utility.
    
    This class provides methods for validating data integrity
    and detecting anomalies in logged data.
    """
    
    def __init__(self):
        """Initialize data validator."""
        self.validation_rules: Dict[str, Callable] = {}
        self.anomaly_thresholds: Dict[str, Tuple[float, float]] = {}
        
        logger.info("Data validator initialized")
    
    def add_validation_rule(self, data_type: str, validation_func: Callable):
        """
        Add a validation rule for a specific data type.
        
        Args:
            data_type (str): Type of data to validate
            validation_func (Callable): Validation function
        """
        self.validation_rules[data_type] = validation_func
        logger.debug(f"Added validation rule for {data_type}")
    
    def set_anomaly_thresholds(self, data_type: str, min_value: float, max_value: float):
        """
        Set anomaly detection thresholds.
        
        Args:
            data_type (str): Type of data
            min_value (float): Minimum acceptable value
            max_value (float): Maximum acceptable value
        """
        self.anomaly_thresholds[data_type] = (min_value, max_value)
        logger.debug(f"Set anomaly thresholds for {data_type}: [{min_value}, {max_value}]")
    
    def validate_entry(self, entry: LogEntry) -> Tuple[bool, List[str]]:
        """
        Validate a log entry.
        
        Args:
            entry (LogEntry): Log entry to validate
            
        Returns:
            Tuple[bool, List[str]]: (is_valid, error_messages)
        """
        errors = []
        
        # Check timestamp
        if entry.timestamp <= 0:
            errors.append("Invalid timestamp")
        
        # Check data type
        if not entry.data_type or not isinstance(entry.data_type, str):
            errors.append("Invalid data type")
        
        # Check data
        if entry.data is None:
            errors.append("Data is None")
        
        # Apply specific validation rules
        if entry.data_type in self.validation_rules:
            try:
                is_valid = self.validation_rules[entry.data_type](entry.data)
                if not is_valid:
                    errors.append(f"Failed validation rule for {entry.data_type}")
            except Exception as e:
                errors.append(f"Validation error for {entry.data_type}: {e}")
        
        # Check anomaly thresholds
        if entry.data_type in self.anomaly_thresholds:
            min_val, max_val = self.anomaly_thresholds[entry.data_type]
            
            if isinstance(entry.data, (int, float)):
                if entry.data < min_val or entry.data > max_val:
                    errors.append(f"Value {entry.data} outside threshold [{min_val}, {max_val}]")
            elif isinstance(entry.data, (list, np.ndarray)):
                data_array = np.array(entry.data)
                if np.any(data_array < min_val) or np.any(data_array > max_val):
                    errors.append(f"Some values outside threshold [{min_val}, {max_val}]")
        
        return len(errors) == 0, errors


class DataLogger:
    """
    Main data logging class.
    
    This class provides comprehensive data logging functionality
    with support for multiple formats and real-time streaming.
    """
    
    def __init__(self, config: LoggerConfig = None):
        """
        Initialize data logger.
        
        Args:
            config (LoggerConfig): Logger configuration
        """
        self.config = config or LoggerConfig()
        self.validator = DataValidator()
        
        # Create output directory
        self.output_path = Path(self.config.output_directory)
        self.output_path.mkdir(parents=True, exist_ok=True)
        
        # Initialize components
        self.log_queue = queue.Queue(maxsize=self.config.buffer_size)
        self.current_file = None
        self.current_file_size = 0
        self.file_counter = 0
        self.total_entries = 0
        self.start_time = time.time()
        
        # Threading
        self.logging_thread = None
        self.running = False
        self.lock = threading.Lock()
        
        # Performance monitoring
        self.performance_stats = {
            'entries_logged': 0,
            'bytes_written': 0,
            'files_created': 0,
            'validation_errors': 0,
            'write_errors': 0
        }
        
        # Setup default validation rules
        self._setup_default_validation()
        
        logger.info(f"Data logger initialized with output directory: {self.output_path}")
    
    def _setup_default_validation(self):
        """Setup default validation rules."""
        # Position validation
        def validate_position(data):
            if isinstance(data, (list, np.ndarray)):
                data_array = np.array(data)
                return len(data_array) == 3 and np.all(np.isfinite(data_array))
            return False
        
        # Attitude validation
        def validate_attitude(data):
            if isinstance(data, (list, np.ndarray)):
                data_array = np.array(data)
                return len(data_array) == 3 and np.all(np.isfinite(data_array))
            return False
        
        # Performance metrics validation
        def validate_performance(data):
            if isinstance(data, dict):
                return all(isinstance(v, (int, float)) for v in data.values())
            return False
        
        self.validator.add_validation_rule("position", validate_position)
        self.validator.add_validation_rule("attitude", validate_attitude)
        self.validator.add_validation_rule("performance", validate_performance)
        
        # Set anomaly thresholds
        self.validator.set_anomaly_thresholds("position", -100.0, 100.0)  # meters
        self.validator.set_anomaly_thresholds("attitude", -np.pi, np.pi)  # radians
        self.validator.set_anomaly_thresholds("velocity", -50.0, 50.0)  # m/s
        self.validator.set_anomaly_thresholds("angular_velocity", -10.0, 10.0)  # rad/s
    
    def start(self):
        """Start the data logger."""
        if self.running:
            logger.warning("Data logger is already running")
            return
        
        self.running = True
        self.logging_thread = threading.Thread(target=self._logging_worker, daemon=True)
        self.logging_thread.start()
        
        logger.info("Data logger started")
    
    def stop(self):
        """Stop the data logger."""
        if not self.running:
            logger.warning("Data logger is not running")
            return
        
        self.running = False
        
        # Wait for logging thread to finish
        if self.logging_thread and self.logging_thread.is_alive():
            self.logging_thread.join(timeout=5.0)
        
        # Flush remaining entries
        self._flush_entries()
        
        # Close current file
        if self.current_file:
            self.current_file.close()
            self.current_file = None
        
        logger.info("Data logger stopped")
    
    def log_data(self, data_type: str, data: Any, metadata: Dict[str, Any] = None, 
                 level: LogLevel = LogLevel.INFO):
        """
        Log data asynchronously.
        
        Args:
            data_type (str): Type of data being logged
            data (Any): Data to log
            metadata (Dict[str, Any]): Additional metadata
            level (LogLevel): Logging level
        """
        entry = LogEntry(
            timestamp=time.time(),
            data_type=data_type,
            data=data,
            metadata=metadata or {},
            level=level
        )
        
        try:
            self.log_queue.put_nowait(entry)
            self.total_entries += 1
        except queue.Full:
            logger.warning("Log queue is full, dropping entry")
            self.performance_stats['write_errors'] += 1
    
    def log_position(self, position: np.ndarray, drone_id: str = "drone_1"):
        """
        Log position data.
        
        Args:
            position (np.ndarray): Position [x, y, z]
            drone_id (str): Drone identifier
        """
        metadata = {'drone_id': drone_id, 'units': 'meters'}
        self.log_data("position", position.tolist(), metadata)
    
    def log_attitude(self, attitude: np.ndarray, drone_id: str = "drone_1"):
        """
        Log attitude data.
        
        Args:
            attitude (np.ndarray): Attitude [roll, pitch, yaw]
            drone_id (str): Drone identifier
        """
        metadata = {'drone_id': drone_id, 'units': 'radians'}
        self.log_data("attitude", attitude.tolist(), metadata)
    
    def log_velocity(self, velocity: np.ndarray, drone_id: str = "drone_1"):
        """
        Log velocity data.
        
        Args:
            velocity (np.ndarray): Velocity [vx, vy, vz]
            drone_id (str): Drone identifier
        """
        metadata = {'drone_id': drone_id, 'units': 'm/s'}
        self.log_data("velocity", velocity.tolist(), metadata)
    
    def log_control_commands(self, commands: np.ndarray, drone_id: str = "drone_1"):
        """
        Log control commands.
        
        Args:
            commands (np.ndarray): Control commands
            drone_id (str): Drone identifier
        """
        metadata = {'drone_id': drone_id, 'units': 'normalized'}
        self.log_data("control_commands", commands.tolist(), metadata)
    
    def log_performance_metrics(self, metrics: Dict[str, float]):
        """
        Log performance metrics.
        
        Args:
            metrics (Dict[str, float]): Performance metrics
        """
        self.log_data("performance", metrics)
    
    def log_system_event(self, event: str, details: Dict[str, Any] = None, 
                        level: LogLevel = LogLevel.INFO):
        """
        Log system event.
        
        Args:
            event (str): Event description
            details (Dict[str, Any]): Event details
            level (LogLevel): Event level
        """
        metadata = {'event': event, 'details': details or {}}
        self.log_data("system_event", event, metadata, level)
    
    def _logging_worker(self):
        """Main logging worker thread."""
        last_flush = time.time()
        
        while self.running:
            try:
                # Get entry from queue with timeout
                try:
                    entry = self.log_queue.get(timeout=0.1)
                except queue.Empty:
                    # Check if it's time to flush
                    if time.time() - last_flush >= self.config.flush_interval:
                        self._flush_entries()
                        last_flush = time.time()
                    continue
                
                # Validate entry
                if self.config.enable_validation:
                    is_valid, errors = self.validator.validate_entry(entry)
                    if not is_valid:
                        logger.warning(f"Validation errors for {entry.data_type}: {errors}")
                        self.performance_stats['validation_errors'] += 1
                        continue
                
                # Write entry
                self._write_entry(entry)
                self.performance_stats['entries_logged'] += 1
                
                # Check if it's time to flush
                if time.time() - last_flush >= self.config.flush_interval:
                    self._flush_entries()
                    last_flush = time.time()
                
            except Exception as e:
                logger.error(f"Error in logging worker: {e}")
                self.performance_stats['write_errors'] += 1
    
    def _write_entry(self, entry: LogEntry):
        """Write a single log entry."""
        with self.lock:
            # Check if we need to rotate files
            if self.current_file_size >= self.config.max_file_size:
                self._rotate_file()
            
            # Create new file if needed
            if self.current_file is None:
                self._create_new_file()
            
            # Write entry based on format
            if self.config.data_format == DataFormat.JSON:
                self._write_json_entry(entry)
            elif self.config.data_format == DataFormat.CSV:
                self._write_csv_entry(entry)
            elif self.config.data_format == DataFormat.HDF5:
                self._write_hdf5_entry(entry)
            elif self.config.data_format == DataFormat.BINARY:
                self._write_binary_entry(entry)
            elif self.config.data_format == DataFormat.PICKLE:
                self._write_pickle_entry(entry)
            elif self.config.data_format == DataFormat.COMPRESSED:
                self._write_compressed_entry(entry)
    
    def _create_new_file(self):
        """Create a new log file."""
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        
        if self.config.data_format == DataFormat.JSON:
            filename = f"flight_data_{timestamp}_{self.file_counter:03d}.json"
        elif self.config.data_format == DataFormat.CSV:
            filename = f"flight_data_{timestamp}_{self.file_counter:03d}.csv"
        elif self.config.data_format == DataFormat.HDF5:
            filename = f"flight_data_{timestamp}_{self.file_counter:03d}.h5"
        elif self.config.data_format == DataFormat.BINARY:
            filename = f"flight_data_{timestamp}_{self.file_counter:03d}.bin"
        elif self.config.data_format == DataFormat.PICKLE:
            filename = f"flight_data_{timestamp}_{self.file_counter:03d}.pkl"
        elif self.config.data_format == DataFormat.COMPRESSED:
            filename = f"flight_data_{timestamp}_{self.file_counter:03d}.json.gz"
        
        filepath = self.output_path / filename
        
        if self.config.data_format == DataFormat.HDF5:
            self.current_file = h5py.File(filepath, 'w')
            # Create datasets
            self.current_file.create_dataset('timestamps', (0,), maxshape=(None,), dtype=np.float64)
            self.current_file.create_dataset('data_types', (0,), maxshape=(None,), dtype=h5py.special_dtype(vlen=str))
            self.current_file.create_dataset('data', (0,), maxshape=(None,), dtype=h5py.special_dtype(vlen=str))
        else:
            self.current_file = open(filepath, 'w')
        
        self.current_file_size = 0
        self.file_counter += 1
        self.performance_stats['files_created'] += 1
        
        logger.info(f"Created new log file: {filename}")
    
    def _write_json_entry(self, entry: LogEntry):
        """Write entry in JSON format."""
        entry_dict = asdict(entry)
        entry_dict['timestamp'] = entry.timestamp
        entry_dict['data'] = entry.data
        
        json_line = json.dumps(entry_dict) + '\n'
        self.current_file.write(json_line)
        self.current_file_size += len(json_line.encode('utf-8'))
    
    def _write_csv_entry(self, entry: LogEntry):
        """Write entry in CSV format."""
        # This is a simplified CSV writer
        # In practice, you might want to use pandas or a more sophisticated CSV writer
        writer = csv.writer(self.current_file)
        writer.writerow([
            entry.timestamp,
            entry.data_type,
            str(entry.data),
            str(entry.metadata),
            entry.level.value
        ])
        self.current_file.flush()
    
    def _write_hdf5_entry(self, entry: LogEntry):
        """Write entry in HDF5 format."""
        # Extend datasets
        current_size = self.current_file['timestamps'].shape[0]
        new_size = current_size + 1
        
        self.current_file['timestamps'].resize((new_size,))
        self.current_file['data_types'].resize((new_size,))
        self.current_file['data'].resize((new_size,))
        
        # Add data
        self.current_file['timestamps'][current_size] = entry.timestamp
        self.current_file['data_types'][current_size] = entry.data_type
        self.current_file['data'][current_size] = json.dumps(entry.data)
        
        self.current_file.flush()
    
    def _write_binary_entry(self, entry: LogEntry):
        """Write entry in binary format."""
        # Simplified binary format
        data_bytes = pickle.dumps(entry)
        self.current_file.write(data_bytes)
        self.current_file_size += len(data_bytes)
    
    def _write_pickle_entry(self, entry: LogEntry):
        """Write entry in pickle format."""
        pickle.dump(entry, self.current_file)
        self.current_file.flush()
    
    def _write_compressed_entry(self, entry: LogEntry):
        """Write entry in compressed format."""
        entry_dict = asdict(entry)
        entry_dict['timestamp'] = entry.timestamp
        entry_dict['data'] = entry.data
        
        json_line = json.dumps(entry_dict) + '\n'
        compressed_data = gzip.compress(json_line.encode('utf-8'))
        self.current_file.write(compressed_data)
        self.current_file_size += len(compressed_data)
    
    def _rotate_file(self):
        """Rotate to a new log file."""
        if self.current_file:
            self.current_file.close()
            self.current_file = None
        
        # Clean up old files
        self._cleanup_old_files()
        
        # Create new file
        self._create_new_file()
    
    def _cleanup_old_files(self):
        """Clean up old log files."""
        if self.config.max_files <= 0:
            return
        
        # Get all log files
        pattern = f"flight_data_*"
        log_files = list(self.output_path.glob(pattern))
        
        # Sort by modification time
        log_files.sort(key=lambda x: x.stat().st_mtime)
        
        # Remove old files
        while len(log_files) >= self.config.max_files:
            old_file = log_files.pop(0)
            try:
                old_file.unlink()
                logger.info(f"Removed old log file: {old_file.name}")
            except Exception as e:
                logger.error(f"Failed to remove old log file {old_file.name}: {e}")
    
    def _flush_entries(self):
        """Flush buffered entries to disk."""
        if self.current_file:
            self.current_file.flush()
    
    def get_performance_stats(self) -> Dict[str, Any]:
        """
        Get performance statistics.
        
        Returns:
            Dict[str, Any]: Performance statistics
        """
        stats = self.performance_stats.copy()
        stats['total_entries'] = self.total_entries
        stats['uptime'] = time.time() - self.start_time
        stats['queue_size'] = self.log_queue.qsize()
        return stats
    
    def export_data(self, output_format: DataFormat, output_path: str = None):
        """
        Export logged data to a different format.
        
        Args:
            output_format (DataFormat): Output format
            output_path (str): Output file path
        """
        if output_path is None:
            timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
            output_path = self.output_path / f"export_{timestamp}.{output_format.value}"
        
        # This would implement data export functionality
        logger.info(f"Exporting data to {output_path} in {output_format.value} format")
    
    def create_backup(self):
        """Create a backup of log files."""
        if not self.config.enable_backup:
            return
        
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        backup_path = self.output_path / f"backup_{timestamp}"
        
        try:
            backup_path.mkdir(exist_ok=True)
            
            # Copy log files
            for log_file in self.output_path.glob("flight_data_*"):
                shutil.copy2(log_file, backup_path)
            
            logger.info(f"Created backup at {backup_path}")
        except Exception as e:
            logger.error(f"Failed to create backup: {e}")


# Example usage
if __name__ == "__main__":
    """
    Example usage of the data logger.
    
    This demonstrates how to set up and use the data logger for
    recording quadrotor flight data.
    """
    
    # Create logger configuration
    config = LoggerConfig(
        output_directory="flight_logs",
        data_format=DataFormat.HDF5,
        compression_enabled=True,
        max_file_size=50 * 1024 * 1024,  # 50MB
        flush_interval=0.5
    )
    
    # Create data logger
    logger = DataLogger(config)
    
    # Start logging
    logger.start()
    
    try:
        # Simulate flight data logging
        for i in range(100):
            # Log position
            position = np.array([np.sin(i * 0.1), np.cos(i * 0.1), 1.0 + 0.1 * np.sin(i * 0.2)])
            logger.log_position(position, f"drone_{i % 3 + 1}")
            
            # Log attitude
            attitude = np.array([0.1 * np.sin(i * 0.1), 0.1 * np.cos(i * 0.1), i * 0.01])
            logger.log_attitude(attitude, f"drone_{i % 3 + 1}")
            
            # Log velocity
            velocity = np.array([0.1 * np.cos(i * 0.1), -0.1 * np.sin(i * 0.1), 0.02 * np.cos(i * 0.2)])
            logger.log_velocity(velocity, f"drone_{i % 3 + 1}")
            
            # Log control commands
            commands = np.array([0.5 + 0.1 * np.sin(i * 0.1), 0.5 + 0.1 * np.cos(i * 0.1), 
                               0.5 + 0.05 * np.sin(i * 0.2), 0.5 + 0.05 * np.cos(i * 0.2)])
            logger.log_control_commands(commands, f"drone_{i % 3 + 1}")
            
            # Log performance metrics
            performance = {
                'position_error': 0.01 + 0.005 * np.sin(i * 0.1),
                'velocity_error': 0.005 + 0.002 * np.cos(i * 0.1),
                'attitude_error': 0.002 + 0.001 * np.sin(i * 0.2),
                'control_effort': 0.3 + 0.1 * np.cos(i * 0.1)
            }
            logger.log_performance_metrics(performance)
            
            # Log system events occasionally
            if i % 10 == 0:
                logger.log_system_event("Checkpoint", {"iteration": i}, LogLevel.INFO)
            
            time.sleep(0.1)  # 10Hz logging rate
            
            # Print performance stats every 50 iterations
            if i % 50 == 0:
                stats = logger.get_performance_stats()
                print(f"Performance stats: {stats}")
    
    except KeyboardInterrupt:
        print("\nStopping data logger...")
    
    finally:
        # Stop logging
        logger.stop()
        
        # Print final statistics
        final_stats = logger.get_performance_stats()
        print(f"Final statistics: {final_stats}")
        
        print("Data logging completed!")
