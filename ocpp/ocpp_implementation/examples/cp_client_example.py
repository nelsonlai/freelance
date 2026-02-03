"""
OCPP 2.1 CP (Charge Point) Client Example

This example demonstrates how to run the CP client and connect
to a CSMS server, simulating a charging station.
"""

import asyncio
import signal
import sys
from typing import Optional
from datetime import datetime, timedelta
import random

# Add the project root to the Python path
import sys
import os
project_root = os.path.dirname(os.path.dirname(__file__))
if project_root not in sys.path:
    sys.path.insert(0, project_root)

from config.settings import get_settings
from config.logging_config import setup_logging, get_logger
from ocpp.cp.client import CPClient


class CPClientExample:
    """
    Example CP client implementation
    
    This class demonstrates how to use the CP client with
    simulated charging station operations and event handling.
    """
    
    def __init__(self, station_id: Optional[str] = None):
        """
        Initialize the CP client example
        
        Args:
            station_id: Charging station ID (if None, uses default from settings)
        """
        self.settings = get_settings()
        self.logger = get_logger("cp.example")
        self.client: Optional[CPClient] = None
        self.is_running = False
        self.station_id = station_id or self.settings.cp.station_id
        
        # Simulated charging station state
        self.evses = {
            1: {"id": 1, "connectors": [1, 2], "status": "Available"},
            2: {"id": 2, "connectors": [3, 4], "status": "Available"}
        }
        
        self.connectors = {
            1: {"id": 1, "evse_id": 1, "status": "Available", "power": 22.0},
            2: {"id": 2, "evse_id": 1, "status": "Available", "power": 22.0},
            3: {"id": 3, "evse_id": 2, "status": "Available", "power": 50.0},
            4: {"id": 4, "evse_id": 2, "status": "Available", "power": 50.0}
        }
        
        # Simulated transactions
        self.active_transactions = {}
        self.transaction_counter = 0
        
        # Setup signal handlers for graceful shutdown
        signal.signal(signal.SIGINT, self._signal_handler)
        signal.signal(signal.SIGTERM, self._signal_handler)
        
        self.logger.info(f"CP Client Example initialized for station {self.station_id}")
    
    def _signal_handler(self, signum, frame):
        """Handle shutdown signals"""
        self.logger.info(f"Received signal {signum}, shutting down...")
        self.is_running = False
    
    async def start(self) -> None:
        """
        Start the CP client example
        
        This method connects to the CSMS server and starts
        simulating charging station operations.
        """
        try:
            self.logger.info("Starting CP Client Example")
            
            # Create and connect client
            self.client = CPClient(self.station_id)
            await self.client.connect()
            
            self.is_running = True
            
            # Start background tasks
            asyncio.create_task(self._simulate_charging_operations())
            asyncio.create_task(self._simulate_meter_values())
            asyncio.create_task(self._simulate_status_changes())
            asyncio.create_task(self._log_statistics())
            
            self.logger.info("CP Client Example started successfully")
            
            # Keep client running
            while self.is_running:
                await asyncio.sleep(1)
                
        except Exception as e:
            self.logger.error(f"Error starting CP Client Example: {str(e)}")
            raise
        finally:
            await self.stop()
    
    async def stop(self) -> None:
        """Stop the CP client example"""
        try:
            self.logger.info("Stopping CP Client Example")
            
            if self.client:
                await self.client.disconnect()
            
            self.logger.info("CP Client Example stopped")
            
        except Exception as e:
            self.logger.error(f"Error stopping CP Client Example: {str(e)}")
    
    async def _simulate_charging_operations(self) -> None:
        """
        Simulate charging operations
        
        This method simulates EV charging sessions by randomly
        starting and stopping transactions.
        """
        while self.is_running:
            try:
                # Randomly start a new transaction
                if random.random() < 0.1 and len(self.active_transactions) < 2:  # 10% chance, max 2 transactions
                    await self._start_transaction()
                
                # Randomly stop an active transaction
                if random.random() < 0.05 and self.active_transactions:  # 5% chance
                    await self._stop_transaction()
                
                await asyncio.sleep(30)  # Check every 30 seconds
                
            except Exception as e:
                self.logger.error(f"Error in charging operations simulation: {str(e)}")
                await asyncio.sleep(30)
    
    async def _start_transaction(self) -> None:
        """
        Start a new charging transaction
        
        This method simulates an EV starting to charge by
        selecting an available connector and starting a transaction.
        """
        try:
            # Find available connector
            available_connectors = [c for c in self.connectors.values() if c["status"] == "Available"]
            
            if not available_connectors:
                return
            
            connector = random.choice(available_connectors)
            evse_id = connector["evse_id"]
            connector_id = connector["id"]
            
            # Generate transaction ID
            self.transaction_counter += 1
            transaction_id = f"TXN_{self.station_id}_{self.transaction_counter:06d}"
            
            # Update connector status
            self.connectors[connector_id]["status"] = "Occupied"
            self.evses[evse_id]["status"] = "Occupied"
            
            # Create transaction
            transaction = {
                "transaction_id": transaction_id,
                "evse_id": evse_id,
                "connector_id": connector_id,
                "start_time": datetime.now(),
                "status": "Active",
                "energy_delivered": 0.0,
                "power": connector["power"]
            }
            
            self.active_transactions[transaction_id] = transaction
            
            # Send transaction event to CSMS
            await self.client.send_transaction_event(
                event_type="Started",
                timestamp=transaction["start_time"],
                transaction_id=transaction_id,
                evse_id=evse_id,
                connector_id=connector_id,
                meter_value=[{
                    "timestamp": transaction["start_time"].isoformat(),
                    "sampledValue": [{
                        "value": "0.0",
                        "context": "Sample.Periodic",
                        "format": "Raw",
                        "measurand": "Energy.Active.Import.Register",
                        "unit": "kWh"
                    }]
                }]
            )
            
            # Send status notification
            await self.client.send_status_notification(
                evse_id=evse_id,
                connector_id=connector_id,
                status="Occupied",
                timestamp=transaction["start_time"]
            )
            
            self.logger.info(f"Started transaction {transaction_id} on EVSE {evse_id}, Connector {connector_id}")
            
        except Exception as e:
            self.logger.error(f"Error starting transaction: {str(e)}")
    
    async def _stop_transaction(self) -> None:
        """
        Stop an active charging transaction
        
        This method simulates an EV finishing charging by
        stopping the transaction and updating connector status.
        """
        try:
            if not self.active_transactions:
                return
            
            # Select random active transaction
            transaction_id = random.choice(list(self.active_transactions.keys()))
            transaction = self.active_transactions[transaction_id]
            
            # Calculate energy delivered (simulated)
            duration = datetime.now() - transaction["start_time"]
            energy_delivered = (transaction["power"] * duration.total_seconds() / 3600) / 1000  # kWh
            
            # Update transaction
            transaction["end_time"] = datetime.now()
            transaction["status"] = "Completed"
            transaction["energy_delivered"] = energy_delivered
            
            # Update connector status
            connector_id = transaction["connector_id"]
            evse_id = transaction["evse_id"]
            
            self.connectors[connector_id]["status"] = "Available"
            
            # Check if EVSE is now available
            evse_connectors = [c for c in self.connectors.values() if c["evse_id"] == evse_id]
            if all(c["status"] == "Available" for c in evse_connectors):
                self.evses[evse_id]["status"] = "Available"
            
            # Send transaction event to CSMS
            await self.client.send_transaction_event(
                event_type="Ended",
                timestamp=transaction["end_time"],
                transaction_id=transaction_id,
                evse_id=evse_id,
                connector_id=connector_id,
                meter_value=[{
                    "timestamp": transaction["end_time"].isoformat(),
                    "sampledValue": [{
                        "value": str(energy_delivered),
                        "context": "Sample.Periodic",
                        "format": "Raw",
                        "measurand": "Energy.Active.Import.Register",
                        "unit": "kWh"
                    }]
                }],
                reason="EVDisconnected"
            )
            
            # Send status notification
            await self.client.send_status_notification(
                evse_id=evse_id,
                connector_id=connector_id,
                status="Available",
                timestamp=transaction["end_time"]
            )
            
            # Remove from active transactions
            del self.active_transactions[transaction_id]
            
            self.logger.info(f"Stopped transaction {transaction_id}, delivered {energy_delivered:.2f} kWh")
            
        except Exception as e:
            self.logger.error(f"Error stopping transaction: {str(e)}")
    
    async def _simulate_meter_values(self) -> None:
        """
        Simulate meter value reporting
        
        This method simulates periodic meter value reporting
        for active transactions.
        """
        while self.is_running:
            try:
                for transaction_id, transaction in self.active_transactions.items():
                    # Calculate current energy delivered
                    duration = datetime.now() - transaction["start_time"]
                    energy_delivered = (transaction["power"] * duration.total_seconds() / 3600) / 1000  # kWh
                    
                    # Create meter value
                    meter_value = [{
                        "timestamp": datetime.now().isoformat(),
                        "sampledValue": [
                            {
                                "value": str(energy_delivered),
                                "context": "Sample.Periodic",
                                "format": "Raw",
                                "measurand": "Energy.Active.Import.Register",
                                "unit": "kWh"
                            },
                            {
                                "value": str(transaction["power"]),
                                "context": "Sample.Periodic",
                                "format": "Raw",
                                "measurand": "Power.Active.Import",
                                "unit": "kW"
                            },
                            {
                                "value": str(transaction["power"] * 1000 / 230),  # Simulated current
                                "context": "Sample.Periodic",
                                "format": "Raw",
                                "measurand": "Current.Import",
                                "unit": "A"
                            }
                        ]
                    }]
                    
                    # Send meter values
                    await self.client.send_meter_values(
                        evse_id=transaction["evse_id"],
                        meter_value=meter_value
                    )
                
                await asyncio.sleep(60)  # Send every minute
                
            except Exception as e:
                self.logger.error(f"Error simulating meter values: {str(e)}")
                await asyncio.sleep(60)
    
    async def _simulate_status_changes(self) -> None:
        """
        Simulate status changes
        
        This method simulates random status changes for
        connectors and EVSEs.
        """
        while self.is_running:
            try:
                # Randomly change connector status
                if random.random() < 0.01:  # 1% chance
                    connector_id = random.choice(list(self.connectors.keys()))
                    connector = self.connectors[connector_id]
                    
                    if connector["status"] == "Available":
                        connector["status"] = "Faulted"
                        await self.client.send_status_notification(
                            evse_id=connector["evse_id"],
                            connector_id=connector_id,
                            status="Faulted"
                        )
                        self.logger.info(f"Connector {connector_id} faulted")
                    elif connector["status"] == "Faulted":
                        connector["status"] = "Available"
                        await self.client.send_status_notification(
                            evse_id=connector["evse_id"],
                            connector_id=connector_id,
                            status="Available"
                        )
                        self.logger.info(f"Connector {connector_id} recovered")
                
                await asyncio.sleep(120)  # Check every 2 minutes
                
            except Exception as e:
                self.logger.error(f"Error simulating status changes: {str(e)}")
                await asyncio.sleep(120)
    
    async def _log_statistics(self) -> None:
        """
        Log client statistics
        
        This method logs client performance and state information.
        """
        while self.is_running:
            try:
                stats = self.client.get_stats()
                
                self.logger.info(f"CP Client Statistics:")
                self.logger.info(f"  Station ID: {self.station_id}")
                self.logger.info(f"  Connected: {self.client.is_connected}")
                self.logger.info(f"  Authenticated: {self.client.is_authenticated}")
                self.logger.info(f"  Messages Sent: {stats['total_messages_sent']}")
                self.logger.info(f"  Messages Received: {stats['total_messages_received']}")
                self.logger.info(f"  Total Transactions: {stats['total_transactions']}")
                self.logger.info(f"  Active Transactions: {len(self.active_transactions)}")
                
                # Log connector status
                for connector_id, connector in self.connectors.items():
                    self.logger.info(f"  Connector {connector_id}: {connector['status']} ({connector['power']} kW)")
                
                await asyncio.sleep(300)  # Log every 5 minutes
                
            except Exception as e:
                self.logger.error(f"Error logging statistics: {str(e)}")
                await asyncio.sleep(300)


async def main():
    """
    Main function to run the CP client example
    
    This function sets up logging, creates the client example,
    and runs it with proper error handling.
    """
    try:
        # Setup logging
        setup_logging()
        logger = get_logger("main")
        
        logger.info("Starting OCPP 2.1 CP Client Example")
        
        # Create and run client example
        client_example = CPClientExample()
        await client_example.start()
        
    except KeyboardInterrupt:
        print("\\nReceived keyboard interrupt, shutting down...")
    except Exception as e:
        print(f"Error running CP client example: {str(e)}")
        sys.exit(1)


if __name__ == "__main__":
    # Run the example
    asyncio.run(main())
