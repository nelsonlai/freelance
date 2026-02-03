# OCPP 2.1 Implementation

This is a comprehensive implementation of the Open Charge Point Protocol (OCPP) 2.1 specification, including both CSMS (Central System Management System) server and CP (Charge Point) client functionality.

## Project Structure

```
ocpp_implementation/
├── README.md
├── requirements.txt
├── config/
│   ├── __init__.py
│   ├── settings.py
│   └── logging_config.py
├── ocpp/
│   ├── __init__.py
│   ├── base/
│   │   ├── __init__.py
│   │   ├── message_types.py
│   │   ├── enums.py
│   │   └── exceptions.py
│   ├── schemas/
│   │   ├── __init__.py
│   │   ├── request_schemas.py
│   │   └── response_schemas.py
│   ├── csms/
│   │   ├── __init__.py
│   │   ├── server.py
│   │   ├── handlers/
│   │   │   ├── __init__.py
│   │   │   ├── authorization.py
│   │   │   ├── charging.py
│   │   │   ├── configuration.py
│   │   │   ├── diagnostics.py
│   │   │   ├── display.py
│   │   │   ├── firmware.py
│   │   │   ├── local_auth_list.py
│   │   │   ├── monitoring.py
│   │   │   ├── provisioning.py
│   │   │   ├── reporting.py
│   │   │   ├── reservation.py
│   │   │   ├── security.py
│   │   │   ├── smart_charging.py
│   │   │   ├── tariff_and_cost.py
│   │   │   └── transactions.py
│   │   └── models/
│   │       ├── __init__.py
│   │       ├── charging_station.py
│   │       ├── transaction.py
│   │       └── user.py
│   ├── cp/
│   │   ├── __init__.py
│   │   ├── client.py
│   │   ├── handlers/
│   │   │   ├── __init__.py
│   │   │   ├── authorization.py
│   │   │   ├── charging.py
│   │   │   ├── configuration.py
│   │   │   ├── diagnostics.py
│   │   │   ├── display.py
│   │   │   ├── firmware.py
│   │   │   ├── local_auth_list.py
│   │   │   ├── monitoring.py
│   │   │   ├── provisioning.py
│   │   │   ├── reporting.py
│   │   │   ├── reservation.py
│   │   │   ├── security.py
│   │   │   ├── smart_charging.py
│   │   │   ├── tariff_and_cost.py
│   │   │   └── transactions.py
│   │   └── models/
│   │       ├── __init__.py
│   │       ├── charging_station.py
│   │       ├── transaction.py
│   │       └── user.py
├── examples/
│   ├── __init__.py
│   ├── csms_server_example.py
│   ├── cp_client_example.py
│   └── integration_test.py
└── tests/
    ├── __init__.py
    ├── test_csms.py
    ├── test_cp.py
    └── test_integration.py
```

## Features

### CSMS (Central System Management System) Server
- WebSocket server for handling CP connections
- Complete message handling for all OCPP 2.1 message types
- Database integration for storing charging station data
- User authentication and authorization
- Transaction management
- Smart charging and load balancing
- Monitoring and diagnostics
- Firmware management
- Tariff and cost management

### CP (Charge Point) Client
- WebSocket client for connecting to CSMS
- Complete message handling for all OCPP 2.1 message types
- Local state management
- Transaction handling
- Meter value reporting
- Status notifications
- Security event reporting
- Firmware update handling

## Installation

```bash
pip install -r requirements.txt
```

## Usage

### Running CSMS Server
```python
from examples.csms_server_example import run_csms_server
run_csms_server()
```

### Running CP Client
```python
from examples.cp_client_example import run_cp_client
run_cp_client()
```

## OCPP 2.1 Compliance

This implementation follows the OCPP 2.1 specification and includes:
- All required message types
- Proper error handling
- Security features
- Extensibility for custom implementations
- Comprehensive logging and monitoring

