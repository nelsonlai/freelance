#!/usr/bin/env python3
"""
Basic UDP Echo Server

A simple UDP server that echoes back whatever it receives.
Note: UDP is connectionless, so no accept() or connect() calls.
"""

import socket

# Configuration
HOST = 'localhost'
PORT = 8080

def main():
    # Create UDP socket
    server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    
    try:
        # Bind socket to address
        server.bind((HOST, PORT))
        print(f"UDP server listening on {HOST}:{PORT}...")
        print("Press Ctrl+C to stop")
        
        while True:
            # Receive datagram (returns data and client address)
            data, client_address = server.recvfrom(1024)
            
            if data:
                message = data.decode('utf-8')
                print(f"Received from {client_address}: {message}")
                
                # Echo back to client (sendto requires address)
                response = f"Echo: {message}".encode('utf-8')
                server.sendto(response, client_address)
                print(f"Echoed to {client_address}")
    
    except KeyboardInterrupt:
        print("\n\nShutting down server...")
    
    except Exception as e:
        print(f"Server error: {e}")
    
    finally:
        # Close socket
        server.close()
        print("Server closed")

if __name__ == '__main__':
    main()

