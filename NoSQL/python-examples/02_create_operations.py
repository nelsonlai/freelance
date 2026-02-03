"""
MongoDB Python Integration - CREATE Operations
===============================================

This module demonstrates how to insert documents into MongoDB using PyMongo.
"""

from pymongo import MongoClient
from datetime import datetime
from bson import ObjectId


def connect_to_mongodb():
    """Connect to MongoDB and return database object."""
    try:
        client = MongoClient("mongodb://localhost:27017/", serverSelectionTimeoutMS=5000)
        client.admin.command('ping')
        db = client["training_db"]
        print("✓ Connected to MongoDB")
        return client, db
    except Exception as e:
        print(f"✗ Connection error: {e}")
        return None, None


def insert_one_document(db):
    """
    Insert a single document into a collection.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Insert One Document")
    print("=" * 50)
    
    collection = db["users"]
    
    # Document to insert
    user_document = {
        "name": "John Doe",
        "age": 30,
        "email": "john.doe@example.com",
        "city": "New York",
        "isActive": True,
        "createdAt": datetime.now()
    }
    
    # Insert document
    result = collection.insert_one(user_document)
    
    print(f"✓ Document inserted with _id: {result.inserted_id}")
    print(f"  Acknowledged: {result.acknowledged}")
    
    return result.inserted_id


def insert_many_documents(db):
    """
    Insert multiple documents into a collection.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Insert Many Documents")
    print("=" * 50)
    
    collection = db["users"]
    
    # Multiple documents to insert
    users = [
        {
            "name": "Jane Smith",
            "age": 25,
            "email": "jane.smith@example.com",
            "city": "Los Angeles",
            "isActive": True,
            "createdAt": datetime.now()
        },
        {
            "name": "Bob Johnson",
            "age": 35,
            "email": "bob.johnson@example.com",
            "city": "Chicago",
            "isActive": False,
            "createdAt": datetime.now()
        },
        {
            "name": "Alice Williams",
            "age": 28,
            "email": "alice.williams@example.com",
            "city": "New York",
            "isActive": True,
            "createdAt": datetime.now()
        },
        {
            "name": "Charlie Brown",
            "age": 40,
            "email": "charlie.brown@example.com",
            "city": "San Francisco",
            "isActive": True,
            "createdAt": datetime.now()
        }
    ]
    
    # Insert documents
    result = collection.insert_many(users)
    
    print(f"✓ Inserted {len(result.inserted_ids)} documents")
    print(f"  Inserted IDs: {result.inserted_ids}")
    print(f"  Acknowledged: {result.acknowledged}")
    
    return result.inserted_ids


def insert_document_with_nested_object(db):
    """
    Insert document with nested objects and arrays.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Insert Document with Nested Objects")
    print("=" * 50)
    
    collection = db["users"]
    
    # Document with nested structure
    user_with_nested = {
        "name": "David Lee",
        "age": 32,
        "email": "david.lee@example.com",
        "address": {
            "street": "456 Oak Avenue",
            "city": "San Francisco",
            "state": "CA",
            "zipCode": "94102",
            "country": "USA"
        },
        "contact": {
            "phone": "555-1234",
            "mobile": "555-5678"
        },
        "hobbies": ["reading", "swimming", "coding", "traveling"],
        "skills": [
            {"name": "Python", "level": "expert"},
            {"name": "JavaScript", "level": "intermediate"},
            {"name": "MongoDB", "level": "beginner"}
        ],
        "tags": ["developer", "tech-enthusiast"],
        "createdAt": datetime.now()
    }
    
    result = collection.insert_one(user_with_nested)
    print(f"✓ Document with nested structure inserted: {result.inserted_id}")
    
    return result.inserted_id


def insert_with_custom_id(db):
    """
    Insert document with custom _id.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Insert Document with Custom _id")
    print("=" * 50)
    
    collection = db["users"]
    
    # Document with custom _id
    user_custom_id = {
        "_id": "user_001",
        "name": "Emma Davis",
        "age": 27,
        "email": "emma.davis@example.com",
        "city": "Boston",
        "isActive": True,
        "createdAt": datetime.now()
    }
    
    try:
        result = collection.insert_one(user_custom_id)
        print(f"✓ Document inserted with custom _id: {result.inserted_id}")
    except Exception as e:
        print(f"✗ Error: {e}")
        print("  (This might happen if _id already exists)")


def insert_products_example(db):
    """
    Example: Insert products into a products collection.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Insert Products Example")
    print("=" * 50)
    
    collection = db["products"]
    
    products = [
        {
            "name": "Laptop",
            "price": 999.99,
            "category": "Electronics",
            "stock": 50,
            "description": "High-performance laptop",
            "tags": ["computer", "electronics", "tech"],
            "createdAt": datetime.now()
        },
        {
            "name": "Smartphone",
            "price": 699.99,
            "category": "Electronics",
            "stock": 100,
            "description": "Latest smartphone model",
            "tags": ["phone", "electronics", "mobile"],
            "createdAt": datetime.now()
        },
        {
            "name": "Coffee Maker",
            "price": 89.99,
            "category": "Appliances",
            "stock": 30,
            "description": "Automatic coffee maker",
            "tags": ["appliance", "kitchen", "coffee"],
            "createdAt": datetime.now()
        },
        {
            "name": "Desk Chair",
            "price": 199.99,
            "category": "Furniture",
            "stock": 25,
            "description": "Ergonomic office chair",
            "tags": ["furniture", "office", "chair"],
            "createdAt": datetime.now()
        }
    ]
    
    result = collection.insert_many(products)
    print(f"✓ Inserted {len(result.inserted_ids)} products")
    
    return result.inserted_ids


def insert_with_validation(db):
    """
    Demonstrate inserting documents (MongoDB doesn't validate by default).
    Note: You should validate data in your application layer.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Insert with Different Data Types")
    print("=" * 50)
    
    collection = db["mixed_data"]
    
    # Document with various data types
    mixed_document = {
        "string_field": "This is a string",
        "integer_field": 42,
        "float_field": 3.14159,
        "boolean_field": True,
        "null_field": None,
        "array_field": [1, 2, 3, "four", 5.0],
        "date_field": datetime.now(),
        "object_id_field": ObjectId(),
        "nested_object": {
            "nested_string": "nested value",
            "nested_number": 100
        }
    }
    
    result = collection.insert_one(mixed_document)
    print(f"✓ Document with mixed data types inserted: {result.inserted_id}")
    
    # Display the inserted document
    inserted_doc = collection.find_one({"_id": result.inserted_id})
    print("\nInserted document:")
    for key, value in inserted_doc.items():
        print(f"  {key}: {value} (type: {type(value).__name__})")


def bulk_insert_example(db):
    """
    Example of bulk insert operations.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Bulk Insert Example")
    print("=" * 50)
    
    collection = db["bulk_data"]
    
    # Generate bulk data
    bulk_documents = []
    for i in range(100):
        bulk_documents.append({
            "index": i,
            "name": f"Item {i}",
            "value": i * 10,
            "timestamp": datetime.now()
        })
    
    # Insert in batches
    batch_size = 50
    total_inserted = 0
    
    for i in range(0, len(bulk_documents), batch_size):
        batch = bulk_documents[i:i + batch_size]
        result = collection.insert_many(batch)
        total_inserted += len(result.inserted_ids)
        print(f"  Inserted batch {i // batch_size + 1}: {len(result.inserted_ids)} documents")
    
    print(f"\n✓ Total documents inserted: {total_inserted}")


# Main execution
if __name__ == "__main__":
    print("=" * 50)
    print("MongoDB Python - CREATE Operations")
    print("=" * 50)
    
    client, db = connect_to_mongodb()
    
    if db:
        # Run examples
        insert_one_document(db)
        insert_many_documents(db)
        insert_document_with_nested_object(db)
        insert_with_custom_id(db)
        insert_products_example(db)
        insert_with_validation(db)
        bulk_insert_example(db)
        
        # Close connection
        client.close()
        print("\n" + "=" * 50)
        print("All CREATE operations completed!")
        print("=" * 50)

