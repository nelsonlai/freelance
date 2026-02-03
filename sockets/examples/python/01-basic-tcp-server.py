#!/usr/bin/env python3
"""
Basic TCP Echo Server

A simple TCP server that echoes back whatever it receives.
This is the simplest possible TCP server implementation.
"""

import socket

# Configuration
HOST = 'localhost'
PORT = 8080

def main():
    # Create TCP socket
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    # Allow reuse of address (helpful for testing)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    try:
        # Bind socket to address
        server.bind((HOST, PORT))
        print(f"Server bound to {HOST}:{PORT}")
        
        # Listen for connections (max 5 pending)
        server.listen(5)
        print(f"Server listening on {HOST}:{PORT}...")
        print("Press Ctrl+C to stop")
        
        while True:
            # Accept incoming connection (blocks until client connects)
            client, address = server.accept()
            print(f"\nConnection from {address}")
            
            try:
                # Receive data from client
                data = client.recv(1024)  # Receive up to 1024 bytes
                
                if data:
                    message = data.decode('utf-8')
                    print(f"Received: {message}")
                    
                    # Echo data back to client
                    client.sendall(data)
                    print(f"Echoed: {message}")
                else:
                    print("Client closed connection")
            
            except Exception as e:
                print(f"Error handling client: {e}")
            
            finally:
                # Close client connection
                client.close()
                print(f"Connection to {address} closed")
    
    except KeyboardInterrupt:
        print("\n\nShutting down server...")
    
    except Exception as e:
        print(f"Server error: {e}")
    
    finally:
        # Close server socket
        server.close()
        print("Server closed")

if __name__ == '__main__':
    main()

