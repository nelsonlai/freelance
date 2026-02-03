# Exercise 3: File Transfer Application

## Objective

Build a file transfer server and client that can reliably transfer files over TCP, handling large files and showing progress.

## Requirements

1. **Server**: Receives files from clients
2. **Client**: Sends files to server
3. **Protocol**: Binary data transfer with metadata
4. **Progress**: Display transfer progress
5. **Reliability**: Verify file integrity
6. **Error Handling**: Handle network errors gracefully

## Protocol Design

### Message Format

```
Header (12 bytes):
- Filename length: 2 bytes (big-endian)
- File size: 8 bytes (big-endian)
- Checksum: 2 bytes (reserved for future)

Body:
- Filename: variable length (UTF-8)
- File data: variable length (binary)
```

### Protocol Flow

```
CLIENT → SERVER: [Header][Filename][File Data]
SERVER → CLIENT: "OK" or "ERROR:message"
```

## Basic Implementation

### Server Structure

```python
import socket
import os

class FileTransferServer:
    def __init__(self, host='localhost', port=8080, save_dir='./received'):
        self.host = host
        self.port = port
        self.save_dir = save_dir
        os.makedirs(save_dir, exist_ok=True)
    
    def start(self):
        # TODO: Create server, accept connections, receive files
        pass
    
    def receive_file(self, client):
        # TODO: Receive header, filename, and file data
        # TODO: Save file to disk
        # TODO: Send confirmation
        pass

if __name__ == '__main__':
    server = FileTransferServer()
    server.start()
```

### Client Structure

```python
import socket
import os

class FileTransferClient:
    def __init__(self, host='localhost', port=8080):
        self.host = host
        self.port = port
    
    def send_file(self, filepath):
        # TODO: Read file
        # TODO: Send header
        # TODO: Send filename
        # TODO: Send file data in chunks
        # TODO: Receive confirmation
        pass

if __name__ == '__main__':
    client = FileTransferClient()
    client.send_file('example.txt')
```

## Implementation Steps

### Step 1: Basic File Transfer

1. Send filename and file size
2. Send file data
3. Receive and save file

### Step 2: Add Progress Display

```python
def show_progress(sent, total):
    percent = (sent / total) * 100
    bar_length = 40
    filled = int(bar_length * sent / total)
    bar = '=' * filled + '-' * (bar_length - filled)
    print(f'\r[{bar}] {percent:.1f}% ({sent}/{total} bytes)', end='')
```

### Step 3: Handle Large Files

Transfer in chunks to avoid memory issues:

```python
CHUNK_SIZE = 4096  # 4KB chunks

with open(filepath, 'rb') as f:
    while True:
        chunk = f.read(CHUNK_SIZE)
        if not chunk:
            break
        client.sendall(chunk)
```

### Step 4: Add Error Handling

- Verify file exists before sending
- Check disk space before receiving
- Handle network errors
- Verify file integrity

## Advanced Features

### Feature 1: Resume Transfer

```
CLIENT → SERVER: "RESUME:filename:offset"
SERVER → CLIENT: "OK" or "NOT_FOUND"
CLIENT → SERVER: [Data from offset]
```

### Feature 2: Multiple Files

```
CLIENT → SERVER: "MULTI:count"
SERVER → CLIENT: "READY"
CLIENT → SERVER: [File 1][File 2]...[File N]
```

### Feature 3: Directory Transfer

- Transfer entire directories
- Preserve directory structure
- Handle nested directories

### Feature 4: Compression

- Compress files before sending
- Decompress on server
- Use gzip or zlib

## Expected Behavior

### Server Output
```
File transfer server started on localhost:8080
Waiting for connections...
Client connected from ('127.0.0.1', 54321)
Receiving file: example.txt (1024 bytes)
[========================================] 100.0% (1024/1024 bytes)
File saved to: ./received/example.txt
Transfer complete
```

### Client Output
```
Connecting to localhost:8080...
Connected
Sending file: example.txt (1024 bytes)
[========================================] 100.0% (1024/1024 bytes)
Transfer complete: OK
```

## Testing

### Test 1: Small File

```bash
# Create test file
echo "Hello, World!" > test.txt

# Terminal 1: Start server
python file_server.py

# Terminal 2: Send file
python file_client.py test.txt
```

### Test 2: Large File

```bash
# Create large file (10MB)
dd if=/dev/urandom of=large.bin bs=1M count=10

# Send large file
python file_client.py large.bin
# Verify progress display works
```

### Test 3: Error Handling

```bash
# Try sending non-existent file
python file_client.py nonexistent.txt
# Should show error

# Stop server during transfer
# Client should handle error gracefully
```

## Solution Hints

<details>
<summary>Receiving file with header</summary>

```python
import struct

def receive_file(self, client):
    # Receive header (2 bytes filename length, 8 bytes file size)
    header = client.recv(10)
    if len(header) != 10:
        raise ValueError("Incomplete header")
    
    filename_len = struct.unpack('!H', header[0:2])[0]
    file_size = struct.unpack('!Q', header[2:10])[0]
    
    # Receive filename
    filename = client.recv(filename_len).decode('utf-8')
    
    # Receive file data
    filepath = os.path.join(self.save_dir, filename)
    with open(filepath, 'wb') as f:
        remaining = file_size
        while remaining > 0:
            chunk = client.recv(min(4096, remaining))
            if not chunk:
                raise ValueError("Connection closed during transfer")
            f.write(chunk)
            remaining -= len(chunk)
    
    client.sendall(b"OK")
```

</details>

## Success Criteria

- ✅ Small files transfer correctly
- ✅ Large files transfer without memory issues
- ✅ Progress display works
- ✅ Error handling for network failures
- ✅ Files saved correctly on server
- ✅ Supports various file types (text, binary, images)

## Bonus Challenges

1. Add file integrity check (MD5/SHA256)
2. Implement transfer encryption
3. Add bandwidth throttling
4. Support multiple concurrent transfers
5. Create a GUI client

---

**Next**: Exercise 4: Simple HTTP Server to understand web protocols.

