# 1. Advanced Functions - Taking Functions to the Next Level

Building on the foundation of basic functions, this lesson explores advanced function concepts that make code more flexible, reusable, and powerful.

## Default and Keyword Arguments

### Default Parameters

```python
def greet_user(name, greeting="Hello", punctuation="!"):
    """Greet a user with customizable greeting."""
    return f"{greeting}, {name}{punctuation}"

# Using default parameters
print(greet_user("Alice"))  # Uses default greeting and punctuation
print(greet_user("Bob", "Hi"))  # Uses default punctuation
print(greet_user("Charlie", "Good morning", "."))  # All custom

# Default parameters with mutable objects (be careful!)
def add_item(item, items_list=None):
    """Add item to list, creating new list if none provided."""
    if items_list is None:
        items_list = []  # Create new list each time
    items_list.append(item)
    return items_list

# This works correctly
list1 = add_item("apple")
list2 = add_item("banana")
print(f"List1: {list1}")  # ['apple']
print(f"List2: {list2}")  # ['banana']

# Keyword-only arguments (Python 3+)
def create_profile(name, *, age, city):
    """Create profile with keyword-only arguments after *."""
    return {"name": name, "age": age, "city": city}

# This works
profile = create_profile("Alice", age=25, city="New York")
print(profile)

# This would raise an error
# profile = create_profile("Alice", 25, "New York")  # TypeError
```

### Keyword Arguments

```python
def calculate_compound_interest(principal, rate, time, compound_frequency=12):
    """Calculate compound interest with customizable frequency."""
    amount = principal * (1 + rate/compound_frequency) ** (compound_frequency * time)
    return amount - principal

# Using keyword arguments for clarity
interest1 = calculate_compound_interest(
    principal=1000,
    rate=0.05,
    time=2,
    compound_frequency=12
)

interest2 = calculate_compound_interest(
    principal=1000,
    rate=0.05,
    time=2,
    compound_frequency=4  # Quarterly compounding
)

print(f"Monthly compounding: ${interest1:.2f}")
print(f"Quarterly compounding: ${interest2:.2f}")
```

## *args and **kwargs

### *args (Arbitrary Positional Arguments)

```python
def calculate_statistics(*args):
    """Calculate basic statistics for any number of values."""
    if not args:
        return "No values provided"
    
    total = sum(args)
    count = len(args)
    average = total / count
    minimum = min(args)
    maximum = max(args)
    
    return {
        "count": count,
        "total": total,
        "average": average,
        "minimum": minimum,
        "maximum": maximum
    }

# Using *args
stats1 = calculate_statistics(1, 2, 3, 4, 5)
stats2 = calculate_statistics(10, 20, 30)
stats3 = calculate_statistics()  # Edge case

print(f"Stats 1: {stats1}")
print(f"Stats 2: {stats2}")
print(f"Stats 3: {stats3}")

# Unpacking with *args
def multiply_all(*args):
    """Multiply all provided numbers."""
    result = 1
    for num in args:
        result *= num
    return result

numbers = [2, 3, 4, 5]
result = multiply_all(*numbers)  # Unpacking the list
print(f"Result: {result}")

# Another practical example
def format_report(title, *data_points):
    """Format a report with title and variable data points."""
    report = f"=== {title} ===\n"
    for i, point in enumerate(data_points, 1):
        report += f"{i}. {point}\n"
    return report

report = format_report("Sales Report", "Q1: $100K", "Q2: $120K", "Q3: $95K")
print(report)
```

### **kwargs (Arbitrary Keyword Arguments)

```python
def create_database_record(table_name, **kwargs):
    """Create a database record with flexible fields."""
    record = {
        "table": table_name,
        "fields": kwargs,
        "created_at": "2024-01-01"  # Example timestamp
    }
    return record

# Using **kwargs
user_record = create_database_record(
    "users",
    id=1,
    name="Alice",
    email="alice@example.com",
    age=25
)

product_record = create_database_record(
    "products",
    id=101,
    name="Laptop",
    price=999.99,
    category="Electronics",
    in_stock=True
)

print(f"User record: {user_record}")
print(f"Product record: {product_record}")

# Unpacking dictionaries with **kwargs
def update_user_profile(**kwargs):
    """Update user profile with provided fields."""
    profile = {"name": "Unknown", "age": 0, "city": "Unknown"}
    profile.update(kwargs)  # Update with provided values
    return profile

existing_data = {"name": "Bob", "city": "New York"}
updated_profile = update_user_profile(**existing_data, age=30)
print(f"Updated profile: {updated_profile}")
```

### Combining *args and **kwargs

```python
def flexible_function(required_arg, *args, **kwargs):
    """Function that accepts required, positional, and keyword arguments."""
    print(f"Required argument: {required_arg}")
    print(f"Positional arguments (*args): {args}")
    print(f"Keyword arguments (**kwargs): {kwargs}")
    
    return {
        "required": required_arg,
        "positional": args,
        "keyword": kwargs
    }

# Using all types of arguments
result = flexible_function(
    "Hello",  # required
    1, 2, 3,  # *args
    name="Alice", age=25  # **kwargs
)

print(f"Function result: {result}")

# Practical example: Database query builder
def build_query(operation, table, *conditions, **options):
    """Build a database query with flexible parameters."""
    query = f"{operation.upper()} FROM {table}"
    
    if conditions:
        query += " WHERE " + " AND ".join(conditions)
    
    if options:
        if 'order_by' in options:
            query += f" ORDER BY {options['order_by']}"
        if 'limit' in options:
            query += f" LIMIT {options['limit']}"
    
    return query

# Example queries
query1 = build_query(
    "SELECT", "users",
    "age > 18", "status = 'active'",
    order_by="name", limit=10
)

query2 = build_query(
    "DELETE", "products",
    "category = 'discontinued'",
    "stock = 0"
)

print(f"Query 1: {query1}")
print(f"Query 2: {query2}")
```

## Lambda Functions

### Basic Lambda Usage

```python
# Basic lambda functions
square = lambda x: x ** 2
add = lambda x, y: x + y
is_even = lambda x: x % 2 == 0

print(f"Square of 5: {square(5)}")
print(f"Add 3 and 4: {add(3, 4)}")
print(f"Is 6 even? {is_even(6)}")

# Lambda with multiple statements (using tuples)
process = lambda x: (x * 2, x ** 2, x + 1)
result = process(5)
print(f"Process result: {result}")
```

### Lambda with Built-in Functions

```python
# Using lambda with map()
numbers = [1, 2, 3, 4, 5]
squares = list(map(lambda x: x ** 2, numbers))
doubles = list(map(lambda x: x * 2, numbers))
print(f"Squares: {squares}")
print(f"Doubles: {doubles}")

# Using lambda with filter()
even_numbers = list(filter(lambda x: x % 2 == 0, numbers))
large_numbers = list(filter(lambda x: x > 3, numbers))
print(f"Even numbers: {even_numbers}")
print(f"Numbers > 3: {large_numbers}")

# Using lambda with sorted()
students = [
    {"name": "Alice", "grade": 85, "age": 20},
    {"name": "Bob", "grade": 92, "age": 19},
    {"name": "Charlie", "grade": 78, "age": 21}
]

# Sort by grade (descending)
by_grade = sorted(students, key=lambda s: s["grade"], reverse=True)
print("Sorted by grade:", by_grade)

# Sort by age (ascending)
by_age = sorted(students, key=lambda s: s["age"])
print("Sorted by age:", by_age)

# Using lambda with reduce()
from functools import reduce
product = reduce(lambda x, y: x * y, numbers)
print(f"Product of all numbers: {product}")

# Complex lambda example
texts = ["hello world", "python programming", "data science"]
word_counts = list(map(lambda text: len(text.split()), texts))
print(f"Word counts: {word_counts}")
```

## Recursion

### Basic Recursion

```python
def factorial(n):
    """Calculate factorial using recursion."""
    # Base case
    if n <= 1:
        return 1
    # Recursive case
    return n * factorial(n - 1)

# Test factorial
for i in range(1, 6):
    print(f"{i}! = {factorial(i)}")

def fibonacci(n):
    """Calculate nth Fibonacci number using recursion."""
    # Base cases
    if n <= 0:
        return 0
    elif n == 1:
        return 1
    # Recursive case
    return fibonacci(n - 1) + fibonacci(n - 2)

# Test fibonacci (note: this is inefficient for large n)
for i in range(10):
    print(f"fibonacci({i}) = {fibonacci(i)}")

# More efficient recursive fibonacci with memoization
def fibonacci_memo(n, memo={}):
    """Calculate nth Fibonacci number with memoization."""
    if n in memo:
        return memo[n]
    
    if n <= 0:
        return 0
    elif n == 1:
        return 1
    
    memo[n] = fibonacci_memo(n - 1, memo) + fibonacci_memo(n - 2, memo)
    return memo[n]

# Test memoized fibonacci
print(f"fibonacci_memo(40) = {fibonacci_memo(40)}")
```

### Practical Recursion Examples

```python
def binary_search(arr, target, left=0, right=None):
    """Binary search using recursion."""
    if right is None:
        right = len(arr) - 1
    
    # Base case
    if left > right:
        return -1
    
    # Calculate middle index
    mid = (left + right) // 2
    
    # Base case: found target
    if arr[mid] == target:
        return mid
    
    # Recursive cases
    elif arr[mid] > target:
        return binary_search(arr, target, left, mid - 1)
    else:
        return binary_search(arr, target, mid + 1, right)

# Test binary search
sorted_numbers = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19]
target = 7
result = binary_search(sorted_numbers, target)
print(f"Binary search for {target}: index {result}")

def tower_of_hanoi(n, source, destination, auxiliary):
    """Solve Tower of Hanoi puzzle using recursion."""
    if n == 1:
        print(f"Move disk 1 from {source} to {destination}")
        return
    
    tower_of_hanoi(n - 1, source, auxiliary, destination)
    print(f"Move disk {n} from {source} to {destination}")
    tower_of_hanoi(n - 1, auxiliary, destination, source)

# Test Tower of Hanoi
print("Tower of Hanoi solution for 3 disks:")
tower_of_hanoi(3, "A", "C", "B")

def flatten_list(nested_list):
    """Flatten a nested list using recursion."""
    result = []
    for item in nested_list:
        if isinstance(item, list):
            result.extend(flatten_list(item))
        else:
            result.append(item)
    return result

# Test flattening
nested = [1, [2, 3], [4, [5, 6]], 7]
flattened = flatten_list(nested)
print(f"Nested: {nested}")
print(f"Flattened: {flattened}")
```

## Function Decorators

### Basic Decorators

```python
def timer_decorator(func):
    """Decorator to measure function execution time."""
    import time
    
    def wrapper(*args, **kwargs):
        start_time = time.time()
        result = func(*args, **kwargs)
        end_time = time.time()
        print(f"{func.__name__} took {end_time - start_time:.4f} seconds")
        return result
    
    return wrapper

# Using the decorator
@timer_decorator
def slow_function():
    """A function that takes some time to execute."""
    import time
    time.sleep(0.1)  # Simulate work
    return "Done"

result = slow_function()
print(f"Result: {result}")

def retry_decorator(max_attempts=3):
    """Decorator to retry function on failure."""
    def decorator(func):
        def wrapper(*args, **kwargs):
            last_exception = None
            
            for attempt in range(max_attempts):
                try:
                    return func(*args, **kwargs)
                except Exception as e:
                    last_exception = e
                    print(f"Attempt {attempt + 1} failed: {e}")
                    if attempt < max_attempts - 1:
                        print("Retrying...")
            
            print(f"All {max_attempts} attempts failed")
            raise last_exception
        
        return wrapper
    return decorator

# Using the retry decorator
@retry_decorator(max_attempts=3)
def unreliable_function():
    """A function that sometimes fails."""
    import random
    if random.random() < 0.7:  # 70% chance of failure
        raise ValueError("Random failure")
    return "Success!"

try:
    result = unreliable_function()
    print(f"Result: {result}")
except ValueError as e:
    print(f"Final error: {e}")
```

### Advanced Decorators

```python
def cache_decorator(func):
    """Decorator to cache function results."""
    cache = {}
    
    def wrapper(*args, **kwargs):
        # Create cache key
        key = str(args) + str(sorted(kwargs.items()))
        
        if key in cache:
            print(f"Cache hit for {func.__name__}")
            return cache[key]
        
        print(f"Cache miss for {func.__name__}")
        result = func(*args, **kwargs)
        cache[key] = result
        return result
    
    return wrapper

# Using cache decorator
@cache_decorator
def expensive_calculation(n):
    """Simulate an expensive calculation."""
    import time
    time.sleep(0.1)  # Simulate work
    return n ** 2

# First call (cache miss)
result1 = expensive_calculation(5)
print(f"Result 1: {result1}")

# Second call (cache hit)
result2 = expensive_calculation(5)
print(f"Result 2: {result2}")

def validation_decorator(validate_func):
    """Decorator for input validation."""
    def decorator(func):
        def wrapper(*args, **kwargs):
            # Validate inputs
            if not validate_func(*args, **kwargs):
                raise ValueError("Input validation failed")
            
            return func(*args, **kwargs)
        return wrapper
    return decorator

# Validation function
def validate_positive_numbers(*args, **kwargs):
    """Validate that all numeric arguments are positive."""
    for arg in args:
        if isinstance(arg, (int, float)) and arg <= 0:
            return False
    for value in kwargs.values():
        if isinstance(value, (int, float)) and value <= 0:
            return False
    return True

# Using validation decorator
@validation_decorator(validate_positive_numbers)
def divide_positive_numbers(a, b):
    """Divide two positive numbers."""
    return a / b

# This will work
try:
    result = divide_positive_numbers(10, 2)
    print(f"Division result: {result}")
except ValueError as e:
    print(f"Error: {e}")

# This will fail validation
try:
    result = divide_positive_numbers(-5, 2)
    print(f"Division result: {result}")
except ValueError as e:
    print(f"Error: {e}")
```

## Practical Examples

### Example 1: Data Processing Pipeline

```python
def data_processing_pipeline():
    """A flexible data processing pipeline using advanced functions."""
    
    def process_numbers(*args, operation="sum", **options):
        """Process numbers with various operations."""
        if not args:
            return "No numbers provided"
        
        numbers = list(args)
        
        # Apply filters if specified
        if 'min_value' in options:
            numbers = [n for n in numbers if n >= options['min_value']]
        if 'max_value' in options:
            numbers = [n for n in numbers if n <= options['max_value']]
        
        # Apply operation
        if operation == "sum":
            result = sum(numbers)
        elif operation == "product":
            result = 1
            for n in numbers:
                result *= n
        elif operation == "average":
            result = sum(numbers) / len(numbers)
        elif operation == "max":
            result = max(numbers)
        elif operation == "min":
            result = min(numbers)
        else:
            return f"Unknown operation: {operation}"
        
        # Apply transformations if specified
        if 'round_to' in options:
            result = round(result, options['round_to'])
        
        return result
    
    # Test the pipeline
    numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    
    # Basic operations
    print(f"Sum: {process_numbers(*numbers, operation='sum')}")
    print(f"Average: {process_numbers(*numbers, operation='average')}")
    print(f"Product: {process_numbers(*numbers, operation='product')}")
    
    # With filters
    print(f"Sum of numbers >= 5: {process_numbers(*numbers, operation='sum', min_value=5)}")
    print(f"Average of numbers <= 7: {process_numbers(*numbers, operation='average', max_value=7)}")
    
    # With rounding
    print(f"Average rounded to 2 decimal places: {process_numbers(*numbers, operation='average', round_to=2)}")

# Run the example
data_processing_pipeline()
```

### Example 2: Function Composition and Higher-Order Functions

```python
def function_composition_examples():
    """Examples of function composition and higher-order functions."""
    
    def compose(f, g):
        """Compose two functions: compose(f, g)(x) = f(g(x))"""
        return lambda x: f(g(x))
    
    def pipe(*functions):
        """Pipe data through multiple functions."""
        def apply_functions(x):
            result = x
            for func in functions:
                result = func(result)
            return result
        return apply_functions
    
    # Define some simple functions
    add_one = lambda x: x + 1
    multiply_by_two = lambda x: x * 2
    square = lambda x: x ** 2
    
    # Compose functions
    add_one_then_square = compose(square, add_one)
    square_then_add_one = compose(add_one, square)
    
    print(f"add_one_then_square(3): {add_one_then_square(3)}")  # (3+1)² = 16
    print(f"square_then_add_one(3): {square_then_add_one(3)}")  # 3²+1 = 10
    
    # Pipe functions
    process = pipe(add_one, multiply_by_two, square)
    result = process(3)  # ((3+1)*2)² = 64
    print(f"Pipe result: {result}")
    
    # Higher-order function for creating transformers
    def create_transformer(*operations):
        """Create a transformer function from a list of operations."""
        def transform(data):
            if isinstance(data, (list, tuple)):
                return [apply_operations(item) for item in data]
            else:
                return apply_operations(data)
        
        def apply_operations(x):
            result = x
            for operation in operations:
                result = operation(result)
            return result
        
        return transform
    
    # Create specific transformers
    number_transformer = create_transformer(lambda x: x + 1, lambda x: x * 2)
    string_transformer = create_transformer(str.upper, lambda x: x + "!")
    
    # Test transformers
    numbers = [1, 2, 3, 4, 5]
    transformed_numbers = number_transformer(numbers)
    print(f"Transformed numbers: {transformed_numbers}")
    
    words = ["hello", "world", "python"]
    transformed_words = string_transformer(words)
    print(f"Transformed words: {transformed_words}")

# Run the example
function_composition_examples()
```

## Key Takeaways

1. **Default parameters** make functions more flexible and easier to use
2. ***args** allows functions to accept any number of positional arguments
3. ****kwargs** enables functions to accept any number of keyword arguments
4. **Lambda functions** are concise for simple operations and work well with map/filter/reduce
5. **Recursion** is powerful but requires careful base case definition
6. **Decorators** add functionality to existing functions without modifying them
7. **Function composition** creates complex behavior from simple functions
8. **Higher-order functions** take or return other functions, enabling advanced patterns

## Next Steps

In the next lesson, we'll explore file handling - reading from and writing to files, working with different file formats like CSV and JSON, and managing file operations safely.
