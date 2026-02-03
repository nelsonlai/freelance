from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
from typing import List, Optional

app = FastAPI(
    title="Student Task Manager API",
    description="A simple API to learn FastAPI basics",
    version="1.0.0"
)

# Pydantic model for Data Validation
class Item(BaseModel):
    id: int
    title: str
    description: Optional[str] = None
    completed: bool = False

# In-memory "database"
db: List[Item] = []

@app.get("/", tags=["Root"])
async def read_root():
    return {"message": "Welcome to the FastAPI Lesson!"}

@app.get("/items", response_model=List[Item], tags=["Items"])
async def get_items():
    """Retrieve all items from the database"""
    return db

@app.post("/items", response_model=Item, status_code=201, tags=["Items"])
async def create_item(item: Item):
    """Create a new item with validation"""
    for existing_item in db:
        if existing_item.id == item.id:
            raise HTTPException(status_code=400, detail="Item ID already exists")
    db.append(item)
    return item

@app.get("/items/{item_id}", response_model=Item, tags=["Items"])
async def get_item(item_id: int):
    """Get a specific item by ID"""
    for item in db:
        if item.id == item_id:
            return item
    raise HTTPException(status_code=404, detail="Item not found")

@app.put("/items/{item_id}", response_model=Item, tags=["Items"])
async def update_item(item_id: int, updated_item: Item):
    """Update an existing item"""
    for index, item in enumerate(db):
        if item.id == item_id:
            db[index] = updated_item
            return updated_item
    raise HTTPException(status_code=404, detail="Item not found")

@app.delete("/items/{item_id}", tags=["Items"])
async def delete_item(item_id: int):
    """Delete an item"""
    for index, item in enumerate(db):
        if item.id == item_id:
            db.pop(index)
            return {"message": "Item deleted successfully"}
    raise HTTPException(status_code=404, detail="Item not found")
