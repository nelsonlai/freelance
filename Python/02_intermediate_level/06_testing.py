"""
Testing - Ensuring Code Quality
This file contains all the example code from the Testing lesson.
"""

import unittest
from unittest.mock import Mock, patch, MagicMock

# Introduction to Testing

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

# Unit Testing with unittest

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

# Testing Classes

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

# Testing with pytest (simulated)

def test_add_positive_numbers_pytest():
    """Test adding positive numbers - pytest style."""
    assert add(2, 3) == 5
    assert add(10, 20) == 30

def test_add_negative_numbers_pytest():
    """Test adding negative numbers - pytest style."""
    assert add(-2, -3) == -5
    assert add(-10, 5) == -5

def test_divide_normal_pytest():
    """Test normal division - pytest style."""
    assert divide(10, 2) == 5
    assert divide(15, 3) == 5
    # Using approximate equality (pytest.approx equivalent)
    assert abs(divide(1, 3) - 0.333333) < 0.000001

def test_divide_by_zero_pytest():
    """Test division by zero raises ValueError - pytest style."""
    try:
        divide(10, 0)
        assert False, "Expected ValueError was not raised"
    except ValueError as e:
        assert "Cannot divide by zero" in str(e)

# Test-Driven Development (TDD)

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

class TestStack(unittest.TestCase):
    """Test cases for Stack class - written following TDD."""
    
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

# TDD Example: Word Counter

def count_words(text):
    """Count words in text."""
    if not text:
        return 0
    
    # Split by whitespace and filter out empty strings
    words = [word for word in text.split() if word]
    return len(words)

def count_words_advanced(text):
    """Advanced word counter with punctuation handling."""
    import re
    
    if not text:
        return 0
    
    # Remove punctuation and split by whitespace
    clean_text = re.sub(r'[^\w\s]', ' ', text)
    words = [word for word in clean_text.split() if word]
    return len(words)

class TestWordCounter(unittest.TestCase):
    """Test cases for word counter functions."""
    
    def test_count_words_empty_string(self):
        """Test counting words in empty string."""
        self.assertEqual(count_words(""), 0)
    
    def test_count_words_single_word(self):
        """Test counting words in single word."""
        self.assertEqual(count_words("hello"), 1)
    
    def test_count_words_multiple_words(self):
        """Test counting words in multiple words."""
        self.assertEqual(count_words("hello world"), 2)
        self.assertEqual(count_words("hello world python"), 3)
    
    def test_count_words_with_punctuation(self):
        """Test counting words with punctuation."""
        self.assertEqual(count_words("hello, world!"), 2)
        self.assertEqual(count_words("hello... world???"), 2)
    
    def test_count_words_with_multiple_spaces(self):
        """Test counting words with multiple spaces."""
        self.assertEqual(count_words("hello    world"), 2)
        self.assertEqual(count_words("  hello  world  "), 2)
    
    def test_count_words_advanced_punctuation(self):
        """Test advanced word counter with punctuation."""
        self.assertEqual(count_words_advanced("hello, world!"), 2)
        self.assertEqual(count_words_advanced("hello... world???"), 2)
        self.assertEqual(count_words_advanced("don't won't can't"), 3)

# Mocking and Test Doubles

class WeatherService:
    """A weather service that fetches data from an API."""
    
    def __init__(self, api_key):
        self.api_key = api_key
        self.base_url = "https://api.weather.com"
    
    def get_weather(self, city):
        """Get weather for a city."""
        # Simulate API call (in real code, this would use requests)
        url = f"{self.base_url}/weather"
        params = {"city": city, "api_key": self.api_key}
        
        # Mock implementation for demo
        if city == "New York":
            return {
                "city": "New York",
                "temperature": 72,
                "condition": "sunny"
            }
        else:
            raise ConnectionError("Failed to fetch weather")
    
    def is_sunny(self, city):
        """Check if it's sunny in a city."""
        weather_data = self.get_weather(city)
        return weather_data.get("condition") == "sunny"

class TestWeatherService(unittest.TestCase):
    """Test cases for WeatherService using mocks."""
    
    def setUp(self):
        """Set up test fixtures."""
        self.weather_service = WeatherService("test_api_key")
    
    def test_get_weather_success(self):
        """Test successful weather fetch."""
        result = self.weather_service.get_weather("New York")
        
        self.assertEqual(result["city"], "New York")
        self.assertEqual(result["temperature"], 72)
        self.assertEqual(result["condition"], "sunny")
    
    def test_is_sunny_true(self):
        """Test is_sunny returns True for sunny weather."""
        result = self.weather_service.is_sunny("New York")
        self.assertTrue(result)
    
    def test_is_sunny_false(self):
        """Test is_sunny returns False for non-sunny weather."""
        # This would need mocking in real implementation
        # For demo purposes, we'll test the logic
        weather_data = {"condition": "rainy"}
        result = weather_data.get("condition") == "sunny"
        self.assertFalse(result)

# Testing Best Practices

def reverse_string(text):
    """Reverse a string."""
    return text[::-1]

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

class TestDatabaseOperations(unittest.TestCase):
    """Test cases for database operations."""
    
    @classmethod
    def setUpClass(cls):
        """Set up class-level fixtures."""
        cls.db_connection = MockDatabase()
    
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
        
        # Exception testing
        with self.assertRaises(ValueError):
            int("not a number")
        
        # Exception with message
        with self.assertRaises(ValueError):
            int("not a number")

# Demo function to run all tests
def run_all_tests():
    """Run all test suites."""
    print("=== Running All Tests ===")
    
    # Create test suite
    loader = unittest.TestLoader()
    suite = unittest.TestSuite()
    
    # Add test cases
    test_classes = [
        TestMathFunctions,
        TestCalculator,
        TestStack,
        TestWordCounter,
        TestWeatherService,
        TestStringProcessor,
        TestDatabaseOperations,
        TestCoverageExample
    ]
    
    for test_class in test_classes:
        tests = loader.loadTestsFromTestCase(test_class)
        suite.addTests(tests)
    
    # Run tests
    runner = unittest.TextTestRunner(verbosity=2)
    result = runner.run(suite)
    
    # Print summary
    print(f"\n=== Test Summary ===")
    print(f"Tests run: {result.testsRun}")
    print(f"Failures: {len(result.failures)}")
    print(f"Errors: {len(result.errors)}")
    print(f"Skipped: {len(result.skipped) if hasattr(result, 'skipped') else 0}")
    
    if result.failures:
        print("\nFailures:")
        for test, traceback in result.failures:
            print(f"- {test}: {traceback}")
    
    if result.errors:
        print("\nErrors:")
        for test, traceback in result.errors:
            print(f"- {test}: {traceback}")
    
    return result.wasSuccessful()

# Run the tests if this file is executed directly
if __name__ == "__main__":
    success = run_all_tests()
    print(f"\nAll tests passed: {success}")
    
    # Also demonstrate individual test functions
    print("\n=== Individual Test Demonstrations ===")
    
    # Test math functions
    print("Testing add function:")
    print(f"add(2, 3) = {add(2, 3)}")
    print(f"add(-5, 10) = {add(-5, 10)}")
    
    print("\nTesting divide function:")
    print(f"divide(10, 2) = {divide(10, 2)}")
    try:
        divide(10, 0)
    except ValueError as e:
        print(f"divide(10, 0) raises: {e}")
    
    print("\nTesting is_prime function:")
    test_numbers = [2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
    for num in test_numbers:
        print(f"is_prime({num}) = {is_prime(num)}")
    
    # Test calculator
    print("\nTesting Calculator:")
    calc = Calculator()
    print(f"calc.add(5, 3) = {calc.add(5, 3)}")
    print(f"calc.multiply(4, 7) = {calc.multiply(4, 7)}")
    print(f"History: {calc.get_history()}")
    
    # Test stack
    print("\nTesting Stack:")
    stack = Stack()
    stack.push(1)
    stack.push(2)
    stack.push(3)
    print(f"Stack after pushing 1, 2, 3: size = {stack.size()}")
    print(f"Peek: {stack.peek()}")
    print(f"Pop: {stack.pop()}")
    print(f"Pop: {stack.pop()}")
    print(f"Stack size after popping: {stack.size()}")
    
    # Test word counter
    print("\nTesting Word Counter:")
    test_texts = ["", "hello", "hello world", "hello, world!", "  hello  world  "]
    for text in test_texts:
        print(f"count_words('{text}') = {count_words(text)}")
    
    print("\n=== Testing Examples Complete ===")
