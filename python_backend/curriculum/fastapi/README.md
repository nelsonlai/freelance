# Module 1: FastAPI - Modern Backend APIs

FastAPI is a modern, fast (high-performance), web framework for building APIs with Python 3.7+ based on standard Python type hints.

## Key Concepts to Learn

1.  **Type Hints & Pydantic**: How FastAPI uses Python types to validate data.
2.  **Path Operations**: GET, POST, PUT, DELETE.
3.  **Automatic Documentation**: Swagger UI (`/docs`) and ReDoc (`/redoc`).
4.  **Dependency Injection**: Managing database connections and security.
5.  **Asynchronous Programming**: Using `async` and `await` for performance.

## Lesson Plan

1.  **Hello World**: Setting up your first FastAPI app.
2.  **Path Parameters & Query Parameters**: Getting data from the URL.
3.  **Request Body**: Using Pydantic models to receive JSON.
4.  **CRUD Operations**: Building a simple "Task Manager" API.
5.  **Middleware & Exceptions**: Handling errors and logging.

## Running the Example

1. `cd curriculum/fastapi`
2. `pip install -r requirements.txt`
3. `uvicorn app.main:app --reload`
4. Open `http://127.0.0.1:8000/docs` to see the interactive documentation.
