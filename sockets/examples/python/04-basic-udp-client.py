#!/usr/bin/env python3
"""
Basic UDP Client

A simple UDP client that sends a message to a server.
Note: UDP is connectionless, so no connect() call needed.
"""

import socket
import sys

# Configuration
HOST = 'localhost'
PORT = 8080

def main():
    # Create UDP socket
    client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    
    try:
        # Send message (sendto requires server address)
        message = "Hello, UDP Server!"
        print(f"Sending to {HOST}:{PORT}: {message}")
        client.sendto(message.encode('utf-8'), (HOST, PORT))
        
        # Receive response (recvfrom returns data and server address)
        data, server_address = client.recvfrom(1024)
        
        if data:
            response = data.decode('utf-8')
            print(f"Received from {server_address}: {response}")
        else:
            print("No response received")
    
    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)
    
    finally:
        # Close socket
        client.close()
        print("Socket closed")

if __name__ == '__main__':
    main()

