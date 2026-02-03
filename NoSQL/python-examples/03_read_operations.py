"""
MongoDB Python Integration - READ Operations
=============================================

This module demonstrates how to query and read documents from MongoDB using PyMongo.
"""

from pymongo import MongoClient
from bson import ObjectId
from datetime import datetime
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


def find_all_documents(db):
    """
    Find all documents in a collection.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Find All Documents")
    print("=" * 50)
    
    collection = db["users"]
    
    # Find all documents
    cursor = collection.find()
    
    print(f"Total documents: {collection.count_documents({})}")
    print("\nFirst 5 documents:")
    for i, doc in enumerate(cursor.limit(5), 1):
        print(f"\n{i}. {doc.get('name', 'N/A')} - {doc.get('email', 'N/A')}")


def find_with_query(db):
    """
    Find documents with query filters.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Find with Query Filters")
    print("=" * 50)
    
    collection = db["users"]
    
    # Equality query
    print("\n1. Find users in New York:")
    ny_users = collection.find({"city": "New York"})
    for user in ny_users:
        print(f"   - {user.get('name')} ({user.get('email')})")
    
    # Comparison operators
    print("\n2. Find users older than 30:")
    older_users = collection.find({"age": {"$gt": 30}})
    for user in older_users:
        print(f"   - {user.get('name')} (Age: {user.get('age')})")
    
    # Logical operators
    print("\n3. Find active users in New York or Los Angeles:")
    active_users = collection.find({
        "$and": [
            {"isActive": True},
            {"$or": [
                {"city": "New York"},
                {"city": "Los Angeles"}
            ]}
        ]
    })
    for user in active_users:
        print(f"   - {user.get('name')} ({user.get('city')})")


def find_one_document(db):
    """
    Find a single document.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Find One Document")
    print("=" * 50)
    
    collection = db["users"]
    
    # Find first document
    first_user = collection.find_one()
    print("First user in collection:")
    pprint(first_user)
    
    # Find specific document
    print("\nFind user by email:")
    user = collection.find_one({"email": "john.doe@example.com"})
    if user:
        pprint(user)
    else:
        print("  User not found")


def find_with_projection(db):
    """
    Find documents with field projection (select specific fields).
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Find with Projection")
    print("=" * 50)
    
    collection = db["users"]
    
    # Include specific fields
    print("\n1. Include only name and email:")
    users = collection.find({}, {"name": 1, "email": 1, "_id": 0})
    for user in users.limit(5):
        print(f"   {user}")
    
    # Exclude specific fields
    print("\n2. Exclude address and contact fields:")
    users = collection.find({}, {"address": 0, "contact": 0})
    for user in users.limit(3):
        print(f"   Name: {user.get('name')}, Age: {user.get('age')}")


def find_with_sort(db):
    """
    Find documents with sorting.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Find with Sorting")
    print("=" * 50)
    
    collection = db["users"]
    
    # Sort by age ascending
    print("\n1. Users sorted by age (ascending):")
    users = collection.find().sort("age", 1).limit(5)
    for user in users:
        print(f"   {user.get('name')} - Age: {user.get('age')}")
    
    # Sort by age descending
    print("\n2. Users sorted by age (descending):")
    users = collection.find().sort("age", -1).limit(5)
    for user in users:
        print(f"   {user.get('name')} - Age: {user.get('age')}")
    
    # Sort by multiple fields
    print("\n3. Users sorted by city, then age:")
    users = collection.find().sort([("city", 1), ("age", -1)]).limit(5)
    for user in users:
        print(f"   {user.get('name')} - {user.get('city')} - Age: {user.get('age')}")


def find_with_limit_skip(db):
    """
    Find documents with limit and skip (pagination).
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Find with Limit and Skip (Pagination)")
    print("=" * 50)
    
    collection = db["users"]
    
    page_size = 3
    total_docs = collection.count_documents({})
    total_pages = (total_docs + page_size - 1) // page_size
    
    print(f"Total documents: {total_docs}")
    print(f"Page size: {page_size}")
    print(f"Total pages: {total_pages}\n")
    
    for page in range(1, min(total_pages + 1, 4)):  # Show first 3 pages
        skip = (page - 1) * page_size
        print(f"Page {page} (skip={skip}, limit={page_size}):")
        users = collection.find().skip(skip).limit(page_size)
        for user in users:
            print(f"   - {user.get('name')} ({user.get('email')})")
        print()


def find_nested_fields(db):
    """
    Find documents with nested field queries.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Find with Nested Fields")
    print("=" * 50)
    
    collection = db["users"]
    
    # Query nested field using dot notation
    print("\n1. Users in San Francisco (nested address.city):")
    users = collection.find({"address.city": "San Francisco"})
    for user in users:
        print(f"   - {user.get('name')} - {user.get('address', {}).get('city')}")
    
    # Query array elements
    print("\n2. Users with 'reading' hobby:")
    users = collection.find({"hobbies": "reading"})
    for user in users:
        print(f"   - {user.get('name')} - Hobbies: {user.get('hobbies', [])}")
    
    # Query nested array elements
    print("\n3. Users with Python skill:")
    users = collection.find({"skills.name": "Python"})
    for user in users:
        skills = user.get('skills', [])
        python_skill = next((s for s in skills if s.get('name') == 'Python'), None)
        if python_skill:
            print(f"   - {user.get('name')} - Python level: {python_skill.get('level')}")


def find_with_array_operators(db):
    """
    Find documents using array operators.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Find with Array Operators")
    print("=" * 50)
    
    collection = db["users"]
    
    # $all - all elements must be present
    print("\n1. Users with both 'reading' and 'coding' hobbies:")
    users = collection.find({"hobbies": {"$all": ["reading", "coding"]}})
    for user in users:
        print(f"   - {user.get('name')} - {user.get('hobbies', [])}")
    
    # $size - array size
    print("\n2. Users with exactly 3 hobbies:")
    users = collection.find({"hobbies": {"$size": 3}})
    for user in users:
        print(f"   - {user.get('name')} - {len(user.get('hobbies', []))} hobbies")
    
    # $elemMatch - match array element
    print("\n3. Users with expert-level skills:")
    users = collection.find({"skills": {"$elemMatch": {"level": "expert"}}})
    for user in users:
        expert_skills = [s for s in user.get('skills', []) if s.get('level') == 'expert']
        print(f"   - {user.get('name')} - Expert in: {[s.get('name') for s in expert_skills]}")


def count_documents(db):
    """
    Count documents matching a query.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Count Documents")
    print("=" * 50)
    
    collection = db["users"]
    
    # Count all documents
    total = collection.count_documents({})
    print(f"Total users: {total}")
    
    # Count with query
    active_count = collection.count_documents({"isActive": True})
    print(f"Active users: {active_count}")
    
    # Count with comparison
    older_count = collection.count_documents({"age": {"$gt": 30}})
    print(f"Users older than 30: {older_count}")
    
    # Count by city
    ny_count = collection.count_documents({"city": "New York"})
    print(f"Users in New York: {ny_count}")


def distinct_values(db):
    """
    Get distinct values for a field.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Distinct Values")
    print("=" * 50)
    
    collection = db["users"]
    
    # Get distinct cities
    cities = collection.distinct("city")
    print(f"\nDistinct cities ({len(cities)}):")
    for city in sorted(cities):
        print(f"   - {city}")
    
    # Get distinct values with query
    active_cities = collection.distinct("city", {"isActive": True})
    print(f"\nDistinct cities for active users ({len(active_cities)}):")
    for city in sorted(active_cities):
        print(f"   - {city}")


def find_products_example(db):
    """
    Example: Query products collection.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Products Query Example")
    print("=" * 50)
    
    collection = db["products"]
    
    # Find products by category
    print("\n1. Electronics products:")
    products = collection.find({"category": "Electronics"})
    for product in products:
        print(f"   - {product.get('name')} - ${product.get('price')}")
    
    # Find products with low stock
    print("\n2. Products with stock < 40:")
    products = collection.find({"stock": {"$lt": 40}})
    for product in products:
        print(f"   - {product.get('name')} - Stock: {product.get('stock')}")
    
    # Find expensive products
    print("\n3. Products over $500:")
    products = collection.find({"price": {"$gt": 500}}).sort("price", -1)
    for product in products:
        print(f"   - {product.get('name')} - ${product.get('price')}")


def complex_query_example(db):
    """
    Example of a complex query combining multiple conditions.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Complex Query Example")
    print("=" * 50)
    
    collection = db["users"]
    
    # Complex query: Active users, age 25-35, in specific cities, with certain hobbies
    query = {
        "$and": [
            {"isActive": True},
            {"age": {"$gte": 25, "$lte": 35}},
            {"$or": [
                {"city": "New York"},
                {"city": "Los Angeles"},
                {"city": "San Francisco"}
            ]},
            {"hobbies": {"$in": ["reading", "coding"]}}
        ]
    }
    
    print("\nQuery: Active users, age 25-35, in NY/LA/SF, with reading or coding hobby")
    users = collection.find(query)
    
    count = 0
    for user in users:
        count += 1
        print(f"\n{count}. {user.get('name')}")
        print(f"   Age: {user.get('age')}")
        print(f"   City: {user.get('city')}")
        print(f"   Hobbies: {user.get('hobbies', [])}")
    
    print(f"\nTotal matches: {count}")


# Main execution
if __name__ == "__main__":
    print("=" * 50)
    print("MongoDB Python - READ Operations")
    print("=" * 50)
    
    client, db = connect_to_mongodb()
    
    if db:
        # Run examples
        find_all_documents(db)
        find_with_query(db)
        find_one_document(db)
        find_with_projection(db)
        find_with_sort(db)
        find_with_limit_skip(db)
        find_nested_fields(db)
        find_with_array_operators(db)
        count_documents(db)
        distinct_values(db)
        find_products_example(db)
        complex_query_example(db)
        
        # Close connection
        client.close()
        print("\n" + "=" * 50)
        print("All READ operations completed!")
        print("=" * 50)

