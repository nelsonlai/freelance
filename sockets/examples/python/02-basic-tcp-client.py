#!/usr/bin/env python3
"""
Basic TCP Client

A simple TCP client that connects to a server and sends a message.
"""

import socket
import sys

# Configuration
HOST = 'localhost'
PORT = 8080

def main():
    # Create TCP socket
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    try:
        # Connect to server
        print(f"Connecting to {HOST}:{PORT}...")
        client.connect((HOST, PORT))
        print("Connected!")
        
        # Send message
        message = "Hello, Server!"
        print(f"Sending: {message}")
        client.sendall(message.encode('utf-8'))
        
        # Receive response
        response = client.recv(1024)
        if response:
            print(f"Received: {response.decode('utf-8')}")
        else:
            print("Server closed connection")
    
    except ConnectionRefusedError:
        print(f"Error: Connection refused.")
        print("Make sure the server is running on {}:{}".format(HOST, PORT))
        sys.exit(1)
    
    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)
    
    finally:
        # Close connection
        client.close()
        print("Connection closed")

if __name__ == '__main__':
    main()

