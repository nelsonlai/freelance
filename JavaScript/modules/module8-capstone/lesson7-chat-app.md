# Lesson 7: Capstone Project - Chat App

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Build a real-time chat application
- Implement WebSocket connections
- Handle user authentication and authorization
- Manage message history and persistence
- Implement file sharing capabilities
- Create responsive chat interface

## 📚 Project Overview

We'll build a real-time chat application that includes:
- WebSocket integration for real-time messaging
- User authentication and authorization
- Message history and persistence
- File sharing (images and documents)
- Responsive design for mobile and desktop
- Online user status and typing indicators

## 🏗️ Project Structure

```
chat-app/
├── package.json
├── server/
│   ├── server.js
│   ├── models/
│   │   ├── User.js
│   │   └── Message.js
│   ├── routes/
│   │   ├── auth.js
│   │   └── messages.js
│   └── middleware/
│       └── auth.js
├── client/
│   ├── package.json
│   ├── src/
│   │   ├── App.js
│   │   ├── components/
│   │   │   ├── Login.js
│   │   │   ├── ChatRoom.js
│   │   │   ├── MessageList.js
│   │   │   ├── MessageInput.js
│   │   │   └── UserList.js
│   │   └── hooks/
│   │       └── useSocket.js
└── README.md
```

## 💻 Complete Implementation

### server/server.js
```javascript
const express = require('express');
const http = require('http');
const socketIo = require('socket.io');
const mongoose = require('mongoose');
const cors = require('cors');
const authRoutes = require('./routes/auth');
const messageRoutes = require('./routes/messages');
const authMiddleware = require('./middleware/auth');

const app = express();
const server = http.createServer(app);
const io = socketIo(server, {
    cors: {
        origin: "http://localhost:3000",
        methods: ["GET", "POST"]
    }
});

// Middleware
app.use(cors());
app.use(express.json());

// Routes
app.use('/api/auth', authRoutes);
app.use('/api/messages', authMiddleware, messageRoutes);

// Socket.io connection handling
io.use((socket, next) => {
    const token = socket.handshake.auth.token;
    if (!token) {
        return next(new Error('Authentication error'));
    }
    
    // Verify JWT token
    const user = jwt.verify(token, process.env.JWT_SECRET);
    socket.userId = user.id;
    socket.username = user.username;
    next();
});

io.on('connection', (socket) => {
    console.log(`User ${socket.username} connected`);
    
    // Join user to general room
    socket.join('general');
    
    // Broadcast user online status
    socket.broadcast.emit('userOnline', {
        userId: socket.userId,
        username: socket.username
    });
    
    // Handle new message
    socket.on('sendMessage', async (data) => {
        try {
            const message = new Message({
                content: data.content,
                sender: socket.userId,
                room: data.room || 'general',
                type: data.type || 'text'
            });
            
            await message.save();
            
            // Broadcast message to room
            io.to(data.room || 'general').emit('newMessage', {
                id: message._id,
                content: message.content,
                sender: {
                    id: socket.userId,
                    username: socket.username
                },
                timestamp: message.timestamp,
                type: message.type
            });
        } catch (error) {
            socket.emit('error', { message: 'Failed to send message' });
        }
    });
    
    // Handle typing indicator
    socket.on('typing', (data) => {
        socket.broadcast.to(data.room || 'general').emit('userTyping', {
            userId: socket.userId,
            username: socket.username,
            isTyping: data.isTyping
        });
    });
    
    // Handle file upload
    socket.on('fileUpload', async (data) => {
        try {
            const message = new Message({
                content: data.filename,
                sender: socket.userId,
                room: data.room || 'general',
                type: 'file',
                fileData: {
                    filename: data.filename,
                    mimetype: data.mimetype,
                    size: data.size
                }
            });
            
            await message.save();
            
            io.to(data.room || 'general').emit('newMessage', {
                id: message._id,
                content: message.content,
                sender: {
                    id: socket.userId,
                    username: socket.username
                },
                timestamp: message.timestamp,
                type: message.type,
                fileData: message.fileData
            });
        } catch (error) {
            socket.emit('error', { message: 'Failed to upload file' });
        }
    });
    
    // Handle disconnect
    socket.on('disconnect', () => {
        console.log(`User ${socket.username} disconnected`);
        socket.broadcast.emit('userOffline', {
            userId: socket.userId,
            username: socket.username
        });
    });
});

// Connect to MongoDB
mongoose.connect(process.env.MONGODB_URI || 'mongodb://localhost:27017/chat-app')
    .then(() => console.log('Connected to MongoDB'))
    .catch(err => console.error('MongoDB connection error:', err));

const PORT = process.env.PORT || 5000;
server.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});
```

### client/src/hooks/useSocket.js
```javascript
import { useEffect, useState } from 'react';
import io from 'socket.io-client';

export function useSocket(token) {
    const [socket, setSocket] = useState(null);
    const [connected, setConnected] = useState(false);
    
    useEffect(() => {
        if (!token) return;
        
        const newSocket = io('http://localhost:5000', {
            auth: { token }
        });
        
        newSocket.on('connect', () => {
            setConnected(true);
            console.log('Connected to server');
        });
        
        newSocket.on('disconnect', () => {
            setConnected(false);
            console.log('Disconnected from server');
        });
        
        setSocket(newSocket);
        
        return () => {
            newSocket.close();
        };
    }, [token]);
    
    return { socket, connected };
}
```

### client/src/components/ChatRoom.js
```javascript
import React, { useState, useEffect, useRef } from 'react';
import MessageList from './MessageList';
import MessageInput from './MessageInput';
import UserList from './UserList';
import { useSocket } from '../hooks/useSocket';

function ChatRoom({ user, token }) {
    const { socket, connected } = useSocket(token);
    const [messages, setMessages] = useState([]);
    const [users, setUsers] = useState([]);
    const [typingUsers, setTypingUsers] = useState([]);
    const messagesEndRef = useRef(null);
    
    useEffect(() => {
        if (!socket) return;
        
        // Listen for new messages
        socket.on('newMessage', (message) => {
            setMessages(prev => [...prev, message]);
        });
        
        // Listen for user online/offline
        socket.on('userOnline', (userData) => {
            setUsers(prev => [...prev, userData]);
        });
        
        socket.on('userOffline', (userData) => {
            setUsers(prev => prev.filter(u => u.userId !== userData.userId));
        });
        
        // Listen for typing indicators
        socket.on('userTyping', (data) => {
            if (data.isTyping) {
                setTypingUsers(prev => [...prev.filter(u => u.userId !== data.userId), data]);
            } else {
                setTypingUsers(prev => prev.filter(u => u.userId !== data.userId));
            }
        });
        
        // Load message history
        fetchMessages();
        
        return () => {
            socket.off('newMessage');
            socket.off('userOnline');
            socket.off('userOffline');
            socket.off('userTyping');
        };
    }, [socket]);
    
    useEffect(() => {
        scrollToBottom();
    }, [messages]);
    
    const scrollToBottom = () => {
        messagesEndRef.current?.scrollIntoView({ behavior: 'smooth' });
    };
    
    const fetchMessages = async () => {
        try {
            const response = await fetch('/api/messages', {
                headers: {
                    'Authorization': `Bearer ${token}`
                }
            });
            const data = await response.json();
            setMessages(data);
        } catch (error) {
            console.error('Error fetching messages:', error);
        }
    };
    
    const sendMessage = (content, type = 'text') => {
        if (socket && content.trim()) {
            socket.emit('sendMessage', {
                content: content.trim(),
                type,
                room: 'general'
            });
        }
    };
    
    const handleTyping = (isTyping) => {
        if (socket) {
            socket.emit('typing', {
                isTyping,
                room: 'general'
            });
        }
    };
    
    const handleFileUpload = (file) => {
        if (socket && file) {
            const reader = new FileReader();
            reader.onload = (e) => {
                socket.emit('fileUpload', {
                    filename: file.name,
                    mimetype: file.type,
                    size: file.size,
                    data: e.target.result,
                    room: 'general'
                });
            };
            reader.readAsDataURL(file);
        }
    };
    
    return (
        <div className="chat-room">
            <div className="chat-header">
                <h2>Chat Room</h2>
                <div className={`connection-status ${connected ? 'connected' : 'disconnected'}`}>
                    {connected ? 'Connected' : 'Disconnected'}
                </div>
            </div>
            
            <div className="chat-content">
                <div className="messages-container">
                    <MessageList 
                        messages={messages}
                        currentUser={user}
                    />
                    <div ref={messagesEndRef} />
                    
                    {typingUsers.length > 0 && (
                        <div className="typing-indicator">
                            {typingUsers.map(user => user.username).join(', ')} 
                            {typingUsers.length === 1 ? ' is' : ' are'} typing...
                        </div>
                    )}
                </div>
                
                <div className="users-sidebar">
                    <UserList users={users} currentUser={user} />
                </div>
            </div>
            
            <MessageInput 
                onSendMessage={sendMessage}
                onTyping={handleTyping}
                onFileUpload={handleFileUpload}
            />
        </div>
    );
}

export default ChatRoom;
```

## 🎯 Key Features Implemented

1. **Real-Time Messaging** - WebSocket integration
2. **User Authentication** - JWT-based authentication
3. **Message History** - Persistent chat data
4. **File Sharing** - Image and document uploads
5. **Typing Indicators** - Real-time typing status
6. **Online Status** - User presence tracking
7. **Responsive Design** - Mobile and desktop support

## 🎯 Key Takeaways

1. **WebSockets** enable real-time communication
2. **Authentication** secures chat sessions
3. **Message persistence** stores chat history
4. **File handling** supports media sharing
5. **User experience** includes typing indicators

## 🚀 Next Steps

Congratulations! You've built a real-time chat application. In the next lesson, we'll create:

- **E-Commerce Shopping Cart** - Product catalog and checkout
- **Payment integration** - Simulated payment processing
- **Order management** - User accounts and order history
- **Inventory tracking** - Product availability

---

**Next Lesson**: [Lesson 8: Capstone Project - E-Commerce Cart](./lesson8-ecommerce.md)
