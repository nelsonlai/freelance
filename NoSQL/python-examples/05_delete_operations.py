"""
MongoDB Python Integration - DELETE Operations
==============================================

This module demonstrates how to delete documents from MongoDB using PyMongo.
"""

from pymongo import MongoClient
from pprint import pprint


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


def delete_one_document(db):
    """
    Delete a single document.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Delete One Document")
    print("=" * 50)
    
    collection = db["users"]
    
    # Count before deletion
    before_count = collection.count_documents({})
    print(f"\nDocuments before deletion: {before_count}")
    
    # Delete one document
    print("\n1. Delete user by email:")
    result = collection.delete_one({"email": "newuser@example.com"})
    print(f"   Deleted: {result.deleted_count} document(s)")
    print(f"   Acknowledged: {result.acknowledged}")
    
    # Count after deletion
    after_count = collection.count_documents({})
    print(f"\nDocuments after deletion: {after_count}")
    
    # Delete by _id
    print("\n2. Delete user by _id:")
    # First, find a user to delete
    user_to_delete = collection.find_one({"email": "charlie.brown@example.com"})
    if user_to_delete:
        result = collection.delete_one({"_id": user_to_delete["_id"]})
        print(f"   Deleted: {result.deleted_count} document(s)")
        print(f"   Deleted user: {user_to_delete.get('name')}")


def delete_many_documents(db):
    """
    Delete multiple documents.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Delete Many Documents")
    print("=" * 50)
    
    collection = db["users"]
    
    # Count before deletion
    before_count = collection.count_documents({})
    print(f"\nDocuments before deletion: {before_count}")
    
    # Delete all inactive users
    print("\n1. Delete all inactive users:")
    result = collection.delete_many({"isActive": False})
    print(f"   Deleted: {result.deleted_count} document(s)")
    print(f"   Acknowledged: {result.acknowledged}")
    
    # Count after deletion
    after_count = collection.count_documents({})
    print(f"\nDocuments after deletion: {after_count}")
    
    # Delete users older than a certain age
    print("\n2. Delete users older than 45:")
    result = collection.delete_many({"age": {"$gt": 45}})
    print(f"   Deleted: {result.deleted_count} document(s)")
    
    # Delete users in specific city
    print("\n3. Delete users in Seattle:")
    result = collection.delete_many({"city": "Seattle"})
    print(f"   Deleted: {result.deleted_count} document(s)")


def delete_all_documents(db):
    """
    Delete all documents from a collection (be careful!).
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Delete All Documents (Example)")
    print("=" * 50)
    
    # Create a test collection for demonstration
    collection = db["test_delete"]
    
    # Insert some test documents
    collection.insert_many([
        {"name": "Test User 1", "value": 1},
        {"name": "Test User 2", "value": 2},
        {"name": "Test User 3", "value": 3}
    ])
    
    print(f"\nDocuments before deletion: {collection.count_documents({})}")
    
    # Delete all documents
    print("\nDeleting all documents...")
    result = collection.delete_many({})
    print(f"   Deleted: {result.deleted_count} document(s)")
    
    print(f"\nDocuments after deletion: {collection.count_documents({})}")
    
    # Drop the test collection
    collection.drop()
    print("\n✓ Test collection dropped")


def find_one_and_delete(db):
    """
    Find and delete a document, return the deleted document.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Find One and Delete")
    print("=" * 50)
    
    collection = db["users"]
    
    # Find and delete, return deleted document
    print("\n1. Find and delete user:")
    deleted_user = collection.find_one_and_delete({"email": "emma.davis@example.com"})
    
    if deleted_user:
        print(f"   Deleted user: {deleted_user.get('name')}")
        print(f"   Email: {deleted_user.get('email')}")
    else:
        print("   No user found to delete")
    
    # Find and delete with sort
    print("\n2. Find and delete oldest user:")
    oldest_user = collection.find_one_and_delete(
        {},
        sort=[("age", -1)]  # Sort by age descending
    )
    
    if oldest_user:
        print(f"   Deleted oldest user: {oldest_user.get('name')}")
        print(f"   Age: {oldest_user.get('age')}")
    else:
        print("   No user found to delete")


def delete_with_conditions(db):
    """
    Delete documents with various conditions.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Delete with Conditions")
    print("=" * 50)
    
    collection = db["users"]
    
    # Delete with multiple conditions
    print("\n1. Delete users with specific conditions:")
    result = collection.delete_many({
        "$and": [
            {"age": {"$lt": 25}},
            {"isActive": False}
        ]
    })
    print(f"   Deleted: {result.deleted_count} document(s)")
    
    # Delete users not in specific cities
    print("\n2. Delete users not in major cities:")
    result = collection.delete_many({
        "city": {"$nin": ["New York", "Los Angeles", "Chicago", "San Francisco"]}
    })
    print(f"   Deleted: {result.deleted_count} document(s)")
    
    # Delete users without email
    print("\n3. Delete users without email field:")
    result = collection.delete_many({"email": {"$exists": False}})
    print(f"   Deleted: {result.deleted_count} document(s)")


def delete_products_example(db):
    """
    Example: Delete products from products collection.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Delete Products Example")
    print("=" * 50)
    
    collection = db["products"]
    
    # Count before deletion
    before_count = collection.count_documents({})
    print(f"\nProducts before deletion: {before_count}")
    
    # Delete products with low stock
    print("\n1. Delete products with stock < 20:")
    result = collection.delete_many({"stock": {"$lt": 20}})
    print(f"   Deleted: {result.deleted_count} product(s)")
    
    # Delete products in specific category
    print("\n2. Delete all furniture products:")
    result = collection.delete_many({"category": "Furniture"})
    print(f"   Deleted: {result.deleted_count} product(s)")
    
    # Count after deletion
    after_count = collection.count_documents({})
    print(f"\nProducts after deletion: {after_count}")


def delete_collection(db):
    """
    Delete an entire collection.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Delete Collection")
    print("=" * 50)
    
    # Create a test collection
    test_collection = db["test_collection"]
    test_collection.insert_many([
        {"name": "Item 1"},
        {"name": "Item 2"},
        {"name": "Item 3"}
    ])
    
    print(f"\nDocuments in test_collection: {test_collection.count_documents({})}")
    
    # Drop the collection
    print("\nDropping collection...")
    test_collection.drop()
    
    # Verify collection is deleted
    collections = db.list_collection_names()
    if "test_collection" in collections:
        print("   ✗ Collection still exists")
    else:
        print("   ✓ Collection successfully dropped")


def safe_delete_example(db):
    """
    Example of safe deletion with verification.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Safe Delete Example")
    print("=" * 50)
    
    collection = db["users"]
    
    # Safe delete: verify before deleting
    email_to_delete = "alice.williams@example.com"
    
    print(f"\nAttempting to delete user: {email_to_delete}")
    
    # First, check if user exists
    user = collection.find_one({"email": email_to_delete})
    
    if user:
        print(f"   Found user: {user.get('name')}")
        
        # Show user details
        print(f"   Age: {user.get('age')}")
        print(f"   City: {user.get('city')}")
        
        # Confirm deletion (in real app, ask user)
        print("\n   Proceeding with deletion...")
        result = collection.delete_one({"email": email_to_delete})
        
        if result.deleted_count > 0:
            print("   ✓ User successfully deleted")
        else:
            print("   ✗ Failed to delete user")
    else:
        print("   ✗ User not found")


def bulk_delete_example(db):
    """
    Example of bulk delete operations.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Bulk Delete Example")
    print("=" * 50)
    
    # Create test collection
    collection = db["bulk_delete_test"]
    
    # Insert test documents
    test_docs = [{"id": i, "value": i * 10} for i in range(1, 21)]
    collection.insert_many(test_docs)
    
    print(f"\nDocuments before deletion: {collection.count_documents({})}")
    
    # Delete in batches
    batch_size = 5
    total_deleted = 0
    
    print(f"\nDeleting in batches of {batch_size}...")
    
    while True:
        # Delete a batch
        result = collection.delete_many({}).limit(batch_size)
        deleted = result.deleted_count
        
        if deleted == 0:
            break
        
        total_deleted += deleted
        print(f"   Deleted batch: {deleted} documents (Total: {total_deleted})")
    
    print(f"\nTotal deleted: {total_deleted}")
    print(f"Remaining documents: {collection.count_documents({})}")
    
    # Clean up
    collection.drop()


# Main execution
if __name__ == "__main__":
    print("=" * 50)
    print("MongoDB Python - DELETE Operations")
    print("=" * 50)
    
    client, db = connect_to_mongodb()
    
    if db:
        # Run examples
        delete_one_document(db)
        delete_many_documents(db)
        delete_all_documents(db)
        find_one_and_delete(db)
        delete_with_conditions(db)
        delete_products_example(db)
        delete_collection(db)
        safe_delete_example(db)
        bulk_delete_example(db)
        
        # Close connection
        client.close()
        print("\n" + "=" * 50)
        print("All DELETE operations completed!")
        print("=" * 50)
        print("\n⚠️  Note: Some documents may have been deleted during examples.")
        print("   Run the CREATE examples again to restore test data.")

