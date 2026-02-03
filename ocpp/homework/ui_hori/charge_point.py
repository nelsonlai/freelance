import asyncio
import logging
import time
import sys
import os

# Add parent directory to path to import ocpp module
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

try:
    import websockets
except ModuleNotFoundError:
    print("This example relies on the 'websockets' package.")
    print("Please install it by running: ")
    print()
    print(" $ pip install websockets")
    sys.exit(1)

from ocpp.v21 import ChargePoint as cp
from ocpp.v21 import call
from ocpp.v21.datatypes import ChargingStationType

logging.basicConfig(level=logging.INFO)


class ChargePoint(cp):
    async def send_heartbeat(self, interval):
        request = call.Heartbeat()
        while True:
            await self.call(request)
            await asyncio.sleep(interval)

    async def send_boot_notification(self):
        print("YESSSS")
        request = call.BootNotification(
            charging_station=ChargingStationType(
                model="Wallbox XYZ", vendor_name="anewone"
            ),
            reason="PowerUp",
        )
        response = await self.call(request)

        if response.status == "Accepted":
            print("Connected to central system.")
            await self.send_heartbeat(response.interval)

    async def send_rfid_data(self, rfid_uid):
        """Send RFID data to the central system using DataTransfer message"""
        try:
            request = call.DataTransfer(
                vendor_id="ChargingStation",
                data=rfid_uid
            )
            response = await self.call(request)
            print(f"RFID data sent to server: {rfid_uid}")
            print(f"Server response: {response.status}")
            print(f"Server data: {response.data}")
            return response
        except Exception as e:
            print(f"Error sending RFID data: {e}")
            return None


async def main():
    async with websockets.connect(
        "ws://localhost:9000/CP_1", subprotocols=["ocpp2.1"]
    ) as ws:
        print("WebSocket connection established.")
        charge_point = ChargePoint("CP_1", ws)
        await asyncio.gather(
            charge_point.start(), charge_point.send_boot_notification()
        )

if __name__ == "__main__":
    # asyncio.run() is used when running this example with Python >= 3.7v
    asyncio.run(main())