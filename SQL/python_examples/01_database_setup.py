"""
====================================================================
Lesson 1: Database Setup and Connection - Flask + SQLAlchemy ORM Examples
====================================================================
This module demonstrates how to connect to MySQL using Flask and SQLAlchemy ORM.
It covers:
1. Flask application setup with SQLAlchemy
2. Environment variable configuration for database credentials
3. Database connection and session management
4. Basic database operations using ORM
5. Error handling and connection management
6. Best practices for Flask-SQLAlchemy integration

Key Concepts:
- Flask: Lightweight web framework for Python
- SQLAlchemy ORM: Object-Relational Mapping for database operations
- Flask-SQLAlchemy: Flask extension that adds SQLAlchemy support
- Database models: Python classes that represent database tables
- Session management: Handling database transactions and connections
====================================================================
"""

# Import required libraries
from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import text, create_engine
from sqlalchemy.orm import sessionmaker
import os
from dotenv import load_dotenv
from datetime import datetime

# Load environment variables from .env file
load_dotenv()

# Initialize Flask application
app = Flask(__name__)

# Configure database connection
app.config['SQLALCHEMY_DATABASE_URI'] = (
    f"mysql+pymysql://{os.getenv('DB_USER', 'student')}:"
    f"{os.getenv('DB_PASSWORD', 'password123')}@"
    f"{os.getenv('DB_HOST', 'localhost')}:"
    f"{os.getenv('DB_PORT', 3306)}/"
    f"{os.getenv('DB_NAME', 'learning_db')}"
)

app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.config['SQLALCHEMY_ENGINE_OPTIONS'] = {
    'pool_pre_ping': True,
    'pool_recycle': 300,
    'connect_args': {'charset': 'utf8mb4'}
}

# Initialize SQLAlchemy with Flask app
db = SQLAlchemy(app)

class DatabaseConnection:
    """
    DatabaseConnection class handles all database connection operations using Flask-SQLAlchemy.
    
    This class encapsulates database connection logic and provides methods
    for common database operations like testing connections, creating databases,
    and managing database sessions using ORM patterns.
    
    Attributes:
        app (Flask): Flask application instance
        db (SQLAlchemy): SQLAlchemy database instance
    """
    
    def __init__(self):
        """
        Initialize database connection using Flask-SQLAlchemy.
        
        Uses the Flask application context to manage database connections
        and provides ORM-based database operations.
        """
        self.app = app
        self.db = db
        
    def test_connection(self):
        """
        Test basic connection to MySQL server using SQLAlchemy ORM.
        
        This method verifies that we can successfully connect to the MySQL server
        and execute a simple query using the ORM session.
        
        Returns:
            bool: True if connection successful, False otherwise
            
        Raises:
            Exception: If connection fails, prints error message and returns False
        """
        try:
            # Use Flask application context
            with self.app.app_context():
                # Test connection by executing a simple query
                result = self.db.session.execute(text("SELECT VERSION()"))
                version = result.fetchone()[0]
                print(f"✅ Connected to MySQL version: {version}")
                return True
        except Exception as e:
            print(f"❌ Connection failed: {e}")
            return False
    
    def show_databases(self):
        """
        Display all available databases on the MySQL server.
        
        This method connects to the MySQL server and executes the SHOW DATABASES 
        command to list all databases that the current user has access to.
        
        Returns:
            list: List of database names, empty list if error occurs
        """
        try:
            with self.app.app_context():
                # Execute SHOW DATABASES command using ORM session
                result = self.db.session.execute(text("SHOW DATABASES"))
                
                # Extract database names from result set
                databases = [row[0] for row in result.fetchall()]
                
                # Display results in a user-friendly format
                print("Available databases:")
                for db_name in databases:
                    print(f"  - {db_name}")
                return databases
        except Exception as e:
            print(f"Error showing databases: {e}")
            return []
    
    def create_database(self, db_name):
        """
        Create a new database with the specified name.
        
        Args:
            db_name (str): Name of the database to create
            
        Returns:
            bool: True if database created successfully, False otherwise
            
        Notes:
            - Uses IF NOT EXISTS to avoid errors if database already exists
            - Commits the transaction to make the change permanent
        """
        try:
            with self.app.app_context():
                # Execute CREATE DATABASE command with IF NOT EXISTS clause
                self.db.session.execute(text(f"CREATE DATABASE IF NOT EXISTS {db_name}"))
                
                # Commit the transaction to make the database creation permanent
                self.db.session.commit()
                print(f"✅ Database '{db_name}' created successfully")
                return True
        except Exception as e:
            print(f"❌ Failed to create database: {e}")
            self.db.session.rollback()
            return False
    
    def use_database(self, db_name):
        """
        Switch the current session to use the specified database.
        
        Args:
            db_name (str): Name of the database to switch to
            
        Returns:
            str: Name of the current database if successful, None if failed
            
        Notes:
            - This is equivalent to the SQL command "USE database_name"
            - Verifies the switch was successful by querying DATABASE()
        """
        try:
            with self.app.app_context():
                # Execute USE command to switch to specified database
                self.db.session.execute(text(f"USE {db_name}"))
                
                # Verify the switch was successful by querying current database
                result = self.db.session.execute(text("SELECT DATABASE()"))
                current_db = result.fetchone()[0]
                print(f"✅ Now using database: {current_db}")
                return current_db
        except Exception as e:
            print(f"❌ Failed to use database: {e}")
            return None
    
    def show_tables(self):
        """
        Display all tables in the current database.
        
        This method shows all tables that exist in the currently selected database.
        It's useful for exploring the database structure and verifying table creation.
        
        Returns:
            list: List of table names, empty list if error occurs
        """
        try:
            with self.app.app_context():
                # Execute SHOW TABLES command
                result = self.db.session.execute(text("SHOW TABLES"))
                
                # Extract table names from result set
                tables = [row[0] for row in result.fetchall()]
                
                # Display results in a user-friendly format
                print("Tables in current database:")
                for table in tables:
                    print(f"  - {table}")
                return tables
        except Exception as e:
            print(f"Error showing tables: {e}")
            return []

class SampleModel(db.Model):
    """
    Sample database model to demonstrate SQLAlchemy ORM usage.
    
    This model represents a simple table for demonstration purposes.
    It shows how to define database models using SQLAlchemy ORM.
    """
    __tablename__ = 'sample_table'
    
    id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    name = db.Column(db.String(100), nullable=False)
    description = db.Column(db.Text)
    created_at = db.Column(db.DateTime, default=datetime.utcnow)
    updated_at = db.Column(db.DateTime, default=datetime.utcnow, onupdate=datetime.utcnow)
    
    def __repr__(self):
        return f'<SampleModel {self.name}>'
    
    def to_dict(self):
        """Convert model instance to dictionary"""
        return {
            'id': self.id,
            'name': self.name,
            'description': self.description,
            'created_at': self.created_at.isoformat() if self.created_at else None,
            'updated_at': self.updated_at.isoformat() if self.updated_at else None
        }

class DatabaseOperations:
    """
    DatabaseOperations class demonstrates ORM-based database operations.
    
    This class shows how to perform CRUD operations using SQLAlchemy ORM
    instead of raw SQL queries.
    """
    
    def __init__(self):
        """Initialize with Flask app and database instance"""
        self.app = app
        self.db = db
    
    def create_tables(self):
        """
        Create all database tables using SQLAlchemy ORM.
        
        This method creates all tables defined in the models.
        
        Returns:
            bool: True if tables created successfully, False otherwise
        """
        try:
            with self.app.app_context():
                # Create all tables defined in models
                self.db.create_all()
                print("✅ All tables created successfully using ORM")
                return True
        except Exception as e:
            print(f"❌ Failed to create tables: {e}")
            return False
    
    def insert_sample_data(self):
        """
        Insert sample data using SQLAlchemy ORM.
        
        This method demonstrates how to create and save model instances
        using the ORM instead of raw SQL INSERT statements.
        
        Returns:
            bool: True if data inserted successfully, False otherwise
        """
        try:
            with self.app.app_context():
                # Create sample model instances
                sample1 = SampleModel(
                    name='Sample Record 1',
                    description='This is a sample record created using SQLAlchemy ORM'
                )
                
                sample2 = SampleModel(
                    name='Sample Record 2',
                    description='Another sample record demonstrating ORM usage'
                )
                
                # Add instances to session
                self.db.session.add(sample1)
                self.db.session.add(sample2)
                
                # Commit the transaction
                self.db.session.commit()
                print("✅ Sample data inserted successfully using ORM")
                return True
        except Exception as e:
            print(f"❌ Failed to insert sample data: {e}")
            self.db.session.rollback()
            return False
    
    def query_sample_data(self):
        """
        Query sample data using SQLAlchemy ORM.
        
        This method demonstrates how to retrieve data using ORM queries
        instead of raw SQL SELECT statements.
        
        Returns:
            list: List of sample records, empty list if error occurs
        """
        try:
            with self.app.app_context():
                # Query all records using ORM
                samples = SampleModel.query.all()
                
                print("Sample records retrieved using ORM:")
                for sample in samples:
                    print(f"  - {sample}")
                    print(f"    Dict: {sample.to_dict()}")
                
                # Query with conditions
                filtered_samples = SampleModel.query.filter(
                    SampleModel.name.like('%Record%')
                ).all()
                
                print(f"\nFiltered records: {len(filtered_samples)} found")
                
                return [sample.to_dict() for sample in samples]
        except Exception as e:
            print(f"❌ Failed to query sample data: {e}")
            return []
    
    def update_sample_data(self):
        """
        Update sample data using SQLAlchemy ORM.
        
        This method demonstrates how to update records using ORM
        instead of raw SQL UPDATE statements.
        
        Returns:
            bool: True if update successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Find and update a record
                sample = SampleModel.query.first()
                if sample:
                    sample.description = "Updated description using SQLAlchemy ORM"
                    sample.updated_at = datetime.utcnow()
                    
                    # Commit the changes
                    self.db.session.commit()
                    print(f"✅ Updated record: {sample}")
                    return True
                else:
                    print("No records found to update")
                    return False
        except Exception as e:
            print(f"❌ Failed to update sample data: {e}")
            self.db.session.rollback()
            return False
    
    def delete_sample_data(self):
        """
        Delete sample data using SQLAlchemy ORM.
        
        This method demonstrates how to delete records using ORM
        instead of raw SQL DELETE statements.
        
        Returns:
            bool: True if deletion successful, False otherwise
        """
        try:
            with self.app.app_context():
                # Find and delete a record
                sample = SampleModel.query.filter(
                    SampleModel.name.like('%Record 2%')
                ).first()
                
                if sample:
                    self.db.session.delete(sample)
                    self.db.session.commit()
                    print(f"✅ Deleted record: {sample}")
                    return True
                else:
                    print("No records found to delete")
                    return False
        except Exception as e:
            print(f"❌ Failed to delete sample data: {e}")
            self.db.session.rollback()
            return False

def main():
    """
    Main function to demonstrate database connection and ORM operations.
    
    This function serves as a comprehensive example of how to:
    1. Initialize a database connection using Flask-SQLAlchemy
    2. Test connectivity to MySQL server
    3. List available databases
    4. Create a new database
    5. Switch to a specific database
    6. List tables in the current database
    7. Perform CRUD operations using SQLAlchemy ORM
    
    The function follows a logical progression that would be typical
    in a real-world Flask application setup process.
    """
    print("=== Flask + SQLAlchemy ORM Database Connection Demo ===\n")
    
    # Initialize database connection object
    db_connection = DatabaseConnection()
    
    # Step 1: Test basic connection to MySQL server
    print("1. Testing connection...")
    if not db_connection.test_connection():
        print("Please check your MySQL server and credentials")
        return  # Exit if connection fails
    
    # Step 2: Display all available databases
    print("\n2. Showing available databases...")
    databases = db_connection.show_databases()
    
    # Step 3: Create the learning database if it doesn't exist
    print("\n3. Creating learning database...")
    db_connection.create_database('learning_db')
    
    # Step 4: Switch to the learning database
    print("\n4. Switching to learning database...")
    db_connection.use_database('learning_db')
    
    # Step 5: Show tables in the current database
    print("\n5. Showing tables in learning database...")
    db_connection.show_tables()
    
    # Step 6: Demonstrate ORM operations
    print("\n6. Demonstrating SQLAlchemy ORM operations...")
    db_operations = DatabaseOperations()
    
    # Create tables using ORM
    print("\n6a. Creating tables using ORM...")
    db_operations.create_tables()
    
    # Show tables again
    print("\n6b. Showing tables after ORM creation...")
    db_connection.show_tables()
    
    # Insert sample data using ORM
    print("\n6c. Inserting sample data using ORM...")
    db_operations.insert_sample_data()
    
    # Query sample data using ORM
    print("\n6d. Querying sample data using ORM...")
    db_operations.query_sample_data()
    
    # Update sample data using ORM
    print("\n6e. Updating sample data using ORM...")
    db_operations.update_sample_data()
    
    # Query updated data
    print("\n6f. Querying updated data using ORM...")
    db_operations.query_sample_data()
    
    # Delete sample data using ORM
    print("\n6g. Deleting sample data using ORM...")
    db_operations.delete_sample_data()
    
    # Final query
    print("\n6h. Final query using ORM...")
    db_operations.query_sample_data()
    
    print("\n=== Flask + SQLAlchemy ORM Connection Demo Complete ===")

# Standard Python idiom for running the script
if __name__ == "__main__":
    main()