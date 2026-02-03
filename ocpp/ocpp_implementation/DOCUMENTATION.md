# OCPP 2.1 Implementation Documentation

## Overview

This is a comprehensive implementation of the Open Charge Point Protocol (OCPP) 2.1 specification, providing both CSMS (Central System Management System) server and CP (Charge Point) client functionality. The implementation is designed for educational purposes with extensive comments and documentation.

## Features

### CSMS (Central System Management System) Server
- **WebSocket Server**: Handles multiple CP connections simultaneously
- **Message Processing**: Complete OCPP 2.1 message handling
- **Connection Management**: Automatic connection monitoring and cleanup
- **Transaction Management**: Track and manage charging transactions
- **Status Monitoring**: Real-time status updates from charging stations
- **Security**: Authentication and authorization support
- **Logging**: Comprehensive logging with structured output
- **Statistics**: Real-time performance monitoring

### CP (Charge Point) Client
- **WebSocket Client**: Connects to CSMS server
- **Boot Process**: Automatic boot notification and authentication
- **Heartbeat**: Periodic heartbeat to maintain connection
- **Status Reporting**: Real-time status notifications
- **Transaction Handling**: Start, stop, and manage transactions
- **Meter Values**: Periodic meter value reporting
- **Data Transfer**: Vendor-specific data exchange
- **Error Handling**: Robust error handling and recovery

## Architecture

### Message Flow
```
CP Client <---> WebSocket <---> CSMS Server
     |                              |
     |                              |
     v                              v
Local State                    Database
Management                     Storage
```

### Key Components

1. **Base Classes** (`ocpp/base/`)
   - Message types and enums
   - Exception handling
   - Common data structures

2. **CSMS Server** (`ocpp/csms/`)
   - WebSocket server implementation
   - Message handlers
   - Connection management
   - Business logic

3. **CP Client** (`ocpp/cp/`)
   - WebSocket client implementation
   - Message handlers
   - State management
   - Event simulation

4. **Configuration** (`config/`)
   - Settings management
   - Logging configuration
   - Environment variables

5. **Examples** (`examples/`)
   - Server example
   - Client example
   - Integration tests

## Installation

### Prerequisites
- Python 3.8+
- pip package manager

### Dependencies
```bash
pip install -r requirements.txt
```

### Required Packages
- `websockets`: WebSocket communication
- `pydantic`: Data validation
- `asyncio`: Asynchronous programming
- `jsonschema`: JSON schema validation
- `cryptography`: Security features
- `aiofiles`: Async file operations
- `aiosqlite`: Async database operations

## Usage

### Running CSMS Server

```python
from examples.csms_server_example import CSMSServerExample

async def main():
    server = CSMSServerExample()
    await server.start()

asyncio.run(main())
```

### Running CP Client

```python
from examples.cp_client_example import CPClientExample

async def main():
    client = CPClientExample()
    await client.start()

asyncio.run(main())
```

### Configuration

The implementation uses environment variables and configuration files for settings:

```python
# Environment variables
export CSMS_HOST=0.0.0.0
export CSMS_PORT=9000
export CP_CSMS_URL=ws://localhost:9000
export LOG_LEVEL=INFO
```

### Customization

#### Adding Custom Message Handlers

```python
class CustomCSMSServer(CSMSServer):
    async def _handle_custom_action(self, payload):
        # Custom handler implementation
        return {"status": "Accepted"}
```

#### Extending Message Types

```python
class CustomMessageType(OCPPBaseMessage):
    custom_field: str
    custom_data: Optional[Dict[str, Any]]
```

## OCPP 2.1 Compliance

### Supported Message Types

#### Core Profile
- `Authorize`: User authorization
- `BootNotification`: Station boot process
- `Heartbeat`: Connection keep-alive
- `StatusNotification`: Status updates
- `TransactionEvent`: Transaction management
- `MeterValues`: Energy measurement
- `DataTransfer`: Vendor-specific data

#### Security Profile
- `SecurityEventNotification`: Security events
- `SignCertificate`: Certificate signing
- `CertificateSigned`: Certificate installation
- `GetInstalledCertificateIds`: Certificate management
- `DeleteCertificate`: Certificate removal
- `InstallCertificate`: Certificate installation
- `GetCertificateStatus`: Certificate validation
- `GetCertificateChainStatus`: Certificate chain validation

#### Smart Charging Profile
- `SetChargingProfile`: Charging profile management
- `GetChargingProfiles`: Profile retrieval
- `ClearChargingProfile`: Profile removal
- `ReportChargingProfiles`: Profile reporting

#### Tariff and Cost Profile
- `GetTariffs`: Tariff information
- `SetDefaultTariff`: Default tariff setting
- `ClearTariffs`: Tariff removal
- `CostUpdated`: Cost updates
- `ChangeTransactionTariff`: Tariff changes

#### Display Messages Profile
- `SetDisplayMessage`: Message display
- `GetDisplayMessages`: Message retrieval
- `ClearDisplayMessage`: Message removal
- `NotifyDisplayMessages`: Message notifications

#### Monitoring Profile
- `SetVariableMonitoring`: Variable monitoring
- `ClearVariableMonitoring`: Monitor removal
- `SetMonitoringBase`: Monitoring base
- `SetMonitoringLevel`: Monitoring level
- `GetMonitoringReport`: Report generation
- `NotifyMonitoringReport`: Report notifications

#### Reporting Profile
- `GetReport`: Report generation
- `NotifyReport`: Report notifications
- `GetBaseReport`: Base report generation

#### Additional Features
- `TriggerMessage`: Message triggering
- `ChangeAvailability`: Availability changes
- `UnlockConnector`: Connector unlocking
- `Reset`: Station reset
- `ClearCache`: Cache clearing
- `UpdateFirmware`: Firmware updates
- `SendLocalList`: Local authorization list
- `GetLocalListVersion`: List version
- `ReserveNow`: Reservation management
- `CancelReservation`: Reservation cancellation
- `ReservationStatusUpdate`: Reservation status
- `GetLog`: Log retrieval
- `Get15118EVCertificate`: ISO 15118 certificates

### Error Handling

The implementation includes comprehensive error handling:

```python
try:
    response = await client.send_message(message)
except OCPPTimeoutError:
    # Handle timeout
except OCPPConnectionError:
    # Handle connection issues
except OCPPValidationError:
    # Handle validation errors
```

### Security Features

- **TLS Support**: Encrypted communication
- **Certificate Management**: X.509 certificate handling
- **Authentication**: User authentication
- **Authorization**: Access control
- **Security Events**: Security monitoring

## Testing

### Unit Tests

```bash
pytest tests/test_csms.py
pytest tests/test_cp.py
```

### Integration Tests

```bash
pytest tests/test_integration.py
```

### Manual Testing

1. Start CSMS server:
```bash
python examples/csms_server_example.py
```

2. Start CP client:
```bash
python examples/cp_client_example.py
```

3. Run integration test:
```bash
python examples/integration_test.py
```

## Performance Considerations

### Scalability
- **Connection Pooling**: Efficient connection management
- **Async Operations**: Non-blocking I/O
- **Message Queuing**: Buffered message processing
- **Resource Management**: Automatic cleanup

### Monitoring
- **Statistics**: Real-time performance metrics
- **Logging**: Structured logging with context
- **Health Checks**: Connection health monitoring
- **Error Tracking**: Comprehensive error reporting

## Troubleshooting

### Common Issues

1. **Connection Failures**
   - Check network connectivity
   - Verify WebSocket URL
   - Check firewall settings

2. **Authentication Errors**
   - Verify station credentials
   - Check certificate validity
   - Review security settings

3. **Message Errors**
   - Validate message format
   - Check required fields
   - Review error logs

### Debugging

Enable debug logging:
```python
import logging
logging.getLogger("ocpp").setLevel(logging.DEBUG)
```

### Log Analysis

The implementation provides structured logging:
```json
{
  "timestamp": "2024-01-01T12:00:00Z",
  "level": "INFO",
  "logger": "ocpp.csms.server",
  "message": "Message received",
  "ocpp_message_type": "AuthorizeRequest",
  "ocpp_direction": "request",
  "charging_station_id": "CP001"
}
```

## Contributing

### Code Style
- Follow PEP 8 guidelines
- Use type hints
- Add comprehensive comments
- Include docstrings

### Testing
- Write unit tests for new features
- Update integration tests
- Ensure all tests pass

### Documentation
- Update README.md
- Add code comments
- Update API documentation

## License

This implementation is provided for educational purposes. Please refer to the OCPP 2.1 specification for official licensing terms.

## References

- [OCPP 2.1 Specification](https://www.openchargealliance.org/protocols/ocpp-2-1/)
- [OCPP 2.1 JSON Schema](https://github.com/OpenChargeAlliance/OCPP-2.1-JSON-Schema)
- [WebSocket Protocol](https://tools.ietf.org/html/rfc6455)
- [JSON Schema](https://json-schema.org/)

## Support

For questions and support:
- Review the documentation
- Check the examples
- Run the integration tests
- Examine the logs

## Future Enhancements

- **Database Integration**: Persistent storage
- **REST API**: HTTP interface
- **MQTT Support**: MQTT transport
- **Load Balancing**: Multiple server instances
- **Metrics**: Prometheus integration
- **Dashboard**: Web-based monitoring
- **Mobile App**: Mobile interface
- **Cloud Integration**: Cloud deployment
