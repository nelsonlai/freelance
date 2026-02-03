"""
MongoDB Python Integration - Advanced Operations
=================================================

This module demonstrates advanced MongoDB operations including:
- Aggregation Pipeline
- Indexes
- Text Search
- Transactions
- Bulk Operations
- GridFS (for large files)
"""

from pymongo import MongoClient, ASCENDING, DESCENDING, TEXT
from pymongo.errors import BulkWriteError, DuplicateKeyError
from datetime import datetime, timedelta
from pprint import pprint
import json


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


def aggregation_pipeline_example(db):
    """
    Demonstrate MongoDB aggregation pipeline.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Aggregation Pipeline")
    print("=" * 50)
    
    collection = db["users"]
    
    # Simple aggregation: Group by city
    print("\n1. Group users by city:")
    pipeline = [
        {
            "$group": {
                "_id": "$city",
                "totalUsers": {"$sum": 1},
                "avgAge": {"$avg": "$age"},
                "maxAge": {"$max": "$age"},
                "minAge": {"$min": "$age"}
            }
        },
        {
            "$sort": {"totalUsers": -1}
        }
    ]
    
    results = list(collection.aggregate(pipeline))
    for result in results:
        print(f"   {result['_id']}: {result['totalUsers']} users, "
              f"avg age: {result['avgAge']:.1f}")
    
    # Complex aggregation: Active users by city with age range
    print("\n2. Active users statistics by city:")
    pipeline = [
        {"$match": {"isActive": True}},
        {
            "$group": {
                "_id": "$city",
                "count": {"$sum": 1},
                "avgAge": {"$avg": "$age"},
                "users": {
                    "$push": {
                        "name": "$name",
                        "age": "$age"
                    }
                }
            }
        },
        {"$sort": {"count": -1}},
        {"$limit": 5}
    ]
    
    results = list(collection.aggregate(pipeline))
    for result in results:
        print(f"\n   City: {result['_id']}")
        print(f"   Count: {result['count']}, Avg Age: {result['avgAge']:.1f}")
    
    # Aggregation with unwind (flatten arrays)
    print("\n3. Unwind hobbies to see all hobbies:")
    pipeline = [
        {"$unwind": "$hobbies"},
        {
            "$group": {
                "_id": "$hobbies",
                "count": {"$sum": 1}
            }
        },
        {"$sort": {"count": -1}}
    ]
    
    results = list(collection.aggregate(pipeline))
    print("   Top hobbies:")
    for result in results[:5]:
        print(f"     {result['_id']}: {result['count']} users")
    
    # Aggregation with project and addFields
    print("\n4. Calculate age group:")
    pipeline = [
        {
            "$addFields": {
                "ageGroup": {
                    "$switch": {
                        "branches": [
                            {"case": {"$lt": ["$age", 25]}, "then": "Young"},
                            {"case": {"$lt": ["$age", 35]}, "then": "Adult"},
                            {"case": {"$lt": ["$age", 50]}, "then": "Middle-aged"},
                            {"case": {"$gte": ["$age", 50]}, "then": "Senior"}
                        ],
                        "default": "Unknown"
                    }
                }
            }
        },
        {
            "$group": {
                "_id": "$ageGroup",
                "count": {"$sum": 1}
            }
        },
        {"$sort": {"count": -1}}
    ]
    
    results = list(collection.aggregate(pipeline))
    print("\n   Users by age group:")
    for result in results:
        print(f"     {result['_id']}: {result['count']} users")


def index_operations(db):
    """
    Demonstrate index creation and usage.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Index Operations")
    print("=" * 50)
    
    collection = db["users"]
    
    # List existing indexes
    print("\n1. Existing indexes:")
    indexes = collection.list_indexes()
    for index in indexes:
        print(f"   {index['name']}: {index.get('key', {})}")
    
    # Create single field index
    print("\n2. Creating index on 'email' field:")
    try:
        collection.create_index("email", unique=True)
        print("   ✓ Index created on email (unique)")
    except Exception as e:
        print(f"   Note: {e}")
    
    # Create compound index
    print("\n3. Creating compound index on 'city' and 'age':")
    collection.create_index([("city", ASCENDING), ("age", DESCENDING)])
    print("   ✓ Compound index created")
    
    # Create text index
    print("\n4. Creating text index on 'name' and 'email':")
    try:
        collection.create_index([("name", TEXT), ("email", TEXT)])
        print("   ✓ Text index created")
    except Exception as e:
        print(f"   Note: {e}")
    
    # Get index information
    print("\n5. All indexes:")
    indexes = list(collection.list_indexes())
    for index in indexes:
        print(f"   {index['name']}: {index.get('key', {})}")
    
    # Explain query to see index usage
    print("\n6. Query execution plan (using index):")
    explain_result = collection.find({"email": "john.doe@example.com"}).explain()
    execution_stats = explain_result.get('executionStats', {})
    print(f"   Execution time: {execution_stats.get('executionTimeMillis', 'N/A')} ms")
    print(f"   Documents examined: {execution_stats.get('totalDocsExamined', 'N/A')}")
    print(f"   Documents returned: {execution_stats.get('nReturned', 'N/A')}")


def text_search_example(db):
    """
    Demonstrate text search functionality.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Text Search")
    print("=" * 50)
    
    collection = db["users"]
    
    # Ensure text index exists
    try:
        collection.create_index([("name", TEXT), ("email", TEXT)])
    except:
        pass  # Index might already exist
    
    # Text search
    print("\n1. Text search for 'John':")
    results = collection.find({"$text": {"$search": "John"}})
    for user in results:
        print(f"   {user.get('name')} - {user.get('email')}")
    
    # Text search with score
    print("\n2. Text search with relevance score:")
    results = collection.find(
        {"$text": {"$search": "john doe"}},
        {"score": {"$meta": "textScore"}}
    ).sort([("score", {"$meta": "textScore"})])
    
    for user in results:
        score = user.get('score', 0)
        print(f"   {user.get('name')} - Score: {score:.2f}")


def bulk_operations_example(db):
    """
    Demonstrate bulk write operations.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Bulk Operations")
    print("=" * 50)
    
    collection = db["bulk_test"]
    
    # Clear collection
    collection.delete_many({})
    
    # Prepare bulk operations
    operations = [
        # Insert operations
        {
            "insertOne": {
                "document": {"name": "Bulk User 1", "value": 1}
            }
        },
        {
            "insertOne": {
                "document": {"name": "Bulk User 2", "value": 2}
            }
        },
        # Update operations
        {
            "updateOne": {
                "filter": {"name": "Bulk User 1"},
                "update": {"$set": {"value": 10}}
            }
        },
        {
            "updateMany": {
                "filter": {"value": {"$lt": 5}},
                "update": {"$set": {"status": "active"}}
            }
        },
        # Replace operation
        {
            "replaceOne": {
                "filter": {"name": "Bulk User 2"},
                "replacement": {"name": "Bulk User 2", "value": 20, "updated": True}
            }
        },
        # Delete operation
        {
            "deleteOne": {
                "filter": {"value": {"$gt": 15}}
            }
        }
    ]
    
    print("\n1. Executing bulk write operations:")
    try:
        result = collection.bulk_write(operations, ordered=False)
        print(f"   Inserted: {result.inserted_count}")
        print(f"   Updated: {result.modified_count}")
        print(f"   Deleted: {result.deleted_count}")
        print(f"   Upserted: {result.upserted_count}")
    except BulkWriteError as e:
        print(f"   Some operations failed: {e.details}")
    
    # Show results
    print("\n2. Documents after bulk operations:")
    for doc in collection.find():
        print(f"   {doc}")


def transaction_example(db):
    """
    Demonstrate transactions (MongoDB 4.0+).
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Transactions")
    print("=" * 50)
    
    client = db.client
    
    # Start a session
    with client.start_session() as session:
        try:
            # Start transaction
            with session.start_transaction():
                users_collection = db["users"]
                accounts_collection = db["accounts"]
                
                print("\n1. Creating user and account in transaction:")
                
                # Create user
                user_result = users_collection.insert_one(
                    {
                        "name": "Transaction User",
                        "email": "transaction@example.com",
                        "createdAt": datetime.now()
                    },
                    session=session
                )
                print(f"   User created: {user_result.inserted_id}")
                
                # Create account
                account_result = accounts_collection.insert_one(
                    {
                        "userId": user_result.inserted_id,
                        "balance": 1000,
                        "createdAt": datetime.now()
                    },
                    session=session
                )
                print(f"   Account created: {account_result.inserted_id}")
                
                # Commit transaction
                session.commit_transaction()
                print("   ✓ Transaction committed")
                
        except Exception as e:
            # Abort transaction on error
            session.abort_transaction()
            print(f"   ✗ Transaction aborted: {e}")


def find_with_projection_advanced(db):
    """
    Advanced projection examples.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Advanced Projection")
    print("=" * 50)
    
    collection = db["users"]
    
    # Project with array slice
    print("\n1. Project with array slice (first 2 hobbies):")
    users = collection.find({}, {"name": 1, "hobbies": {"$slice": 2}})
    for user in users.limit(3):
        print(f"   {user.get('name')}: {user.get('hobbies', [])}")
    
    # Project with conditional
    print("\n2. Project with computed field:")
    pipeline = [
        {
            "$project": {
                "name": 1,
                "age": 1,
                "isSenior": {"$gte": ["$age", 50]},
                "ageGroup": {
                    "$cond": {
                        "if": {"$lt": ["$age", 30]},
                        "then": "Young",
                        "else": "Adult"
                    }
                }
            }
        }
    ]
    
    results = list(collection.aggregate(pipeline))
    for result in results[:3]:
        print(f"   {result.get('name')}: {result.get('ageGroup')}, "
              f"Senior: {result.get('isSenior')}")


def date_operations_example(db):
    """
    Demonstrate date operations and queries.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Date Operations")
    print("=" * 50)
    
    collection = db["users"]
    
    # Find users created in last 7 days
    print("\n1. Users created in last 7 days:")
    seven_days_ago = datetime.now() - timedelta(days=7)
    recent_users = collection.find({
        "createdAt": {"$gte": seven_days_ago}
    })
    
    count = 0
    for user in recent_users:
        count += 1
        print(f"   {user.get('name')} - {user.get('createdAt')}")
    
    if count == 0:
        print("   (No recent users found)")
    
    # Group by date (day)
    print("\n2. Users grouped by creation date:")
    pipeline = [
        {
            "$group": {
                "_id": {
                    "$dateToString": {
                        "format": "%Y-%m-%d",
                        "date": "$createdAt"
                    }
                },
                "count": {"$sum": 1}
            }
        },
        {"$sort": {"_id": -1}}
    ]
    
    results = list(collection.aggregate(pipeline))
    for result in results[:5]:
        print(f"   {result['_id']}: {result['count']} users")


def aggregation_with_lookup(db):
    """
    Demonstrate $lookup (join) in aggregation.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Aggregation with $lookup (Join)")
    print("=" * 50)
    
    # Create sample orders collection
    orders_collection = db["orders"]
    users_collection = db["users"]
    
    # Insert sample orders
    orders_collection.delete_many({})
    user = users_collection.find_one()
    if user:
        orders_collection.insert_many([
            {
                "userId": user["_id"],
                "product": "Laptop",
                "amount": 999.99,
                "date": datetime.now()
            },
            {
                "userId": user["_id"],
                "product": "Mouse",
                "amount": 29.99,
                "date": datetime.now()
            }
        ])
    
    # Lookup users for orders
    print("\n1. Orders with user information:")
    pipeline = [
        {
            "$lookup": {
                "from": "users",
                "localField": "userId",
                "foreignField": "_id",
                "as": "user"
            }
        },
        {
            "$unwind": "$user"
        },
        {
            "$project": {
                "product": 1,
                "amount": 1,
                "userName": "$user.name",
                "userEmail": "$user.email"
            }
        }
    ]
    
    results = list(orders_collection.aggregate(pipeline))
    for result in results:
        print(f"   {result.get('product')} - ${result.get('amount')} - "
              f"User: {result.get('userName')}")


# Main execution
if __name__ == "__main__":
    print("=" * 50)
    print("MongoDB Python - Advanced Operations")
    print("=" * 50)
    
    client, db = connect_to_mongodb()
    
    if db:
        # Run examples
        aggregation_pipeline_example(db)
        index_operations(db)
        text_search_example(db)
        bulk_operations_example(db)
        transaction_example(db)
        find_with_projection_advanced(db)
        date_operations_example(db)
        aggregation_with_lookup(db)
        
        # Close connection
        client.close()
        print("\n" + "=" * 50)
        print("All advanced operations completed!")
        print("=" * 50)

