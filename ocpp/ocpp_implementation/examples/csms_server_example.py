"""
OCPP 2.1 CSMS Server Example

This example demonstrates how to run the CSMS server and handle
connections from Charge Points (CPs).
"""

import asyncio
import signal
import sys
from typing import Optional
from datetime import datetime, timedelta

# Add the project root to the Python path
import sys
import os
project_root = os.path.dirname(os.path.dirname(__file__))
if project_root not in sys.path:
    sys.path.insert(0, project_root)

from config.settings import get_settings
from config.logging_config import setup_logging, get_logger
from ocpp.csms.server import CSMSServer


class CSMSServerExample:
    """
    Example CSMS server implementation
    
    This class demonstrates how to use the CSMS server with
    custom business logic and event handling.
    """
    
    def __init__(self):
        """Initialize the CSMS server example"""
        self.settings = get_settings()
        self.logger = get_logger("csms.example")
        self.server: Optional[CSMSServer] = None
        self.is_running = False
        
        # Setup signal handlers for graceful shutdown
        signal.signal(signal.SIGINT, self._signal_handler)
        signal.signal(signal.SIGTERM, self._signal_handler)
        
        self.logger.info("CSMS Server Example initialized")
    
    def _signal_handler(self, signum, frame):
        """Handle shutdown signals"""
        self.logger.info(f"Received signal {signum}, shutting down...")
        self.is_running = False
    
    async def start(self) -> None:
        """
        Start the CSMS server example
        
        This method starts the server and demonstrates various
        OCPP operations and monitoring capabilities.
        """
        try:
            self.logger.info("Starting CSMS Server Example")
            
            # Create and start server
            self.server = CSMSServer()
            await self.server.start()
            
            self.is_running = True
            
            # Start background tasks
            asyncio.create_task(self._monitor_connections())
            asyncio.create_task(self._simulate_operations())
            asyncio.create_task(self._log_statistics())
            
            self.logger.info("CSMS Server Example started successfully")
            
            # Keep server running
            while self.is_running:
                await asyncio.sleep(1)
                
        except Exception as e:
            self.logger.error(f"Error starting CSMS Server Example: {str(e)}")
            raise
        finally:
            await self.stop()
    
    async def stop(self) -> None:
        """Stop the CSMS server example"""
        try:
            self.logger.info("Stopping CSMS Server Example")
            
            if self.server:
                await self.server.stop()
            
            self.logger.info("CSMS Server Example stopped")
            
        except Exception as e:
            self.logger.error(f"Error stopping CSMS Server Example: {str(e)}")
    
    async def _monitor_connections(self) -> None:
        """
        Monitor charging station connections
        
        This method demonstrates how to monitor and interact with
        connected charging stations.
        """
        while self.is_running:
            try:
                connections = self.server.get_all_connections()
                
                for station_id, connection in connections.items():
                    # Check connection health
                    time_since_heartbeat = datetime.now() - connection.last_heartbeat
                    
                    if time_since_heartbeat > timedelta(minutes=10):
                        self.logger.warning(f"Station {station_id} has not sent heartbeat for {time_since_heartbeat}")
                    
                    # Log station information
                    if connection.station_info:
                        self.logger.info(f"Station {station_id}: {connection.station_info.get('model')} "
                                       f"by {connection.station_info.get('vendor_name')}")
                    
                    # Log active transactions
                    if connection.active_transactions:
                        self.logger.info(f"Station {station_id} has {len(connection.active_transactions)} active transactions")
                
                await asyncio.sleep(60)  # Check every minute
                
            except Exception as e:
                self.logger.error(f"Error monitoring connections: {str(e)}")
                await asyncio.sleep(60)
    
    async def _simulate_operations(self) -> None:
        """
        Simulate CSMS operations
        
        This method demonstrates how to send commands to
        charging stations and handle responses.
        """
        while self.is_running:
            try:
                connections = self.server.get_all_connections()
                
                for station_id, connection in connections.items():
                    # Send heartbeat request (this is typically not needed as CPs send heartbeat)
                    # This is just for demonstration
                    if connection.is_authenticated:
                        try:
                            # Example: Send a data transfer request
                            data_transfer = OCPPMessage(
                                message_type=MessageType.CALL,
                                unique_id=str(uuid.uuid4()),
                                action=ActionType.DataTransfer,
                                payload={
                                    "vendorId": "ExampleVendor",
                                    "messageId": "StatusRequest",
                                    "data": "Request station status"
                                }
                            )
                            
                            response = await connection.send_message(data_transfer)
                            if response:
                                self.logger.info(f"Data transfer response from {station_id}: {response}")
                                
                        except Exception as e:
                            self.logger.error(f"Error sending data transfer to {station_id}: {str(e)}")
                
                await asyncio.sleep(300)  # Send every 5 minutes
                
            except Exception as e:
                self.logger.error(f"Error in simulate operations: {str(e)}")
                await asyncio.sleep(300)
    
    async def _log_statistics(self) -> None:
        """
        Log server statistics
        
        This method demonstrates how to monitor server performance
        and log statistics.
        """
        while self.is_running:
            try:
                stats = self.server.get_stats()
                
                self.logger.info(f"CSMS Server Statistics:")
                self.logger.info(f"  Active Connections: {stats['active_connections']}")
                self.logger.info(f"  Total Connections: {stats['total_connections']}")
                self.logger.info(f"  Total Messages: {stats['total_messages']}")
                self.logger.info(f"  Total Transactions: {stats['total_transactions']}")
                
                if stats['start_time']:
                    uptime = datetime.now() - stats['start_time']
                    self.logger.info(f"  Uptime: {uptime}")
                
                await asyncio.sleep(300)  # Log every 5 minutes
                
            except Exception as e:
                self.logger.error(f"Error logging statistics: {str(e)}")
                await asyncio.sleep(300)


async def main():
    """
    Main function to run the CSMS server example
    
    This function sets up logging, creates the server example,
    and runs it with proper error handling.
    """
    try:
        # Setup logging
        setup_logging()
        logger = get_logger("main")
        
        logger.info("Starting OCPP 2.1 CSMS Server Example")
        
        # Create and run server example
        server_example = CSMSServerExample()
        await server_example.start()
        
    except KeyboardInterrupt:
        print("\\nReceived keyboard interrupt, shutting down...")
    except Exception as e:
        print(f"Error running CSMS server example: {str(e)}")
        sys.exit(1)


if __name__ == "__main__":
    # Import required modules for the example
    import uuid
    from ocpp.base.message_types import OCPPMessage, MessageType, ActionType
    
    # Run the example
    asyncio.run(main())
