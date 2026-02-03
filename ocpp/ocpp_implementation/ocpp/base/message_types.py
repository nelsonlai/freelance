"""
OCPP 2.1 Base Message Types and Enums

This module contains the fundamental message types, enums, and base classes
for the OCPP 2.1 implementation.
"""

from enum import Enum
from typing import Any, Dict, List, Optional, Union
from pydantic import BaseModel, Field
from datetime import datetime


class MessageType(str, Enum):
    """OCPP 2.1 Message Types"""
    CALL = "2"           # Request message
    CALL_RESULT = "3"    # Response message  
    CALL_ERROR = "4"     # Error message


class ActionType(str, Enum):
    """OCPP 2.1 Action Types - Core Profile"""
    # Authorization
    Authorize = "Authorize"
    
    # Boot and Status
    BootNotification = "BootNotification"
    Heartbeat = "Heartbeat"
    StatusNotification = "StatusNotification"
    
    # Transactions
    TransactionEvent = "TransactionEvent"
    RequestStartTransaction = "RequestStartTransaction"
    RequestStopTransaction = "RequestStopTransaction"
    
    # Meter Values
    MeterValues = "MeterValues"
    
    # Data Transfer
    DataTransfer = "DataTransfer"
    
    # Diagnostics
    GetLog = "GetLog"
    LogStatusNotification = "LogStatusNotification"
    
    # Firmware Management
    UpdateFirmware = "UpdateFirmware"
    FirmwareStatusNotification = "FirmwareStatusNotification"
    
    # Local Authorization List
    SendLocalList = "SendLocalList"
    GetLocalListVersion = "GetLocalListVersion"
    
    # Reservation
    ReserveNow = "ReserveNow"
    CancelReservation = "CancelReservation"
    ReservationStatusUpdate = "ReservationStatusUpdate"
    
    # Security
    SecurityEventNotification = "SecurityEventNotification"
    SignCertificate = "SignCertificate"
    CertificateSigned = "CertificateSigned"
    GetInstalledCertificateIds = "GetInstalledCertificateIds"
    DeleteCertificate = "DeleteCertificate"
    InstallCertificate = "InstallCertificate"
    GetCertificateStatus = "GetCertificateStatus"
    GetCertificateChainStatus = "GetCertificateChainStatus"
    
    # Smart Charging
    SetChargingProfile = "SetChargingProfile"
    GetChargingProfiles = "GetChargingProfiles"
    ClearChargingProfile = "ClearChargingProfile"
    ReportChargingProfiles = "ReportChargingProfiles"
    
    # Tariff and Cost
    GetTariffs = "GetTariffs"
    SetDefaultTariff = "SetDefaultTariff"
    ClearTariffs = "ClearTariffs"
    CostUpdated = "CostUpdated"
    ChangeTransactionTariff = "ChangeTransactionTariff"
    
    # Display Messages
    SetDisplayMessage = "SetDisplayMessage"
    GetDisplayMessages = "GetDisplayMessages"
    ClearDisplayMessage = "ClearDisplayMessage"
    NotifyDisplayMessages = "NotifyDisplayMessages"
    
    # Monitoring
    SetVariableMonitoring = "SetVariableMonitoring"
    ClearVariableMonitoring = "ClearVariableMonitoring"
    SetMonitoringBase = "SetMonitoringBase"
    SetMonitoringLevel = "SetMonitoringLevel"
    GetMonitoringReport = "GetMonitoringReport"
    NotifyMonitoringReport = "NotifyMonitoringReport"
    
    # Reporting
    GetReport = "GetReport"
    NotifyReport = "NotifyReport"
    GetBaseReport = "GetBaseReport"
    
    # Additional Features
    TriggerMessage = "TriggerMessage"
    ChangeAvailability = "ChangeAvailability"
    UnlockConnector = "UnlockConnector"
    Reset = "Reset"
    ClearCache = "ClearCache"
    
    # ISO 15118
    Get15118EVCertificate = "Get15118EVCertificate"
    
    # Custom Actions (for extensibility)
    CustomAction = "CustomAction"


class GenericStatusEnum(str, Enum):
    """Generic status enumeration"""
    Accepted = "Accepted"
    Rejected = "Rejected"


class RegistrationStatusEnum(str, Enum):
    """Registration status enumeration"""
    Accepted = "Accepted"
    Pending = "Pending"
    Rejected = "Rejected"


class AuthorizationStatusEnum(str, Enum):
    """Authorization status enumeration"""
    Accepted = "Accepted"
    Blocked = "Blocked"
    ConcurrentTx = "ConcurrentTx"
    Expired = "Expired"
    Invalid = "Invalid"
    NoCredit = "NoCredit"
    NotAllowedTypeEVSE = "NotAllowedTypeEVSE"
    NotAtThisLocation = "NotAtThisLocation"
    NotAtThisTime = "NotAtThisTime"
    Unknown = "Unknown"


class TransactionEventEnum(str, Enum):
    """Transaction event enumeration"""
    Started = "Started"
    Updated = "Updated"
    Ended = "Ended"


class ConnectorStatusEnum(str, Enum):
    """Connector status enumeration"""
    Available = "Available"
    Occupied = "Occupied"
    Reserved = "Reserved"
    Unavailable = "Unavailable"
    Faulted = "Faulted"


class BootReasonEnum(str, Enum):
    """Boot reason enumeration"""
    ApplicationReset = "ApplicationReset"
    FirmwareUpdate = "FirmwareUpdate"
    LocalReset = "LocalReset"
    PowerUp = "PowerUp"
    RemoteReset = "RemoteReset"
    ScheduledReset = "ScheduledReset"
    Triggered = "Triggered"
    Unknown = "Unknown"
    Watchdog = "Watchdog"


class ResetEnum(str, Enum):
    """Reset type enumeration"""
    Immediate = "Immediate"
    OnIdle = "OnIdle"


class OperationalStatusEnum(str, Enum):
    """Operational status enumeration"""
    Inoperative = "Inoperative"
    Operative = "Operative"


class MessageFormatEnum(str, Enum):
    """Message format enumeration"""
    ASCII = "ASCII"
    HTML = "HTML"
    URI = "URI"
    UTF8 = "UTF8"
    QRCODE = "QRCODE"


class HashAlgorithmEnum(str, Enum):
    """Hash algorithm enumeration"""
    SHA256 = "SHA256"
    SHA384 = "SHA384"
    SHA512 = "SHA512"


class CertificateSigningUseEnum(str, Enum):
    """Certificate signing use enumeration"""
    ChargingStationCertificate = "ChargingStationCertificate"
    V2GCertificate = "V2GCertificate"
    V2G20Certificate = "V2G20Certificate"


class CertificateStatusEnum(str, Enum):
    """Certificate status enumeration"""
    Accepted = "Accepted"
    SignatureError = "SignatureError"
    CertificateExpired = "CertificateExpired"
    CertificateRevoked = "CertificateRevoked"
    NoCertificateAvailable = "NoCertificateAvailable"
    CertChainError = "CertChainError"
    ContractCancelled = "ContractCancelled"


class ChargingProfilePurposeEnum(str, Enum):
    """Charging profile purpose enumeration"""
    ChargingStationExternalConstraints = "ChargingStationExternalConstraints"
    ChargingStationMaxProfile = "ChargingStationMaxProfile"
    TxDefaultProfile = "TxDefaultProfile"
    TxProfile = "TxProfile"
    PriorityCharging = "PriorityCharging"
    LocalGeneration = "LocalGeneration"


class ChargingProfileStatusEnum(str, Enum):
    """Charging profile status enumeration"""
    Accepted = "Accepted"
    Rejected = "Rejected"
    RejectedByEVSE = "RejectedByEVSE"


class ClearChargingProfileStatusEnum(str, Enum):
    """Clear charging profile status enumeration"""
    Accepted = "Accepted"
    Unknown = "Unknown"


class ClearCacheStatusEnum(str, Enum):
    """Clear cache status enumeration"""
    Accepted = "Accepted"
    Rejected = "Rejected"


class ClearMessageStatusEnum(str, Enum):
    """Clear message status enumeration"""
    Accepted = "Accepted"
    Unknown = "Unknown"
    Rejected = "Rejected"


class CancelReservationStatusEnum(str, Enum):
    """Cancel reservation status enumeration"""
    Accepted = "Accepted"
    Rejected = "Rejected"


class ReserveNowStatusEnum(str, Enum):
    """Reserve now status enumeration"""
    Accepted = "Accepted"
    Faulted = "Faulted"
    Occupied = "Occupied"
    Rejected = "Rejected"
    Unavailable = "Unavailable"


class ReservationStatusEnum(str, Enum):
    """Reservation status enumeration"""
    Expired = "Expired"
    Removed = "Removed"


class UpdateFirmwareStatusEnum(str, Enum):
    """Update firmware status enumeration"""
    Accepted = "Accepted"
    Rejected = "Rejected"
    AcceptedCanceled = "AcceptedCanceled"
    InvalidCertificate = "InvalidCertificate"
    RevokedCertificate = "RevokedCertificate"


class FirmwareStatusEnum(str, Enum):
    """Firmware status enumeration"""
    Downloaded = "Downloaded"
    DownloadFailed = "DownloadFailed"
    Downloading = "Downloading"
    DownloadScheduled = "DownloadScheduled"
    DownloadPaused = "DownloadPaused"
    Idle = "Idle"
    InstallationFailed = "InstallationFailed"
    Installing = "Installing"
    Installed = "Installed"
    InstallRebooting = "InstallRebooting"
    InstallScheduled = "InstallScheduled"
    InstallVerificationFailed = "InstallVerificationFailed"
    InvalidSignature = "InvalidSignature"
    SignatureVerified = "SignatureVerified"


class LogStatusEnum(str, Enum):
    """Log status enumeration"""
    Accepted = "Accepted"
    Rejected = "Rejected"
    AcceptedCanceled = "AcceptedCanceled"


class LogEnum(str, Enum):
    """Log type enumeration"""
    DiagnosticsLog = "DiagnosticsLog"
    SecurityLog = "SecurityLog"


class UploadLogStatusEnum(str, Enum):
    """Upload log status enumeration"""
    BadMessage = "BadMessage"
    Idle = "Idle"
    NotSupportedOperation = "NotSupportedOperation"
    PermissionDenied = "PermissionDenied"
    Uploaded = "Uploaded"
    UploadFailure = "UploadFailure"
    Uploading = "Uploading"


class DataTransferStatusEnum(str, Enum):
    """Data transfer status enumeration"""
    Accepted = "Accepted"
    Rejected = "Rejected"
    UnknownMessageId = "UnknownMessageId"
    UnknownVendorId = "UnknownVendorId"


class TriggerMessageStatusEnum(str, Enum):
    """Trigger message status enumeration"""
    Accepted = "Accepted"
    Rejected = "Rejected"
    NotImplemented = "NotImplemented"


class TriggerMessageEnum(str, Enum):
    """Trigger message enumeration"""
    BootNotification = "BootNotification"
    DiagnosticsStatusNotification = "DiagnosticsStatusNotification"
    FirmwareStatusNotification = "FirmwareStatusNotification"
    Heartbeat = "Heartbeat"
    MeterValues = "MeterValues"
    StatusNotification = "StatusNotification"


class OCPPBaseMessage(BaseModel):
    """Base class for all OCPP messages"""
    
    class Config:
        # Allow extra fields for extensibility
        extra = "allow"
        # Use enum values instead of enum names
        use_enum_values = True
        # Validate assignment
        validate_assignment = True


class OCPPRequest(OCPPBaseMessage):
    """Base class for OCPP request messages"""
    pass


class OCPPResponse(OCPPBaseMessage):
    """Base class for OCPP response messages"""
    pass


class OCPPError(OCPPBaseMessage):
    """Base class for OCPP error messages"""
    error_code: str = Field(..., description="Error code")
    error_description: str = Field(..., description="Error description")
    error_details: Optional[Dict[str, Any]] = Field(None, description="Additional error details")


class CustomDataType(OCPPBaseMessage):
    """
    Custom data type for extensibility.
    This class allows adding arbitrary JSON properties for vendor-specific data.
    """
    vendor_id: str = Field(..., max_length=255, description="Vendor identifier")


class StatusInfoType(OCPPBaseMessage):
    """Status information type"""
    reason_code: str = Field(..., max_length=20, description="Reason code")
    additional_info: Optional[str] = Field(None, max_length=1024, description="Additional information")
    custom_data: Optional[CustomDataType] = Field(None, description="Custom data")


class IdTokenType(OCPPBaseMessage):
    """ID token type for authorization"""
    id_token: str = Field(..., max_length=255, description="ID token value")
    type: str = Field(..., max_length=20, description="Token type")
    additional_info: Optional[List[Dict[str, Any]]] = Field(None, description="Additional information")
    custom_data: Optional[CustomDataType] = Field(None, description="Custom data")


class AdditionalInfoType(OCPPBaseMessage):
    """Additional information type"""
    additional_id_token: str = Field(..., max_length=255, description="Additional ID token")
    type: str = Field(..., max_length=50, description="Information type")
    custom_data: Optional[CustomDataType] = Field(None, description="Custom data")


class MessageContentType(OCPPBaseMessage):
    """Message content type for display messages"""
    format: MessageFormatEnum = Field(..., description="Message format")
    language: Optional[str] = Field(None, max_length=8, description="Language code")
    content: str = Field(..., max_length=1024, description="Message content")
    custom_data: Optional[CustomDataType] = Field(None, description="Custom data")


class ChargingStationType(OCPPBaseMessage):
    """Charging station information"""
    model: str = Field(..., max_length=20, description="Station model")
    vendor_name: str = Field(..., max_length=50, description="Vendor name")
    serial_number: Optional[str] = Field(None, max_length=25, description="Serial number")
    firmware_version: Optional[str] = Field(None, max_length=50, description="Firmware version")
    modem: Optional[Dict[str, Any]] = Field(None, description="Modem information")
    custom_data: Optional[CustomDataType] = Field(None, description="Custom data")


class EVSEType(OCPPBaseMessage):
    """EVSE (Electric Vehicle Supply Equipment) information"""
    id: int = Field(..., ge=0, description="EVSE ID")
    connector_id: Optional[int] = Field(None, ge=0, description="Connector ID")
    custom_data: Optional[CustomDataType] = Field(None, description="Custom data")


class ModemType(OCPPBaseMessage):
    """Modem information"""
    iccid: Optional[str] = Field(None, max_length=20, description="ICCID")
    imsi: Optional[str] = Field(None, max_length=20, description="IMSI")
    custom_data: Optional[CustomDataType] = Field(None, description="Custom data")


class MeterValueType(OCPPBaseMessage):
    """Meter value type"""
    timestamp: datetime = Field(..., description="Timestamp")
    sampled_value: List[Dict[str, Any]] = Field(..., description="Sampled values")
    custom_data: Optional[CustomDataType] = Field(None, description="Custom data")


class SampledValueType(OCPPBaseMessage):
    """Sampled value type"""
    value: str = Field(..., description="Value")
    context: Optional[str] = Field(None, description="Context")
    format: Optional[str] = Field(None, description="Format")
    measurand: Optional[str] = Field(None, description="Measurand")
    phase: Optional[str] = Field(None, description="Phase")
    location: Optional[str] = Field(None, description="Location")
    unit: Optional[str] = Field(None, description="Unit")
    custom_data: Optional[CustomDataType] = Field(None, description="Custom data")


class OCPPMessage(BaseModel):
    """
    OCPP message envelope containing the message type, unique ID, action, and payload.
    This is the top-level structure for all OCPP messages.
    """
    message_type: MessageType = Field(..., description="OCPP message type")
    unique_id: str = Field(..., description="Unique message identifier")
    action: Optional[str] = Field(None, description="Action name")
    payload: Optional[Dict[str, Any]] = Field(None, description="Message payload")
    
    class Config:
        use_enum_values = True
        validate_assignment = True
