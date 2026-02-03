import asyncio
import logging
from datetime import datetime, timezone

try:
    import websockets
except ModuleNotFoundError:
    print("This example relies on the 'websockets' package.")
    print("Please install it by running: ")
    print()
    print(" $ pip install websockets")
    import sys

    sys.exit(1)

from ocpp.routing import on
from ocpp.v21 import ChargePoint as cp
from ocpp.v21 import call_result
from ocpp.v21.enums import Action, DataTransferStatusEnumType

logging.basicConfig(level=logging.INFO)


class ChargePoint(cp):
    @on(Action.boot_notification)
    def on_boot_notification(self, charging_station, reason, **kwargs):
        return call_result.BootNotification(
            current_time=datetime.now(timezone.utc).isoformat(),
            interval=10,
            status="Accepted",
        )

    @on(Action.heartbeat)
    def on_heartbeat(self):
        print("Got a Heartbeat!")
        return call_result.Heartbeat(
            current_time=datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%S") + "Z"
        )

    @on(Action.data_transfer)
    def on_data_transfer(self, vendor_id, data, **kwargs):
        print(f"=== RFID DATA RECEIVED FROM CLIENT ===")
        print(f"Charge Point ID: {self.id}")
        print(f"Vendor ID: {vendor_id}")
        print(f"RFID UID: {data}")
        print(f"Timestamp: {datetime.now(timezone.utc).isoformat()}")
        print(f"=====================================")
        card_dict = {
            "7A4C91E2F5B3": "Alice Wong",
            "D19F73C5A28B": "Brian Johnson",
            "3F7A1E9C84D2": "Chloe Zhang",
            "9B62C4D7A1E8": "David Patel",
            "5E1C8A3F9D47": "Emma Rodriguez",
            "B2D47F8C31E9": "Frank Nguyen",
            "4A9F2C7E5D13": "Grace Thompson",
            "E1B47D9C3A52": "Henry Lee",
            "8C2F5B7A1E49": "Isabella Martinez",
            "F73D29E1C84B": "Jason Kim"
        }
        respond_message = ""
        if data in card_dict:
            respond_message = card_dict[data]
            print(f"RFID UID: {data}")
        else:
            print(f"RFID UID: {data} is not in the card dictionary")
            respond_message = "Welcome to the system. Please contact the administrator."
            print(f"RFID UID: {data}")
        return call_result.DataTransfer(
            status=DataTransferStatusEnumType.accepted,
            data=respond_message
        )


async def on_connect(websocket):
    """For every new charge point that connects, create a ChargePoint
    instance and start listening for messages.
    """
    try:
        requested_protocols = websocket.request.headers["Sec-WebSocket-Protocol"]
    except KeyError:
        logging.error("Client hasn't requested any Subprotocol. Closing Connection")
        return await websocket.close()
    if websocket.subprotocol:
        logging.info("Protocols Matched: %s", websocket.subprotocol)
    else:
        # In the websockets lib if no subprotocols are supported by the
        # client and the server, it proceeds without a subprotocol,
        # so we have to manually close the connection.
        logging.warning(
            "Protocols Mismatched | Expected Subprotocols: %s,"
            " but client supports %s | Closing connection",
            websocket.available_subprotocols,
            requested_protocols,
        )
        return await websocket.close()

    charge_point_id = websocket.request.path.strip("/")
    charge_point = ChargePoint(charge_point_id, websocket)

    await charge_point.start()


async def main():
    #  deepcode ignore BindToAllNetworkInterfaces: <Example Purposes>
    server = await websockets.serve(
        on_connect, "0.0.0.0", 9000, subprotocols=["ocpp2.1"]
    )

    logging.info("Server Started listening to new connections...")
    await server.wait_closed()


if __name__ == "__main__":
    # asyncio.run() is used when running this example with Python >= 3.7v
    asyncio.run(main())
