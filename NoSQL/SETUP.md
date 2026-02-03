# MongoDB Training Materials - Setup Guide

This guide will help you set up your environment to follow along with the MongoDB training materials.

## Table of Contents

1. [Prerequisites](#prerequisites)
2. [MongoDB Installation](#mongodb-installation)
3. [Python Setup](#python-setup)
4. [Verification](#verification)
5. [Quick Start](#quick-start)
6. [Troubleshooting](#troubleshooting)

---

## Prerequisites

Before you begin, ensure you have:

- A computer with internet access
- Administrator/sudo access (for installation)
- Basic command-line knowledge
- Text editor or IDE (VS Code, PyCharm, etc.)

---

## MongoDB Installation

### macOS Installation

#### Option 1: Using Homebrew (Recommended)

```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Add MongoDB tap
brew tap mongodb/brew

# Install MongoDB Community Edition
brew install mongodb-community

# Start MongoDB service
brew services start mongodb-community

# Verify installation
mongosh --version
```

#### Option 2: Manual Installation

1. Download MongoDB Community Server from [mongodb.com](https://www.mongodb.com/try/download/community)
2. Extract the archive
3. Move to `/usr/local/mongodb`
4. Add to PATH in `~/.zshrc` or `~/.bash_profile`:
   ```bash
   export PATH="/usr/local/mongodb/bin:$PATH"
   ```
5. Create data directory:
   ```bash
   sudo mkdir -p /data/db
   sudo chown $(whoami) /data/db
   ```
6. Start MongoDB:
   ```bash
   mongod
   ```

### Linux Installation (Ubuntu/Debian)

```bash
# Import MongoDB public GPG key
wget -qO - https://www.mongodb.org/static/pgp/server-7.0.asc | sudo apt-key add -

# Add MongoDB repository
echo "deb [ arch=amd64,arm64 ] https://repo.mongodb.org/apt/ubuntu jammy/mongodb-org/7.0 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-7.0.list

# Update package list
sudo apt-get update

# Install MongoDB
sudo apt-get install -y mongodb-org

# Start MongoDB service
sudo systemctl start mongod

# Enable MongoDB to start on boot
sudo systemctl enable mongod

# Verify installation
mongosh --version
```

### Windows Installation

1. **Download MongoDB:**
   - Visit [MongoDB Download Center](https://www.mongodb.com/try/download/community)
   - Select Windows version
   - Download the MSI installer

2. **Run Installer:**
   - Run the downloaded MSI file
   - Choose "Complete" installation
   - Select "Install MongoDB as a Service"
   - Choose "Run service as Network Service user"
   - Install MongoDB Compass (optional GUI tool)

3. **Verify Installation:**
   - Open Command Prompt or PowerShell
   - Run: `mongosh --version`

4. **Start MongoDB:**
   - MongoDB should start automatically as a Windows service
   - If not, go to Services and start "MongoDB" service

### Docker Installation (All Platforms)

```bash
# Pull MongoDB image
docker pull mongo:latest

# Run MongoDB container
docker run -d \
  --name mongodb \
  -p 27017:27017 \
  -v mongodb_data:/data/db \
  mongo:latest

# Connect to MongoDB
docker exec -it mongodb mongosh
```

---

## Python Setup

### 1. Install Python

#### macOS

```bash
# Check if Python is installed
python3 --version

# If not installed, install via Homebrew
brew install python3
```

#### Linux

```bash
# Install Python 3
sudo apt-get update
sudo apt-get install python3 python3-pip
```

#### Windows

1. Download Python from [python.org](https://www.python.org/downloads/)
2. Run installer
3. Check "Add Python to PATH" during installation
4. Verify: `python --version`

### 2. Install Python Dependencies

```bash
# Navigate to project directory
cd /path/to/NonSQL

# Install required packages
pip install -r python-examples/requirements.txt

# Or install individually
pip install pymongo python-dotenv
```

### 3. Verify Python Installation

```bash
# Check Python version (should be 3.7+)
python3 --version

# Check pip
pip3 --version

# Test PyMongo import
python3 -c "import pymongo; print(pymongo.__version__)"
```

---

## Verification

### 1. Verify MongoDB Installation

```bash
# Check MongoDB version
mongosh --version

# Connect to MongoDB
mongosh

# In mongosh, run:
db.adminCommand('ping')
# Should return: { ok: 1 }

# Exit mongosh
exit
```

### 2. Verify Python Setup

```bash
# Run basic connection test
cd python-examples
python3 01_basic_connection.py

# Expected output:
# ✓ Successfully connected to MongoDB!
# ✓ Using database: testdb
```

### 3. Test Complete Workflow

```bash
# 1. Create some data
python3 02_create_operations.py

# 2. Read the data
python3 03_read_operations.py

# 3. Update the data
python3 04_update_operations.py

# 4. Delete some data
python3 05_delete_operations.py
```

---

## Quick Start

### Step 1: Start MongoDB

**macOS/Linux:**
```bash
# If using Homebrew
brew services start mongodb-community

# Or manually
mongod
```

**Windows:**
- MongoDB should run as a service automatically
- Or start from Services panel

**Docker:**
```bash
docker start mongodb
```

### Step 2: Connect to MongoDB Shell

```bash
mongosh
```

### Step 3: Try Basic Commands

```javascript
// In mongosh
show dbs
use testdb
db.users.insertOne({name: "Test User", age: 25})
db.users.find()
```

### Step 4: Run Python Examples

```bash
cd python-examples
python3 01_basic_connection.py
```

---

## Troubleshooting

### MongoDB Issues

#### Issue: "mongosh: command not found"

**Solution:**
- Verify MongoDB is installed: `which mongosh`
- Add MongoDB to PATH
- Reinstall MongoDB

#### Issue: "Connection refused"

**Solution:**
```bash
# Check if MongoDB is running
ps aux | grep mongod

# Start MongoDB
brew services start mongodb-community  # macOS
sudo systemctl start mongod           # Linux
```

#### Issue: "Permission denied" for /data/db

**Solution:**
```bash
# Create directory and set permissions
sudo mkdir -p /data/db
sudo chown $(whoami) /data/db
```

#### Issue: Port 27017 already in use

**Solution:**
```bash
# Find process using port 27017
lsof -i :27017

# Kill the process or use different port
mongod --port 27018
```

### Python Issues

#### Issue: "ModuleNotFoundError: No module named 'pymongo'"

**Solution:**
```bash
# Install pymongo
pip3 install pymongo

# Or use virtual environment
python3 -m venv venv
source venv/bin/activate  # macOS/Linux
# or
venv\Scripts\activate      # Windows
pip install pymongo
```

#### Issue: "ConnectionFailure" in Python

**Solution:**
1. Verify MongoDB is running
2. Check connection string
3. Verify firewall settings
4. Check MongoDB logs

#### Issue: Python version too old

**Solution:**
```bash
# Check Python version
python3 --version

# Should be 3.7 or higher
# Update Python if needed
```

### General Issues

#### Issue: Can't connect to MongoDB Atlas

**Solution:**
1. Check connection string
2. Verify IP whitelist in Atlas
3. Check username/password
4. Verify network connectivity

#### Issue: Authentication failed

**Solution:**
1. Verify username and password
2. Check authentication database
3. Ensure user has proper roles

---

## Next Steps

After completing setup:

1. **Read the main README.md** - Overview of NoSQL and MongoDB
2. **Study mongosh-examples.md** - Learn MongoDB shell commands
3. **Work through Python examples** - Start with `01_basic_connection.py`
4. **Practice with exercises** - Try the exercises in each guide
5. **Build a project** - Apply what you've learned

---

## Additional Resources

- [MongoDB Installation Guide](https://docs.mongodb.com/manual/installation/)
- [PyMongo Installation](https://pymongo.readthedocs.io/en/stable/installation.html)
- [MongoDB Community Forums](https://developer.mongodb.com/community/forums/)
- [MongoDB University](https://university.mongodb.com/)

---

## Getting Help

If you encounter issues:

1. Check the troubleshooting section above
2. Review MongoDB logs: `/var/log/mongodb/mongod.log` (Linux) or check system logs
3. Search MongoDB documentation
4. Ask on MongoDB community forums
5. Check GitHub issues for PyMongo

---

**Setup Complete! You're ready to start learning MongoDB! 🚀**

