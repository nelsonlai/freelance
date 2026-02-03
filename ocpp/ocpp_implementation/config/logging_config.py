"""
OCPP 2.1 Logging Configuration

This module provides comprehensive logging configuration for the OCPP 2.1 implementation.
It includes structured logging, different log levels, and multiple output destinations.
"""

import logging
import logging.handlers
import sys
import json
from typing import Any, Dict, Optional
from datetime import datetime
from pathlib import Path

from config.settings import get_settings


class OCPPFormatter(logging.Formatter):
    """
    Custom formatter for OCPP messages that includes additional context
    such as message type, direction (request/response), and timing information.
    """
    
    def __init__(self, use_json: bool = False):
        """
        Initialize the formatter
        
        Args:
            use_json: Whether to format logs as JSON
        """
        self.use_json = use_json
        
        if use_json:
            super().__init__()
        else:
            # Standard format with timestamp, logger name, level, and message
            super().__init__(
                fmt="%(asctime)s - %(name)s - %(levelname)s - %(message)s",
                datefmt="%Y-%m-%d %H:%M:%S"
            )
    
    def format(self, record: logging.LogRecord) -> str:
        """
        Format the log record
        
        Args:
            record: The log record to format
            
        Returns:
            Formatted log message
        """
        if self.use_json:
            return self._format_json(record)
        else:
            return super().format(record)
    
    def _format_json(self, record: logging.LogRecord) -> str:
        """
        Format log record as JSON
        
        Args:
            record: The log record to format
            
        Returns:
            JSON formatted log message
        """
        log_data = {
            "timestamp": datetime.fromtimestamp(record.created).isoformat(),
            "level": record.levelname,
            "logger": record.name,
            "message": record.getMessage(),
            "module": record.module,
            "function": record.funcName,
            "line": record.lineno,
        }
        
        # Add OCPP-specific context if available
        if hasattr(record, 'ocpp_message_type'):
            log_data["ocpp_message_type"] = record.ocpp_message_type
        
        if hasattr(record, 'ocpp_direction'):
            log_data["ocpp_direction"] = record.ocpp_direction
        
        if hasattr(record, 'charging_station_id'):
            log_data["charging_station_id"] = record.charging_station_id
        
        if hasattr(record, 'transaction_id'):
            log_data["transaction_id"] = record.transaction_id
        
        # Add exception information if present
        if record.exc_info:
            log_data["exception"] = self.formatException(record.exc_info)
        
        return json.dumps(log_data, ensure_ascii=False)


class OCPPLogger:
    """
    OCPP-specific logger that provides structured logging for OCPP messages
    and operations.
    """
    
    def __init__(self, name: str):
        """
        Initialize the OCPP logger
        
        Args:
            name: Logger name (typically module name)
        """
        self.logger = logging.getLogger(name)
        self._setup_logger()
    
    def _setup_logger(self) -> None:
        """Setup the logger with appropriate handlers and formatters"""
        settings = get_settings()
        
        # Set log level
        level = getattr(logging, settings.logging.level.upper())
        self.logger.setLevel(level)
        
        # Clear existing handlers
        self.logger.handlers.clear()
        
        # Add console handler if enabled
        if settings.logging.enable_console:
            console_handler = logging.StreamHandler(sys.stdout)
            console_handler.setLevel(level)
            console_formatter = OCPPFormatter(use_json=settings.logging.json_format)
            console_handler.setFormatter(console_formatter)
            self.logger.addHandler(console_handler)
        
        # Add file handler if enabled
        if settings.logging.enable_file:
            # Ensure log directory exists
            log_path = Path(settings.logging.file_path)
            log_path.parent.mkdir(parents=True, exist_ok=True)
            
            # Create rotating file handler
            file_handler = logging.handlers.RotatingFileHandler(
                filename=settings.logging.file_path,
                maxBytes=settings.logging.max_file_size,
                backupCount=settings.logging.backup_count,
                encoding='utf-8'
            )
            file_handler.setLevel(level)
            file_formatter = OCPPFormatter(use_json=settings.logging.json_format)
            file_handler.setFormatter(file_formatter)
            self.logger.addHandler(file_handler)
        
        # Prevent duplicate logs
        self.logger.propagate = False
    
    def debug(self, message: str, **kwargs) -> None:
        """Log debug message with optional OCPP context"""
        self._log(logging.DEBUG, message, **kwargs)
    
    def info(self, message: str, **kwargs) -> None:
        """Log info message with optional OCPP context"""
        self._log(logging.INFO, message, **kwargs)
    
    def warning(self, message: str, **kwargs) -> None:
        """Log warning message with optional OCPP context"""
        self._log(logging.WARNING, message, **kwargs)
    
    def error(self, message: str, **kwargs) -> None:
        """Log error message with optional OCPP context"""
        self._log(logging.ERROR, message, **kwargs)
    
    def critical(self, message: str, **kwargs) -> None:
        """Log critical message with optional OCPP context"""
        self._log(logging.CRITICAL, message, **kwargs)
    
    def _log(self, level: int, message: str, **kwargs) -> None:
        """
        Internal logging method that adds OCPP context to log records
        
        Args:
            level: Log level
            message: Log message
            **kwargs: Additional context (ocpp_message_type, charging_station_id, etc.)
        """
        # Create a new log record with additional context
        record = self.logger.makeRecord(
            name=self.logger.name,
            level=level,
            fn="",
            lno=0,
            msg=message,
            args=(),
            exc_info=None
        )
        
        # Add OCPP context to the record
        for key, value in kwargs.items():
            setattr(record, key, value)
        
        # Log the record
        self.logger.handle(record)
    
    def log_ocpp_message(self, 
                         message_type: str, 
                         direction: str, 
                         message: str, 
                         charging_station_id: Optional[str] = None,
                         transaction_id: Optional[str] = None,
                         level: int = logging.INFO) -> None:
        """
        Log OCPP message with specific context
        
        Args:
            message_type: OCPP message type (e.g., 'AuthorizeRequest')
            direction: Message direction ('request' or 'response')
            message: Log message
            charging_station_id: Charging station ID
            transaction_id: Transaction ID
            level: Log level
        """
        self._log(
            level=level,
            message=message,
            ocpp_message_type=message_type,
            ocpp_direction=direction,
            charging_station_id=charging_station_id,
            transaction_id=transaction_id
        )
    
    def log_transaction_event(self, 
                            event: str, 
                            transaction_id: str, 
                            charging_station_id: str,
                            level: int = logging.INFO) -> None:
        """
        Log transaction-related events
        
        Args:
            event: Transaction event description
            transaction_id: Transaction ID
            charging_station_id: Charging station ID
            level: Log level
        """
        self._log(
            level=level,
            message=f"Transaction event: {event}",
            transaction_id=transaction_id,
            charging_station_id=charging_station_id
        )
    
    def log_security_event(self, 
                          event: str, 
                          charging_station_id: str,
                          level: int = logging.WARNING) -> None:
        """
        Log security-related events
        
        Args:
            event: Security event description
            charging_station_id: Charging station ID
            level: Log level
        """
        self._log(
            level=level,
            message=f"Security event: {event}",
            charging_station_id=charging_station_id
        )


def get_logger(name: str) -> OCPPLogger:
    """
    Get an OCPP logger instance
    
    Args:
        name: Logger name (typically __name__)
        
    Returns:
        OCPP logger instance
    """
    return OCPPLogger(name)


def setup_logging() -> None:
    """
    Setup logging configuration for the entire application.
    This should be called once at application startup.
    """
    settings = get_settings()
    
    # Configure root logger
    root_logger = logging.getLogger()
    root_logger.setLevel(getattr(logging, settings.logging.level.upper()))
    
    # Remove default handlers
    for handler in root_logger.handlers[:]:
        root_logger.removeHandler(handler)
    
    # Create OCPP logger for root
    ocpp_logger = OCPPLogger("ocpp")
    
    # Log startup message
    ocpp_logger.info("OCPP 2.1 logging system initialized")


# Example usage and testing
if __name__ == "__main__":
    # Setup logging
    setup_logging()
    
    # Create a logger
    logger = get_logger(__name__)
    
    # Test different log levels
    logger.debug("This is a debug message")
    logger.info("This is an info message")
    logger.warning("This is a warning message")
    logger.error("This is an error message")
    
    # Test OCPP-specific logging
    logger.log_ocpp_message(
        message_type="AuthorizeRequest",
        direction="request",
        message="Received authorization request",
        charging_station_id="CP001"
    )
    
    # Test transaction logging
    logger.log_transaction_event(
        event="Transaction started",
        transaction_id="TXN001",
        charging_station_id="CP001"
    )
    
    # Test security event logging
    logger.log_security_event(
        event="Invalid authentication attempt",
        charging_station_id="CP001"
    )
