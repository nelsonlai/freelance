"""
OCPP 2.1 Exceptions

This module defines custom exceptions for the OCPP 2.1 implementation.
These exceptions provide specific error handling for different OCPP scenarios.
"""

from typing import Optional, Dict, Any


class OCPPError(Exception):
    """
    Base exception class for all OCPP-related errors.
    
    This is the parent class for all OCPP exceptions and provides
    common functionality for error handling.
    """
    
    def __init__(self, message: str, error_code: Optional[str] = None, 
                 error_details: Optional[Dict[str, Any]] = None):
        """
        Initialize OCPP error
        
        Args:
            message: Error message
            error_code: OCPP error code
            error_details: Additional error details
        """
        super().__init__(message)
        self.message = message
        self.error_code = error_code
        self.error_details = error_details or {}


class OCPPProtocolError(OCPPError):
    """
    Exception raised for OCPP protocol violations.
    
    This includes malformed messages, invalid message types,
    and other protocol-level errors.
    """
    
    def __init__(self, message: str, error_code: str = "ProtocolError", 
                 error_details: Optional[Dict[str, Any]] = None):
        super().__init__(message, error_code, error_details)


class OCPPMessageError(OCPPError):
    """
    Exception raised for OCPP message-related errors.
    
    This includes validation errors, missing required fields,
    and other message-level errors.
    """
    
    def __init__(self, message: str, error_code: str = "FormationViolation", 
                 error_details: Optional[Dict[str, Any]] = None):
        super().__init__(message, error_code, error_details)


class OCPPAuthenticationError(OCPPError):
    """
    Exception raised for authentication failures.
    
    This includes invalid credentials, expired tokens,
    and other authentication-related errors.
    """
    
    def __init__(self, message: str, error_code: str = "SecurityError", 
                 error_details: Optional[Dict[str, Any]] = None):
        super().__init__(message, error_code, error_details)


class OCPPAuthorizationError(OCPPError):
    """
    Exception raised for authorization failures.
    
    This includes insufficient permissions, blocked access,
    and other authorization-related errors.
    """
    
    def __init__(self, message: str, error_code: str = "NotAllowed", 
                 error_details: Optional[Dict[str, Any]] = None):
        super().__init__(message, error_code, error_details)


class OCPPValidationError(OCPPError):
    """
    Exception raised for validation errors.
    
    This includes invalid data types, out-of-range values,
    and other validation-related errors.
    """
    
    def __init__(self, message: str, error_code: str = "PropertyConstraintViolation", 
                 error_details: Optional[Dict[str, Any]] = None):
        super().__init__(message, error_code, error_details)


class OCPPNotImplementedError(OCPPError):
    """
    Exception raised when a requested action is not implemented.
    
    This is used when the CSMS or CP doesn't support
    a particular OCPP action or feature.
    """
    
    def __init__(self, message: str, error_code: str = "NotImplemented", 
                 error_details: Optional[Dict[str, Any]] = None):
        super().__init__(message, error_code, error_details)


class OCPPNotSupportedError(OCPPError):
    """
    Exception raised when a requested action is not supported.
    
    This is used when the CSMS or CP doesn't support
    a particular OCPP action or feature.
    """
    
    def __init__(self, message: str, error_code: str = "NotSupported", 
                 error_details: Optional[Dict[str, Any]] = None):
        super().__init__(message, error_code, error_details)


class OCPPInternalError(OCPPError):
    """
    Exception raised for internal errors.
    
    This includes database errors, system failures,
    and other internal errors.
    """
    
    def __init__(self, message: str, error_code: str = "InternalError", 
                 error_details: Optional[Dict[str, Any]] = None):
        super().__init__(message, error_code, error_details)


class OCPPTimeoutError(OCPPError):
    """
    Exception raised for timeout errors.
    
    This includes message timeouts, connection timeouts,
    and other timeout-related errors.
    """
    
    def __init__(self, message: str, error_code: str = "Timeout", 
                 error_details: Optional[Dict[str, Any]] = None):
        super().__init__(message, error_code, error_details)


class OCPPConnectionError(OCPPError):
    """
    Exception raised for connection errors.
    
    This includes network errors, connection failures,
    and other connection-related errors.
    """
    
    def __init__(self, message: str, error_code: str = "ConnectionError", 
                 error_details: Optional[Dict[str, Any]] = None):
        super().__init__(message, error_code, error_details)


class OCPPTransactionError(OCPPError):
    """
    Exception raised for transaction-related errors.
    
    This includes transaction not found, invalid transaction state,
    and other transaction-related errors.
    """
    
    def __init__(self, message: str, error_code: str = "TransactionError", 
                 error_details: Optional[Dict[str, Any]] = None):
        super().__init__(message, error_code, error_details)


class OCPPChargingProfileError(OCPPError):
    """
    Exception raised for charging profile errors.
    
    This includes invalid charging profiles, profile conflicts,
    and other charging profile-related errors.
    """
    
    def __init__(self, message: str, error_code: str = "ChargingProfileError", 
                 error_details: Optional[Dict[str, Any]] = None):
        super().__init__(message, error_code, error_details)


class OCPPCertificateError(OCPPError):
    """
    Exception raised for certificate-related errors.
    
    This includes invalid certificates, certificate validation failures,
    and other certificate-related errors.
    """
    
    def __init__(self, message: str, error_code: str = "CertificateError", 
                 error_details: Optional[Dict[str, Any]] = None):
        super().__init__(message, error_code, error_details)


class OCPPFirmwareError(OCPPError):
    """
    Exception raised for firmware-related errors.
    
    This includes firmware update failures, invalid firmware,
    and other firmware-related errors.
    """
    
    def __init__(self, message: str, error_code: str = "FirmwareError", 
                 error_details: Optional[Dict[str, Any]] = None):
        super().__init__(message, error_code, error_details)


class OCPPConfigurationError(OCPPError):
    """
    Exception raised for configuration errors.
    
    This includes invalid configuration values, missing configuration,
    and other configuration-related errors.
    """
    
    def __init__(self, message: str, error_code: str = "ConfigurationError", 
                 error_details: Optional[Dict[str, Any]] = None):
        super().__init__(message, error_code, error_details)


class OCPPReservationError(OCPPError):
    """
    Exception raised for reservation errors.
    
    This includes reservation conflicts, invalid reservations,
    and other reservation-related errors.
    """
    
    def __init__(self, message: str, error_code: str = "ReservationError", 
                 error_details: Optional[Dict[str, Any]] = None):
        super().__init__(message, error_code, error_details)


class OCPPTariffError(OCPPError):
    """
    Exception raised for tariff-related errors.
    
    This includes invalid tariffs, tariff conflicts,
    and other tariff-related errors.
    """
    
    def __init__(self, message: str, error_code: str = "TariffError", 
                 error_details: Optional[Dict[str, Any]] = None):
        super().__init__(message, error_code, error_details)


class OCPPMonitoringError(OCPPError):
    """
    Exception raised for monitoring errors.
    
    This includes monitoring configuration errors, invalid monitors,
    and other monitoring-related errors.
    """
    
    def __init__(self, message: str, error_code: str = "MonitoringError", 
                 error_details: Optional[Dict[str, Any]] = None):
        super().__init__(message, error_code, error_details)


class OCPPReportingError(OCPPError):
    """
    Exception raised for reporting errors.
    
    This includes report generation failures, invalid reports,
    and other reporting-related errors.
    """
    
    def __init__(self, message: str, error_code: str = "ReportingError", 
                 error_details: Optional[Dict[str, Any]] = None):
        super().__init__(message, error_code, error_details)


class OCPPDisplayError(OCPPError):
    """
    Exception raised for display message errors.
    
    This includes invalid display messages, message conflicts,
    and other display-related errors.
    """
    
    def __init__(self, message: str, error_code: str = "DisplayError", 
                 error_details: Optional[Dict[str, Any]] = None):
        super().__init__(message, error_code, error_details)


class OCPPSecurityError(OCPPError):
    """
    Exception raised for security-related errors.
    
    This includes security violations, invalid security events,
    and other security-related errors.
    """
    
    def __init__(self, message: str, error_code: str = "SecurityError", 
                 error_details: Optional[Dict[str, Any]] = None):
        super().__init__(message, error_code, error_details)


class OCPPDataTransferError(OCPPError):
    """
    Exception raised for data transfer errors.
    
    This includes data transfer failures, invalid data,
    and other data transfer-related errors.
    """
    
    def __init__(self, message: str, error_code: str = "DataTransferError", 
                 error_details: Optional[Dict[str, Any]] = None):
        super().__init__(message, error_code, error_details)


class OCPPGenericError(OCPPError):
    """
    Exception raised for generic OCPP errors.
    
    This is used for errors that don't fit into specific categories.
    """
    
    def __init__(self, message: str, error_code: str = "GenericError", 
                 error_details: Optional[Dict[str, Any]] = None):
        super().__init__(message, error_code, error_details)


# Error code mappings for OCPP 2.1
OCPP_ERROR_CODES = {
    "FormationViolation": "The message is not properly formatted according to the OCPP 2.1 specification",
    "PropertyConstraintViolation": "A property constraint has been violated",
    "OccurenceConstraintViolation": "An occurrence constraint has been violated",
    "TypeConstraintViolation": "A type constraint has been violated",
    "GenericError": "An internal error occurred",
    "NotImplemented": "The requested action is not implemented",
    "NotSupported": "The requested action is not supported",
    "InternalError": "An internal error occurred",
    "ProtocolError": "A protocol error occurred",
    "SecurityError": "A security error occurred",
    "FormationViolation": "The message formation is invalid",
    "PropertyConstraintViolation": "A property constraint has been violated",
    "OccurenceConstraintViolation": "An occurrence constraint has been violated",
    "TypeConstraintViolation": "A type constraint has been violated",
    "GenericError": "An internal error occurred",
    "NotImplemented": "The requested action is not implemented",
    "NotSupported": "The requested action is not supported",
    "InternalError": "An internal error occurred",
    "ProtocolError": "A protocol error occurred",
    "SecurityError": "A security error occurred",
    "MessageTypeNotSupported": "The message type is not supported",
    "RpcFrameworkError": "An RPC framework error occurred",
    "UnknownVendorId": "The vendor ID is unknown",
    "UnknownMessageId": "The message ID is unknown",
    "UnknownAction": "The action is unknown",
    "UnknownError": "An unknown error occurred",
    "Timeout": "A timeout occurred",
    "ConnectionError": "A connection error occurred",
    "TransactionError": "A transaction error occurred",
    "ChargingProfileError": "A charging profile error occurred",
    "CertificateError": "A certificate error occurred",
    "FirmwareError": "A firmware error occurred",
    "ConfigurationError": "A configuration error occurred",
    "ReservationError": "A reservation error occurred",
    "TariffError": "A tariff error occurred",
    "MonitoringError": "A monitoring error occurred",
    "ReportingError": "A reporting error occurred",
    "DisplayError": "A display error occurred",
    "SecurityError": "A security error occurred",
    "DataTransferError": "A data transfer error occurred",
    "GenericError": "A generic error occurred",
}


def get_error_description(error_code: str) -> str:
    """
    Get the description for an OCPP error code
    
    Args:
        error_code: The OCPP error code
        
    Returns:
        Error description
    """
    return OCPP_ERROR_CODES.get(error_code, "Unknown error")


def create_ocpp_error(error_code: str, message: str, 
                     error_details: Optional[Dict[str, Any]] = None) -> OCPPError:
    """
    Create an OCPP error with the appropriate exception type
    
    Args:
        error_code: The OCPP error code
        message: Error message
        error_details: Additional error details
        
    Returns:
        Appropriate OCPP exception instance
    """
    error_classes = {
        "ProtocolError": OCPPProtocolError,
        "FormationViolation": OCPPMessageError,
        "PropertyConstraintViolation": OCPPValidationError,
        "OccurenceConstraintViolation": OCPPValidationError,
        "TypeConstraintViolation": OCPPValidationError,
        "NotImplemented": OCPPNotImplementedError,
        "NotSupported": OCPPNotSupportedError,
        "InternalError": OCPPInternalError,
        "SecurityError": OCPPSecurityError,
        "Timeout": OCPPTimeoutError,
        "ConnectionError": OCPPConnectionError,
        "TransactionError": OCPPTransactionError,
        "ChargingProfileError": OCPPChargingProfileError,
        "CertificateError": OCPPCertificateError,
        "FirmwareError": OCPPFirmwareError,
        "ConfigurationError": OCPPConfigurationError,
        "ReservationError": OCPPReservationError,
        "TariffError": OCPPTariffError,
        "MonitoringError": OCPPMonitoringError,
        "ReportingError": OCPPReportingError,
        "DisplayError": OCPPDisplayError,
        "DataTransferError": OCPPDataTransferError,
        "GenericError": OCPPGenericError,
    }
    
    error_class = error_classes.get(error_code, OCPPGenericError)
    return error_class(message, error_code, error_details)
