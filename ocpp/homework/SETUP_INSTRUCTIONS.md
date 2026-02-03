# OCPP Homework - Setup Instructions

## Issues Fixed

### 1. Missing Dependencies
The project was missing several Python packages required for the OCPP implementation and UI:

**Fixed by creating `requirements.txt` with:**
- `websockets>=15.0` - For WebSocket communication
- `jsonschema>=4.23.0` - For OCPP message validation
- `pyscard>=2.0.0` - For RFID card reader functionality
- `PyQt5>=5.15.0` - For the charging station UI

### 2. Module Import Path Issue
The `ui_hori/charge_point.py` file couldn't import the `ocpp` module because it's located in the parent directory.

**Fixed by adding path resolution in `ui_hori/charge_point.py`:**
```python
import sys
import os

# Add parent directory to path to import ocpp module
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
```

## Installation

To set up the environment, run:

```bash
# Activate the virtual environment
source venv/bin/activate

# Install dependencies
pip install -r requirements.txt
```

## Running the Applications

### Central System (OCPP Server)
```bash
python central_system.py
```
This starts the OCPP central system server on `ws://0.0.0.0:9000` supporting OCPP 2.1 protocol.

### Charge Point UI
```bash
cd ui_hori
python charging_ui.py
```
This starts the PyQt5-based charging station user interface.

### Standalone Charge Point
```bash
cd ui_hori
python charge_point.py
```
This runs the charge point client that connects to the central system.

## Architecture

- **ocpp/** - Core OCPP library implementation
  - `messages.py` - OCPP message handling and validation
  - `routing.py` - Message routing decorators
  - `charge_point.py` - Base ChargePoint class
  - `v21/` - OCPP 2.1 specific implementations

- **central_system.py** - OCPP central system server
- **ui_hori/** - Charging station UI application
  - `charging_ui.py` - Main PyQt5 UI application
  - `charge_point.py` - OCPP charge point client

## Verified Functionality

✓ All Python module imports work correctly
✓ Central system can start and listen for connections
✓ Charge point can connect to central system
✓ BootNotification and Heartbeat messages exchange successfully
✓ UI can import all required modules (PyQt5, charge_point, ocpp, smartcard)

