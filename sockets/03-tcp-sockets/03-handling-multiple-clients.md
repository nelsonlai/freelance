# Handling Multiple Clients

A basic TCP server handles only one client at a time. Real-world servers need to handle multiple clients concurrently. This module covers different approaches.

## Problem with Sequential Servers

```python
# Sequential server - only handles one client at a time
while True:
    client, addr = server.accept()
    handle_client(client, addr)  # Blocks here!
    # Next client must wait
```

**Issues:**
- Only one client served at a time
- Other clients wait in queue
- Poor user experience
- Wastes resources

## Solution Approaches

1. **Threading**: One thread per client
2. **Multiprocessing**: One process per client
3. **Async/Await**: Event-driven with coroutines
4. **Select/Poll/Epoll**: I/O multiplexing

## Approach 1: Threading

### Basic Threading Server

```python
import socket
import threading

def handle_client(client, address):
    """Handle communication with a single client."""
    print(f"Thread {threading.current_thread().name} handling {address}")
    
    try:
        while True:
            data = client.recv(1024)
            if not data:
                break
            
            print(f"Received from {address}: {data.decode()}")
            client.sendall(data)  # Echo back
    
    except Exception as e:
        print(f"Error with {address}: {e}")
    finally:
        client.close()
        print(f"Connection to {address} closed")

def threaded_server(host='localhost', port=8080):
    """TCP server that handles multiple clients using threads."""
    
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((host, port))
    server.listen(5)
    
    print(f"Threaded server listening on {host}:{port}")
    
    try:
        while True:
            client, address = server.accept()
            print(f"New connection from {address}")
            
            # Create thread for this client
            thread = threading.Thread(
                target=handle_client,
                args=(client, address),
                daemon=True  # Dies when main program exits
            )
            thread.start()
            # Main loop continues immediately
    
    except KeyboardInterrupt:
        print("\nShutting down server...")
    finally:
        server.close()

if __name__ == '__main__':
    threaded_server()
```

### Thread Pool Server (Better Resource Management)

```python
import socket
import threading
from concurrent.futures import ThreadPoolExecutor

def handle_client(client, address):
    """Handle communication with a single client."""
    try:
        while True:
            data = client.recv(1024)
            if not data:
                break
            
            client.sendall(data.upper())
    
    except Exception as e:
        print(f"Error with {address}: {e}")
    finally:
        client.close()

def thread_pool_server(host='localhost', port=8080, max_workers=10):
    """TCP server using thread pool for client handling."""
    
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((host, port))
    server.listen(5)
    
    print(f"Thread pool server listening on {host}:{port} (max {max_workers} workers)")
    
    # Create thread pool
    with ThreadPoolExecutor(max_workers=max_workers) as executor:
        try:
            while True:
                client, address = server.accept()
                print(f"New connection from {address}")
                
                # Submit to thread pool
                executor.submit(handle_client, client, address)
        
        except KeyboardInterrupt:
            print("\nShutting down server...")
        finally:
            server.close()

if __name__ == '__main__':
    thread_pool_server()
```

**Pros:**
- Simple to implement
- Good for I/O-bound operations
- Works well with blocking operations

**Cons:**
- Thread overhead (memory, context switching)
- Limited scalability (thread limit)
- GIL in Python limits CPU-bound operations

## Approach 2: Multiprocessing

```python
import socket
import multiprocessing

def handle_client(client, address):
    """Handle communication with a single client."""
    try:
        while True:
            data = client.recv(1024)
            if not data:
                break
            
            client.sendall(data.upper())
    
    except Exception as e:
        print(f"Error with {address}: {e}")
    finally:
        client.close()

def process_based_server(host='localhost', port=8080):
    """TCP server using separate processes for each client."""
    
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((host, port))
    server.listen(5)
    
    print(f"Process-based server listening on {host}:{port}")
    
    try:
        while True:
            client, address = server.accept()
            print(f"New connection from {address}")
            
            # Create process for this client
            process = multiprocessing.Process(
                target=handle_client,
                args=(client, address)
            )
            process.daemon = True
            process.start()
            
            # Close client in parent (child has its own copy)
            client.close()
    
    except KeyboardInterrupt:
        print("\nShutting down server...")
    finally:
        server.close()

if __name__ == '__main__':
    multiprocessing.freeze_support()
    process_based_server()
```

**Pros:**
- True parallelism (bypasses GIL in Python)
- Process isolation (crash doesn't affect others)
- Good for CPU-bound operations

**Cons:**
- Higher overhead (process creation)
- More memory usage
- Slower than threading for I/O-bound

## Approach 3: Async/Await (asyncio)

```python
import asyncio

async def handle_client(reader, writer):
    """Handle communication with a single client."""
    address = writer.get_extra_info('peername')
    print(f"New connection from {address}")
    
    try:
        while True:
            data = await reader.read(1024)
            if not data:
                break
            
            message = data.decode()
            print(f"Received from {address}: {message}")
            
            # Echo back
            writer.write(data)
            await writer.drain()  # Wait until data is sent
    
    except Exception as e:
        print(f"Error with {address}: {e}")
    finally:
        writer.close()
        await writer.wait_closed()
        print(f"Connection to {address} closed")

async def async_server(host='localhost', port=8080):
    """Async TCP server using asyncio."""
    
    server = await asyncio.start_server(
        handle_client,
        host,
        port
    )
    
    print(f"Async server listening on {host}:{port}")
    
    async with server:
        await server.serve_forever()

if __name__ == '__main__':
    try:
        asyncio.run(async_server())
    except KeyboardInterrupt:
        print("\nShutting down server...")
```

**Pros:**
- Very efficient for many concurrent connections
- Low memory overhead
- Single-threaded (no GIL issues)
- Excellent for I/O-bound operations

**Cons:**
- More complex code
- Requires async-compatible libraries
- Learning curve

## Approach 4: Select/Poll (I/O Multiplexing)

### Using select()

```python
import socket
import select

def select_server(host='localhost', port=8080):
    """TCP server using select() for I/O multiplexing."""
    
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((host, port))
    server.listen(5)
    server.setblocking(False)  # Non-blocking mode
    
    # List of sockets to monitor
    inputs = [server]
    outputs = []
    message_queues = {}
    
    print(f"Select-based server listening on {host}:{port}")
    
    while inputs:
        # Wait for activity
        readable, writable, exceptional = select.select(
            inputs, outputs, inputs, 0.1  # 100ms timeout
        )
        
        # Handle readable sockets
        for sock in readable:
            if sock is server:
                # New connection
                client, address = server.accept()
                client.setblocking(False)
                inputs.append(client)
                message_queues[client] = []
                print(f"New connection from {address}")
            
            else:
                # Existing client
                data = sock.recv(1024)
                if data:
                    # Add to output queue
                    message_queues[sock].append(data)
                    if sock not in outputs:
                        outputs.append(sock)
                else:
                    # Client disconnected
                    if sock in outputs:
                        outputs.remove(sock)
                    inputs.remove(sock)
                    sock.close()
                    del message_queues[sock]
        
        # Handle writable sockets
        for sock in writable:
            if message_queues[sock]:
                data = message_queues[sock].pop(0)
                sock.sendall(data)
            else:
                outputs.remove(sock)
        
        # Handle exceptional conditions
        for sock in exceptional:
            inputs.remove(sock)
            if sock in outputs:
                outputs.remove(sock)
            sock.close()
            del message_queues[sock]
    
    server.close()

if __name__ == '__main__':
    try:
        select_server()
    except KeyboardInterrupt:
        print("\nShutting down server...")
```

**Pros:**
- Efficient for many connections
- Single-threaded
- Cross-platform (select available everywhere)

**Cons:**
- Complex code
- Limited on some platforms (FD_SETSIZE limit)
- Less efficient than epoll/kqueue on Linux/macOS

## Comparison

| Approach | Scalability | Complexity | Best For |
|----------|-------------|------------|----------|
| Threading | Medium (~100s) | Low | I/O-bound, simple code |
| Multiprocessing | Medium | Medium | CPU-bound, isolation needed |
| Async/Await | High (1000s+) | Medium | I/O-bound, many connections |
| Select/Poll | High | High | Cross-platform, control needed |

## Hybrid Approach

Combine approaches for best results:

```python
import socket
import threading
from concurrent.futures import ThreadPoolExecutor

def handle_client(client, address):
    """Handle communication with a single client."""
    try:
        while True:
            data = client.recv(1024)
            if not data:
                break
            client.sendall(data.upper())
    finally:
        client.close()

def hybrid_server(host='localhost', port=8080):
    """Server using thread pool with reasonable limit."""
    
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((host, port))
    server.listen(10)  # Larger backlog
    
    # Limit thread pool size to prevent resource exhaustion
    max_workers = min(50, (os.cpu_count() or 1) + 4)
    
    with ThreadPoolExecutor(max_workers=max_workers) as executor:
        print(f"Hybrid server listening on {host}:{port} (max {max_workers} workers)")
        
        try:
            while True:
                client, address = server.accept()
                executor.submit(handle_client, client, address)
        except KeyboardInterrupt:
            print("\nShutting down...")
        finally:
            server.close()

if __name__ == '__main__':
    hybrid_server()
```

## Best Practices

1. **Set connection limits** to prevent resource exhaustion
2. **Use timeouts** to prevent hanging connections
3. **Handle exceptions** properly in each client handler
4. **Clean up resources** when clients disconnect
5. **Monitor performance** and adjust approach as needed
6. **Consider load balancing** for very high loads

---

**Key Takeaway**: Multiple approaches exist for handling concurrent clients. Choose based on your needs: threading for simplicity, async for scalability, or select for control.

