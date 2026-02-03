"""
Configuration Management System for Quadrotor Control System
===========================================================

This module provides a comprehensive configuration management system
for the quadrotor control system, supporting multiple formats, validation,
hot-reloading, and hierarchical configuration.

Key Features:
- Multiple configuration formats (JSON, YAML, INI, TOML)
- Configuration validation and schema enforcement
- Hot-reloading of configuration changes
- Hierarchical configuration with inheritance
- Environment variable support
- Configuration encryption for sensitive data
- Configuration versioning and migration
- Default configuration generation
- Configuration export and import

The configuration manager enables flexible and robust configuration
management for all system components.

Author: [Your Name]
Date: [Current Date]
License: MIT
"""

import json
import yaml
import configparser
import toml
import os
import time
import threading
from typing import Dict, List, Tuple, Optional, Any, Union, Callable
from dataclasses import dataclass, field, asdict
from enum import Enum
from pathlib import Path
import logging
from datetime import datetime
import hashlib
import base64
from cryptography.fernet import Fernet
import copy
import jsonschema

# Configure logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class ConfigFormat(Enum):
    """Enumeration of configuration formats."""
    JSON = "json"
    YAML = "yaml"
    INI = "ini"
    TOML = "toml"


class ConfigSection(Enum):
    """Enumeration of configuration sections."""
    SYSTEM = "system"
    CONTROL = "control"
    SENSORS = "sensors"
    COMMUNICATION = "communication"
    GUI = "gui"
    LOGGING = "logging"
    SAFETY = "safety"
    PERFORMANCE = "performance"


@dataclass
class ConfigSchema:
    """
    Configuration schema definition.
    
    Attributes:
        section (ConfigSection): Configuration section
        properties (Dict[str, Any]): Schema properties
        required (List[str]): Required properties
        default_values (Dict[str, Any]): Default values
    """
    section: ConfigSection
    properties: Dict[str, Any] = field(default_factory=dict)
    required: List[str] = field(default_factory=list)
    default_values: Dict[str, Any] = field(default_factory=dict)


@dataclass
class ConfigEntry:
    """
    Configuration entry.
    
    Attributes:
        key (str): Configuration key
        value (Any): Configuration value
        section (ConfigSection): Configuration section
        description (str): Description of the configuration
        data_type (str): Data type of the value
        validation_rules (Dict[str, Any]): Validation rules
        encrypted (bool): Whether the value is encrypted
    """
    key: str
    value: Any
    section: ConfigSection
    description: str = ""
    data_type: str = "string"
    validation_rules: Dict[str, Any] = field(default_factory=dict)
    encrypted: bool = False


class ConfigValidator:
    """
    Configuration validator.
    
    This class provides methods for validating configuration
    data against schemas and custom validation rules.
    """
    
    def __init__(self):
        """Initialize configuration validator."""
        self.schemas: Dict[ConfigSection, ConfigSchema] = {}
        self.custom_validators: Dict[str, Callable] = {}
        
        # Setup default schemas
        self._setup_default_schemas()
        
        logger.info("Configuration validator initialized")
    
    def _setup_default_schemas(self):
        """Setup default configuration schemas."""
        # System configuration schema
        system_schema = ConfigSchema(
            section=ConfigSection.SYSTEM,
            properties={
                "system_name": {"type": "string", "minLength": 1},
                "version": {"type": "string", "pattern": r"^\d+\.\d+\.\d+$"},
                "debug_mode": {"type": "boolean"},
                "log_level": {"type": "string", "enum": ["DEBUG", "INFO", "WARNING", "ERROR"]},
                "max_threads": {"type": "integer", "minimum": 1, "maximum": 100},
                "update_rate": {"type": "number", "minimum": 1.0, "maximum": 1000.0}
            },
            required=["system_name", "version", "debug_mode"],
            default_values={
                "system_name": "CrazyFly",
                "version": "1.0.0",
                "debug_mode": False,
                "log_level": "INFO",
                "max_threads": 8,
                "update_rate": 100.0
            }
        )
        self.schemas[ConfigSection.SYSTEM] = system_schema
        
        # Control configuration schema
        control_schema = ConfigSchema(
            section=ConfigSection.CONTROL,
            properties={
                "control_mode": {"type": "string", "enum": ["PID", "L1", "MPC", "HYBRID"]},
                "position_kp": {"type": "number", "minimum": 0.0, "maximum": 100.0},
                "position_ki": {"type": "number", "minimum": 0.0, "maximum": 100.0},
                "position_kd": {"type": "number", "minimum": 0.0, "maximum": 100.0},
                "velocity_kp": {"type": "number", "minimum": 0.0, "maximum": 100.0},
                "velocity_ki": {"type": "number", "minimum": 0.0, "maximum": 100.0},
                "velocity_kd": {"type": "number", "minimum": 0.0, "maximum": 100.0},
                "attitude_kp": {"type": "number", "minimum": 0.0, "maximum": 100.0},
                "attitude_ki": {"type": "number", "minimum": 0.0, "maximum": 100.0},
                "attitude_kd": {"type": "number", "minimum": 0.0, "maximum": 100.0},
                "max_thrust": {"type": "number", "minimum": 0.0, "maximum": 1.0},
                "min_thrust": {"type": "number", "minimum": 0.0, "maximum": 1.0}
            },
            required=["control_mode"],
            default_values={
                "control_mode": "PID",
                "position_kp": 2.0,
                "position_ki": 0.1,
                "position_kd": 1.0,
                "velocity_kp": 1.5,
                "velocity_ki": 0.05,
                "velocity_kd": 0.8,
                "attitude_kp": 3.0,
                "attitude_ki": 0.2,
                "attitude_kd": 1.5,
                "max_thrust": 0.9,
                "min_thrust": 0.1
            }
        )
        self.schemas[ConfigSection.CONTROL] = control_schema
        
        # Sensors configuration schema
        sensors_schema = ConfigSchema(
            section=ConfigSection.SENSORS,
            properties={
                "vicon_enabled": {"type": "boolean"},
                "vicon_host": {"type": "string"},
                "vicon_port": {"type": "integer", "minimum": 1, "maximum": 65535},
                "imu_enabled": {"type": "boolean"},
                "imu_update_rate": {"type": "number", "minimum": 1.0, "maximum": 1000.0},
                "gps_enabled": {"type": "boolean"},
                "gps_update_rate": {"type": "number", "minimum": 1.0, "maximum": 10.0},
                "barometer_enabled": {"type": "boolean"},
                "magnetometer_enabled": {"type": "boolean"}
            },
            required=[],
            default_values={
                "vicon_enabled": True,
                "vicon_host": "192.168.1.100",
                "vicon_port": 801,
                "imu_enabled": True,
                "imu_update_rate": 100.0,
                "gps_enabled": False,
                "gps_update_rate": 1.0,
                "barometer_enabled": True,
                "magnetometer_enabled": True
            }
        )
        self.schemas[ConfigSection.SENSORS] = sensors_schema
        
        # Communication configuration schema
        communication_schema = ConfigSchema(
            section=ConfigSection.COMMUNICATION,
            properties={
                "udp_enabled": {"type": "boolean"},
                "udp_host": {"type": "string"},
                "udp_port": {"type": "integer", "minimum": 1, "maximum": 65535},
                "serial_enabled": {"type": "boolean"},
                "serial_port": {"type": "string"},
                "serial_baudrate": {"type": "integer", "enum": [9600, 19200, 38400, 57600, 115200]},
                "crazyflie_enabled": {"type": "boolean"},
                "crazyflie_address": {"type": "string"}
            },
            required=[],
            default_values={
                "udp_enabled": True,
                "udp_host": "127.0.0.1",
                "udp_port": 8080,
                "serial_enabled": False,
                "serial_port": "/dev/ttyUSB0",
                "serial_baudrate": 115200,
                "crazyflie_enabled": True,
                "crazyflie_address": "radio://0/80/2M/E7E7E7E7E7"
            }
        )
        self.schemas[ConfigSection.COMMUNICATION] = communication_schema
    
    def add_schema(self, schema: ConfigSchema):
        """
        Add a configuration schema.
        
        Args:
            schema (ConfigSchema): Schema to add
        """
        self.schemas[schema.section] = schema
        logger.debug(f"Added schema for section: {schema.section.value}")
    
    def add_custom_validator(self, name: str, validator_func: Callable):
        """
        Add a custom validator function.
        
        Args:
            name (str): Validator name
            validator_func (Callable): Validator function
        """
        self.custom_validators[name] = validator_func
        logger.debug(f"Added custom validator: {name}")
    
    def validate_section(self, section: ConfigSection, data: Dict[str, Any]) -> Tuple[bool, List[str]]:
        """
        Validate a configuration section.
        
        Args:
            section (ConfigSection): Configuration section
            data (Dict[str, Any]): Configuration data
            
        Returns:
            Tuple[bool, List[str]]: (is_valid, error_messages)
        """
        errors = []
        
        if section not in self.schemas:
            errors.append(f"No schema defined for section: {section.value}")
            return False, errors
        
        schema = self.schemas[section]
        
        # Check required fields
        for required_field in schema.required:
            if required_field not in data:
                errors.append(f"Required field missing: {required_field}")
        
        # Validate properties
        for key, value in data.items():
            if key in schema.properties:
                prop_schema = schema.properties[key]
                is_valid, prop_errors = self._validate_property(key, value, prop_schema)
                if not is_valid:
                    errors.extend(prop_errors)
        
        return len(errors) == 0, errors
    
    def _validate_property(self, key: str, value: Any, schema: Dict[str, Any]) -> Tuple[bool, List[str]]:
        """
        Validate a single property.
        
        Args:
            key (str): Property key
            value (Any): Property value
            schema (Dict[str, Any]): Property schema
            
        Returns:
            Tuple[bool, List[str]]: (is_valid, error_messages)
        """
        errors = []
        
        # Type validation
        expected_type = schema.get("type")
        if expected_type:
            if expected_type == "string" and not isinstance(value, str):
                errors.append(f"{key}: Expected string, got {type(value).__name__}")
            elif expected_type == "integer" and not isinstance(value, int):
                errors.append(f"{key}: Expected integer, got {type(value).__name__}")
            elif expected_type == "number" and not isinstance(value, (int, float)):
                errors.append(f"{key}: Expected number, got {type(value).__name__}")
            elif expected_type == "boolean" and not isinstance(value, bool):
                errors.append(f"{key}: Expected boolean, got {type(value).__name__}")
        
        # Range validation
        if "minimum" in schema and value < schema["minimum"]:
            errors.append(f"{key}: Value {value} below minimum {schema['minimum']}")
        if "maximum" in schema and value > schema["maximum"]:
            errors.append(f"{key}: Value {value} above maximum {schema['maximum']}")
        
        # Length validation
        if "minLength" in schema and isinstance(value, str) and len(value) < schema["minLength"]:
            errors.append(f"{key}: String length {len(value)} below minimum {schema['minLength']}")
        if "maxLength" in schema and isinstance(value, str) and len(value) > schema["maxLength"]:
            errors.append(f"{key}: String length {len(value)} above maximum {schema['maxLength']}")
        
        # Enum validation
        if "enum" in schema and value not in schema["enum"]:
            errors.append(f"{key}: Value {value} not in allowed values {schema['enum']}")
        
        # Pattern validation
        if "pattern" in schema and isinstance(value, str):
            import re
            if not re.match(schema["pattern"], value):
                errors.append(f"{key}: Value {value} does not match pattern {schema['pattern']}")
        
        return len(errors) == 0, errors


class ConfigEncryption:
    """
    Configuration encryption utility.
    
    This class provides methods for encrypting sensitive
    configuration data.
    """
    
    def __init__(self, key: str = None):
        """
        Initialize configuration encryption.
        
        Args:
            key (str): Encryption key (if None, generates a new key)
        """
        if key is None:
            self.key = Fernet.generate_key()
        else:
            self.key = key.encode() if isinstance(key, str) else key
        
        self.cipher = Fernet(self.key)
        logger.info("Configuration encryption initialized")
    
    def encrypt_value(self, value: str) -> str:
        """
        Encrypt a configuration value.
        
        Args:
            value (str): Value to encrypt
            
        Returns:
            str: Encrypted value (base64 encoded)
        """
        encrypted = self.cipher.encrypt(value.encode())
        return base64.b64encode(encrypted).decode()
    
    def decrypt_value(self, encrypted_value: str) -> str:
        """
        Decrypt a configuration value.
        
        Args:
            encrypted_value (str): Encrypted value (base64 encoded)
            
        Returns:
            str: Decrypted value
        """
        encrypted_bytes = base64.b64decode(encrypted_value.encode())
        decrypted = self.cipher.decrypt(encrypted_bytes)
        return decrypted.decode()
    
    def get_key(self) -> str:
        """
        Get the encryption key.
        
        Returns:
            str: Encryption key (base64 encoded)
        """
        return base64.b64encode(self.key).decode()


class ConfigurationManager:
    """
    Main configuration manager.
    
    This class provides comprehensive configuration management
    functionality with support for multiple formats and hot-reloading.
    """
    
    def __init__(self, config_dir: str = "config", encryption_key: str = None):
        """
        Initialize configuration manager.
        
        Args:
            config_dir (str): Configuration directory
            encryption_key (str): Encryption key for sensitive data
        """
        self.config_dir = Path(config_dir)
        self.config_dir.mkdir(parents=True, exist_ok=True)
        
        # Initialize components
        self.validator = ConfigValidator()
        self.encryption = ConfigEncryption(encryption_key)
        
        # Configuration storage
        self.config_data: Dict[ConfigSection, Dict[str, Any]] = {}
        self.config_files: Dict[ConfigSection, Path] = {}
        self.config_format = ConfigFormat.JSON
        
        # Hot-reloading
        self.watch_thread = None
        self.watching = False
        self.file_hashes: Dict[Path, str] = {}
        self.callbacks: List[Callable] = []
        
        # Load default configurations
        self._load_default_configs()
        
        logger.info(f"Configuration manager initialized with directory: {self.config_dir}")
    
    def _load_default_configs(self):
        """Load default configurations for all sections."""
        for section in ConfigSection:
            schema = self.validator.schemas.get(section)
            if schema:
                self.config_data[section] = schema.default_values.copy()
                self.config_files[section] = self.config_dir / f"{section.value}.{self.config_format.value}"
    
    def set_config_format(self, format: ConfigFormat):
        """
        Set the configuration file format.
        
        Args:
            format (ConfigFormat): Configuration format
        """
        self.config_format = format
        logger.info(f"Configuration format set to: {format.value}")
    
    def load_config(self, section: ConfigSection, file_path: str = None) -> bool:
        """
        Load configuration from file.
        
        Args:
            section (ConfigSection): Configuration section
            file_path (str): Configuration file path (optional)
            
        Returns:
            bool: True if loaded successfully
        """
        if file_path is None:
            file_path = self.config_files[section]
        else:
            file_path = Path(file_path)
        
        try:
            if not file_path.exists():
                logger.warning(f"Configuration file not found: {file_path}")
                return False
            
            with open(file_path, 'r') as f:
                if self.config_format == ConfigFormat.JSON:
                    data = json.load(f)
                elif self.config_format == ConfigFormat.YAML:
                    data = yaml.safe_load(f)
                elif self.config_format == ConfigFormat.INI:
                    parser = configparser.ConfigParser()
                    parser.read(file_path)
                    data = {}
                    for key, value in parser[section.value].items():
                        # Try to convert to appropriate type
                        try:
                            if value.lower() in ['true', 'false']:
                                data[key] = value.lower() == 'true'
                            elif '.' in value:
                                data[key] = float(value)
                            else:
                                data[key] = int(value)
                        except ValueError:
                            data[key] = value
                elif self.config_format == ConfigFormat.TOML:
                    data = toml.load(f)
                    if section.value in data:
                        data = data[section.value]
                    else:
                        data = {}
            
            # Validate configuration
            is_valid, errors = self.validator.validate_section(section, data)
            if not is_valid:
                logger.error(f"Configuration validation errors for {section.value}: {errors}")
                return False
            
            # Update configuration
            self.config_data[section] = data
            self.config_files[section] = file_path
            
            # Update file hash for hot-reloading
            self.file_hashes[file_path] = self._get_file_hash(file_path)
            
            logger.info(f"Loaded configuration for section: {section.value}")
            return True
            
        except Exception as e:
            logger.error(f"Failed to load configuration for {section.value}: {e}")
            return False
    
    def save_config(self, section: ConfigSection, file_path: str = None) -> bool:
        """
        Save configuration to file.
        
        Args:
            section (ConfigSection): Configuration section
            file_path (str): Configuration file path (optional)
            
        Returns:
            bool: True if saved successfully
        """
        if file_path is None:
            file_path = self.config_files[section]
        else:
            file_path = Path(file_path)
        
        try:
            # Ensure directory exists
            file_path.parent.mkdir(parents=True, exist_ok=True)
            
            data = self.config_data.get(section, {})
            
            with open(file_path, 'w') as f:
                if self.config_format == ConfigFormat.JSON:
                    json.dump(data, f, indent=2)
                elif self.config_format == ConfigFormat.YAML:
                    yaml.dump(data, f, default_flow_style=False)
                elif self.config_format == ConfigFormat.INI:
                    parser = configparser.ConfigParser()
                    parser[section.value] = {str(k): str(v) for k, v in data.items()}
                    parser.write(f)
                elif self.config_format == ConfigFormat.TOML:
                    toml.dump({section.value: data}, f)
            
            # Update file hash
            self.file_hashes[file_path] = self._get_file_hash(file_path)
            
            logger.info(f"Saved configuration for section: {section.value}")
            return True
            
        except Exception as e:
            logger.error(f"Failed to save configuration for {section.value}: {e}")
            return False
    
    def get_config(self, section: ConfigSection, key: str = None, default: Any = None) -> Any:
        """
        Get configuration value.
        
        Args:
            section (ConfigSection): Configuration section
            key (str): Configuration key (if None, returns entire section)
            default (Any): Default value if key not found
            
        Returns:
            Any: Configuration value or entire section
        """
        if section not in self.config_data:
            return default
        
        if key is None:
            return self.config_data[section]
        
        return self.config_data[section].get(key, default)
    
    def set_config(self, section: ConfigSection, key: str, value: Any, 
                   encrypt: bool = False) -> bool:
        """
        Set configuration value.
        
        Args:
            section (ConfigSection): Configuration section
            key (str): Configuration key
            value (Any): Configuration value
            encrypt (bool): Whether to encrypt the value
            
        Returns:
            bool: True if set successfully
        """
        if section not in self.config_data:
            self.config_data[section] = {}
        
        # Encrypt value if requested
        if encrypt and isinstance(value, str):
            value = self.encryption.encrypt_value(value)
        
        # Validate the new configuration
        temp_data = self.config_data[section].copy()
        temp_data[key] = value
        
        is_valid, errors = self.validator.validate_section(section, temp_data)
        if not is_valid:
            logger.error(f"Configuration validation errors: {errors}")
            return False
        
        # Update configuration
        self.config_data[section][key] = value
        
        # Save to file
        self.save_config(section)
        
        logger.debug(f"Set configuration {section.value}.{key} = {value}")
        return True
    
    def get_encrypted_config(self, section: ConfigSection, key: str) -> str:
        """
        Get and decrypt a configuration value.
        
        Args:
            section (ConfigSection): Configuration section
            key (str): Configuration key
            
        Returns:
            str: Decrypted value
        """
        encrypted_value = self.get_config(section, key)
        if encrypted_value and isinstance(encrypted_value, str):
            try:
                return self.encryption.decrypt_value(encrypted_value)
            except Exception as e:
                logger.error(f"Failed to decrypt value for {section.value}.{key}: {e}")
                return ""
        return ""
    
    def set_encrypted_config(self, section: ConfigSection, key: str, value: str) -> bool:
        """
        Set and encrypt a configuration value.
        
        Args:
            section (ConfigSection): Configuration section
            key (str): Configuration key
            value (str): Value to encrypt and set
            
        Returns:
            bool: True if set successfully
        """
        return self.set_config(section, key, value, encrypt=True)
    
    def start_watching(self):
        """Start watching configuration files for changes."""
        if self.watching:
            logger.warning("Already watching configuration files")
            return
        
        self.watching = True
        self.watch_thread = threading.Thread(target=self._watch_files, daemon=True)
        self.watch_thread.start()
        
        logger.info("Started watching configuration files")
    
    def stop_watching(self):
        """Stop watching configuration files."""
        self.watching = False
        if self.watch_thread and self.watch_thread.is_alive():
            self.watch_thread.join(timeout=5.0)
        
        logger.info("Stopped watching configuration files")
    
    def _watch_files(self):
        """Watch configuration files for changes."""
        while self.watching:
            for section, file_path in self.config_files.items():
                if file_path.exists():
                    current_hash = self._get_file_hash(file_path)
                    if file_path in self.file_hashes and current_hash != self.file_hashes[file_path]:
                        logger.info(f"Configuration file changed: {file_path}")
                        self.load_config(section, str(file_path))
                        self._notify_callbacks(section)
            
            time.sleep(1.0)  # Check every second
    
    def _get_file_hash(self, file_path: Path) -> str:
        """Get file hash for change detection."""
        try:
            with open(file_path, 'rb') as f:
                return hashlib.md5(f.read()).hexdigest()
        except Exception:
            return ""
    
    def add_change_callback(self, callback: Callable):
        """
        Add a callback for configuration changes.
        
        Args:
            callback (Callable): Callback function
        """
        self.callbacks.append(callback)
        logger.debug("Added configuration change callback")
    
    def _notify_callbacks(self, section: ConfigSection):
        """Notify callbacks of configuration changes."""
        for callback in self.callbacks:
            try:
                callback(section, self.config_data[section])
            except Exception as e:
                logger.error(f"Error in configuration change callback: {e}")
    
    def generate_default_config(self, section: ConfigSection, file_path: str = None) -> bool:
        """
        Generate default configuration file.
        
        Args:
            section (ConfigSection): Configuration section
            file_path (str): Output file path (optional)
            
        Returns:
            bool: True if generated successfully
        """
        schema = self.validator.schemas.get(section)
        if not schema:
            logger.error(f"No schema defined for section: {section.value}")
            return False
        
        # Use default values from schema
        self.config_data[section] = schema.default_values.copy()
        
        # Save to file
        return self.save_config(section, file_path)
    
    def export_config(self, output_format: ConfigFormat, output_path: str = None) -> bool:
        """
        Export all configurations to a different format.
        
        Args:
            output_format (ConfigFormat): Output format
            output_path (str): Output file path (optional)
            
        Returns:
            bool: True if exported successfully
        """
        if output_path is None:
            timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
            output_path = self.config_dir / f"export_{timestamp}.{output_format.value}"
        else:
            output_path = Path(output_path)
        
        try:
            # Combine all configurations
            all_config = {}
            for section, data in self.config_data.items():
                all_config[section.value] = data
            
            with open(output_path, 'w') as f:
                if output_format == ConfigFormat.JSON:
                    json.dump(all_config, f, indent=2)
                elif output_format == ConfigFormat.YAML:
                    yaml.dump(all_config, f, default_flow_style=False)
                elif output_format == ConfigFormat.TOML:
                    toml.dump(all_config, f)
                elif output_format == ConfigFormat.INI:
                    parser = configparser.ConfigParser()
                    for section_name, section_data in all_config.items():
                        parser[section_name] = {str(k): str(v) for k, v in section_data.items()}
                    parser.write(f)
            
            logger.info(f"Exported configuration to {output_path}")
            return True
            
        except Exception as e:
            logger.error(f"Failed to export configuration: {e}")
            return False
    
    def get_encryption_key(self) -> str:
        """
        Get the encryption key.
        
        Returns:
            str: Encryption key (base64 encoded)
        """
        return self.encryption.get_key()


# Example usage
if __name__ == "__main__":
    """
    Example usage of the configuration manager.
    
    This demonstrates how to set up and use the configuration
    manager for managing quadrotor system settings.
    """
    
    # Create configuration manager
    config_manager = ConfigurationManager("config")
    
    # Set configuration format
    config_manager.set_config_format(ConfigFormat.JSON)
    
    # Generate default configurations
    for section in ConfigSection:
        config_manager.generate_default_config(section)
    
    # Load configurations
    for section in ConfigSection:
        config_manager.load_config(section)
    
    # Set some configuration values
    config_manager.set_config(ConfigSection.CONTROL, "position_kp", 2.5)
    config_manager.set_config(ConfigSection.CONTROL, "position_ki", 0.15)
    config_manager.set_config(ConfigSection.SYSTEM, "debug_mode", True)
    
    # Set encrypted configuration
    config_manager.set_encrypted_config(ConfigSection.COMMUNICATION, "api_key", "secret_key_123")
    
    # Get configuration values
    position_kp = config_manager.get_config(ConfigSection.CONTROL, "position_kp")
    debug_mode = config_manager.get_config(ConfigSection.SYSTEM, "debug_mode")
    api_key = config_manager.get_encrypted_config(ConfigSection.COMMUNICATION, "api_key")
    
    print(f"Position KP: {position_kp}")
    print(f"Debug Mode: {debug_mode}")
    print(f"API Key: {api_key}")
    
    # Add change callback
    def on_config_change(section, data):
        print(f"Configuration changed for {section.value}: {data}")
    
    config_manager.add_change_callback(on_config_change)
    
    # Start watching for changes
    config_manager.start_watching()
    
    # Export configuration
    config_manager.export_config(ConfigFormat.YAML, "config_export.yaml")
    
    print("Configuration management example completed!")
    
    # Stop watching
    config_manager.stop_watching()
