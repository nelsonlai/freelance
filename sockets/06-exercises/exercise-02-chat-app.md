# Exercise 2: Chat Application

## Objective

Build a multi-user chat server where clients can send messages that are broadcast to all connected clients.

## Requirements

1. **TCP Server** that accepts multiple client connections
2. **Message Broadcasting**: When one client sends a message, all other clients receive it
3. **Client Identification**: Each client should have a username
4. **Connection Management**: Handle clients joining and leaving
5. **Message Format**: Format messages with username and timestamp

## Basic Implementation

### Server Features

- Accept multiple client connections
- Maintain list of connected clients
- Broadcast messages to all clients
- Handle client disconnections

### Message Protocol

```
CLIENT → SERVER: "JOIN:username"
SERVER → CLIENT: "JOINED:username"
SERVER → ALL: "USER_JOINED:username"

CLIENT → SERVER: "MESSAGE:Hello everyone"
SERVER → ALL: "USERNAME [TIME]: Hello everyone"

CLIENT → SERVER: "QUIT"
SERVER → ALL: "USER_LEFT:username"
```

## Starter Code Structure

### Server Structure

```python
import socket
import threading
from datetime import datetime

class ChatServer:
    def __init__(self, host='localhost', port=8080):
        self.host = host
        self.port = port
        self.clients = []  # List of (socket, username, address)
        self.server = None
    
    def start(self):
        # TODO: Create socket, bind, listen
        pass
    
    def broadcast(self, message, exclude_client=None):
        # TODO: Send message to all clients except exclude_client
        pass
    
    def handle_client(self, client, address):
        # TODO: Handle client connection, messages, disconnection
        pass

if __name__ == '__main__':
    server = ChatServer()
    server.start()
```

### Client Structure

```python
import socket
import threading

class ChatClient:
    def __init__(self, host='localhost', port=8080):
        self.host = host
        self.port = port
        self.client = None
        self.username = None
    
    def connect(self, username):
        # TODO: Connect to server and send JOIN message
        pass
    
    def send_message(self, message):
        # TODO: Send message to server
        pass
    
    def receive_messages(self):
        # TODO: Continuously receive and display messages
        pass
    
    def start(self):
        # TODO: Start receiving thread and input loop
        pass

if __name__ == '__main__':
    username = input("Enter username: ")
    client = ChatClient()
    client.connect(username)
    client.start()
```

## Implementation Steps

### Step 1: Basic Server (Single Message)

1. Create server that accepts connections
2. Store connected clients
3. When client sends message, broadcast to all

### Step 2: Add Usernames

1. Client sends username on connection
2. Server stores username with socket
3. Include username in broadcast messages

### Step 3: Handle Disconnections

1. Detect when client disconnects
2. Remove from clients list
3. Notify other clients

### Step 4: Add Timestamps

1. Include timestamp in messages
2. Format: "Username [HH:MM:SS]: Message"

## Expected Behavior

### Server Output
```
Chat server started on localhost:8080
Client connected from ('127.0.0.1', 54321)
User 'Alice' joined
User 'Bob' joined
Broadcasting message from Alice to 2 clients
User 'Alice' disconnected
```

### Client Output
```
Connected to chat server
Enter username: Alice
Joined as: Alice
> Hello everyone!
Alice [14:30:15]: Hello everyone!
Bob [14:30:20]: Hi Alice!
> quit
Disconnected
```

## Advanced Features

### Feature 1: Private Messages

```
Protocol:
CLIENT → SERVER: "PRIVATE:username:message"
SERVER → TARGET: "PRIVATE:from_username:message"
```

### Feature 2: Room/Channel Support

```
CLIENT → SERVER: "JOIN_ROOM:roomname"
SERVER → CLIENT: "JOINED_ROOM:roomname"
# Messages only broadcast to same room
```

### Feature 3: User List

```
CLIENT → SERVER: "LIST_USERS"
SERVER → CLIENT: "USERS:Alice,Bob,Charlie"
```

### Feature 4: Message History

- Store last N messages
- Send to new clients when they join

## Testing

### Test 1: Multiple Clients

```bash
# Terminal 1: Start server
python chat_server.py

# Terminal 2: Client 1
python chat_client.py
# Enter username: Alice

# Terminal 3: Client 2
python chat_client.py
# Enter username: Bob

# Type messages in each terminal
```

### Test 2: Disconnection

```bash
# Connect multiple clients
# Disconnect one client (Ctrl+C)
# Verify other clients are notified
```

## Solution Hints

<details>
<summary>Thread-safe client list</summary>

```python
import threading

class ChatServer:
    def __init__(self):
        self.clients = []
        self.lock = threading.Lock()
    
    def add_client(self, client, username, address):
        with self.lock:
            self.clients.append((client, username, address))
    
    def remove_client(self, client):
        with self.lock:
            self.clients = [c for c in self.clients if c[0] != client]
```

</details>

<details>
<summary>Broadcasting to all clients</summary>

```python
def broadcast(self, message, exclude_client=None):
    with self.lock:
        for client, username, address in self.clients:
            if client != exclude_client:
                try:
                    client.sendall(message.encode())
                except:
                    # Client disconnected
                    self.remove_client(client)
```

</details>

## Success Criteria

- ✅ Server accepts multiple clients
- ✅ Usernames are assigned and displayed
- ✅ Messages broadcast to all clients
- ✅ Disconnections handled gracefully
- ✅ No crashes when clients disconnect unexpectedly
- ✅ Thread-safe operations

## Bonus Challenges

1. Add encryption for messages
2. Implement file sharing
3. Add server-side message logging
4. Create a web-based client interface
5. Implement message moderation features

## Common Issues and Solutions

### Issue: Messages not received by all clients

**Solution**: Ensure broadcast sends to all clients in the list, check for exceptions

### Issue: Server crashes when client disconnects

**Solution**: Wrap send/recv in try-except, remove dead clients

### Issue: Race conditions with client list

**Solution**: Use locks (threading.Lock) for thread-safe operations

---

**Next**: Exercise 3: File Transfer to learn about handling binary data and larger transfers.

