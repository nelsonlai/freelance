"""
MongoDB Python Integration - Basic Connection
==============================================

This module demonstrates how to connect to MongoDB using PyMongo.
"""

from pymongo import MongoClient
from pymongo.errors import ConnectionFailure, ServerSelectionTimeoutError
import sys


def connect_to_mongodb(connection_string="mongodb://localhost:27017/", database_name="testdb"):
    """
    Connect to MongoDB and return database object.
    
    Args:
        connection_string (str): MongoDB connection string
        database_name (str): Name of the database to use
    
    Returns:
        pymongo.database.Database: Database object
    """
    try:
        # Create MongoDB client
        # For local MongoDB: mongodb://localhost:27017/
        # For MongoDB Atlas: mongodb+srv://username:password@cluster.mongodb.net/
        client = MongoClient(connection_string, serverSelectionTimeoutMS=5000)
        
        # Test connection
        client.admin.command('ping')
        print("✓ Successfully connected to MongoDB!")
        
        # Get database (creates if doesn't exist)
        db = client[database_name]
        print(f"✓ Using database: {database_name}")
        
        return client, db
        
    except ConnectionFailure as e:
        print(f"✗ Connection failed: {e}")
        sys.exit(1)
    except ServerSelectionTimeoutError as e:
        print(f"✗ Server selection timeout: {e}")
        print("  Make sure MongoDB is running on your system")
        sys.exit(1)
    except Exception as e:
        print(f"✗ Unexpected error: {e}")
        sys.exit(1)


def get_server_info(client):
    """
    Get MongoDB server information.
    
    Args:
        client: MongoDB client object
    """
    try:
        server_info = client.server_info()
        print("\n=== MongoDB Server Information ===")
        print(f"Version: {server_info['version']}")
        print(f"Platform: {server_info.get('targetMinOS', 'N/A')}")
        print(f"Git Version: {server_info.get('gitVersion', 'N/A')}")
    except Exception as e:
        print(f"Error getting server info: {e}")


def list_databases(client):
    """
    List all databases.
    
    Args:
        client: MongoDB client object
    """
    try:
        databases = client.list_database_names()
        print("\n=== Available Databases ===")
        for db_name in databases:
            print(f"  - {db_name}")
    except Exception as e:
        print(f"Error listing databases: {e}")


def list_collections(db):
    """
    List all collections in the database.
    
    Args:
        db: Database object
    """
    try:
        collections = db.list_collection_names()
        print(f"\n=== Collections in '{db.name}' ===")
        if collections:
            for collection_name in collections:
                print(f"  - {collection_name}")
        else:
            print("  (No collections found)")
    except Exception as e:
        print(f"Error listing collections: {e}")


def close_connection(client):
    """
    Close MongoDB connection.
    
    Args:
        client: MongoDB client object
    """
    try:
        client.close()
        print("\n✓ Connection closed successfully")
    except Exception as e:
        print(f"Error closing connection: {e}")


# Example usage
if __name__ == "__main__":
    print("=" * 50)
    print("MongoDB Python Connection Example")
    print("=" * 50)
    
    # Connect to MongoDB
    client, db = connect_to_mongodb()
    
    # Get server information
    get_server_info(client)
    
    # List databases
    list_databases(client)
    
    # List collections
    list_collections(db)
    
    # Close connection
    close_connection(client)

