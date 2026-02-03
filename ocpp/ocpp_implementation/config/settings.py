"""
OCPP 2.1 Configuration Settings

This module provides configuration management for the OCPP 2.1 implementation.
It includes settings for both CSMS (server) and CP (client) components.
"""

import os
import uuid
from typing import Optional, List, Dict, Any
from pydantic import BaseModel, Field


class DatabaseConfig(BaseModel):
    """Database configuration settings"""
    
    url: str = Field(default="sqlite:///ocpp.db", description="Database URL")
    echo: bool = Field(default=False, description="Enable SQL query logging")
    pool_size: int = Field(default=5, description="Connection pool size")
    max_overflow: int = Field(default=10, description="Maximum overflow connections")
    pool_timeout: int = Field(default=30, description="Pool timeout in seconds")
    pool_recycle: int = Field(default=3600, description="Pool recycle time in seconds")


class CSMSConfig(BaseModel):
    """CSMS (Central System Management System) configuration"""
    
    host: str = Field(default="0.0.0.0", description="CSMS server host")
    port: int = Field(default=9000, description="CSMS server port")
    max_connections: int = Field(default=1000, description="Maximum concurrent connections")
    connection_timeout: int = Field(default=30, description="Connection timeout in seconds")
    heartbeat_interval: int = Field(default=300, description="Heartbeat interval in seconds")
    message_timeout: int = Field(default=30, description="Message timeout in seconds")
    websocket_ping_interval: int = Field(default=20, description="WebSocket ping interval in seconds")
    websocket_ping_timeout: int = Field(default=10, description="WebSocket ping timeout in seconds")
    websocket_max_size: int = Field(default=2**20, description="WebSocket maximum message size in bytes")
    enable_tls: bool = Field(default=False, description="Enable TLS/SSL")
    cert_file: Optional[str] = Field(default=None, description="Certificate file path")
    key_file: Optional[str] = Field(default=None, description="Private key file path")
    ca_file: Optional[str] = Field(default=None, description="CA certificate file path")
    require_client_cert: bool = Field(default=False, description="Require client certificates")


class CPConfig(BaseModel):
    """CP (Charge Point) configuration"""
    
    station_id: str = Field(default_factory=lambda: f"CP{uuid.uuid4().hex[:4].upper()}", description="Charge Point station ID")
    model: str = Field(default="Generic OCPP 2.1 CP", description="Charge Point model")
    vendor_name: str = Field(default="OCPP Implementation", description="Charge Point vendor name")
    serial_number: str = Field(default="N908FCSON_CP01", description="Charge Point serial number")
    firmware_version: str = Field(default="1.0.0", description="Charge Point firmware version")
    csms_url: str = Field(default="ws://localhost:9000", description="CSMS WebSocket URL")
    reconnect_interval: int = Field(default=30, description="Reconnect interval in seconds")
    max_reconnect_attempts: int = Field(default=10, description="Maximum reconnect attempts")
    heartbeat_interval: int = Field(default=8, description="Heartbeat interval in seconds")
    message_timeout: int = Field(default=30, description="Message timeout in seconds")
    enable_tls: bool = Field(default=False, description="Enable TLS/SSL")
    cert_file: Optional[str] = Field(default=None, description="Certificate file path")
    key_file: Optional[str] = Field(default=None, description="Private key file path")
    ca_file: Optional[str] = Field(default=None, description="CA certificate file path")
    verify_cert: bool = Field(default=True, description="Verify server certificate")


class LoggingConfig(BaseModel):
    """Logging configuration"""
    
    level: str = Field(default="INFO", description="Logging level")
    format: str = Field(default="%(asctime)s - %(name)s - %(levelname)s - %(message)s", description="Log format")
    file_path: Optional[str] = Field(default="ocpp.log", description="Log file path")
    max_file_size: int = Field(default=10485760, description="Maximum log file size in bytes")
    backup_count: int = Field(default=5, description="Number of backup log files")
    enable_console: bool = Field(default=True, description="Enable console logging")
    enable_file: bool = Field(default=True, description="Enable file logging")
    json_format: bool = Field(default=False, description="Use JSON format for logs")


class SecurityConfig(BaseModel):
    """Security configuration"""
    
    enable_auth: bool = Field(default=False, description="Enable authentication")
    auth_method: str = Field(default="basic", description="Authentication method")
    jwt_secret: Optional[str] = Field(default=None, description="JWT secret key")
    jwt_expiry: int = Field(default=3600, description="JWT expiry time in seconds")
    enable_encryption: bool = Field(default=False, description="Enable message encryption")
    encryption_key: Optional[str] = Field(default=None, description="Encryption key")
    enable_rate_limiting: bool = Field(default=True, description="Enable rate limiting")
    rate_limit_requests: int = Field(default=100, description="Rate limit requests per minute")
    rate_limit_window: int = Field(default=60, description="Rate limit window in seconds")


class MonitoringConfig(BaseModel):
    """Monitoring and metrics configuration"""
    
    enable_metrics: bool = Field(default=True, description="Enable metrics collection")
    metrics_port: int = Field(default=9090, description="Metrics server port")
    enable_health_check: bool = Field(default=True, description="Enable health check endpoint")
    health_check_port: int = Field(default=8080, description="Health check server port")
    enable_tracing: bool = Field(default=False, description="Enable distributed tracing")
    tracing_endpoint: Optional[str] = Field(default=None, description="Tracing endpoint URL")
    enable_profiling: bool = Field(default=False, description="Enable performance profiling")


class OCPPSettings(BaseModel):
    """Main OCPP configuration settings"""
    
    # Environment
    environment: str = Field(default="development", description="Environment (development, staging, production)")
    debug: bool = Field(default=False, description="Enable debug mode")
    
    # Component configurations
    database: DatabaseConfig = Field(default_factory=DatabaseConfig)
    csms: CSMSConfig = Field(default_factory=CSMSConfig)
    cp: CPConfig = Field(default_factory=CPConfig)
    logging: LoggingConfig = Field(default_factory=LoggingConfig)
    security: SecurityConfig = Field(default_factory=SecurityConfig)
    monitoring: MonitoringConfig = Field(default_factory=MonitoringConfig)
    
    # OCPP specific settings
    ocpp_version: str = Field(default="2.1", description="OCPP version")
    supported_profiles: List[str] = Field(
        default=[
            "Core", "SmartCharging", "Security", "FirmwareManagement",
            "LocalAuthListManagement", "Reservation", "TariffAndCost",
            "DisplayMessage", "ISO15118Pnc", "ISO15118GeneralMessages"
        ],
        description="Supported OCPP profiles"
    )
    
    # Custom settings
    custom_settings: Dict[str, Any] = Field(default_factory=dict, description="Custom settings")
    
    class Config:
        """Pydantic configuration"""
        env_prefix = "OCPP_"
        case_sensitive = False
        validate_assignment = True
        use_enum_values = True


# Global settings instance
_settings: Optional[OCPPSettings] = None


def get_settings() -> OCPPSettings:
    """
    Get the global settings instance.
    
    This function returns a singleton instance of the settings,
    loading from environment variables if not already initialized.
    
    Returns:
        OCPPSettings: The global settings instance
    """
    global _settings
    
    if _settings is None:
        # Load from environment variables
        _settings = OCPPSettings()
        
        # Override with environment variables if present
        if os.getenv("OCPP_ENVIRONMENT"):
            _settings.environment = os.getenv("OCPP_ENVIRONMENT")
        
        if os.getenv("OCPP_DEBUG"):
            _settings.debug = os.getenv("OCPP_DEBUG").lower() in ("true", "1", "yes")
        
        # CSMS settings
        if os.getenv("CSMS_HOST"):
            _settings.csms.host = os.getenv("CSMS_HOST")
        if os.getenv("CSMS_PORT"):
            _settings.csms.port = int(os.getenv("CSMS_PORT"))
        if os.getenv("CSMS_MAX_CONNECTIONS"):
            _settings.csms.max_connections = int(os.getenv("CSMS_MAX_CONNECTIONS"))
        
        # CP settings
        if os.getenv("CP_STATION_ID"):
            _settings.cp.station_id = os.getenv("CP_STATION_ID")
        if os.getenv("CP_CSMS_URL"):
            _settings.cp.csms_url = os.getenv("CP_CSMS_URL")
        
        # Logging settings
        if os.getenv("LOG_LEVEL"):
            _settings.logging.level = os.getenv("LOG_LEVEL")
        if os.getenv("LOG_FILE_PATH"):
            _settings.logging.file_path = os.getenv("LOG_FILE_PATH")
    
    return _settings


def reload_settings() -> OCPPSettings:
    """
    Reload settings from environment variables.
    
    This function forces a reload of the settings from environment variables,
    useful for testing or when environment variables change at runtime.
    
    Returns:
        OCPPSettings: The reloaded settings instance
    """
    global _settings
    _settings = None
    return get_settings()


# Convenience functions for common settings
def get_csms_config() -> CSMSConfig:
    """Get CSMS configuration"""
    return get_settings().csms


def get_cp_config() -> CPConfig:
    """Get CP configuration"""
    return get_settings().cp


def get_logging_config() -> LoggingConfig:
    """Get logging configuration"""
    return get_settings().logging


def get_database_config() -> DatabaseConfig:
    """Get database configuration"""
    return get_settings().database


def get_security_config() -> SecurityConfig:
    """Get security configuration"""
    return get_settings().security


def get_monitoring_config() -> MonitoringConfig:
    """Get monitoring configuration"""
    return get_settings().monitoring


# Environment-specific settings
def is_development() -> bool:
    """Check if running in development environment"""
    return get_settings().environment == "development"


def is_production() -> bool:
    """Check if running in production environment"""
    return get_settings().environment == "production"


def is_debug_enabled() -> bool:
    """Check if debug mode is enabled"""
    return get_settings().debug


# Export the main settings instance
__all__ = [
    "OCPPSettings",
    "get_settings",
    "reload_settings",
    "get_csms_config",
    "get_cp_config", 
    "get_logging_config",
    "get_database_config",
    "get_security_config",
    "get_monitoring_config",
    "is_development",
    "is_production",
    "is_debug_enabled"
]