#!/bin/bash

echo "🚀 Setting up Password CRUD Demo Application..."
echo ""

# Check if Node.js is installed
if ! command -v node &> /dev/null; then
    echo "❌ Node.js is not installed. Please install Node.js 20.x or higher."
    exit 1
fi

# Check Node.js version
NODE_VERSION=$(node -v | cut -d'v' -f2 | cut -d'.' -f1)
if [ "$NODE_VERSION" -lt 20 ]; then
    echo "❌ Node.js version 20.x or higher is required. Current version: $(node -v)"
    exit 1
fi

echo "✅ Node.js version: $(node -v)"

# Install root dependencies
echo "📦 Installing root dependencies..."
npm install

# Install backend dependencies
echo "📦 Installing backend dependencies..."
cd backend
npm install

# Install frontend dependencies
echo "📦 Installing frontend dependencies..."
cd ../frontend
npm install

# Go back to root
cd ..

# Generate Prisma client
echo "🗄️ Generating Prisma client..."
cd backend
npx prisma generate

# Create and run initial migration
echo "🗄️ Setting up database..."
npx prisma migrate dev --name init

cd ..

echo ""
echo "✅ Setup complete!"
echo ""
echo "🚀 To start the application:"
echo "   npm run dev"
echo ""
echo "📖 For more information, see README.md"
echo ""
echo "⚠️  REMEMBER: This application stores passwords in plain text for demo purposes only!"
echo "   Do not use in production environments."
