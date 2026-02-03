"""
OCPP 2.1 CSMS (Central System Management System) Server

This module implements the CSMS server that handles connections from Charge Points (CPs)
and manages charging operations, user authentication, and system monitoring.
"""

import asyncio
import json
import uuid
from typing import Dict, Set, Optional, Any, Callable, List
from datetime import datetime, timedelta
import websockets
from websockets.server import WebSocketServerProtocol
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


class ChargingStationConnection:
    """
    Represents a connection to a charging station (CP).
    
    This class manages the WebSocket connection, message handling,
    and state for a single charging station.
    """
    
    def __init__(self, websocket: WebSocketServerProtocol, station_id: str, server=None):
        """
        Initialize charging station connection
        
        Args:
            websocket: WebSocket connection
            station_id: Charging station ID
            server: Reference to the CSMS server
        """
        self.websocket = websocket
        self.station_id = station_id
        self.server = server
        self.connected_at = datetime.now()
        self.last_heartbeat = datetime.now()
        self.heartbeat_count = 0  # Counter for heartbeat messages
        self.is_authenticated = False
        self.pending_messages: Dict[str, asyncio.Future] = {}
        self.logger = get_logger(f"csms.connection.{station_id}")
        
        # Charging station information
        self.station_info: Optional[Dict[str, Any]] = None
        self.evses: Dict[int, Dict[str, Any]] = {}
        self.connectors: Dict[int, Dict[str, Any]] = {}
        
        # Transaction management
        self.active_transactions: Dict[str, Dict[str, Any]] = {}
        self.transaction_history: List[Dict[str, Any]] = []
        
        # Charging profiles
        self.charging_profiles: Dict[int, Dict[str, Any]] = {}
        
        # Monitoring
        self.monitoring_data: Dict[str, Any] = {}
        
        # Security
        self.security_events: List[Dict[str, Any]] = []
        
        self.logger.info(f"Charging station connection established: {station_id}")
    
    async def send_message(self, message: OCPPMessage) -> Optional[Dict[str, Any]]:
        """
        Send a message to the charging station
        
        Args:
            message: OCPP message to send
            
        Returns:
            Response message if it's a request, None otherwise
        """
        try:
            # Serialize message to JSON
            message_data = message.model_dump()
            
            # Add unique ID if not present
            if not message_data.get("unique_id"):
                message_data["unique_id"] = str(uuid.uuid4())
            
            # Send message
            message_json = json.dumps(message_data)
            self.logger.info(f"Sending JSON to websocket: {message_json}")
            await self.websocket.send(message_json)
            
            self.logger.log_ocpp_message(
                message_type=message.action or "Unknown",
                direction="request",
                message=f"Sent message to {self.station_id}",
                charging_station_id=self.station_id
            )
            
            # If it's a request, wait for response
            if message.message_type == MessageType.CALL:
                unique_id = message_data["unique_id"]
                future = asyncio.Future()
                self.pending_messages[unique_id] = future
                
                try:
                    # Wait for response with timeout
                    response = await asyncio.wait_for(future, timeout=30.0)
                    return response
                except asyncio.TimeoutError:
                    self.pending_messages.pop(unique_id, None)
                    raise OCPPTimeoutError(f"Timeout waiting for response from {self.station_id}")
                finally:
                    self.pending_messages.pop(unique_id, None)
            
            return None
            
        except Exception as e:
            self.logger.error(f"Failed to send message to {self.station_id}: {str(e)}")
            raise OCPPConnectionError(f"Failed to send message: {str(e)}")
    
    async def handle_message(self, message_data: Dict[str, Any]) -> None:
        """
        Handle incoming message from charging station
        
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
                message=f"Received message from {self.station_id}",
                charging_station_id=self.station_id
            )
            
            # Handle different message types
            if message_type == MessageType.CALL:
                # Handle request from charging station
                self.logger.info(f"Handling request: {action} with payload: {payload}")
                
                response = await self._handle_request(action, payload)
                if response:
                    self.logger.info(f"Sending response: {response}")
                    await self._send_response(unique_id, response)
                else:
                    self.logger.warning(f"No response generated for action: {action}")
            
            elif message_type == MessageType.CALL_RESULT:
                # Handle response from charging station
                await self._handle_response(unique_id, payload)
            
            elif message_type == MessageType.CALL_ERROR:
                # Handle error from charging station
                await self._handle_error(unique_id, payload)
            
            else:
                raise OCPPProtocolError(f"Invalid message type: {message_type}")
                
        except Exception as e:
            self.logger.error(f"Error handling message from {self.station_id}: {str(e)}")
            # Only send error if we have a unique_id
            if 'unique_id' in locals():
                await self._send_error(unique_id, "InternalError", str(e))
    
    async def _handle_request(self, action: str, payload: Dict[str, Any]) -> Optional[Dict[str, Any]]:
        """
        Handle request from charging station
        
        Args:
            action: Action name
            payload: Request payload
            
        Returns:
            Response payload
        """
        try:
            if action == ActionType.BootNotification:
                return await self._handle_boot_notification(payload)
            elif action == ActionType.Heartbeat:
                return await self._handle_heartbeat(payload)
            elif action == ActionType.StatusNotification:
                return await self._handle_status_notification(payload)
            elif action == ActionType.TransactionEvent:
                return await self._handle_transaction_event(payload)
            elif action == ActionType.MeterValues:
                return await self._handle_meter_values(payload)
            elif action == ActionType.DataTransfer:
                return await self._handle_data_transfer(payload)
            elif action == ActionType.LogStatusNotification:
                return await self._handle_log_status_notification(payload)
            elif action == ActionType.FirmwareStatusNotification:
                return await self._handle_firmware_status_notification(payload)
            elif action == ActionType.SecurityEventNotification:
                return await self._handle_security_event_notification(payload)
            elif action == ActionType.ReservationStatusUpdate:
                return await self._handle_reservation_status_update(payload)
            elif action == ActionType.ReportChargingProfiles:
                return await self._handle_report_charging_profiles(payload)
            elif action == ActionType.NotifyReport:
                return await self._handle_notify_report(payload)
            elif action == ActionType.NotifyMonitoringReport:
                return await self._handle_notify_monitoring_report(payload)
            elif action == ActionType.NotifyDisplayMessages:
                return await self._handle_notify_display_messages(payload)
            elif action == ActionType.CostUpdated:
                return await self._handle_cost_updated(payload)
            else:
                self.logger.warning(f"Unknown action: {action}")
                return None
                
        except Exception as e:
            self.logger.error(f"Error handling request {action}: {str(e)}")
            return None
    
    async def _handle_response(self, unique_id: str, payload: Dict[str, Any]) -> None:
        """
        Handle response from charging station
        
        Args:
            unique_id: Message unique ID
            payload: Response payload
        """
        if unique_id in self.pending_messages:
            future = self.pending_messages[unique_id]
            if not future.done():
                future.set_result(payload)
    
    async def _handle_error(self, unique_id: str, payload: Dict[str, Any]) -> None:
        """
        Handle error from charging station
        
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
        Send response to charging station
        
        Args:
            unique_id: Message unique ID
            payload: Response payload
        """
        response = OCPPMessage(
            message_type=MessageType.CALL_RESULT,
            unique_id=unique_id,
            payload=payload
        )
        self.logger.info(f"Sending response: {response.model_dump()}")
        await self.send_message(response)
    
    async def _send_error(self, unique_id: str, error_code: str, 
                         error_description: str, error_details: Optional[Dict[str, Any]] = None) -> None:
        """
        Send error to charging station
        
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
    
    async def _send_authorize_request(self, station_id: str) -> None:
        """
        Send AuthorizeRequest to charging station
        
        Args:
            station_id: Station ID to send request to
        """
        try:
            # Create AuthorizeRequest payload
            payload = {
                "idToken": {
                    "idToken": f"RFID-{station_id}",  # Use station ID as base for RFID
                    "type": "RFID"
                }
            }
            
            # Create request message
            request = OCPPMessage(
                message_type=MessageType.CALL,
                unique_id=str(uuid.uuid4()),
                action=ActionType.Authorize,
                payload=payload
            )
            
            self.logger.info(f"Sending AuthorizeRequest to station {station_id}")
            await self.send_message(request)
            
        except Exception as e:
            self.logger.error(f"Error sending AuthorizeRequest to {station_id}: {str(e)}")
    
    async def _send_authorize_request_after_response(self, station_id: str) -> None:
        """
        Send AuthorizeRequest after a short delay to ensure response is sent first
        
        Args:
            station_id: Station ID to send request to
        """
        # Wait a short time to ensure the boot notification response is sent first
        await asyncio.sleep(0.5)
        await self._send_authorize_request(station_id)
    
    # Request handlers
    async def _handle_boot_notification(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """
        Handle BootNotification request
        
        Args:
            payload: Request payload
            
        Returns:
            Response payload
        """
        try:
            # Extract charging station information
            charging_station = payload.get("chargingStation", {})
            reason = payload.get("reason")
            
            # Get station ID from boot notification payload
            station_id = charging_station.get("station_id", charging_station.get("serial_number", charging_station.get("serialNumber", "Unknown")))
            
            # Update connection with proper station ID
            if self.station_id == "Unknown":
                self.station_id = station_id
                # Update server's connection registry
                if self.server:
                    self.server.connections[station_id] = self
                    if "Unknown" in self.server.connections:
                        del self.server.connections["Unknown"]
            
            # Store charging station information
            self.station_info = {
                "model": charging_station.get("model"),
                "vendor_name": charging_station.get("vendorName"),
                "serial_number": charging_station.get("serialNumber"),
                "firmware_version": charging_station.get("firmwareVersion"),
                "modem": charging_station.get("modem"),
                "boot_reason": reason,
                "boot_time": datetime.now()
            }
            
            # Mark as authenticated
            self.is_authenticated = True
            
            self.logger.info(f"Boot notification processed for station {station_id}")
            
            # Return acceptance response
            response = {
                "currentTime": datetime.now().isoformat(),
                "interval": 300,  # 5 minutes heartbeat interval
                "status": "Accepted"
            }
            
            # Send AuthorizeRequest after successful boot notification
            # We need to do this asynchronously after the response is sent
            asyncio.create_task(self._send_authorize_request_after_response(station_id))
            
            return response
            
        except Exception as e:
            self.logger.error(f"Error handling boot notification: {str(e)}")
            raise OCPPInternalError(f"Error processing boot notification: {str(e)}")
    
    async def _handle_heartbeat(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """
        Handle Heartbeat request
        
        Args:
            payload: Request payload
            
        Returns:
            Response payload
        """
        try:
            # Update last heartbeat time
            self.last_heartbeat = datetime.now()
            
            # Increment heartbeat counter
            self.heartbeat_count += 1
            
            self.logger.info(f"Heartbeat #{self.heartbeat_count} received from {self.station_id}")
            
            # Send AuthorizeRequest after 5 heartbeats
            if self.heartbeat_count == 5:
                self.logger.info(f"Sending AuthorizeRequest after 5th heartbeat from {self.station_id}")
                asyncio.create_task(self._send_authorize_request_after_response(self.station_id))
            
            # Return current time
            return {
                "currentTime": datetime.now().isoformat()
            }
            
        except Exception as e:
            self.logger.error(f"Error handling heartbeat: {str(e)}")
            raise OCPPInternalError(f"Error processing heartbeat: {str(e)}")
    
    async def _handle_status_notification(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """
        Handle StatusNotification request
        
        Args:
            payload: Request payload
            
        Returns:
            Response payload
        """
        try:
            # Extract status information
            evse_id = payload.get("evseId")
            connector_id = payload.get("connectorId")
            status = payload.get("status")
            timestamp = payload.get("timestamp")
            
            # Update connector status
            if evse_id is not None and connector_id is not None:
                connector_key = f"{evse_id}_{connector_id}"
                self.connectors[connector_key] = {
                    "evse_id": evse_id,
                    "connector_id": connector_id,
                    "status": status,
                    "timestamp": timestamp,
                    "last_updated": datetime.now()
                }
            
            self.logger.info(f"Status update from {self.station_id}: EVSE {evse_id}, Connector {connector_id}, Status {status}")
            
            # Return empty response (StatusNotification doesn't require response data)
            return {"status": "Accepted"}
            
        except Exception as e:
            self.logger.error(f"Error handling status notification: {str(e)}")
            raise OCPPInternalError(f"Error processing status notification: {str(e)}")
    
    async def _handle_transaction_event(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """
        Handle TransactionEvent request
        
        Args:
            payload: Request payload
            
        Returns:
            Response payload
        """
        try:
            # Extract transaction information
            event_type = payload.get("eventType")
            timestamp = payload.get("timestamp")
            transaction_id = payload.get("transactionId")
            evse_id = payload.get("evseId")
            connector_id = payload.get("connectorId")
            
            # Update transaction information
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
                        self.transaction_history.append(transaction)
            
            self.logger.log_transaction_event(
                event=f"Transaction {event_type}",
                transaction_id=transaction_id or "Unknown",
                charging_station_id=self.station_id
            )
            
            # Return empty response (TransactionEvent doesn't require response data)
            return {"status": "Accepted"}
            
        except Exception as e:
            self.logger.error(f"Error handling transaction event: {str(e)}")
            raise OCPPInternalError(f"Error processing transaction event: {str(e)}")
    
    async def _handle_meter_values(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """
        Handle MeterValues request
        
        Args:
            payload: Request payload
            
        Returns:
            Response payload
        """
        try:
            # Extract meter values
            evse_id = payload.get("evseId")
            meter_value = payload.get("meterValue", [])
            
            # Store meter values
            self.monitoring_data[f"meter_values_{evse_id}"] = {
                "evse_id": evse_id,
                "meter_value": meter_value,
                "timestamp": datetime.now()
            }
            
            self.logger.info(f"Meter values received from {self.station_id} for EVSE {evse_id}")
            
            # Return empty response (MeterValues doesn't require response data)
            return {"status": "Accepted"}
            
        except Exception as e:
            self.logger.error(f"Error handling meter values: {str(e)}")
            raise OCPPInternalError(f"Error processing meter values: {str(e)}")
    
    async def _handle_data_transfer(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """
        Handle DataTransfer request
        
        Args:
            payload: Request payload
            
        Returns:
            Response payload
        """
        try:
            # Extract data transfer information
            vendor_id = payload.get("vendorId")
            message_id = payload.get("messageId")
            data = payload.get("data")
            
            self.logger.info(f"Data transfer from {self.station_id}: Vendor {vendor_id}, Message {message_id}")
            
            # Process data transfer (implementation depends on vendor)
            status = "Accepted"  # Default to accepted
            
            return {
                "status": status,
                "data": data  # Echo back the data
            }
            
        except Exception as e:
            self.logger.error(f"Error handling data transfer: {str(e)}")
            raise OCPPInternalError(f"Error processing data transfer: {str(e)}")
    
    async def _handle_log_status_notification(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """
        Handle LogStatusNotification request
        
        Args:
            payload: Request payload
            
        Returns:
            Response payload
        """
        try:
            # Extract log status information
            status = payload.get("status")
            request_id = payload.get("requestId")
            
            self.logger.info(f"Log status notification from {self.station_id}: Status {status}, Request {request_id}")
            
            # Return empty response (LogStatusNotification doesn't require response data)
            return {}
            
        except Exception as e:
            self.logger.error(f"Error handling log status notification: {str(e)}")
            raise OCPPInternalError(f"Error processing log status notification: {str(e)}")
    
    async def _handle_firmware_status_notification(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """
        Handle FirmwareStatusNotification request
        
        Args:
            payload: Request payload
            
        Returns:
            Response payload
        """
        try:
            # Extract firmware status information
            status = payload.get("status")
            request_id = payload.get("requestId")
            
            self.logger.info(f"Firmware status notification from {self.station_id}: Status {status}, Request {request_id}")
            
            # Return empty response (FirmwareStatusNotification doesn't require response data)
            return {}
            
        except Exception as e:
            self.logger.error(f"Error handling firmware status notification: {str(e)}")
            raise OCPPInternalError(f"Error processing firmware status notification: {str(e)}")
    
    async def _handle_security_event_notification(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """
        Handle SecurityEventNotification request
        
        Args:
            payload: Request payload
            
        Returns:
            Response payload
        """
        try:
            # Extract security event information
            event_type = payload.get("eventType")
            timestamp = payload.get("timestamp")
            tech_info = payload.get("techInfo")
            
            # Store security event
            security_event = {
                "event_type": event_type,
                "timestamp": timestamp,
                "tech_info": tech_info,
                "station_id": self.station_id,
                "received_at": datetime.now()
            }
            self.security_events.append(security_event)
            
            self.logger.log_security_event(
                event=f"Security event: {event_type}",
                charging_station_id=self.station_id
            )
            
            # Return empty response (SecurityEventNotification doesn't require response data)
            return {}
            
        except Exception as e:
            self.logger.error(f"Error handling security event notification: {str(e)}")
            raise OCPPInternalError(f"Error processing security event notification: {str(e)}")
    
    async def _handle_reservation_status_update(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """
        Handle ReservationStatusUpdate request
        
        Args:
            payload: Request payload
            
        Returns:
            Response payload
        """
        try:
            # Extract reservation status information
            reservation_id = payload.get("reservationId")
            reservation_status = payload.get("reservationStatus")
            
            self.logger.info(f"Reservation status update from {self.station_id}: ID {reservation_id}, Status {reservation_status}")
            
            # Return empty response (ReservationStatusUpdate doesn't require response data)
            return {}
            
        except Exception as e:
            self.logger.error(f"Error handling reservation status update: {str(e)}")
            raise OCPPInternalError(f"Error processing reservation status update: {str(e)}")
    
    async def _handle_report_charging_profiles(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """
        Handle ReportChargingProfiles request
        
        Args:
            payload: Request payload
            
        Returns:
            Response payload
        """
        try:
            # Extract charging profile information
            charging_profile = payload.get("chargingProfile", [])
            
            # Store charging profiles
            for profile in charging_profile:
                profile_id = profile.get("chargingProfileId")
                if profile_id:
                    self.charging_profiles[profile_id] = profile
            
            self.logger.info(f"Charging profiles reported from {self.station_id}: {len(charging_profile)} profiles")
            
            # Return empty response (ReportChargingProfiles doesn't require response data)
            return {}
            
        except Exception as e:
            self.logger.error(f"Error handling report charging profiles: {str(e)}")
            raise OCPPInternalError(f"Error processing report charging profiles: {str(e)}")
    
    async def _handle_notify_report(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """
        Handle NotifyReport request
        
        Args:
            payload: Request payload
            
        Returns:
            Response payload
        """
        try:
            # Extract report information
            request_id = payload.get("requestId")
            generated_at = payload.get("generatedAt")
            report_data = payload.get("reportData", [])
            
            self.logger.info(f"Report notification from {self.station_id}: Request {request_id}, {len(report_data)} data items")
            
            # Return empty response (NotifyReport doesn't require response data)
            return {}
            
        except Exception as e:
            self.logger.error(f"Error handling notify report: {str(e)}")
            raise OCPPInternalError(f"Error processing notify report: {str(e)}")
    
    async def _handle_notify_monitoring_report(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """
        Handle NotifyMonitoringReport request
        
        Args:
            payload: Request payload
            
        Returns:
            Response payload
        """
        try:
            # Extract monitoring report information
            request_id = payload.get("requestId")
            generated_at = payload.get("generatedAt")
            monitor_data = payload.get("monitor", [])
            
            self.logger.info(f"Monitoring report notification from {self.station_id}: Request {request_id}, {len(monitor_data)} monitors")
            
            # Return empty response (NotifyMonitoringReport doesn't require response data)
            return {}
            
        except Exception as e:
            self.logger.error(f"Error handling notify monitoring report: {str(e)}")
            raise OCPPInternalError(f"Error processing notify monitoring report: {str(e)}")
    
    async def _handle_notify_display_messages(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """
        Handle NotifyDisplayMessages request
        
        Args:
            payload: Request payload
            
        Returns:
            Response payload
        """
        try:
            # Extract display message information
            request_id = payload.get("requestId")
            message_info = payload.get("messageInfo", [])
            
            self.logger.info(f"Display message notification from {self.station_id}: Request {request_id}, {len(message_info)} messages")
            
            # Return empty response (NotifyDisplayMessages doesn't require response data)
            return {}
            
        except Exception as e:
            self.logger.error(f"Error handling notify display messages: {str(e)}")
            raise OCPPInternalError(f"Error processing notify display messages: {str(e)}")
    
    async def _handle_cost_updated(self, payload: Dict[str, Any]) -> Dict[str, Any]:
        """
        Handle CostUpdated request
        
        Args:
            payload: Request payload
            
        Returns:
            Response payload
        """
        try:
            # Extract cost information
            total_cost = payload.get("totalCost")
            transaction_id = payload.get("transactionId")
            
            self.logger.info(f"Cost updated from {self.station_id}: Transaction {transaction_id}, Cost {total_cost}")
            
            # Return empty response (CostUpdated doesn't require response data)
            return {}
            
        except Exception as e:
            self.logger.error(f"Error handling cost updated: {str(e)}")
            raise OCPPInternalError(f"Error processing cost updated: {str(e)}")
    
    async def close(self) -> None:
        """Close the connection"""
        try:
            await self.websocket.close()
            self.logger.info(f"Connection closed for {self.station_id}")
        except Exception as e:
            self.logger.error(f"Error closing connection for {self.station_id}: {str(e)}")


class CSMSServer:
    """
    OCPP 2.1 CSMS Server
    
    This class implements the Central System Management System server
    that handles connections from Charge Points and manages charging operations.
    """
    
    def __init__(self):
        """Initialize CSMS server"""
        self.settings = get_settings()
        self.logger = get_logger("csms.server")
        self.connections: Dict[str, ChargingStationConnection] = {}
        self.server: Optional[websockets.WebSocketServer] = None
        self.is_running = False
        
        # Statistics
        self.stats = {
            "total_connections": 0,
            "active_connections": 0,
            "total_messages": 0,
            "total_transactions": 0,
            "start_time": None
        }
        
        self.logger.info("CSMS Server initialized")
    
    async def start(self) -> None:
        """
        Start the CSMS server
        
        This method starts the WebSocket server and begins accepting
        connections from Charge Points.
        """
        try:
            self.logger.info(f"Starting CSMS server on {self.settings.csms.host}:{self.settings.csms.port}")
            
            # Start WebSocket server
            self.server = await websockets.serve(
                self._handle_connection,
                self.settings.csms.host,
                self.settings.csms.port,
                ping_interval=self.settings.csms.websocket_ping_interval,
                ping_timeout=self.settings.csms.websocket_ping_timeout,
                max_size=self.settings.csms.websocket_max_size,
                subprotocols=['ocpp2.1']
            )
            
            self.is_running = True
            self.stats["start_time"] = datetime.now()
            
            self.logger.info("CSMS server started successfully")
            
            # Start background tasks
            asyncio.create_task(self._heartbeat_monitor())
            asyncio.create_task(self._stats_monitor())
            
        except Exception as e:
            self.logger.error(f"Failed to start CSMS server: {str(e)}")
            raise OCPPInternalError(f"Failed to start server: {str(e)}")
    
    async def stop(self) -> None:
        """
        Stop the CSMS server
        
        This method stops the WebSocket server and closes all
        active connections.
        """
        try:
            self.logger.info("Stopping CSMS server")
            
            # Close all connections
            for connection in self.connections.values():
                await connection.close()
            
            # Stop server
            if self.server:
                self.server.close()
                await self.server.wait_closed()
            
            self.is_running = False
            
            self.logger.info("CSMS server stopped")
            
        except Exception as e:
            self.logger.error(f"Error stopping CSMS server: {str(e)}")
    
    async def _handle_connection(self, websocket: WebSocketServerProtocol) -> None:
        """
        Handle new WebSocket connection
        
        Args:
            websocket: WebSocket connection
        """
        connection_id = None
        try:
            # Extract connection information
            client_address = websocket.remote_address
            connection_id = f"{client_address[0]}:{client_address[1]}"
            
            self.logger.info(f"New connection from {connection_id}")
            
            # Create charging station connection immediately
            connection = ChargingStationConnection(websocket, "Unknown", self)
            self.connections["Unknown"] = connection
            
            # Update statistics
            self.stats["total_connections"] += 1
            self.stats["active_connections"] = len(self.connections)
            
            self.logger.info(f"Charging station Unknown connected from {connection_id}")
            
            # Handle messages from this connection
            await self._handle_messages(connection)
            
        except ConnectionClosed:
            self.logger.info(f"Connection {connection_id} closed")
        except Exception as e:
            self.logger.error(f"Error handling connection {connection_id}: {str(e)}")
        finally:
            # Clean up connection
            if connection_id and connection_id in self.connections:
                connection = self.connections.pop(connection_id)
                await connection.close()
                self.stats["active_connections"] = len(self.connections)
    
    
    async def _handle_messages(self, connection: ChargingStationConnection) -> None:
        """
        Handle messages from a charging station connection
        
        Args:
            connection: Charging station connection
        """
        try:
            self.logger.info(f"Starting message loop for connection {connection.station_id}")
            async for message in connection.websocket:
                try:
                    self.logger.info(f"Received raw message: {message}")
                    message_data = json.loads(message)
                    self.logger.info(f"Parsed message data: {message_data}")
                    await connection.handle_message(message_data)
                    self.stats["total_messages"] += 1
                except json.JSONDecodeError as e:
                    self.logger.error(f"Invalid JSON message from {connection.station_id}: {str(e)}")
                except Exception as e:
                    self.logger.error(f"Error processing message from {connection.station_id}: {str(e)}")
                    
        except ConnectionClosed:
            self.logger.info(f"Connection closed for {connection.station_id}")
        except Exception as e:
            self.logger.error(f"Error handling messages for {connection.station_id}: {str(e)}")
    
    async def _heartbeat_monitor(self) -> None:
        """Monitor heartbeat from charging stations"""
        while self.is_running:
            try:
                current_time = datetime.now()
                
                for station_id, connection in list(self.connections.items()):
                    # Check if heartbeat is overdue
                    time_since_heartbeat = current_time - connection.last_heartbeat
                    if time_since_heartbeat > timedelta(seconds=self.settings.csms.heartbeat_interval * 2):
                        self.logger.warning(f"Heartbeat overdue for {station_id}")
                        
                        # Close connection if heartbeat is too overdue
                        if time_since_heartbeat > timedelta(seconds=self.settings.csms.heartbeat_interval * 4):
                            self.logger.warning(f"Closing connection for {station_id} due to overdue heartbeat")
                            await connection.close()
                            self.connections.pop(station_id, None)
                            self.stats["active_connections"] = len(self.connections)
                
                await asyncio.sleep(60)  # Check every minute
                
            except Exception as e:
                self.logger.error(f"Error in heartbeat monitor: {str(e)}")
                await asyncio.sleep(60)
    
    async def _stats_monitor(self) -> None:
        """Monitor and log server statistics"""
        while self.is_running:
            try:
                self.logger.info(f"CSMS Server Stats - Active Connections: {self.stats['active_connections']}, "
                               f"Total Messages: {self.stats['total_messages']}, "
                               f"Total Transactions: {self.stats['total_transactions']}")
                
                await asyncio.sleep(300)  # Log stats every 5 minutes
                
            except Exception as e:
                self.logger.error(f"Error in stats monitor: {str(e)}")
                await asyncio.sleep(300)
    
    def get_connection(self, station_id: str) -> Optional[ChargingStationConnection]:
        """
        Get connection for a charging station
        
        Args:
            station_id: Charging station ID
            
        Returns:
            Connection if found, None otherwise
        """
        return self.connections.get(station_id)
    
    def get_all_connections(self) -> Dict[str, ChargingStationConnection]:
        """
        Get all active connections
        
        Returns:
            Dictionary of all active connections
        """
        return self.connections.copy()
    
    def get_stats(self) -> Dict[str, Any]:
        """
        Get server statistics
        
        Returns:
            Server statistics
        """
        return self.stats.copy()


# Example usage
async def main():
    """Main function to run the CSMS server"""
    server = CSMSServer()
    
    try:
        await server.start()
        
        # Keep server running
        while server.is_running:
            await asyncio.sleep(1)
            
    except KeyboardInterrupt:
        print("Shutting down CSMS server...")
    finally:
        await server.stop()


if __name__ == "__main__":
    asyncio.run(main())
