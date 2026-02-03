"""
Basic OCPP 2.1 Implementation Tests

This module provides basic tests to verify the OCPP 2.1 implementation
is working correctly.
"""

import asyncio
import pytest
import sys
import os

# Add the project root to the Python path
project_root = os.path.dirname(os.path.dirname(__file__))
if project_root not in sys.path:
    sys.path.insert(0, project_root)

from config.settings import get_settings
from config.logging_config import get_logger
from ocpp.base.message_types import OCPPMessage, MessageType, ActionType
from ocpp.base.exceptions import OCPPError


class TestOCPPBase:
    """Test basic OCPP functionality"""
    
    def test_settings_loading(self):
        """Test that settings can be loaded"""
        settings = get_settings()
        assert settings is not None
        assert hasattr(settings, 'csms')
        assert hasattr(settings, 'cp')
        assert hasattr(settings, 'logging')
    
    def test_logger_creation(self):
        """Test that logger can be created"""
        logger = get_logger("test")
        assert logger is not None
    
    def test_message_creation(self):
        """Test that OCPP messages can be created"""
        message = OCPPMessage(
            message_type=MessageType.CALL,
            unique_id="test-123",
            action=ActionType.Heartbeat,
            payload={}
        )
        assert message.message_type == MessageType.CALL
        assert message.unique_id == "test-123"
        assert message.action == ActionType.Heartbeat
        assert message.payload == {}
    
    def test_message_serialization(self):
        """Test that OCPP messages can be serialized"""
        message = OCPPMessage(
            message_type=MessageType.CALL,
            unique_id="test-123",
            action=ActionType.Heartbeat,
            payload={}
        )
        
        # Test dict conversion
        message_dict = message.dict()
        assert message_dict["message_type"] == "2"
        assert message_dict["unique_id"] == "test-123"
        assert message_dict["action"] == "Heartbeat"
        assert message_dict["payload"] == {}
    
    def test_exception_creation(self):
        """Test that OCPP exceptions can be created"""
        error = OCPPError("Test error", "TestError")
        assert error.message == "Test error"
        assert error.error_code == "TestError"
        assert str(error) == "Test error"


class TestOCPPServer:
    """Test CSMS server functionality"""
    
    def test_server_creation(self):
        """Test that CSMS server can be created"""
        from ocpp.csms.server import CSMSServer
        
        server = CSMSServer()
        assert server is not None
        assert hasattr(server, 'connections')
        assert hasattr(server, 'stats')
    
    def test_server_stats(self):
        """Test server statistics"""
        from ocpp.csms.server import CSMSServer
        
        server = CSMSServer()
        stats = server.get_stats()
        assert isinstance(stats, dict)
        assert "total_connections" in stats
        assert "active_connections" in stats
        assert "total_messages" in stats


class TestOCPPClient:
    """Test CP client functionality"""
    
    def test_client_creation(self):
        """Test that CP client can be created"""
        from ocpp.cp.client import CPClient
        
        client = CPClient("TEST_CP_001")
        assert client is not None
        assert client.station_id == "TEST_CP_001"
        assert hasattr(client, 'station_info')
        assert hasattr(client, 'evses')
        assert hasattr(client, 'connectors')
    
    def test_client_stats(self):
        """Test client statistics"""
        from ocpp.cp.client import CPClient
        
        client = CPClient("TEST_CP_001")
        stats = client.get_stats()
        assert isinstance(stats, dict)
        assert "total_messages_sent" in stats
        assert "total_messages_received" in stats
        assert "total_transactions" in stats


@pytest.mark.asyncio
class TestOCPPAsync:
    """Test async OCPP functionality"""
    
    async def test_async_message_handling(self):
        """Test async message handling"""
        from ocpp.csms.server import CSMSServer
        
        server = CSMSServer()
        
        # Test that server can be created without errors
        assert server is not None
        
        # Test that server has required methods
        assert hasattr(server, 'start')
        assert hasattr(server, 'stop')
        assert callable(server.start)
        assert callable(server.stop)
    
    async def test_async_client_handling(self):
        """Test async client handling"""
        from ocpp.cp.client import CPClient
        
        client = CPClient("TEST_CP_001")
        
        # Test that client can be created without errors
        assert client is not None
        
        # Test that client has required methods
        assert hasattr(client, 'connect')
        assert hasattr(client, 'disconnect')
        assert callable(client.connect)
        assert callable(client.disconnect)


def test_import_structure():
    """Test that all modules can be imported"""
    try:
        from config.settings import get_settings
        from config.logging_config import get_logger
        from ocpp.base.message_types import OCPPMessage, MessageType, ActionType
        from ocpp.base.exceptions import OCPPError
        from ocpp.csms.server import CSMSServer
        from ocpp.cp.client import CPClient
        assert True
    except ImportError as e:
        pytest.fail(f"Import failed: {e}")


def test_message_types():
    """Test that all message types are available"""
    from ocpp.base.message_types import ActionType
    
    # Test some key action types
    assert ActionType.Authorize == "Authorize"
    assert ActionType.BootNotification == "BootNotification"
    assert ActionType.Heartbeat == "Heartbeat"
    assert ActionType.StatusNotification == "StatusNotification"
    assert ActionType.TransactionEvent == "TransactionEvent"
    assert ActionType.MeterValues == "MeterValues"
    assert ActionType.DataTransfer == "DataTransfer"


def test_error_codes():
    """Test that error codes are available"""
    from ocpp.base.exceptions import OCPP_ERROR_CODES
    
    # Test some key error codes
    assert "FormationViolation" in OCPP_ERROR_CODES
    assert "PropertyConstraintViolation" in OCPP_ERROR_CODES
    assert "NotImplemented" in OCPP_ERROR_CODES
    assert "NotSupported" in OCPP_ERROR_CODES
    assert "InternalError" in OCPP_ERROR_CODES


if __name__ == "__main__":
    # Run basic tests
    print("Running basic OCPP 2.1 implementation tests...")
    
    # Test settings
    try:
        settings = get_settings()
        print("✅ Settings loading: PASSED")
    except Exception as e:
        print(f"❌ Settings loading: FAILED - {e}")
    
    # Test logger
    try:
        logger = get_logger("test")
        print("✅ Logger creation: PASSED")
    except Exception as e:
        print(f"❌ Logger creation: FAILED - {e}")
    
    # Test message creation
    try:
        message = OCPPMessage(
            message_type=MessageType.CALL,
            unique_id="test-123",
            action=ActionType.Heartbeat,
            payload={}
        )
        print("✅ Message creation: PASSED")
    except Exception as e:
        print(f"❌ Message creation: FAILED - {e}")
    
    # Test server creation
    try:
        from ocpp.csms.server import CSMSServer
        server = CSMSServer()
        print("✅ Server creation: PASSED")
    except Exception as e:
        print(f"❌ Server creation: FAILED - {e}")
    
    # Test client creation
    try:
        from ocpp.cp.client import CPClient
        client = CPClient("TEST_CP_001")
        print("✅ Client creation: PASSED")
    except Exception as e:
        print(f"❌ Client creation: FAILED - {e}")
    
    print("\\nBasic tests completed!")
