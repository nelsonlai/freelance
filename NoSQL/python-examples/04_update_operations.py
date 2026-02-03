"""
MongoDB Python Integration - UPDATE Operations
===============================================

This module demonstrates how to update documents in MongoDB using PyMongo.
"""

from pymongo import MongoClient
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


def update_one_document(db):
    """
    Update a single document.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Update One Document")
    print("=" * 50)
    
    collection = db["users"]
    
    # Update single field using $set
    print("\n1. Update user's age:")
    result = collection.update_one(
        {"email": "john.doe@example.com"},
        {"$set": {"age": 31}}
    )
    print(f"   Matched: {result.matched_count}, Modified: {result.modified_count}")
    
    # Update multiple fields
    print("\n2. Update multiple fields:")
    result = collection.update_one(
        {"email": "john.doe@example.com"},
        {
            "$set": {
                "age": 32,
                "city": "Boston",
                "updatedAt": datetime.now()
            }
        }
    )
    print(f"   Matched: {result.matched_count}, Modified: {result.modified_count}")
    
    # Show updated document
    updated_user = collection.find_one({"email": "john.doe@example.com"})
    print("\n   Updated user:")
    print(f"   Name: {updated_user.get('name')}")
    print(f"   Age: {updated_user.get('age')}")
    print(f"   City: {updated_user.get('city')}")


def update_many_documents(db):
    """
    Update multiple documents.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Update Many Documents")
    print("=" * 50)
    
    collection = db["users"]
    
    # Update all active users
    print("\n1. Add lastLogin timestamp to all active users:")
    result = collection.update_many(
        {"isActive": True},
        {"$set": {"lastLogin": datetime.now()}}
    )
    print(f"   Matched: {result.matched_count}, Modified: {result.modified_count}")
    
    # Increment age for all users
    print("\n2. Increment age by 1 for all users:")
    result = collection.update_many(
        {},
        {"$inc": {"age": 1}}
    )
    print(f"   Matched: {result.matched_count}, Modified: {result.modified_count}")


def update_with_operators(db):
    """
    Demonstrate various update operators.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Update with Various Operators")
    print("=" * 50)
    
    collection = db["users"]
    
    # $set - Set field value
    print("\n1. $set - Set field value:")
    collection.update_one(
        {"email": "jane.smith@example.com"},
        {"$set": {"status": "premium"}}
    )
    print("   ✓ Set status field")
    
    # $unset - Remove field
    print("\n2. $unset - Remove field:")
    collection.update_one(
        {"email": "jane.smith@example.com"},
        {"$unset": {"status": ""}}
    )
    print("   ✓ Removed status field")
    
    # $inc - Increment value
    print("\n3. $inc - Increment age:")
    before = collection.find_one({"email": "jane.smith@example.com"})
    collection.update_one(
        {"email": "jane.smith@example.com"},
        {"$inc": {"age": 1}}
    )
    after = collection.find_one({"email": "jane.smith@example.com"})
    print(f"   Age: {before.get('age')} → {after.get('age')}")
    
    # $mul - Multiply value
    print("\n4. $mul - Multiply value:")
    collection.update_one(
        {"email": "jane.smith@example.com"},
        {"$mul": {"age": 0.9}}  # Decrease by 10%
    )
    print("   ✓ Multiplied age by 0.9")
    
    # $min - Set minimum value
    print("\n5. $min - Set minimum value:")
    collection.update_one(
        {"email": "jane.smith@example.com"},
        {"$min": {"age": 25}}
    )
    print("   ✓ Set minimum age to 25")
    
    # $max - Set maximum value
    print("\n6. $max - Set maximum value:")
    collection.update_one(
        {"email": "jane.smith@example.com"},
        {"$max": {"age": 50}}
    )
    print("   ✓ Set maximum age to 50")
    
    # $rename - Rename field
    print("\n7. $rename - Rename field:")
    collection.update_one(
        {"email": "jane.smith@example.com"},
        {"$rename": {"city": "location"}}
    )
    print("   ✓ Renamed 'city' to 'location'")
    
    # Rename it back
    collection.update_one(
        {"email": "jane.smith@example.com"},
        {"$rename": {"location": "city"}}
    )


def update_nested_fields(db):
    """
    Update nested fields in documents.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Update Nested Fields")
    print("=" * 50)
    
    collection = db["users"]
    
    # Update nested field using dot notation
    print("\n1. Update nested address field:")
    result = collection.update_one(
        {"email": "david.lee@example.com"},
        {"$set": {"address.city": "Oakland"}}
    )
    print(f"   Matched: {result.matched_count}, Modified: {result.modified_count}")
    
    # Update nested object
    print("\n2. Update entire nested object:")
    result = collection.update_one(
        {"email": "david.lee@example.com"},
        {"$set": {
            "address": {
                "street": "789 Pine Street",
                "city": "Berkeley",
                "state": "CA",
                "zipCode": "94704",
                "country": "USA"
            }
        }}
    )
    print(f"   Matched: {result.matched_count}, Modified: {result.modified_count}")
    
    # Show updated document
    user = collection.find_one({"email": "david.lee@example.com"})
    if user and "address" in user:
        print("\n   Updated address:")
        pprint(user["address"])


def update_arrays(db):
    """
    Update array fields in documents.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Update Arrays")
    print("=" * 50)
    
    collection = db["users"]
    
    # $push - Add element to array
    print("\n1. $push - Add hobby to array:")
    result = collection.update_one(
        {"email": "david.lee@example.com"},
        {"$push": {"hobbies": "gaming"}}
    )
    print(f"   Matched: {result.matched_count}, Modified: {result.modified_count}")
    
    # $push with $each - Add multiple elements
    print("\n2. $push with $each - Add multiple hobbies:")
    result = collection.update_one(
        {"email": "david.lee@example.com"},
        {"$push": {"hobbies": {"$each": ["photography", "hiking"]}}}
    )
    print(f"   Matched: {result.matched_count}, Modified: {result.modified_count}")
    
    # $addToSet - Add if not exists
    print("\n3. $addToSet - Add unique hobby:")
    result = collection.update_one(
        {"email": "david.lee@example.com"},
        {"$addToSet": {"hobbies": "reading"}}  # Won't add if already exists
    )
    print(f"   Matched: {result.matched_count}, Modified: {result.modified_count}")
    
    # $pop - Remove first or last element
    print("\n4. $pop - Remove last hobby:")
    result = collection.update_one(
        {"email": "david.lee@example.com"},
        {"$pop": {"hobbies": 1}}  # 1 = last, -1 = first
    )
    print(f"   Matched: {result.matched_count}, Modified: {result.modified_count}")
    
    # $pull - Remove matching elements
    print("\n5. $pull - Remove specific hobby:")
    result = collection.update_one(
        {"email": "david.lee@example.com"},
        {"$pull": {"hobbies": "gaming"}}
    )
    print(f"   Matched: {result.matched_count}, Modified: {result.modified_count}")
    
    # $pullAll - Remove multiple elements
    print("\n6. $pullAll - Remove multiple hobbies:")
    result = collection.update_one(
        {"email": "david.lee@example.com"},
        {"$pullAll": {"hobbies": ["photography", "hiking"]}}
    )
    print(f"   Matched: {result.matched_count}, Modified: {result.modified_count}")
    
    # Show updated hobbies
    user = collection.find_one({"email": "david.lee@example.com"})
    if user:
        print(f"\n   Current hobbies: {user.get('hobbies', [])}")


def update_array_elements(db):
    """
    Update specific elements in arrays.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Update Array Elements")
    print("=" * 50)
    
    collection = db["users"]
    
    # Update element at specific index
    print("\n1. Update hobby at index 0:")
    result = collection.update_one(
        {"email": "david.lee@example.com"},
        {"$set": {"hobbies.0": "programming"}}
    )
    print(f"   Matched: {result.matched_count}, Modified: {result.modified_count}")
    
    # Update matching array element using $ operator
    print("\n2. Update skill level using $ operator:")
    result = collection.update_one(
        {"email": "david.lee@example.com", "skills.name": "Python"},
        {"$set": {"skills.$.level": "expert"}}
    )
    print(f"   Matched: {result.matched_count}, Modified: {result.modified_count}")
    print("   Note: $ refers to the matched array element")
    
    # Update all array elements using $[]
    print("\n3. Update all skills with timestamp:")
    result = collection.update_one(
        {"email": "david.lee@example.com"},
        {"$set": {"skills.$[].updatedAt": datetime.now()}}
    )
    print(f"   Matched: {result.matched_count}, Modified: {result.modified_count}")
    
    # Show updated skills
    user = collection.find_one({"email": "david.lee@example.com"})
    if user and "skills" in user:
        print("\n   Updated skills:")
        for skill in user["skills"]:
            print(f"     - {skill.get('name')}: {skill.get('level')}")


def replace_document(db):
    """
    Replace an entire document.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Replace Document")
    print("=" * 50)
    
    collection = db["users"]
    
    # Get original document
    original = collection.find_one({"email": "bob.johnson@example.com"})
    if not original:
        print("   User not found")
        return
    
    print("\n1. Original document:")
    print(f"   Name: {original.get('name')}")
    print(f"   Age: {original.get('age')}")
    print(f"   City: {original.get('city')}")
    
    # Replace document (keeps _id)
    new_document = {
        "name": "Bob Johnson",
        "age": 36,
        "email": "bob.johnson@example.com",
        "city": "Seattle",
        "isActive": True,
        "role": "admin",
        "updatedAt": datetime.now()
    }
    
    result = collection.replace_one(
        {"email": "bob.johnson@example.com"},
        new_document
    )
    
    print(f"\n2. Replacement result:")
    print(f"   Matched: {result.matched_count}, Modified: {result.modified_count}")
    
    # Show replaced document
    replaced = collection.find_one({"email": "bob.johnson@example.com"})
    print("\n3. Replaced document:")
    pprint(replaced)


def upsert_operation(db):
    """
    Upsert operation (update if exists, insert if not).
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Upsert Operation")
    print("=" * 50)
    
    collection = db["users"]
    
    # Upsert - will insert if doesn't exist
    print("\n1. Upsert new user (will insert):")
    result = collection.update_one(
        {"email": "newuser@example.com"},
        {
            "$set": {
                "name": "New User",
                "age": 25,
                "email": "newuser@example.com",
                "city": "Portland",
                "isActive": True,
                "createdAt": datetime.now()
            }
        },
        upsert=True
    )
    print(f"   Matched: {result.matched_count}")
    print(f"   Modified: {result.modified_count}")
    print(f"   Upserted ID: {result.upserted_id}")
    
    # Upsert - will update if exists
    print("\n2. Upsert existing user (will update):")
    result = collection.update_one(
        {"email": "newuser@example.com"},
        {
            "$set": {
                "age": 26,
                "updatedAt": datetime.now()
            }
        },
        upsert=True
    )
    print(f"   Matched: {result.matched_count}")
    print(f"   Modified: {result.modified_count}")
    print(f"   Upserted ID: {result.upserted_id}")


def update_products_example(db):
    """
    Example: Update products collection.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Update Products Example")
    print("=" * 50)
    
    collection = db["products"]
    
    # Update product price
    print("\n1. Increase laptop price by 10%:")
    result = collection.update_one(
        {"name": "Laptop"},
        {"$mul": {"price": 1.1}}
    )
    print(f"   Matched: {result.matched_count}, Modified: {result.modified_count}")
    
    # Update stock for all electronics
    print("\n2. Decrease stock by 5 for all electronics:")
    result = collection.update_many(
        {"category": "Electronics"},
        {"$inc": {"stock": -5}}
    )
    print(f"   Matched: {result.matched_count}, Modified: {result.modified_count}")
    
    # Add discount field
    print("\n3. Add discount to products over $500:")
    result = collection.update_many(
        {"price": {"$gt": 500}},
        {"$set": {"discount": 0.15}}
    )
    print(f"   Matched: {result.matched_count}, Modified: {result.modified_count}")
    
    # Show updated products
    print("\n4. Updated products:")
    products = collection.find({"price": {"$gt": 500}})
    for product in products:
        print(f"   - {product.get('name')}: ${product.get('price'):.2f} (Discount: {product.get('discount', 0)})")


def find_one_and_update(db):
    """
    Find and update a document, return the document.
    
    Args:
        db: Database object
    """
    print("\n" + "=" * 50)
    print("Find One and Update")
    print("=" * 50)
    
    collection = db["users"]
    
    # Find and update, return original
    print("\n1. Find and update (return original):")
    original = collection.find_one_and_update(
        {"email": "alice.williams@example.com"},
        {"$set": {"status": "premium"}},
        return_document=False  # Return original document
    )
    print(f"   Original status: {original.get('status', 'N/A')}")
    
    # Find and update, return updated
    print("\n2. Find and update (return updated):")
    updated = collection.find_one_and_update(
        {"email": "alice.williams@example.com"},
        {"$set": {"status": "vip"}},
        return_document=True  # Return updated document
    )
    print(f"   Updated status: {updated.get('status')}")
    
    # Find and update with sort
    print("\n3. Find and update oldest user:")
    oldest = collection.find_one_and_update(
        {},
        {"$set": {"special": True}},
        sort=[("age", -1)],  # Sort by age descending
        return_document=True
    )
    print(f"   Updated: {oldest.get('name')} (Age: {oldest.get('age')})")


# Main execution
if __name__ == "__main__":
    print("=" * 50)
    print("MongoDB Python - UPDATE Operations")
    print("=" * 50)
    
    client, db = connect_to_mongodb()
    
    if db:
        # Run examples
        update_one_document(db)
        update_many_documents(db)
        update_with_operators(db)
        update_nested_fields(db)
        update_arrays(db)
        update_array_elements(db)
        replace_document(db)
        upsert_operation(db)
        update_products_example(db)
        find_one_and_update(db)
        
        # Close connection
        client.close()
        print("\n" + "=" * 50)
        print("All UPDATE operations completed!")
        print("=" * 50)

