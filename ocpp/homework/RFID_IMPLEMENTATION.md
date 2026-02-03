# RFID Communication Implementation

## Overview
This implementation adds RFID card reading functionality that sends the RFID UID to the OCPP central system server when a card is scanned.

## Changes Made

### 1. **charge_point.py** - Client Side RFID Sending
- Added `send_rfid_data()` method that uses OCPP DataTransfer message
- Sends RFID UID to central system with vendor_id="ChargingStation"
- Includes error handling and response logging

```python
async def send_rfid_data(self, rfid_uid):
    """Send RFID data to the central system using DataTransfer message"""
    request = call.DataTransfer(
        vendor_id="ChargingStation",
        data=rfid_uid
    )
    response = await self.call(request)
    return response
```

### 2. **central_system.py** - Server Side RFID Reception
- Added `on_data_transfer()` handler for DataTransfer messages
- Prints detailed RFID information when received:
  - Charge Point ID
  - Vendor ID
  - RFID UID
  - Timestamp
- Returns accepted status to confirm receipt

```python
@on(Action.data_transfer)
def on_data_transfer(self, vendor_id, data, **kwargs):
    print(f"=== RFID DATA RECEIVED FROM CLIENT ===")
    print(f"Charge Point ID: {self.id}")
    print(f"Vendor ID: {vendor_id}")
    print(f"RFID UID: {data}")
    print(f"Timestamp: {datetime.now(timezone.utc).isoformat()}")
    print(f"=====================================")
    
    return call_result.DataTransfer(
        status=DataTransferStatusEnumType.accepted,
        data="RFID data received successfully"
    )
```

### 3. **charging_ui.py** - UI Integration
- Modified `WorkerThread` to maintain reference to charge point instance
- Updated `rfid_read()` method to send RFID data when card is read
- Added communication between UI thread and charge point thread
- Currently uses fixed RFID UID: `'92345678901234567890'`

Key changes:
- Worker thread keeps reference to charge point instance
- RFID read triggers server communication
- Proper thread communication for async operations

## How It Works

1. **User Flow:**
   - User clicks "CARD" button in step 4
   - UI shows step 5_2: "Place the RFID card close to the card sensing zone"
   - RFID timer starts checking every 1 second

2. **RFID Reading:**
   - When RFID is detected (currently simulated with fixed UID)
   - `rfid_read()` method is called
   - Fixed UID `'92345678901234567890'` is set
   - Timer stops

3. **Server Communication:**
   - RFID UID is sent to central system via `send_rfid_to_server()`
   - Uses OCPP DataTransfer message with vendor_id="ChargingStation"
   - Central system receives and prints RFID data

4. **UI Update:**
   - UI proceeds to step 6 showing "Access granted"
   - Displays the RFID UID on screen

## Testing

### Method 1: Using the UI
1. Start central system: `python central_system.py`
2. Start UI: `cd ui_hori && python charging_ui.py`
3. Navigate to step 4 and click "CARD"
4. Wait for RFID simulation (1 second timer)
5. Check central system console for RFID reception

### Method 2: Using Test Script
1. Start central system: `python central_system.py`
2. Run test: `python test_rfid_communication.py`
3. Check central system console for RFID reception

## Expected Output

**Central System Console:**
```
=== RFID DATA RECEIVED FROM CLIENT ===
Charge Point ID: CP_1
Vendor ID: ChargingStation
RFID UID: 92345678901234567890
Timestamp: 2025-01-XX XX:XX:XX.XXXXXX+00:00
=====================================
```

**Client Console:**
```
RFID read: 92345678901234567890
RFID data sent to server: 92345678901234567890
✓ RFID data sent to server: 92345678901234567890
✓ Server response: accepted
```

## Real RFID Reader Integration

To use with actual RFID reader, uncomment the original RFID code in `rfid_read()`:

```python
r = readers()
if r:
    conn = r[0].createConnection()
    try:
        conn.connect()
        get_uid = [0xFF, 0xCA, 0x00, 0x00, 0x00]
        data, sw1, sw2 = conn.transmit(get_uid)
        
        if sw1 == 0x90:
            uid_hex = toHexString(data)
            uid_dec = f'{int(uid_hex.replace(" ", ""), 16)}'
            self.UID = uid_dec
            # Send to server...
```

## Dependencies
- `websockets` - WebSocket communication
- `jsonschema` - OCPP message validation  
- `pyscard` - RFID card reader functionality
- `PyQt5` - UI framework

All dependencies are included in `requirements.txt`.
