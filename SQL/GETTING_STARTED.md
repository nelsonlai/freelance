# Getting Started with SQL Learning Course

## Quick Start Guide

This guide will help you set up your environment and start learning SQL with MySQL and Python SQLAlchemy.

## Prerequisites

Before starting, ensure you have:

- **MySQL Server** installed and running
- **Python 3.7+** installed
- **pip** (Python package manager)
- Basic command line knowledge

## Step 1: Install MySQL Server

### macOS (using Homebrew)
```bash
# Install MySQL
brew install mysql

# Start MySQL service
brew services start mysql

# Secure the installation
mysql_secure_installation
```

### Ubuntu/Debian
```bash
# Update package list
sudo apt update

# Install MySQL
sudo apt install mysql-server

# Start MySQL service
sudo systemctl start mysql
sudo systemctl enable mysql

# Secure the installation
sudo mysql_secure_installation
```

### Windows
1. Download MySQL Installer from [mysql.com](https://dev.mysql.com/downloads/installer/)
2. Run the installer and follow the setup wizard
3. Start MySQL service from Services

## Step 2: Set Up Database User

Connect to MySQL as root and create a user for the course:

```sql
-- Connect to MySQL
mysql -u root -p

-- Create user and database
CREATE USER 'student'@'localhost' IDENTIFIED BY 'password123';
CREATE DATABASE learning_db CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
GRANT ALL PRIVILEGES ON learning_db.* TO 'student'@'localhost';
FLUSH PRIVILEGES;

-- Test connection
mysql -u student -p learning_db
```

## Step 3: Install Python Dependencies

```bash
# Navigate to the course directory
cd /path/to/SQL

# Install required packages
pip install -r requirements.txt
```

## Step 4: Configure Environment

```bash
# Copy the environment template
cp env_example.txt .env

# Edit .env with your database credentials
# DB_HOST=localhost
# DB_PORT=3306
# DB_USER=student
# DB_PASSWORD=password123
# DB_NAME=learning_db
```

## Step 5: Set Up Database Schema

```bash
# Run the database setup script
mysql -u student -p < setup_database.sql

# Load sample data
mysql -u student -p < sample_data/sample_data.sql
```

## Step 6: Test Your Setup

Run the connection test:

```bash
python python_examples/01_database_setup.py
```

You should see:
```
✅ Connected to MySQL version: 8.0.xx
✅ Database 'learning_db' created successfully
✅ All tables created successfully!
```

## Learning Path

### Module 1: Database Fundamentals (Lessons 1-3)
1. **Lesson 1**: Database Setup and Connection
2. **Lesson 2**: Creating Databases and Tables
3. **Lesson 3**: Data Types and Constraints

**Python Examples**: `01_database_setup.py`, `02_create_database_tables.py`

### Module 2: Basic SQL Operations (Lessons 4-6)
4. **Lesson 4**: Inserting Data
5. **Lesson 5**: Querying Data (SELECT)
6. **Lesson 6**: Updating and Deleting Data

**Python Examples**: `04_insert_data.py`, `05_select_queries.py`, `06_update_delete.py`

### Module 3: Intermediate SQL (Lessons 7-9)
7. **Lesson 7**: Joins and Relationships
8. **Lesson 8**: Aggregation Functions
9. **Lesson 9**: Subqueries

**Python Examples**: `07_joins.py`

### Module 4: Advanced SQL (Lessons 10-13)
10. **Lesson 10**: Views and Indexes
11. **Lesson 11**: Stored Procedures and Functions
12. **Lesson 12**: Triggers
13. **Lesson 13**: Performance Optimization

**Python Examples**: `11_stored_procedures.py`

### Module 5: Python SQLAlchemy Integration (Lessons 14-15)
14. **Lesson 14**: SQLAlchemy ORM Basics
15. **Lesson 15**: Advanced SQLAlchemy

## Practice Exercises

Each lesson includes hands-on exercises:

- **Basic Queries**: `exercises/exercise_01_basic_queries.sql`
- **JOIN Operations**: `exercises/exercise_02_joins.sql`
- **More exercises**: Check the `exercises/` directory

## Sample Data

The course includes comprehensive sample data:

- **School Management System**: Complete database with students, courses, departments, and enrollments
- **Sample Data**: `sample_data/sample_data.sql`

## Common Issues and Solutions

### Issue 1: Connection Refused
```
ERROR 2003 (HY000): Can't connect to MySQL server
```
**Solution**: Ensure MySQL server is running
```bash
# macOS
brew services start mysql

# Ubuntu/Debian
sudo systemctl start mysql

# Windows: Start MySQL service from Services
```

### Issue 2: Access Denied
```
ERROR 1045 (28000): Access denied for user 'student'@'localhost'
```
**Solution**: Check username and password, ensure user exists
```sql
-- Connect as root and recreate user
mysql -u root -p
CREATE USER 'student'@'localhost' IDENTIFIED BY 'password123';
GRANT ALL PRIVILEGES ON learning_db.* TO 'student'@'localhost';
FLUSH PRIVILEGES;
```

### Issue 3: Module Not Found
```
ModuleNotFoundError: No module named 'sqlalchemy'
```
**Solution**: Install required packages
```bash
pip install -r requirements.txt
```

### Issue 4: Database Not Found
```
ERROR 1049 (42000): Unknown database 'learning_db'
```
**Solution**: Create the database
```sql
CREATE DATABASE learning_db CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
```

## Tips for Success

1. **Practice Regularly**: Complete all exercises in each lesson
2. **Experiment**: Try modifying queries and see what happens
3. **Use Both Methods**: Practice both SQL commands and Python SQLAlchemy
4. **Read Error Messages**: They often contain helpful information
5. **Backup Your Data**: Always test on sample data first

## Additional Resources

- **MySQL Documentation**: [dev.mysql.com/doc](https://dev.mysql.com/doc/)
- **SQLAlchemy Documentation**: [docs.sqlalchemy.org](https://docs.sqlalchemy.org/)
- **SQL Tutorial**: [w3schools.com/sql](https://www.w3schools.com/sql/)

## Getting Help

If you encounter issues:

1. Check the troubleshooting section above
2. Review the lesson materials carefully
3. Test your setup with the provided examples
4. Ensure all prerequisites are met

## Next Steps

Once you've completed the setup:

1. Start with **Lesson 1: Database Setup and Connection**
2. Follow the lessons in order
3. Complete all exercises
4. Practice with the sample data
5. Experiment with your own queries

Happy learning! 🎓
