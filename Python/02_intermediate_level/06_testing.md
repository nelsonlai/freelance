# 6. Testing - Ensuring Code Quality

Testing is crucial for ensuring code reliability and preventing bugs. This lesson covers unit testing, testing frameworks, test-driven development, and best practices for writing effective tests.

## Introduction to Testing

### Why Test Your Code?

Testing helps you:
- Catch bugs before they reach production
- Refactor code with confidence
- Document how your code should behave
- Ensure new changes don't break existing functionality
- Improve code design and architecture

### Types of Testing

1. **Unit Testing** - Testing individual functions or methods
2. **Integration Testing** - Testing how components work together
3. **System Testing** - Testing the complete system
4. **Acceptance Testing** - Testing from user perspective

## Unit Testing with unittest

### Basic Unit Testing

```python
import unittest

def add(a, b):
    """Add two numbers."""
    return a + b

def divide(a, b):
    """Divide a by b."""
    if b == 0:
        raise ValueError("Cannot divide by zero")
    return a / b

def is_prime(n):
    """Check if a number is prime."""
    if n < 2:
        return False
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            return False
    return True

class TestMathFunctions(unittest.TestCase):
    """Test cases for math functions."""
    
    def test_add_positive_numbers(self):
        """Test adding positive numbers."""
        self.assertEqual(add(2, 3), 5)
        self.assertEqual(add(10, 20), 30)
    
    def test_add_negative_numbers(self):
        """Test adding negative numbers."""
        self.assertEqual(add(-2, -3), -5)
        self.assertEqual(add(-10, 5), -5)
    
    def test_add_zero(self):
        """Test adding with zero."""
        self.assertEqual(add(5, 0), 5)
        self.assertEqual(add(0, 0), 0)
    
    def test_divide_normal(self):
        """Test normal division."""
        self.assertEqual(divide(10, 2), 5)
        self.assertEqual(divide(15, 3), 5)
        self.assertAlmostEqual(divide(1, 3), 0.333333, places=5)
    
    def test_divide_by_zero(self):
        """Test division by zero raises ValueError."""
        with self.assertRaises(ValueError):
            divide(10, 0)
        with self.assertRaises(ValueError):
            divide(0, 0)
    
    def test_is_prime_true(self):
        """Test prime numbers return True."""
        primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
        for prime in primes:
            with self.subTest(prime=prime):
                self.assertTrue(is_prime(prime))
    
    def test_is_prime_false(self):
        """Test non-prime numbers return False."""
        non_primes = [1, 4, 6, 8, 9, 10, 12, 14, 15, 16]
        for non_prime in non_primes:
            with self.subTest(non_prime=non_prime):
                self.assertFalse(is_prime(non_prime))
    
    def test_is_prime_edge_cases(self):
        """Test edge cases for prime function."""
        self.assertFalse(is_prime(0))
        self.assertFalse(is_prime(1))
        self.assertFalse(is_prime(-5))

# Running the tests
if __name__ == "__main__":
    unittest.main()
```

### Testing Classes

```python
class Calculator:
    """A simple calculator class."""
    
    def __init__(self):
        self.history = []
    
    def add(self, a, b):
        """Add two numbers."""
        result = a + b
        self.history.append(f"{a} + {b} = {result}")
        return result
    
    def subtract(self, a, b):
        """Subtract b from a."""
        result = a - b
        self.history.append(f"{a} - {b} = {result}")
        return result
    
    def multiply(self, a, b):
        """Multiply two numbers."""
        result = a * b
        self.history.append(f"{a} * {b} = {result}")
        return result
    
    def divide(self, a, b):
        """Divide a by b."""
        if b == 0:
            raise ValueError("Cannot divide by zero")
        result = a / b
        self.history.append(f"{a} / {b} = {result}")
        return result
    
    def clear_history(self):
        """Clear calculation history."""
        self.history = []
    
    def get_history(self):
        """Get calculation history."""
        return self.history.copy()

class TestCalculator(unittest.TestCase):
    """Test cases for Calculator class."""
    
    def setUp(self):
        """Set up test fixtures before each test method."""
        self.calculator = Calculator()
    
    def tearDown(self):
        """Clean up after each test method."""
        self.calculator.clear_history()
    
    def test_add(self):
        """Test addition."""
        result = self.calculator.add(5, 3)
        self.assertEqual(result, 8)
        self.assertIn("5 + 3 = 8", self.calculator.get_history())
    
    def test_subtract(self):
        """Test subtraction."""
        result = self.calculator.subtract(10, 4)
        self.assertEqual(result, 6)
        self.assertIn("10 - 4 = 6", self.calculator.get_history())
    
    def test_multiply(self):
        """Test multiplication."""
        result = self.calculator.multiply(4, 7)
        self.assertEqual(result, 28)
        self.assertIn("4 * 7 = 28", self.calculator.get_history())
    
    def test_divide(self):
        """Test division."""
        result = self.calculator.divide(15, 3)
        self.assertEqual(result, 5)
        self.assertIn("15 / 3 = 5.0", self.calculator.get_history())
    
    def test_divide_by_zero(self):
        """Test division by zero."""
        with self.assertRaises(ValueError):
            self.calculator.divide(10, 0)
    
    def test_history(self):
        """Test calculation history."""
        self.calculator.add(1, 2)
        self.calculator.subtract(5, 3)
        self.calculator.multiply(4, 6)
        
        history = self.calculator.get_history()
        self.assertEqual(len(history), 3)
        self.assertIn("1 + 2 = 3", history)
        self.assertIn("5 - 3 = 2", history)
        self.assertIn("4 * 6 = 24", history)
    
    def test_clear_history(self):
        """Test clearing history."""
        self.calculator.add(1, 2)
        self.calculator.subtract(5, 3)
        
        self.assertEqual(len(self.calculator.get_history()), 2)
        
        self.calculator.clear_history()
        self.assertEqual(len(self.calculator.get_history()), 0)

# Run the calculator tests
if __name__ == "__main__":
    unittest.main()
```

## Testing with pytest

### Installing and Using pytest

```bash
# Install pytest
pip install pytest

# Run tests
pytest test_file.py
pytest test_file.py::TestClass::test_method  # Run specific test
pytest -v  # Verbose output
pytest -k "test_add"  # Run tests matching pattern
```

### pytest Examples

```python
import pytest

def add(a, b):
    """Add two numbers."""
    return a + b

def divide(a, b):
    """Divide a by b."""
    if b == 0:
        raise ValueError("Cannot divide by zero")
    return a / b

class Calculator:
    """A simple calculator for pytest examples."""
    
    def __init__(self):
        self.history = []
    
    def add(self, a, b):
        result = a + b
        self.history.append(f"{a} + {b} = {result}")
        return result
    
    def multiply(self, a, b):
        result = a * b
        self.history.append(f"{a} * {b} = {result}")
        return result

# pytest test functions (no class needed)
def test_add_positive_numbers():
    """Test adding positive numbers."""
    assert add(2, 3) == 5
    assert add(10, 20) == 30

def test_add_negative_numbers():
    """Test adding negative numbers."""
    assert add(-2, -3) == -5
    assert add(-10, 5) == -5

def test_divide_normal():
    """Test normal division."""
    assert divide(10, 2) == 5
    assert divide(15, 3) == 5
    assert divide(1, 3) == pytest.approx(0.333333, rel=1e-5)

def test_divide_by_zero():
    """Test division by zero raises ValueError."""
    with pytest.raises(ValueError, match="Cannot divide by zero"):
        divide(10, 0)

# pytest fixtures
@pytest.fixture
def calculator():
    """Create a calculator instance for testing."""
    calc = Calculator()
    yield calc
    calc.history = []  # Cleanup after test

def test_calculator_add(calculator):
    """Test calculator addition."""
    result = calculator.add(5, 3)
    assert result == 8
    assert "5 + 3 = 8" in calculator.history

def test_calculator_multiply(calculator):
    """Test calculator multiplication."""
    result = calculator.multiply(4, 7)
    assert result == 28
    assert "4 * 7 = 28" in calculator.history

# Parametrized tests
@pytest.mark.parametrize("a,b,expected", [
    (2, 3, 5),
    (10, 20, 30),
    (-5, 5, 0),
    (0, 0, 0),
])
def test_add_parametrized(a, b, expected):
    """Test add function with multiple inputs."""
    assert add(a, b) == expected

@pytest.mark.parametrize("n,expected", [
    (2, True),
    (3, True),
    (4, False),
    (5, True),
    (6, False),
    (7, True),
    (8, False),
    (9, False),
    (10, False),
    (11, True),
])
def test_is_prime_parametrized(n, expected):
    """Test prime function with multiple inputs."""
    def is_prime(num):
        if num < 2:
            return False
        for i in range(2, int(num ** 0.5) + 1):
            if num % i == 0:
                return False
        return True
    
    assert is_prime(n) == expected
```

### Advanced pytest Features

```python
import pytest
import tempfile
import os

class FileManager:
    """A simple file manager for testing."""
    
    def __init__(self):
        self.files = {}
    
    def create_file(self, filename, content):
        """Create a file with content."""
        if filename in self.files:
            raise ValueError(f"File {filename} already exists")
        self.files[filename] = content
        return f"Created file: {filename}"
    
    def read_file(self, filename):
        """Read file content."""
        if filename not in self.files:
            raise FileNotFoundError(f"File {filename} not found")
        return self.files[filename]
    
    def delete_file(self, filename):
        """Delete a file."""
        if filename not in self.files:
            raise FileNotFoundError(f"File {filename} not found")
        del self.files[filename]
        return f"Deleted file: {filename}"
    
    def list_files(self):
        """List all files."""
        return list(self.files.keys())

# Fixtures with setup and teardown
@pytest.fixture
def file_manager():
    """Create a file manager for testing."""
    fm = FileManager()
    # Setup
    fm.create_file("test1.txt", "Hello World")
    fm.create_file("test2.txt", "Python Testing")
    yield fm
    # Teardown
    fm.files.clear()

# Using fixtures
def test_read_existing_file(file_manager):
    """Test reading an existing file."""
    content = file_manager.read_file("test1.txt")
    assert content == "Hello World"

def test_read_nonexistent_file(file_manager):
    """Test reading a nonexistent file."""
    with pytest.raises(FileNotFoundError):
        file_manager.read_file("nonexistent.txt")

def test_create_duplicate_file(file_manager):
    """Test creating a duplicate file."""
    with pytest.raises(ValueError):
        file_manager.create_file("test1.txt", "New content")

def test_delete_file(file_manager):
    """Test deleting a file."""
    result = file_manager.delete_file("test1.txt")
    assert result == "Deleted file: test1.txt"
    assert "test1.txt" not in file_manager.list_files()

# Temporary files
@pytest.fixture
def temp_file():
    """Create a temporary file."""
    with tempfile.NamedTemporaryFile(mode='w', delete=False) as f:
        f.write("Temporary content")
        temp_path = f.name
    
    yield temp_path
    
    # Cleanup
    os.unlink(temp_path)

def test_temp_file(temp_file):
    """Test with temporary file."""
    assert os.path.exists(temp_file)
    with open(temp_file, 'r') as f:
        content = f.read()
    assert content == "Temporary content"

# Skip and mark tests
@pytest.mark.skip(reason="Feature not implemented yet")
def test_unimplemented_feature():
    """Test for unimplemented feature."""
    assert False

@pytest.mark.slow
def test_slow_operation():
    """Test that takes a long time."""
    import time
    time.sleep(0.1)  # Simulate slow operation
    assert True

# Conditional skipping
@pytest.mark.skipif(
    not hasattr(os, 'getenv'),
    reason="os.getenv not available"
)
def test_environment_variable():
    """Test environment variable access."""
    assert os.getenv('PATH') is not None
```

## Test-Driven Development (TDD)

### TDD Cycle: Red-Green-Refactor

1. **Red** - Write a failing test
2. **Green** - Write minimal code to make test pass
3. **Refactor** - Improve code while keeping tests passing

### TDD Example: Building a Stack

```python
import unittest

# Step 1: Write failing tests (Red)
class TestStack(unittest.TestCase):
    """Test cases for Stack class - written before implementation."""
    
    def test_empty_stack_is_empty(self):
        """Test that empty stack reports as empty."""
        stack = Stack()
        self.assertTrue(stack.is_empty())
        self.assertEqual(stack.size(), 0)
    
    def test_push_increases_size(self):
        """Test that push increases stack size."""
        stack = Stack()
        stack.push(1)
        self.assertFalse(stack.is_empty())
        self.assertEqual(stack.size(), 1)
    
    def test_pop_decreases_size(self):
        """Test that pop decreases stack size."""
        stack = Stack()
        stack.push(1)
        stack.push(2)
        self.assertEqual(stack.size(), 2)
        
        item = stack.pop()
        self.assertEqual(item, 2)
        self.assertEqual(stack.size(), 1)
    
    def test_pop_empty_stack_raises_error(self):
        """Test that popping empty stack raises error."""
        stack = Stack()
        with self.assertRaises(IndexError):
            stack.pop()
    
    def test_peek_returns_top_item(self):
        """Test that peek returns top item without removing it."""
        stack = Stack()
        stack.push(1)
        stack.push(2)
        
        self.assertEqual(stack.peek(), 2)
        self.assertEqual(stack.size(), 2)  # Size unchanged
    
    def test_lifo_behavior(self):
        """Test Last-In-First-Out behavior."""
        stack = Stack()
        stack.push(1)
        stack.push(2)
        stack.push(3)
        
        self.assertEqual(stack.pop(), 3)
        self.assertEqual(stack.pop(), 2)
        self.assertEqual(stack.pop(), 1)
        self.assertTrue(stack.is_empty())

# Step 2: Write minimal implementation (Green)
class Stack:
    """A stack implementation following TDD."""
    
    def __init__(self):
        self.items = []
    
    def push(self, item):
        self.items.append(item)
    
    def pop(self):
        if self.is_empty():
            raise IndexError("Cannot pop from empty stack")
        return self.items.pop()
    
    def peek(self):
        if self.is_empty():
            raise IndexError("Cannot peek at empty stack")
        return self.items[-1]
    
    def is_empty(self):
        return len(self.items) == 0
    
    def size(self):
        return len(self.items)

# Step 3: Run tests to ensure they pass
if __name__ == "__main__":
    unittest.main()

# Step 4: Refactor (if needed)
# The current implementation is already clean and efficient
```

### TDD Example: Word Counter

```python
import pytest

# Step 1: Write failing tests
def test_count_words_empty_string():
    """Test counting words in empty string."""
    assert count_words("") == 0

def test_count_words_single_word():
    """Test counting words in single word."""
    assert count_words("hello") == 1

def test_count_words_multiple_words():
    """Test counting words in multiple words."""
    assert count_words("hello world") == 2
    assert count_words("hello world python") == 3

def test_count_words_with_punctuation():
    """Test counting words with punctuation."""
    assert count_words("hello, world!") == 2
    assert count_words("hello... world???") == 2

def test_count_words_with_multiple_spaces():
    """Test counting words with multiple spaces."""
    assert count_words("hello    world") == 2
    assert count_words("  hello  world  ") == 2

# Step 2: Write minimal implementation
def count_words(text):
    """Count words in text."""
    if not text:
        return 0
    
    # Split by whitespace and filter out empty strings
    words = [word for word in text.split() if word]
    return len(words)

# Step 3: Run tests to ensure they pass
# pytest will run these tests

# Step 4: Refactor and add more features
def count_words_advanced(text):
    """Advanced word counter with punctuation handling."""
    import re
    
    if not text:
        return 0
    
    # Remove punctuation and split by whitespace
    clean_text = re.sub(r'[^\w\s]', ' ', text)
    words = [word for word in clean_text.split() if word]
    return len(words)

# Additional tests for advanced version
def test_count_words_advanced_punctuation():
    """Test advanced word counter with punctuation."""
    assert count_words_advanced("hello, world!") == 2
    assert count_words_advanced("hello... world???") == 2
    assert count_words_advanced("don't won't can't") == 3
```

## Mocking and Test Doubles

### Using unittest.mock

```python
import unittest
from unittest.mock import Mock, patch, MagicMock
import requests

class WeatherService:
    """A weather service that fetches data from an API."""
    
    def __init__(self, api_key):
        self.api_key = api_key
        self.base_url = "https://api.weather.com"
    
    def get_weather(self, city):
        """Get weather for a city."""
        url = f"{self.base_url}/weather"
        params = {"city": city, "api_key": self.api_key}
        
        try:
            response = requests.get(url, params=params)
            response.raise_for_status()
            return response.json()
        except requests.RequestException as e:
            raise ConnectionError(f"Failed to fetch weather: {e}")
    
    def is_sunny(self, city):
        """Check if it's sunny in a city."""
        weather_data = self.get_weather(city)
        return weather_data.get("condition") == "sunny"

class TestWeatherService(unittest.TestCase):
    """Test cases for WeatherService using mocks."""
    
    def setUp(self):
        """Set up test fixtures."""
        self.weather_service = WeatherService("test_api_key")
    
    @patch('requests.get')
    def test_get_weather_success(self, mock_get):
        """Test successful weather fetch."""
        # Mock the response
        mock_response = Mock()
        mock_response.json.return_value = {
            "city": "New York",
            "temperature": 72,
            "condition": "sunny"
        }
        mock_response.raise_for_status.return_value = None
        mock_get.return_value = mock_response
        
        # Test the method
        result = self.weather_service.get_weather("New York")
        
        # Verify the result
        self.assertEqual(result["city"], "New York")
        self.assertEqual(result["temperature"], 72)
        self.assertEqual(result["condition"], "sunny")
        
        # Verify the mock was called correctly
        mock_get.assert_called_once_with(
            "https://api.weather.com/weather",
            params={"city": "New York", "api_key": "test_api_key"}
        )
    
    @patch('requests.get')
    def test_get_weather_connection_error(self, mock_get):
        """Test weather fetch with connection error."""
        # Mock the exception
        mock_get.side_effect = requests.ConnectionError("Network error")
        
        # Test that the exception is properly handled
        with self.assertRaises(ConnectionError) as context:
            self.weather_service.get_weather("New York")
        
        self.assertIn("Failed to fetch weather", str(context.exception))
    
    @patch.object(WeatherService, 'get_weather')
    def test_is_sunny_true(self, mock_get_weather):
        """Test is_sunny returns True for sunny weather."""
        # Mock the weather data
        mock_get_weather.return_value = {"condition": "sunny"}
        
        # Test the method
        result = self.weather_service.is_sunny("New York")
        
        # Verify the result
        self.assertTrue(result)
        mock_get_weather.assert_called_once_with("New York")
    
    @patch.object(WeatherService, 'get_weather')
    def test_is_sunny_false(self, mock_get_weather):
        """Test is_sunny returns False for non-sunny weather."""
        # Mock the weather data
        mock_get_weather.return_value = {"condition": "rainy"}
        
        # Test the method
        result = self.weather_service.is_sunny("New York")
        
        # Verify the result
        self.assertFalse(result)

# Run the tests
if __name__ == "__main__":
    unittest.main()
```

## Testing Best Practices

### Test Organization and Naming

```python
import unittest

class TestStringProcessor(unittest.TestCase):
    """Test cases for string processing functions."""
    
    def test_reverse_string_empty(self):
        """Test reversing an empty string."""
        result = reverse_string("")
        self.assertEqual(result, "")
    
    def test_reverse_string_single_character(self):
        """Test reversing a single character."""
        result = reverse_string("a")
        self.assertEqual(result, "a")
    
    def test_reverse_string_normal(self):
        """Test reversing a normal string."""
        result = reverse_string("hello")
        self.assertEqual(result, "olleh")
    
    def test_reverse_string_with_spaces(self):
        """Test reversing a string with spaces."""
        result = reverse_string("hello world")
        self.assertEqual(result, "dlrow olleh")

def reverse_string(text):
    """Reverse a string."""
    return text[::-1]

# Test fixtures and setup
class TestDatabaseOperations(unittest.TestCase):
    """Test cases for database operations."""
    
    @classmethod
    def setUpClass(cls):
        """Set up class-level fixtures."""
        cls.db_connection = create_test_database()
    
    @classmethod
    def tearDownClass(cls):
        """Clean up class-level fixtures."""
        cls.db_connection.close()
    
    def setUp(self):
        """Set up test fixtures before each test."""
        self.db_connection.clear_test_data()
        self.user_id = self.db_connection.create_test_user("test_user")
    
    def tearDown(self):
        """Clean up after each test."""
        self.db_connection.delete_user(self.user_id)
    
    def test_create_user(self):
        """Test creating a new user."""
        user_id = self.db_connection.create_user("new_user", "email@test.com")
        self.assertIsNotNone(user_id)
        
        user = self.db_connection.get_user(user_id)
        self.assertEqual(user["username"], "new_user")
        self.assertEqual(user["email"], "email@test.com")
    
    def test_delete_user(self):
        """Test deleting a user."""
        result = self.db_connection.delete_user(self.user_id)
        self.assertTrue(result)
        
        user = self.db_connection.get_user(self.user_id)
        self.assertIsNone(user)

# Mock database for testing
class MockDatabase:
    """Mock database for testing."""
    
    def __init__(self):
        self.users = {}
        self.next_id = 1
    
    def create_test_database(self):
        """Create a test database."""
        return self
    
    def close(self):
        """Close the database connection."""
        pass
    
    def clear_test_data(self):
        """Clear test data."""
        self.users = {}
        self.next_id = 1
    
    def create_test_user(self, username):
        """Create a test user."""
        user_id = self.next_id
        self.users[user_id] = {"id": user_id, "username": username}
        self.next_id += 1
        return user_id
    
    def create_user(self, username, email):
        """Create a new user."""
        user_id = self.next_id
        self.users[user_id] = {
            "id": user_id,
            "username": username,
            "email": email
        }
        self.next_id += 1
        return user_id
    
    def get_user(self, user_id):
        """Get a user by ID."""
        return self.users.get(user_id)
    
    def delete_user(self, user_id):
        """Delete a user."""
        if user_id in self.users:
            del self.users[user_id]
            return True
        return False

def create_test_database():
    """Create a test database."""
    return MockDatabase()

# Test coverage and assertions
class TestCoverageExample(unittest.TestCase):
    """Example showing different types of assertions."""
    
    def test_various_assertions(self):
        """Test various assertion methods."""
        # Equality
        self.assertEqual(5, 5)
        self.assertNotEqual(5, 3)
        
        # Truthiness
        self.assertTrue(True)
        self.assertFalse(False)
        
        # None
        self.assertIsNone(None)
        self.assertIsNotNone("hello")
        
        # Membership
        self.assertIn("a", "hello")
        self.assertNotIn("z", "hello")
        
        # Type checking
        self.assertIsInstance("hello", str)
        self.assertIsInstance(42, int)
        
        # Approximate equality
        self.assertAlmostEqual(0.1 + 0.2, 0.3, places=10)
        
        # Regular expressions
        import re
        self.assertRegex("hello world", r"hello \w+")
        
        # Exception testing
        with self.assertRaises(ValueError):
            int("not a number")
        
        # Exception with message
        with self.assertRaisesRegex(ValueError, "invalid literal"):
            int("not a number")

if __name__ == "__main__":
    unittest.main()
```

## Key Takeaways

1. **Testing is essential** for reliable, maintainable code
2. **unittest** is Python's built-in testing framework
3. **pytest** provides a more concise and powerful testing experience
4. **Test-Driven Development** helps design better code
5. **Mocking** allows testing components in isolation
6. **Fixtures** help set up and clean up test environments
7. **Parametrized tests** reduce code duplication
8. **Good test names** document expected behavior
9. **Test coverage** helps identify untested code
10. **Continuous testing** catches regressions early

## Next Steps

Congratulations! You've completed the Intermediate Level. You now have a solid foundation in:

- Advanced function concepts
- File handling and data persistence
- Modules and packages
- Object-oriented programming
- Advanced data structures
- Testing and quality assurance

You're ready to move to the **Advanced Level** where you'll learn about:
- Advanced OOP concepts
- Functional programming
- Concurrency and parallelism
- Data handling with pandas and NumPy
- Algorithms and problem solving
- Web development and APIs
- Databases and ORMs
- Deployment and DevOps practices

The Advanced Level will prepare you for professional Python development and specialized domains like data science, web development, and automation.
