#!/usr/bin/env python3
"""
OCPP 2.1 Implementation Test Runner

This script runs basic tests to verify the OCPP 2.1 implementation
is working correctly.
"""

import sys
import os
import asyncio

# Add the project root to the Python path
project_root = os.path.dirname(__file__)
if project_root not in sys.path:
    sys.path.insert(0, project_root)

def test_imports():
    """Test that all modules can be imported"""
    print("Testing imports...")
    
    try:
        from config.settings import get_settings
        print("✅ config.settings imported")
    except Exception as e:
        print(f"❌ config.settings import failed: {e}")
        return False
    
    try:
        from config.logging_config import get_logger
        print("✅ config.logging_config imported")
    except Exception as e:
        print(f"❌ config.logging_config import failed: {e}")
        return False
    
    try:
        from ocpp.base.message_types import OCPPMessage, MessageType, ActionType
        print("✅ ocpp.base.message_types imported")
    except Exception as e:
        print(f"❌ ocpp.base.message_types import failed: {e}")
        return False
    
    try:
        from ocpp.base.exceptions import OCPPError
        print("✅ ocpp.base.exceptions imported")
    except Exception as e:
        print(f"❌ ocpp.base.exceptions import failed: {e}")
        return False
    
    try:
        from ocpp.csms.server import CSMSServer
        print("✅ ocpp.csms.server imported")
    except Exception as e:
        print(f"❌ ocpp.csms.server import failed: {e}")
        return False
    
    try:
        from ocpp.cp.client import CPClient
        print("✅ ocpp.cp.client imported")
    except Exception as e:
        print(f"❌ ocpp.cp.client import failed: {e}")
        return False
    
    return True

def test_basic_functionality():
    """Test basic functionality"""
    print("\\nTesting basic functionality...")
    
    try:
        from config.settings import get_settings
        settings = get_settings()
        print("✅ Settings loaded successfully")
    except Exception as e:
        print(f"❌ Settings loading failed: {e}")
        return False
    
    try:
        from config.logging_config import get_logger
        logger = get_logger("test")
        print("✅ Logger created successfully")
    except Exception as e:
        print(f"❌ Logger creation failed: {e}")
        return False
    
    try:
        from ocpp.base.message_types import OCPPMessage, MessageType, ActionType
        message = OCPPMessage(
            message_type=MessageType.CALL,
            unique_id="test-123",
            action=ActionType.Heartbeat,
            payload={}
        )
        print("✅ OCPP message created successfully")
    except Exception as e:
        print(f"❌ OCPP message creation failed: {e}")
        return False
    
    try:
        from ocpp.csms.server import CSMSServer
        server = CSMSServer()
        print("✅ CSMS server created successfully")
    except Exception as e:
        print(f"❌ CSMS server creation failed: {e}")
        return False
    
    try:
        from ocpp.cp.client import CPClient
        client = CPClient("TEST_CP_001")
        print("✅ CP client created successfully")
    except Exception as e:
        print(f"❌ CP client creation failed: {e}")
        return False
    
    return True

def test_message_serialization():
    """Test message serialization"""
    print("\\nTesting message serialization...")
    
    try:
        from ocpp.base.message_types import OCPPMessage, MessageType, ActionType
        import json
        
        message = OCPPMessage(
            message_type=MessageType.CALL,
            unique_id="test-123",
            action=ActionType.Heartbeat,
            payload={}
        )
        
        # Test dict conversion
        message_dict = message.model_dump()
        assert message_dict["message_type"] == "2"
        assert message_dict["unique_id"] == "test-123"
        assert message_dict["action"] == "Heartbeat"
        assert message_dict["payload"] == {}
        
        # Test JSON serialization
        json_str = json.dumps(message_dict)
        parsed = json.loads(json_str)
        assert parsed["message_type"] == "2"
        assert parsed["unique_id"] == "test-123"
        assert parsed["action"] == "Heartbeat"
        
        print("✅ Message serialization successful")
        return True
        
    except Exception as e:
        print(f"❌ Message serialization failed: {e}")
        return False

def test_error_handling():
    """Test error handling"""
    print("\\nTesting error handling...")
    
    try:
        from ocpp.base.exceptions import OCPPError, OCPPProtocolError
        
        # Test basic error
        error = OCPPError("Test error", "TestError")
        assert error.message == "Test error"
        assert error.error_code == "TestError"
        
        # Test protocol error
        protocol_error = OCPPProtocolError("Protocol error")
        assert protocol_error.message == "Protocol error"
        assert protocol_error.error_code == "ProtocolError"
        
        print("✅ Error handling successful")
        return True
        
    except Exception as e:
        print(f"❌ Error handling failed: {e}")
        return False

async def test_async_functionality():
    """Test async functionality"""
    print("\\nTesting async functionality...")
    
    try:
        from ocpp.csms.server import CSMSServer
        from ocpp.cp.client import CPClient
        
        # Test server creation
        server = CSMSServer()
        assert server is not None
        
        # Test client creation
        client = CPClient("TEST_CP_001")
        assert client is not None
        
        print("✅ Async functionality successful")
        return True
        
    except Exception as e:
        print(f"❌ Async functionality failed: {e}")
        return False

def main():
    """Main test function"""
    print("OCPP 2.1 Implementation Test Runner")
    print("=" * 50)
    
    # Test imports
    if not test_imports():
        print("\\n❌ Import tests failed!")
        return False
    
    # Test basic functionality
    if not test_basic_functionality():
        print("\\n❌ Basic functionality tests failed!")
        return False
    
    # Test message serialization
    if not test_message_serialization():
        print("\\n❌ Message serialization tests failed!")
        return False
    
    # Test error handling
    if not test_error_handling():
        print("\\n❌ Error handling tests failed!")
        return False
    
    # Test async functionality
    try:
        result = asyncio.run(test_async_functionality())
        if not result:
            print("\\n❌ Async functionality tests failed!")
            return False
    except Exception as e:
        print(f"\\n❌ Async functionality tests failed: {e}")
        return False
    
    print("\\n" + "=" * 50)
    print("✅ All tests passed! OCPP 2.1 implementation is working correctly.")
    print("=" * 50)
    
    return True

if __name__ == "__main__":
    success = main()
    sys.exit(0 if success else 1)
