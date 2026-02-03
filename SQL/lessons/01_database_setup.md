# Lesson 1: Database Setup and Connection

## Learning Objectives
- Understand what a relational database is
- Learn how to connect to MySQL
- Understand basic database concepts
- Set up your development environment

## What is a Relational Database?

A relational database is a type of database that stores and provides access to data points that are related to one another. It uses tables to organize data into rows and columns, where:
- **Tables** represent entities (like customers, orders, products)
- **Rows** represent individual records
- **Columns** represent attributes or fields
- **Relationships** connect tables through foreign keys

## MySQL Connection Methods

### 1. Command Line Interface (CLI)

```bash
# Connect to MySQL server
mysql -u root -p

# Connect with specific user
mysql -u student -p

# Connect to specific database
mysql -u student -p database_name
```

### 2. Python Connection (SQLAlchemy)

```python
from sqlalchemy import create_engine, text
import os
from dotenv import load_dotenv

# Load environment variables
load_dotenv()

# Database connection string
DATABASE_URL = "mysql+pymysql://student:password123@localhost:3306"

# Create engine
engine = create_engine(DATABASE_URL)

# Test connection
try:
    with engine.connect() as connection:
        result = connection.execute(text("SELECT VERSION()"))
        version = result.fetchone()
        print(f"Connected to MySQL version: {version[0]}")
except Exception as e:
    print(f"Connection failed: {e}")
```

## Basic MySQL Commands

### Essential Commands

```sql
-- Show all databases
SHOW DATABASES;

-- Use a specific database
USE database_name;

-- Show current database
SELECT DATABASE();

-- Show all tables in current database
SHOW TABLES;

-- Show table structure
DESCRIBE table_name;
-- or
SHOW COLUMNS FROM table_name;

-- Exit MySQL
EXIT;
-- or
QUIT;
```

## Environment Setup

### 1. Create Environment File

Create a `.env` file in your project root:

```env
DB_HOST=localhost
DB_PORT=3306
DB_USER=student
DB_PASSWORD=password123
DB_NAME=learning_db
```

### 2. Database Configuration

```python
# config.py
import os
from dotenv import load_dotenv

load_dotenv()

class DatabaseConfig:
    HOST = os.getenv('DB_HOST', 'localhost')
    PORT = int(os.getenv('DB_PORT', 3306))
    USER = os.getenv('DB_USER', 'root')
    PASSWORD = os.getenv('DB_PASSWORD', '')
    DATABASE = os.getenv('DB_NAME', 'learning_db')
    
    @property
    def connection_string(self):
        return f"mysql+pymysql://{self.USER}:{self.PASSWORD}@{self.HOST}:{self.PORT}/{self.DATABASE}"
```

## Hands-on Exercise

### Exercise 1: Test Your Connection

1. Start MySQL server
2. Connect using CLI: `mysql -u student -p`
3. Run: `SELECT VERSION();`
4. Run: `SHOW DATABASES;`

### Exercise 2: Python Connection Test

Create a Python script to test your database connection:

```python
# test_connection.py
from sqlalchemy import create_engine, text
from config import DatabaseConfig

def test_connection():
    config = DatabaseConfig()
    engine = create_engine(config.connection_string)
    
    try:
        with engine.connect() as connection:
            # Test basic query
            result = connection.execute(text("SELECT 1 as test"))
            print("✅ Connection successful!")
            
            # Get MySQL version
            result = connection.execute(text("SELECT VERSION()"))
            version = result.fetchone()[0]
            print(f"MySQL Version: {version}")
            
    except Exception as e:
        print(f"❌ Connection failed: {e}")

if __name__ == "__main__":
    test_connection()
```

## Common Connection Issues

### Issue 1: Access Denied
```
ERROR 1045 (28000): Access denied for user 'student'@'localhost'
```
**Solution**: Check username and password, ensure user exists

### Issue 2: Connection Refused
```
ERROR 2003 (HY000): Can't connect to MySQL server
```
**Solution**: Ensure MySQL server is running

### Issue 3: Unknown Database
```
ERROR 1049 (42000): Unknown database 'learning_db'
```
**Solution**: Create the database first

## Key Takeaways

- Relational databases organize data in tables with relationships
- MySQL can be accessed via CLI or programmatically
- Always test your connection before proceeding
- Use environment variables for sensitive configuration
- SQLAlchemy provides a Python interface to MySQL

## Next Steps

In the next lesson, we'll learn how to create databases and tables. Make sure you can successfully connect to MySQL before proceeding!

## Practice Questions

1. What are the main components of a relational database?
2. How do you check which database you're currently using?
3. What's the difference between `DESCRIBE` and `SHOW COLUMNS`?
4. Why is it important to use environment variables for database credentials?
