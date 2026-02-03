# Exercise 1: Echo Server

## Objective

Build a TCP echo server that receives messages from clients and sends them back.

## Requirements

1. Create a TCP server that listens on `localhost:8080`
2. Accept client connections
3. Receive messages from clients
4. Echo (send back) the received message
5. Handle multiple clients (use threading)
6. Implement proper error handling

## Basic Implementation (Single Client)

### Starter Code

```python
import socket

def echo_server():
    # TODO: Create TCP socket
    # TODO: Bind to localhost:8080
    # TODO: Listen for connections
    # TODO: Accept connection
    # TODO: Receive and echo messages
    # TODO: Close connections
    pass

if __name__ == '__main__':
    echo_server()
```

### Expected Behavior

**Server side:**
```
Server listening on localhost:8080...
Connection from ('127.0.0.1', 54321)
Received: Hello, Server!
Echoed: Hello, Server!
Connection closed
```

**Client side:**
```
Connected to server
Sent: Hello, Server!
Received: Hello, Server!
```

## Intermediate Implementation (Multiple Clients)

Extend the basic server to handle multiple clients simultaneously using threading.

### Requirements

- Use `threading.Thread` for each client
- Server should continue accepting new connections while handling existing ones
- Each client should be handled independently

## Advanced Implementation (Enhanced Echo Server)

Add the following features:

1. **Connection logging**: Log all connections with timestamp
2. **Message statistics**: Count total messages received
3. **Command support**: 
   - Send "QUIT" to disconnect
   - Send "STATS" to get message count
   - Send "TIME" to get server time
4. **Timeout handling**: Disconnect idle clients after 30 seconds
5. **Graceful shutdown**: Handle Ctrl+C and close all connections

## Testing

### Test 1: Basic Echo

```bash
# Terminal 1: Start server
python echo_server.py

# Terminal 2: Test with telnet
telnet localhost 8080
# Type: Hello, Server!
# Should receive: Hello, Server!
```

### Test 2: Multiple Clients

```bash
# Terminal 1: Start server
python echo_server.py

# Terminal 2: Client 1
telnet localhost 8080

# Terminal 3: Client 2
telnet localhost 8080

# Both should work simultaneously
```

### Test 3: Python Client

```python
import socket

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('localhost', 8080))

messages = ["Hello", "World", "Test"]
for msg in messages:
    client.sendall(msg.encode())
    response = client.recv(1024)
    print(f"Sent: {msg}, Received: {response.decode()}")

client.close()
```

## Solution Hints

<details>
<summary>Click for hints</summary>

### Creating and Binding Socket
```python
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server.bind(('localhost', 8080))
server.listen(5)
```

### Handling Client
```python
while True:
    data = client.recv(1024)
    if not data:
        break
    client.sendall(data)
```

### Threading
```python
import threading

def handle_client(client, address):
    # Handle client here
    pass

while True:
    client, addr = server.accept()
    thread = threading.Thread(target=handle_client, args=(client, addr))
    thread.start()
```

</details>

## Success Criteria

- ✅ Server accepts connections
- ✅ Messages are echoed correctly
- ✅ Multiple clients can connect simultaneously
- ✅ Proper error handling (connection closed, etc.)
- ✅ Server can be stopped gracefully (Ctrl+C)

## Bonus Challenges

1. Add support for UDP echo server
2. Implement message history (last N messages)
3. Add client authentication (simple password)
4. Implement rate limiting (max messages per second)
5. Add support for binary data (images, files)

## Next Steps

After completing this exercise, you should understand:
- TCP server creation and binding
- Accepting client connections
- Sending and receiving data
- Handling multiple clients
- Basic error handling

Proceed to Exercise 2: Chat Application to build on these skills.

