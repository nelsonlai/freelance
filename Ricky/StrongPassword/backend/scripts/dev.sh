#!/bin/bash

# Development script for backend
# This script kills any existing process on port 4000 and starts the server

echo "🔧 Starting backend development server..."

# Kill any existing process on port 4000
echo "🛑 Checking for existing processes on port 4000..."
EXISTING_PID=$(lsof -ti:4000)

if [ ! -z "$EXISTING_PID" ]; then
    echo "⚠️  Found existing process (PID: $EXISTING_PID), killing it..."
    kill -9 $EXISTING_PID
    sleep 2
    echo "✅ Process killed"
else
    echo "✅ Port 4000 is free"
fi

# Start the development server
echo "🚀 Starting development server..."
npm run dev
