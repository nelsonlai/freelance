#!/bin/bash

echo "🚀 Starting Flask RESTful API Demo..."
echo ""

# Check if Python is installed
if ! command -v python3 &> /dev/null; then
    echo "❌ Python 3 is not installed. Please install Python 3.7 or higher."
    exit 1
fi

# Check if pip is installed
if ! command -v pip3 &> /dev/null; then
    echo "❌ pip3 is not installed. Please install pip."
    exit 1
fi

echo "📦 Installing dependencies..."
pip3 install -r requirements.txt

echo ""
echo "🌐 Starting the Flask server..."
echo "   The API will be available at: http://localhost:54321"
echo "   Press Ctrl+C to stop the server"
echo ""

# Run the Flask application
python3 app.py
