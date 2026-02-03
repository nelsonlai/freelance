"""
OCPP 2.1 CP (Charge Point) Client

This module implements the CP client that connects to a CSMS server
and handles charging operations, status reporting, and system management.
"""

import asyncio
import json
import uuid
from typing import Dict, Optional, Any, List
from datetime import datetime, timedelta
import websockets
from websockets.client import WebSocketClientProtocol
from websockets.exceptions import ConnectionClosed, WebSocketException

# Add the project root to the Python path
import sys
import os
project_root = os.path.dirname(os.path.dirname(os.path.dirname(__file__)))
if project_root not in sys.path:
    sys.path.insert(0, project_root)

from config.settings import get_settings
from config.logging_config import get_logger
from ocpp.base.message_types import (
    OCPPMessage, MessageType, ActionType, OCPPRequest, OCPPResponse, OCPPError
)
from ocpp.base.exceptions import (
    OCPPError, OCPPProtocolError, OCPPMessageError, OCPPAuthenticationError,
    OCPPAuthorizationError, OCPPValidationError, OCPPNotImplementedError,
    OCPPNotSupportedError, OCPPInternalError, OCPPTimeoutError,
    OCPPConnectionError, OCPPTransactionError, OCPPChargingProfileError,
    OCPPCertificateError, OCPPFirmwareError, OCPPConfigurationError,
    OCPPReservationError, OCPPTariffError, OCPPMonitoringError,
    OCPPReportingError, OCPPDisplayError, OCPPSecurityError,
    OCPPDataTransferError, OCPPGenericError, create_ocpp_error
)


class CPClient:
    """
    OCPP 2.1 CP (Charge Point) Client
    
    This class implements the Charge Point client that connects to a CSMS server
    and handles charging operations, status reporting, and system management.
    """
    
    def __init__(self, station_id: Optional[str] = None):
        """
        Initialize CP client
        
        Args:
            station_id: Charging station ID (if None, uses default from settings)
        """
        self.settings = get_settings()
        if station_id is None:
            # Generate UUID-based station ID: CP{UUID.4Hex}
            import uuid
            self.station_id = f"CP{uuid.uuid4().hex[:4].upper()}"
        else:
            self.station_id = station_id
        self.logger = get_logger(f"cp.client.{self.station_id}")
        
        # Connection state
        self.websocket: Optional[WebSocketClientProtocol] = None
        self.is_connected = False
        self.is_authenticated = False
        self.connection_attempts = 0
        self.last_heartbeat = datetime.now()
        
        # Message handling
        self.pending_messages: Dict[str, asyncio.Future] = {}
        self.message_handlers: Dict[str, callable] = {}
        self.message_task: Optional[asyncio.Task] = None
        
        # Charging station state
        self.station_info = {
            "model": self.settings.cp.model,
            "vendor_name": self.settings.cp.vendor_name,
            "serial_number": self.settings.cp.serial_number,
            "firmware_version": self.settings.cp.firmware_version,
            "station_id": self.station_id  # Add station ID to boot notification
        }
        
        # EVSE and connector state
        self.evses: Dict[int, Dict[str, Any]] = {}
        self.connectors: Dict[int, Dict[str, Any]] = {}
        
        # Transaction state
        self.active_transactions: Dict[str, Dict[str, Any]] = {}
        self.transaction_counter = 0
        
        # Charging profiles
        self.charging_profiles: Dict[int, Dict[str, Any]] = {}
        
        # Monitoring
        self.monitoring_data: Dict[str, Any] = {}
        
        # Security
        self.security_events: List[Dict[str, Any]] = []
        
        # Statistics
        self.stats = {
            "total_messages_sent": 0,
            "total_messages_received": 0,
            "total_transactions": 0,
            "connection_time": None,
            "last_message_time": None
        }
        
        self.logger.info(f"CP Client initialized for station {self.station_id}")
    
    async def connect(self) -> None:
        """
        Connect to CSMS server
        
        This method establishes a WebSocket connection to the CSMS server
        and performs the boot notification process.
        """
        try:
            self.logger.info(f"Connecting to CSMS at {self.settings.cp.csms_url}")
            
            # Connect to WebSocket server
            self.websocket = await websockets.connect(
                self.settings.cp.csms_url,
                ping_interval=self.settings.cp.heartbeat_interval,
                ping_timeout=10,
                max_size=1048576,
                subprotocols=['ocpp2.1']
            )
            
            self.is_connected = True
            self.connection_attempts = 0
            self.stats["connection_time"] = datetime.now()
            
            self.logger.info("Connected to CSMS server")
            
            # Start message handling in background first
            self.message_task = asyncio.create_task(self._handle_messages())
            self.logger.info(f"Created message task: {self.message_task}")
            
            # Send boot notification
            await self._send_boot_notification()
            
            self.logger.info("CP Client connected and ready")
            
        except Exception as e:
            self.logger.error(f"Failed to connect to CSMS: {str(e)}")
            self.is_connected = False
            raise OCPPConnectionError(f"Failed to connect: {str(e)}")
    
    async def disconnect(self) -> None:
        """
        Disconnect from CSMS server
        
        This method closes the WebSocket connection and cleans up resources.
        """
        try:
            if self.websocket:
                await self.websocket.close()
                self.websocket = None
            
            self.is_connected = False
            self.is_authenticated = False
            
            self.logger.info("Disconnected from CSMS server")
            
        except Exception as e:
            self.logger.error(f"Error disconnecting from CSMS: {str(e)}")
    
    async def reconnect(self) -> None:
        """
        Reconnect to CSMS server
        
        This method attempts to reconnect to the CSMS server with
        exponential backoff for failed attempts.
        """
        while self.connection_attempts < self.settings.cp.max_reconnect_attempts:
            try:
                self.connection_attempts += 1
                self.logger.info(f"Reconnection attempt {self.connection_attempts}")
                
                await asyncio.sleep(min(2 ** self.connection_attempts, 60))
                await self.connect()
                return
                
            except Exception as e:
                self.logger.error(f"Reconnection attempt {self.connection_attempts} failed: {str(e)}")
        
        self.logger.error("Maximum reconnection attempts reached")
        raise OCPPConnectionError("Failed to reconnect after maximum attempts")
    
    async def send_message(self, message: OCPPMessage) -> Optional[Dict[str, Any]]:
        """
        Send a message to the CSMS server
        
        Args:
            message: OCPP message to send
            
        Returns:
            Response message if it's a request, None otherwise
        """
        if not self.is_connected or not self.websocket:
            raise OCPPConnectionError("Not connected to CSMS server")
        
        try:
            # Serialize message to JSON
            message_data = message.model_dump()
            
            # Add unique ID if not present
            if not message_data.get("unique_id"):
                message_data["unique_id"] = str(uuid.uuid4())
            
            # Send message
            message_json = json.dumps(message_data)
            self.logger.info(f"Sending message JSON: {message_json}")
            await self.websocket.send(message_json)
            
            self.logger.log_ocpp_message(
                message_type=message.action or "Unknown",
                direction="request",
                message=f"Sent message to CSMS",
                charging_station_id=self.station_id
            )
            
            self.stats["total_messages_sent"] += 1
            self.stats["last_message_time"] = datetime.now()
            
            # If it's a request, wait for response
            if message.message_type == MessageType.CALL:
                unique_id = message_data["unique_id"]
                future = asyncio.Future()
                self.pending_messages[unique_id] = future
                
                try:
                    # Wait for response with timeout
                    response = await asyncio.wait_for(future, timeout=self.settings.cp.message_timeout)
                    return response
                except asyncio.TimeoutError:
                    self.pending_messages.pop(unique_id, None)
                    raise OCPPTimeoutError("Timeout waiting for response from CSMS")
                finally:
                    self.pending_messages.pop(unique_id, None)
            
            return None
            
        except Exception as e:
            self.logger.error(f"Failed to send message to CSMS: {str(e)}")
            raise OCPPConnectionError(f"Failed to send message: {str(e)}")
    
    async def _handle_messages(self) -> None:
        """Handle incoming messages from CSMS server"""
        self.logger.info("Starting message handling loop")
        try:
            async for message in self.websocket:
                try:
                    self.logger.info(f"Received raw message from CSMS: {message}")
                    message_data = json.loads(message)
                    self.logger.info(f"Parsed message data: {message_data}")
                    await self._process_message(message_data)
                    self.stats["total_messages_received"] += 1
                    self.stats["last_message_time"] = datetime.now()
                except json.JSONDecodeError as e:
                    self.logger.error(f"Invalid JSON message from CSMS: {str(e)}")
                except Exception as e:
                    self.logger.error(f"Error processing message from CSMS: {str(e)}")
                    
        except ConnectionClosed:
            self.logger.info("Connection to CSMS closed")
            self.is_connected = False
        except Exception as e:
            self.logger.error(f"Error handling messages from CSMS: {str(e)}")
            self.is_connected = False
    
    async def _process_message(self, message_data: Dict[str, Any]) -> None:
        """
        Process incoming message from CSMS
        
        Args:
            message_data: Parsed message data
        """
        try:
            message_type = message_data.get("message_type")
            unique_id = message_data.get("unique_id")
            action = message_data.get("action")
            payload = message_data.get("payload", {})
            
            self.logger.log_ocpp_message(
                message_type=action or "Unknown",
                direction="response" if message_type == MessageType.CALL_RESULT else "request",
                message=f"Received message from CSMS",
                charging_station_id=self.station_id
            )
            
            # Handle different message types
            if message_type == MessageType.CALL:
                # Handle request from CSMS
                response = await self._handle_request(action, payload)
                if response is not None:
                    await self._send_response(unique_id, response)
            
            elif message_type == MessageType.CALL_RESULT:
                # Handle response from CSMS
                await self._handle_response(unique_id, payload)
            
            elif message_type == MessageType.CALL_ERROR:
                # Handle error from CSMS
                await self._handle_error(unique_id, payload)
            
            else:
                raise OCPPProtocolError(f"Invalid message type: {message_type}")
                
        except Exception as e:
            self.logger.error(f"Error processing message from CSMS: {str(e)}")
            await self._send_error(unique_id, "InternalError", str(e))
    
    async def _handle_request(self, action: str, payload: Dict[str, Any]) -> Optional[Dict[str, Any]]:
        """
        Handle request from CSMS
        
        Args:
            action: Action name
            payload: Request payload
            
        Returns:
            Response payload
        """
        # Route to appropriate handler based on action
        handler_map = {
            ActionType.Authorize: self._handle_authorize,
            ActionType.RequestStartTransaction: self._handle_request_start_transaction,
            ActionType.RequestStopTransaction: self._handle_request_stop_transaction,
            ActionType.SetChargingProfile: self._handle_set_charging_profile,
            ActionType.ClearChargingProfile: self._handle_clear_charging_profile,
            ActionType.GetChargingProfiles: self._handle_get_charging_profiles,
            ActionType.ChangeAvailability: self._handle_change_availability,
            ActionType.UnlockConnector: self._handle_unlock_connector,
            ActionType.Reset: self._handle_reset,
            ActionType.ClearCache: self._handle_clear_cache,
            ActionType.UpdateFirmware: self._handle_update_firmware,
            ActionType.SendLocalList: self._handle_send_local_list,
            ActionType.GetLocalListVersion: self._handle_get_local_list_version,
            ActionType.ReserveNow: self._handle_reserve_now,
            ActionType.CancelReservation: self._handle_cancel_reservation,
            ActionType.SecurityEventNotification: self._handle_security_event_notification,
            ActionType.SignCertificate: self._handle_sign_certificate,
            ActionType.CertificateSigned: self._handle_certificate_signed,
            ActionType.GetInstalledCertificateIds: self._handle_get_installed_certificate_ids,
            ActionType.DeleteCertificate: self._handle_delete_certificate,
            ActionType.InstallCertificate: self._handle_install_certificate,
            ActionType.GetCertificateStatus: self._handle_get_certificate_status,
            ActionType.GetCertificateChainStatus: self._handle_get_certificate_chain_status,
            ActionType.GetTariffs: self._handle_get_tariffs,
            ActionType.SetDefaultTariff: self._handle_set_default_tariff,
            ActionType.ClearTariffs: self._handle_clear_tariffs,
            ActionType.SetDisplayMessage: self._handle_set_display_message,
            ActionType.GetDisplayMessages: self._handle_get_display_messages,
            ActionType.ClearDisplayMessage: self._handle_clear_display_message,
            ActionType.SetVariableMonitoring: self._handle_set_variable_monitoring,
            ActionType.ClearVariableMonitoring: self._handle_clear_variable_monitoring,
            ActionType.SetMonitoringBase: self._handle_set_monitoring_base,
            ActionType.SetMonitoringLevel: self._handle_set_monitoring_level,
            ActionType.GetMonitoringReport: self._handle_get_monitoring_report,
            ActionType.GetReport: self._handle_get_report,
            ActionType.GetBaseReport: self._handle_get_base_report,
            ActionType.TriggerMessage: self._handle_trigger_message,
            ActionType.DataTransfer: self._handle_data_transfer,
            ActionType.GetLog: self._handle_get_log,
            ActionType.Get15118EVCertificate: self._handle_get_15118_ev_certificate,
        }
        
        handler = handler_map.get(action)
        if handler:
            return await handler(payload)
        else:
            raise OCPPNotSupportedError(f"Action not supported: {action}")
    
    async def _handle_response(self, unique_id: str, payload: Dict[str, Any]) -> None:
        """
        Handle response from CSMS
        
        Args:
            unique_id: Message unique ID
            payload: Response payload
        """
        self.logger.info(f"Handling response for unique_id: {unique_id}, payload: {payload}")
        if unique_id in self.pending_messages:
            future = self.pending_messages[unique_id]
            if not future.done():
                self.logger.info(f"Setting result for future {unique_id}")
                future.set_result(payload)
            else:
                self.logger.warning(f"Future {unique_id} already done")
        else:
            self.logger.warning(f"No pending message found for unique_id: {unique_id}")
    
    async def _handle_error(self, unique_id: str, payload: Dict[str, Any]) -> None:
        """
        Handle error from CSMS
        
        Args:
            unique_id: Message unique ID
            payload: Error payload
        """
        if unique_id in self.pending_messages:
            future = self.pending_messages[unique_id]
            if not future.done():
                error_code = payload.get("error_code", "UnknownError")
                error_description = payload.get("error_description", "Unknown error")
                error_details = payload.get("error_details", {})
                
                error = create_ocpp_error(error_code, error_description, error_details)
                future.set_exception(error)
    
    async def _send_response(self, unique_id: str, payload: Dict[str, Any]) -> None:
        """
        Send response to CSMS
        
        Args:
            unique_id: Message unique ID
            payload: Response payload
        """
        response = OCPPMessage(
            message_type=MessageType.CALL_RESULT,
            unique_id=unique_id,
            payload=payload
        )
        await self.send_message(response)
    
    async def _send_error(self, unique_id: str, error_code: str, 
                         error_description: str, error_details: Optional[Dict[str, Any]] = None) -> None:
        """
        Send error to CSMS
        
        Args:
            unique_id: Message unique ID
            error_code: Error code
            error_description: Error description
            error_details: Additional error details
        """
        error_payload = {
            "error_code": error_code,
            "error_description": error_description,
            "error_details": error_details or {}
        }
        
        error_message = OCPPMessage(
            message_type=MessageType.CALL_ERROR,
            unique_id=unique_id,
            payload=error_payload
        )
        await self.send_message(error_message)
    
    # Boot notification
    async def _send_boot_notification(self) -> None:
        """Send boot notification to CSMS"""
        try:
            boot_notification = OCPPMessage(
                message_type=MessageType.CALL,
                unique_id=str(uuid.uuid4()),
                action=ActionType.BootNotification,
                payload={
                    "chargingStation": self.station_info,
                    "reason": "PowerUp"
                }
            )
            
            response = await self.send_message(boot_notification)
            
            if response and response.get("status") == "Accepted":
                self.is_authenticated = True
                self.logger.info("Boot notification accepted by CSMS")
                
                # Start heartbeat
                asyncio.create_task(self._heartbeat_loop())
            else:
                self.logger.error("Boot notification rejected by CSMS")
                raise OCPPAuthenticationError("Boot notification rejected")
                
        except Exception as e:
            self.logger.error(f"Error sending boot notification: {str(e)}")
            raise OCPPInternalError(f"Failed to send boot notification: {str(e)}")
    
    # Heartbeat
    async def _heartbeat_loop(self) -> None:
        """Send periodic heartbeat to CSMS"""
        while self.is_connected:
            try:
                await asyncio.sleep(self.settings.cp.heartbeat_interval)
                
                if self.is_connected:
                    heartbeat = OCPPMessage(
                        message_type=MessageType.CALL,
                        unique_id=str(uuid.uuid4()),
                        action=ActionType.Heartbeat,
                        payload={}
                    )
                    
                    await self.send_message(heartbeat)
                    self.last_heartbeat = datetime.now()
                    
            except Exception as e:
                self.logger.error(f"Error sending heartbeat: {str(e)}")
                break
    
    # Status notification
    async def send_status_notification(self, evse_id: int, connector_id: int, 
                                     status: str, timestamp: Optional[datetime] = None) -> None:
        """
        Send status notification to CSMS
        
        Args:
            evse_id: EVSE ID
            connector_id: Connector ID
            status: Connector status
            timestamp: Status timestamp
        """
        try:
            status_notification = OCPPMessage(
                message_type=MessageType.CALL,
                unique_id=str(uuid.uuid4()),
                action=ActionType.StatusNotification,
                payload={
                    "evseId": evse_id,
                    "connectorId": connector_id,
                    "status": status,
                    "timestamp": (timestamp or datetime.now()).isoformat()
                }
            )
            
            await self.send_message(status_notification)
            
            # Update local state
            connector_key = f"{evse_id}_{connector_id}"
            self.connectors[connector_key] = {
                "evse_id": evse_id,
                "connector_id": connector_id,
                "status": status,
                "timestamp": timestamp or datetime.now()
            }
            
            self.logger.info(f"Status notification sent: EVSE {evse_id}, Connector {connector_id}, Status {status}")
            
        except Exception as e:
            self.logger.error(f"Error sending status notification: {str(e)}")
            raise OCPPInternalError(f"Failed to send status notification: {str(e)}")
    
    # Transaction event
    async def send_transaction_event(self, event_type: str, timestamp: datetime,
                                   transaction_id: Optional[str] = None,
                                   evse_id: Optional[int] = None,
                                   connector_id: Optional[int] = None,
                                   meter_value: Optional[List[Dict[str, Any]]] = None,
                                   reason: Optional[str] = None,
                                   custom_data: Optional[Dict[str, Any]] = None) -> None:
        """
        Send transaction event to CSMS
        
        Args:
            event_type: Transaction event type
            timestamp: Event timestamp
            transaction_id: Transaction ID
            evse_id: EVSE ID
            connector_id: Connector ID
            meter_value: Meter values
            reason: Event reason
            custom_data: Custom data
        """
        try:
            # Generate transaction ID if not provided
            if not transaction_id and event_type == "Started":
                self.transaction_counter += 1
                transaction_id = f"TXN_{self.station_id}_{self.transaction_counter:06d}"
            
            payload = {
                "eventType": event_type,
                "timestamp": timestamp.isoformat(),
                "evseId": evse_id,
                "connectorId": connector_id,
                "customData": custom_data
            }
            
            if transaction_id:
                payload["transactionId"] = transaction_id
            
            if meter_value:
                payload["meterValue"] = meter_value
            
            if reason:
                payload["reason"] = reason
            
            transaction_event = OCPPMessage(
                message_type=MessageType.CALL,
                unique_id=str(uuid.uuid4()),
                action=ActionType.TransactionEvent,
                payload=payload
            )
            
            await self.send_message(transaction_event)
            
            # Update local transaction state
            if transaction_id:
                if event_type == "Started":
                    self.active_transactions[transaction_id] = {
                        "transaction_id": transaction_id,
                        "evse_id": evse_id,
                        "connector_id": connector_id,
                        "start_time": timestamp,
                        "status": "Active"
                    }
                elif event_type == "Ended":
                    if transaction_id in self.active_transactions:
                        transaction = self.active_transactions.pop(transaction_id)
                        transaction["end_time"] = timestamp
                        transaction["status"] = "Completed"
                        self.stats["total_transactions"] += 1
            
            self.logger.log_transaction_event(
                event=f"Transaction {event_type}",
                transaction_id=transaction_id or "Unknown",
                charging_station_id=self.station_id
            )
            
        except Exception as e:
            self.logger.error(f"Error sending transaction event: {str(e)}")
            raise OCPPInternalError(f"Failed to send transaction event: {str(e)}")
    
    # Meter values
    async def send_meter_values(self, evse_id: int, meter_value: List[Dict[str, Any]]) -> None:
        """
        Send meter values to CSMS
        
        Args:
            evse_id: EVSE ID
            meter_value: Meter values
        """
        try:
            meter_values = OCPPMessage(
                message_type=MessageType.CALL,
                unique_id=str(uuid.uuid4()),
                action=ActionType.MeterValues,
                payload={
                    "evseId": evse_id,
                    "meterValue": meter_value
                }
            )
            
            await self.send_message(meter_values)
            
            self.logger.info(f"Meter values sent for EVSE {evse_id}")
            
        except Exception as e:
            self.logger.error(f"Error sending meter values: {str(e)}")
            raise OCPPInternalError(f"Failed to send meter values: {str(e)}")
    
    # Data transfer
    async def send_data_transfer(self, vendor_id: str, message_id: Optional[str] = None,
                               data: Optional[str] = None) -> Dict[str, Any]:
        """
        Send data transfer to CSMS
        
        Args:
            vendor_id: Vendor ID
            message_id: Message ID
            data: Data to transfer
            
        Returns:
            Response from CSMS
        """
        try:
            payload = {
                "vendorId": vendor_id
            }
            
            if message_id:
                payload["messageId"] = message_id
            
            if data:
                payload["data"] = data
            
            data_transfer = OCPPMessage(
                message_type=MessageType.CALL,
                unique_id=str(uuid.uuid4()),
                action=ActionType.DataTransfer,
                payload=payload
            )
            
            response = await self.send_message(data_transfer)
            return response or {}
            
        except Exception as e:
            self.logger.error(f"Error sending data transfer: {str(e)}")
            raise OCPPInternalError(f"Failed to send data transfer: {str(e)}")
    
    # Request handlers (simplified implementations)
    async def _handle_authorize(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle Authorize request"""
        import uuid
        
        # Generate RFID token with format RFID-{UUID(8)}
        rfid_token = f"RFID-{str(uuid.uuid4())[:8].upper()}"
        
        self.logger.info(f"Authorize request received, generated RFID token: {rfid_token}")
        
        return {
            "idTokenInfo": {
                "status": "Accepted",
                "idToken": rfid_token,  # Include the generated RFID token
                "cacheExpiryDateTime": (datetime.now() + timedelta(hours=1)).isoformat(),
                "chargingPriority": 1,
                "language1": "en",
                "evseId": [1]  # Available on all EVSEs
            }
        }
    
    async def _handle_request_start_transaction(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle RequestStartTransaction request"""
        # Simplified implementation - always accept
        return {
            "status": "Accepted",
            "transactionId": f"TXN_{self.station_id}_{self.transaction_counter + 1:06d}"
        }
    
    async def _handle_request_stop_transaction(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle RequestStopTransaction request"""
        # Simplified implementation - always accept
        return {
            "status": "Accepted"
        }
    
    async def _handle_set_charging_profile(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle SetChargingProfile request"""
        # Simplified implementation - always accept
        return {
            "status": "Accepted"
        }
    
    async def _handle_clear_charging_profile(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle ClearChargingProfile request"""
        # Simplified implementation - always accept
        return {
            "status": "Accepted"
        }
    
    async def _handle_get_charging_profiles(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle GetChargingProfiles request"""
        # Simplified implementation - return empty list
        return {
            "chargingProfile": []
        }
    
    async def _handle_change_availability(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle ChangeAvailability request"""
        # Simplified implementation - always accept
        return {
            "status": "Accepted"
        }
    
    async def _handle_unlock_connector(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle UnlockConnector request"""
        # Simplified implementation - always accept
        return {
            "status": "Unlocked"
        }
    
    async def _handle_reset(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle Reset request"""
        # Simplified implementation - always accept
        return {
            "status": "Accepted"
        }
    
    async def _handle_clear_cache(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle ClearCache request"""
        # Simplified implementation - always accept
        return {
            "status": "Accepted"
        }
    
    async def _handle_update_firmware(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle UpdateFirmware request"""
        # Simplified implementation - always accept
        return {
            "status": "Accepted"
        }
    
    async def _handle_send_local_list(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle SendLocalList request"""
        # Simplified implementation - always accept
        return {
            "status": "Accepted"
        }
    
    async def _handle_get_local_list_version(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle GetLocalListVersion request"""
        # Simplified implementation - return version 0
        return {
            "versionNumber": 0
        }
    
    async def _handle_reserve_now(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle ReserveNow request"""
        # Simplified implementation - always accept
        return {
            "status": "Accepted"
        }
    
    async def _handle_cancel_reservation(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle CancelReservation request"""
        # Simplified implementation - always accept
        return {
            "status": "Accepted"
        }
    
    async def _handle_security_event_notification(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle SecurityEventNotification request"""
        # Simplified implementation - always accept
        return {}
    
    async def _handle_sign_certificate(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle SignCertificate request"""
        # Simplified implementation - always accept
        return {
            "status": "Accepted"
        }
    
    async def _handle_certificate_signed(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle CertificateSigned request"""
        # Simplified implementation - always accept
        return {
            "status": "Accepted"
        }
    
    async def _handle_get_installed_certificate_ids(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle GetInstalledCertificateIds request"""
        # Simplified implementation - return empty list
        return {
            "certificateHashData": []
        }
    
    async def _handle_delete_certificate(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle DeleteCertificate request"""
        # Simplified implementation - always accept
        return {
            "status": "Accepted"
        }
    
    async def _handle_install_certificate(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle InstallCertificate request"""
        # Simplified implementation - always accept
        return {
            "status": "Accepted"
        }
    
    async def _handle_get_certificate_status(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle GetCertificateStatus request"""
        # Simplified implementation - return accepted
        return {
            "status": "Accepted"
        }
    
    async def _handle_get_certificate_chain_status(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle GetCertificateChainStatus request"""
        # Simplified implementation - return accepted
        return {
            "status": "Accepted"
        }
    
    async def _handle_get_tariffs(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle GetTariffs request"""
        # Simplified implementation - return empty list
        return {
            "tariff": []
        }
    
    async def _handle_set_default_tariff(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle SetDefaultTariff request"""
        # Simplified implementation - always accept
        return {
            "status": "Accepted"
        }
    
    async def _handle_clear_tariffs(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle ClearTariffs request"""
        # Simplified implementation - always accept
        return {
            "clearTariffsResult": []
        }
    
    async def _handle_set_display_message(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle SetDisplayMessage request"""
        # Simplified implementation - always accept
        return {
            "status": "Accepted"
        }
    
    async def _handle_get_display_messages(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle GetDisplayMessages request"""
        # Simplified implementation - return empty list
        return {
            "messageInfo": []
        }
    
    async def _handle_clear_display_message(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle ClearDisplayMessage request"""
        # Simplified implementation - always accept
        return {
            "status": "Accepted"
        }
    
    async def _handle_set_variable_monitoring(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle SetVariableMonitoring request"""
        # Simplified implementation - always accept
        return {
            "setMonitoringResult": []
        }
    
    async def _handle_clear_variable_monitoring(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle ClearVariableMonitoring request"""
        # Simplified implementation - always accept
        return {
            "clearMonitoringResult": []
        }
    
    async def _handle_set_monitoring_base(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle SetMonitoringBase request"""
        # Simplified implementation - always accept
        return {
            "status": "Accepted"
        }
    
    async def _handle_set_monitoring_level(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle SetMonitoringLevel request"""
        # Simplified implementation - always accept
        return {
            "status": "Accepted"
        }
    
    async def _handle_get_monitoring_report(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle GetMonitoringReport request"""
        # Simplified implementation - return empty report
        return {
            "monitor": []
        }
    
    async def _handle_get_report(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle GetReport request"""
        # Simplified implementation - return empty report
        return {
            "reportData": []
        }
    
    async def _handle_get_base_report(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle GetBaseReport request"""
        # Simplified implementation - return empty report
        return {
            "reportData": []
        }
    
    async def _handle_trigger_message(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle TriggerMessage request"""
        # Simplified implementation - always accept
        return {
            "status": "Accepted"
        }
    
    async def _handle_data_transfer(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle DataTransfer request"""
        # Simplified implementation - always accept
        return {
            "status": "Accepted"
        }
    
    async def _handle_get_log(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle GetLog request"""
        # Simplified implementation - always accept
        return {
            "status": "Accepted"
        }
    
    async def _handle_get_15118_ev_certificate(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """Handle Get15118EVCertificate request"""
        # Simplified implementation - always accept
        return {
            "status": "Accepted"
        }
    
    def get_stats(self) -> Dict[str, Any]:
        """
        Get client statistics
        
        Returns:
            Client statistics
        """
        return self.stats.copy()


# Example usage
async def main():
    """Main function to run the CP client"""
    client = CPClient()
    
    try:
        await client.connect()
        
        # Keep client running
        while client.is_connected:
            await asyncio.sleep(1)
            
    except KeyboardInterrupt:
        print("Shutting down CP client...")
    finally:
        await client.disconnect()


if __name__ == "__main__":
    asyncio.run(main())
