"""
OCPP 2.1 Integration Test

This module provides integration tests for the OCPP 2.1 implementation,
testing the interaction between CSMS server and CP client.
"""

import asyncio
import pytest
from datetime import datetime
from typing import Dict, Any

# Add the project root to the Python path
import sys
import os
project_root = os.path.dirname(os.path.dirname(__file__))
if project_root not in sys.path:
    sys.path.insert(0, project_root)

from config.settings import get_settings
from config.logging_config import setup_logging, get_logger
from ocpp.csms.server import CSMSServer
from ocpp.cp.client import CPClient
from ocpp.base.message_types import OCPPMessage, MessageType, ActionType


class OCPPIntegrationTest:
    """
    Integration test class for OCPP 2.1 implementation
    
    This class provides comprehensive tests for the interaction
    between CSMS server and CP client.
    """
    
    def __init__(self):
        """Initialize the integration test"""
        self.settings = get_settings()
        self.logger = get_logger("integration.test")
        
        # Test configuration
        # Generate UUID-based station ID: CP{UUID.4Hex}
        import uuid
        self.test_station_id = f"CP{uuid.uuid4().hex[:4].upper()}"
        self.test_port = 9001  # Use different port for testing
        
        # Test components
        self.csms_server: CSMSServer = None
        self.cp_client: CPClient = None
        
        # Test results
        self.test_results = {
            "boot_notification": False,
            "heartbeat": False,
            "status_notification": False,
            "transaction_event": False,
            "meter_values": False,
            "data_transfer": False
        }
        
        self.logger.info("OCPP Integration Test initialized")
    
    async def setup(self) -> None:
        """
        Setup test environment
        
        This method creates and configures the CSMS server
        and CP client for testing.
        """
        try:
            self.logger.info("Setting up integration test environment")
            
            # Create CSMS server
            self.csms_server = CSMSServer()
            
            # Modify server port for testing
            self.csms_server.settings.csms.port = self.test_port
            
            # Start server
            await self.csms_server.start()
            
            # Create CP client
            self.cp_client = CPClient(self.test_station_id)
            
            # Modify client URL for testing
            self.cp_client.settings.cp.csms_url = f"ws://localhost:{self.test_port}"
            
            self.logger.info("Integration test environment setup complete")
            
        except Exception as e:
            self.logger.error(f"Error setting up integration test: {str(e)}")
            raise
    
    async def teardown(self) -> None:
        """
        Teardown test environment
        
        This method cleans up the test environment by
        stopping the server and disconnecting the client.
        """
        try:
            self.logger.info("Tearing down integration test environment")
            
            if self.cp_client:
                await self.cp_client.disconnect()
            
            if self.csms_server:
                await self.csms_server.stop()
            
            self.logger.info("Integration test environment teardown complete")
            
        except Exception as e:
            self.logger.error(f"Error tearing down integration test: {str(e)}")
    
    async def test_boot_notification(self) -> bool:
        """
        Test boot notification process
        
        This test verifies that the CP client can successfully
        send a boot notification to the CSMS server.
        
        Returns:
            True if test passes, False otherwise
        """
        try:
            self.logger.info("Testing boot notification")
            
            # Connect client to server
            await self.cp_client.connect()
            
            # Wait for connection to be established
            await asyncio.sleep(2)
            
            # Check if client is authenticated
            if self.cp_client.is_authenticated:
                self.test_results["boot_notification"] = True
                self.logger.info("Boot notification test PASSED")
                return True
            else:
                self.logger.error("Boot notification test FAILED - client not authenticated")
                return False
                
        except Exception as e:
            self.logger.error(f"Boot notification test FAILED: {str(e)}")
            return False
    
    async def test_heartbeat(self) -> bool:
        """
        Test heartbeat functionality
        
        This test verifies that the CP client can send
        heartbeat messages to the CSMS server.
        
        Returns:
            True if test passes, False otherwise
        """
        try:
            self.logger.info("Testing heartbeat")
            
            # Wait for heartbeat to be sent
            await asyncio.sleep(5)
            
            # Check if heartbeat was received
            connection = self.csms_server.get_connection(self.test_station_id)
            if connection and connection.last_heartbeat:
                time_since_heartbeat = datetime.now() - connection.last_heartbeat
                if time_since_heartbeat < timedelta(minutes=1):
                    self.test_results["heartbeat"] = True
                    self.logger.info("Heartbeat test PASSED")
                    return True
            
            self.logger.error("Heartbeat test FAILED - no heartbeat received")
            return False
            
        except Exception as e:
            self.logger.error(f"Heartbeat test FAILED: {str(e)}")
            return False
    
    async def test_status_notification(self) -> bool:
        """
        Test status notification functionality
        
        This test verifies that the CP client can send
        status notifications to the CSMS server.
        
        Returns:
            True if test passes, False otherwise
        """
        try:
            self.logger.info("Testing status notification")
            
            # Send status notification
            await self.cp_client.send_status_notification(
                evse_id=1,
                connector_id=1,
                status="Available"
            )
            
            # Wait for message to be processed
            await asyncio.sleep(1)
            
            # Check if status was received
            connection = self.csms_server.get_connection(self.test_station_id)
            if connection and connection.connectors:
                connector_key = "1_1"
                if connector_key in connection.connectors:
                    self.test_results["status_notification"] = True
                    self.logger.info("Status notification test PASSED")
                    return True
            
            self.logger.error("Status notification test FAILED - status not received")
            return False
            
        except Exception as e:
            self.logger.error(f"Status notification test FAILED: {str(e)}")
            return False
    
    async def test_transaction_event(self) -> bool:
        """
        Test transaction event functionality
        
        This test verifies that the CP client can send
        transaction events to the CSMS server.
        
        Returns:
            True if test passes, False otherwise
        """
        try:
            self.logger.info("Testing transaction event")
            
            # Send transaction started event
            await self.cp_client.send_transaction_event(
                event_type="Started",
                timestamp=datetime.now(),
                transaction_id="TEST_TXN_001",
                evse_id=1,
                connector_id=1,
                meter_value=[{
                    "timestamp": datetime.now().isoformat(),
                    "sampledValue": [{
                        "value": "0.0",
                        "context": "Sample.Periodic",
                        "format": "Raw",
                        "measurand": "Energy.Active.Import.Register",
                        "unit": "kWh"
                    }]
                }]
            )
            
            # Wait for message to be processed
            await asyncio.sleep(1)
            
            # Check if transaction was received
            connection = self.csms_server.get_connection(self.test_station_id)
            if connection and connection.active_transactions:
                if "TEST_TXN_001" in connection.active_transactions:
                    self.test_results["transaction_event"] = True
                    self.logger.info("Transaction event test PASSED")
                    return True
            
            self.logger.error("Transaction event test FAILED - transaction not received")
            return False
            
        except Exception as e:
            self.logger.error(f"Transaction event test FAILED: {str(e)}")
            return False
    
    async def test_meter_values(self) -> bool:
        """
        Test meter values functionality
        
        This test verifies that the CP client can send
        meter values to the CSMS server.
        
        Returns:
            True if test passes, False otherwise
        """
        try:
            self.logger.info("Testing meter values")
            
            # Send meter values
            await self.cp_client.send_meter_values(
                evse_id=1,
                meter_value=[{
                    "timestamp": datetime.now().isoformat(),
                    "sampledValue": [
                        {
                            "value": "1.5",
                            "context": "Sample.Periodic",
                            "format": "Raw",
                            "measurand": "Energy.Active.Import.Register",
                            "unit": "kWh"
                        },
                        {
                            "value": "22.0",
                            "context": "Sample.Periodic",
                            "format": "Raw",
                            "measurand": "Power.Active.Import",
                            "unit": "kW"
                        }
                    ]
                }]
            )
            
            # Wait for message to be processed
            await asyncio.sleep(1)
            
            # Check if meter values were received
            connection = self.csms_server.get_connection(self.test_station_id)
            if connection and connection.monitoring_data:
                meter_key = "meter_values_1"
                if meter_key in connection.monitoring_data:
                    self.test_results["meter_values"] = True
                    self.logger.info("Meter values test PASSED")
                    return True
            
            self.logger.error("Meter values test FAILED - meter values not received")
            return False
            
        except Exception as e:
            self.logger.error(f"Meter values test FAILED: {str(e)}")
            return False
    
    async def test_data_transfer(self) -> bool:
        """
        Test data transfer functionality
        
        This test verifies that the CP client can send
        data transfer messages to the CSMS server.
        
        Returns:
            True if test passes, False otherwise
        """
        try:
            self.logger.info("Testing data transfer")
            
            # Send data transfer
            response = await self.cp_client.send_data_transfer(
                vendor_id="TestVendor",
                message_id="TestMessage",
                data="Test data"
            )
            
            # Check if response was received
            if response and response.get("status") == "Accepted":
                self.test_results["data_transfer"] = True
                self.logger.info("Data transfer test PASSED")
                return True
            
            self.logger.error("Data transfer test FAILED - invalid response")
            return False
            
        except Exception as e:
            self.logger.error(f"Data transfer test FAILED: {str(e)}")
            return False
    
    async def run_all_tests(self) -> Dict[str, bool]:
        """
        Run all integration tests
        
        This method runs all integration tests and returns
        the results.
        
        Returns:
            Dictionary of test results
        """
        try:
            self.logger.info("Starting integration tests")
            
            # Setup test environment
            await self.setup()
            
            # Run tests
            await self.test_boot_notification()
            await self.test_heartbeat()
            await self.test_status_notification()
            await self.test_transaction_event()
            await self.test_meter_values()
            await self.test_data_transfer()
            
            # Teardown test environment
            await self.teardown()
            
            # Log results
            self.logger.info("Integration test results:")
            for test_name, result in self.test_results.items():
                status = "PASSED" if result else "FAILED"
                self.logger.info(f"  {test_name}: {status}")
            
            return self.test_results
            
        except Exception as e:
            self.logger.error(f"Error running integration tests: {str(e)}")
            await self.teardown()
            return self.test_results
    
    def get_test_summary(self) -> str:
        """
        Get test summary
        
        Returns:
            Test summary string
        """
        total_tests = len(self.test_results)
        passed_tests = sum(1 for result in self.test_results.values() if result)
        failed_tests = total_tests - passed_tests
        
        summary = f"Integration Test Summary:\\n"
        summary += f"Total Tests: {total_tests}\\n"
        summary += f"Passed: {passed_tests}\\n"
        summary += f"Failed: {failed_tests}\\n"
        summary += f"Success Rate: {(passed_tests/total_tests)*100:.1f}%"
        
        return summary


# Pytest integration
@pytest.fixture
async def integration_test():
    """Pytest fixture for integration test"""
    test = OCPPIntegrationTest()
    await test.setup()
    yield test
    await test.teardown()


@pytest.mark.asyncio
async def test_boot_notification(integration_test):
    """Test boot notification"""
    result = await integration_test.test_boot_notification()
    assert result is True


@pytest.mark.asyncio
async def test_heartbeat(integration_test):
    """Test heartbeat"""
    result = await integration_test.test_heartbeat()
    assert result is True


@pytest.mark.asyncio
async def test_status_notification(integration_test):
    """Test status notification"""
    result = await integration_test.test_status_notification()
    assert result is True


@pytest.mark.asyncio
async def test_transaction_event(integration_test):
    """Test transaction event"""
    result = await integration_test.test_transaction_event()
    assert result is True


@pytest.mark.asyncio
async def test_meter_values(integration_test):
    """Test meter values"""
    result = await integration_test.test_meter_values()
    assert result is True


@pytest.mark.asyncio
async def test_data_transfer(integration_test):
    """Test data transfer"""
    result = await integration_test.test_data_transfer()
    assert result is True


# Example usage
async def main():
    """
    Main function to run integration tests
    
    This function runs all integration tests and displays
    the results.
    """
    try:
        # Setup logging
        setup_logging()
        logger = get_logger("main")
        
        logger.info("Starting OCPP 2.1 Integration Tests")
        
        # Create and run integration test
        integration_test = OCPPIntegrationTest()
        results = await integration_test.run_all_tests()
        
        # Display results
        print("\\n" + "="*50)
        print(integration_test.get_test_summary())
        print("="*50)
        
        # Check if all tests passed
        all_passed = all(results.values())
        if all_passed:
            logger.info("All integration tests PASSED")
            print("\\n✅ All tests passed!")
        else:
            logger.error("Some integration tests FAILED")
            print("\\n❌ Some tests failed!")
            
    except Exception as e:
        print(f"Error running integration tests: {str(e)}")


if __name__ == "__main__":
    # Import required modules
    from datetime import timedelta
    
    # Run the integration tests
    asyncio.run(main())
