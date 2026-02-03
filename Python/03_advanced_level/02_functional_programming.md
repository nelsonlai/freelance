# 2. Functional Programming - Elegant and Efficient Code

Functional programming is a programming paradigm that treats computation as the evaluation of mathematical functions. This lesson explores higher-order functions, closures, decorators, and functional programming techniques that make Python code more elegant and efficient.

## Understanding Functional Programming

### Core Principles

1. **Pure Functions** - Functions that don't have side effects and always return the same output for the same input
2. **Immutability** - Data doesn't change after creation
3. **Higher-Order Functions** - Functions that take other functions as arguments or return functions
4. **Function Composition** - Combining simple functions to build complex operations

### Pure Functions vs Impure Functions

```python
# Pure function - no side effects, deterministic
def pure_add(a, b):
    """Pure function that adds two numbers."""
    return a + b

def pure_square(x):
    """Pure function that squares a number."""
    return x ** 2

def pure_factorial(n):
    """Pure recursive factorial function."""
    if n <= 1:
        return 1
    return n * pure_factorial(n - 1)

# Impure function - has side effects
counter = 0

def impure_increment():
    """Impure function with side effect."""
    global counter
    counter += 1
    return counter

def impure_print_and_add(a, b):
    """Impure function that prints (side effect)."""
    result = a + b
    print(f"Adding {a} + {b} = {result}")  # Side effect
    return result

# Using pure and impure functions
print("=== Pure vs Impure Functions ===")
print(f"pure_add(5, 3): {pure_add(5, 3)}")
print(f"pure_square(4): {pure_square(4)}")
print(f"pure_factorial(5): {pure_factorial(5)}")

print(f"impure_increment(): {impure_increment()}")
print(f"impure_increment(): {impure_increment()}")
print(f"Counter value: {counter}")

result = impure_print_and_add(10, 20)
print(f"Result: {result}")
```

## Higher-Order Functions

### Functions as First-Class Objects

```python
def greet(name):
    """Simple greeting function."""
    return f"Hello, {name}!"

def goodbye(name):
    """Goodbye function."""
    return f"Goodbye, {name}!"

def create_greeting(greeting_func, name):
    """Higher-order function that takes a function as argument."""
    return greeting_func(name)

def create_multiplier(factor):
    """Higher-order function that returns a function."""
    def multiplier(number):
        return number * factor
    return multiplier

def apply_operation(operation, a, b):
    """Higher-order function that applies an operation."""
    return operation(a, b)

# Using higher-order functions
print("\n=== Higher-Order Functions ===")

# Function as argument
print(create_greeting(greet, "Alice"))
print(create_greeting(goodbye, "Bob"))

# Function as return value
double = create_multiplier(2)
triple = create_multiplier(3)
quadruple = create_multiplier(4)

print(f"double(5): {double(5)}")
print(f"triple(5): {triple(5)}")
print(f"quadruple(5): {quadruple(5)}")

# Function as argument with lambda
add = lambda x, y: x + y
multiply = lambda x, y: x * y

print(f"apply_operation(add, 10, 20): {apply_operation(add, 10, 20)}")
print(f"apply_operation(multiply, 5, 6): {apply_operation(multiply, 5, 6)}")
```

### Built-in Higher-Order Functions

```python
# Map - Apply function to every item in iterable
numbers = [1, 2, 3, 4, 5]
squares = list(map(lambda x: x ** 2, numbers))
doubles = list(map(lambda x: x * 2, numbers))

print("=== Built-in Higher-Order Functions ===")
print(f"Numbers: {numbers}")
print(f"Squares: {squares}")
print(f"Doubles: {doubles}")

# Filter - Filter items based on condition
even_numbers = list(filter(lambda x: x % 2 == 0, numbers))
positive_numbers = list(filter(lambda x: x > 0, [-2, -1, 0, 1, 2, 3]))

print(f"Even numbers: {even_numbers}")
print(f"Positive numbers: {positive_numbers}")

# Reduce - Reduce iterable to single value
from functools import reduce

sum_all = reduce(lambda x, y: x + y, numbers)
product_all = reduce(lambda x, y: x * y, numbers)
max_number = reduce(lambda x, y: x if x > y else y, numbers)

print(f"Sum of all numbers: {sum_all}")
print(f"Product of all numbers: {product_all}")
print(f"Maximum number: {max_number}")

# Sorted - Sort with custom key function
words = ["python", "programming", "functional", "code", "lambda"]
sorted_by_length = sorted(words, key=len)
sorted_alphabetically = sorted(words)

print(f"Words sorted by length: {sorted_by_length}")
print(f"Words sorted alphabetically: {sorted_alphabetically}")

# Complex sorting example
students = [
    {"name": "Alice", "grade": 85, "age": 20},
    {"name": "Bob", "grade": 92, "age": 19},
    {"name": "Charlie", "grade": 78, "age": 21},
    {"name": "Diana", "grade": 92, "age": 20}
]

# Sort by grade (descending), then by age (ascending)
sorted_students = sorted(students, key=lambda s: (-s["grade"], s["age"]))
print("Students sorted by grade (desc) then age (asc):")
for student in sorted_students:
    print(f"  {student}")
```

## Closures and Nested Functions

### Understanding Closures

```python
def outer_function(x):
    """Outer function that creates a closure."""
    def inner_function(y):
        """Inner function that captures x from outer scope."""
        return x + y
    return inner_function

def create_counter(initial_value=0):
    """Create a counter function using closure."""
    count = initial_value
    
    def counter(increment=1):
        nonlocal count
        count += increment
        return count
    
    def get_count():
        return count
    
    def reset():
        nonlocal count
        count = initial_value
        return count
    
    # Return multiple functions
    return counter, get_count, reset

def create_multiplier_table(n):
    """Create a multiplication table function using closure."""
    def multiplier(m):
        return n * m
    
    def get_table(limit=10):
        return [multiplier(i) for i in range(1, limit + 1)]
    
    return multiplier, get_table

# Using closures
print("\n=== Closures Demo ===")

# Simple closure
add_five = outer_function(5)
add_ten = outer_function(10)

print(f"add_five(3): {add_five(3)}")
print(f"add_ten(3): {add_ten(3)}")

# Counter closure
counter1, get_count1, reset1 = create_counter(0)
counter2, get_count2, reset2 = create_counter(100)

print(f"Counter1: {counter1()}")  # 1
print(f"Counter1: {counter1(5)}")  # 6
print(f"Counter1: {counter1()}")   # 7
print(f"Counter1 get_count: {get_count1()}")  # 7

print(f"Counter2: {counter2()}")   # 101
print(f"Counter2: {counter2(10)}") # 111
print(f"Counter2 get_count: {get_count2()}") # 111

# Multiplication table closure
multiply_by_3, table_3 = create_multiplier_table(3)
multiply_by_7, table_7 = create_multiplier_table(7)

print(f"3 * 5 = {multiply_by_3(5)}")
print(f"7 * 5 = {multiply_by_7(5)}")
print(f"3 times table: {table_3()}")
print(f"7 times table: {table_7()}")
```

### Advanced Closure Examples

```python
def create_validator(min_value=None, max_value=None, allowed_types=None):
    """Create a validator function using closure."""
    def validator(value):
        errors = []
        
        # Type validation
        if allowed_types and not isinstance(value, allowed_types):
            errors.append(f"Value must be of type {allowed_types}")
        
        # Range validation
        if min_value is not None and value < min_value:
            errors.append(f"Value must be >= {min_value}")
        
        if max_value is not None and value > max_value:
            errors.append(f"Value must be <= {max_value}")
        
        if errors:
            raise ValueError(f"Validation failed: {'; '.join(errors)}")
        
        return value
    
    return validator

def create_logger(level="INFO"):
    """Create a logger function using closure."""
    import datetime
    
    def log(message, log_level="INFO"):
        timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        
        if level == "DEBUG" or (level == "INFO" and log_level in ["INFO", "WARNING", "ERROR"]):
            print(f"[{timestamp}] {log_level}: {message}")
    
    return log

def create_cache(max_size=100):
    """Create a caching function using closure."""
    cache = {}
    access_order = []
    
    def cached_function(func):
        def wrapper(*args, **kwargs):
            # Create cache key
            key = str(args) + str(sorted(kwargs.items()))
            
            # Check cache
            if key in cache:
                # Move to end (most recently used)
                access_order.remove(key)
                access_order.append(key)
                return cache[key]
            
            # Compute result
            result = func(*args, **kwargs)
            
            # Add to cache
            cache[key] = result
            access_order.append(key)
            
            # Remove oldest if cache is full
            if len(cache) > max_size:
                oldest_key = access_order.pop(0)
                del cache[oldest_key]
            
            return result
        
        def cache_info():
            return {
                "size": len(cache),
                "max_size": max_size,
                "keys": list(cache.keys())
            }
        
        def clear_cache():
            nonlocal cache, access_order
            cache.clear()
            access_order.clear()
        
        wrapper.cache_info = cache_info
        wrapper.clear_cache = clear_cache
        return wrapper
    
    return cached_function

# Using advanced closures
print("\n=== Advanced Closures Demo ===")

# Validator closure
validate_age = create_validator(min_value=0, max_value=150, allowed_types=int)
validate_score = create_validator(min_value=0, max_value=100, allowed_types=(int, float))

try:
    age = validate_age(25)
    print(f"Valid age: {age}")
    
    score = validate_score(85.5)
    print(f"Valid score: {score}")
    
    # This will raise an error
    # invalid_age = validate_age(-5)
except ValueError as e:
    print(f"Validation error: {e}")

# Logger closure
debug_logger = create_logger("DEBUG")
info_logger = create_logger("INFO")

debug_logger("This is a debug message", "DEBUG")
info_logger("This is an info message", "INFO")
info_logger("This is a warning", "WARNING")

# Cache closure
cache_decorator = create_cache(max_size=3)

@cache_decorator
def expensive_computation(n):
    """Simulate expensive computation."""
    print(f"Computing factorial of {n}")
    if n <= 1:
        return 1
    return n * expensive_computation(n - 1)

print("\nCache demo:")
print(f"factorial(5): {expensive_computation(5)}")
print(f"factorial(4): {expensive_computation(4)}")
print(f"factorial(5): {expensive_computation(5)}")  # Should use cache
print(f"factorial(6): {expensive_computation(6)}")
print(f"Cache info: {expensive_computation.cache_info()}")
```

## Function Decorators

### Basic Decorators

```python
def simple_decorator(func):
    """Simple decorator that adds functionality."""
    def wrapper(*args, **kwargs):
        print(f"Before calling {func.__name__}")
        result = func(*args, **kwargs)
        print(f"After calling {func.__name__}")
        return result
    return wrapper

def timing_decorator(func):
    """Decorator that measures execution time."""
    import time
    
    def wrapper(*args, **kwargs):
        start_time = time.time()
        result = func(*args, **kwargs)
        end_time = time.time()
        print(f"{func.__name__} took {end_time - start_time:.4f} seconds")
        return result
    return wrapper

def retry_decorator(max_attempts=3, delay=1):
    """Decorator that retries function on failure."""
    import time
    
    def decorator(func):
        def wrapper(*args, **kwargs):
            last_exception = None
            
            for attempt in range(max_attempts):
                try:
                    return func(*args, **kwargs)
                except Exception as e:
                    last_exception = e
                    if attempt < max_attempts - 1:
                        print(f"Attempt {attempt + 1} failed: {e}. Retrying in {delay}s...")
                        time.sleep(delay)
                    else:
                        print(f"All {max_attempts} attempts failed")
            
            raise last_exception
        return wrapper
    return decorator

# Using basic decorators
@simple_decorator
def greet(name):
    return f"Hello, {name}!"

@timing_decorator
def slow_function():
    import time
    time.sleep(0.1)
    return "Done"

@retry_decorator(max_attempts=3, delay=0.5)
def unreliable_function():
    import random
    if random.random() < 0.7:  # 70% chance of failure
        raise Exception("Random failure")
    return "Success!"

print("=== Basic Decorators Demo ===")
print(greet("World"))
print(slow_function())

try:
    result = unreliable_function()
    print(f"Unreliable function result: {result}")
except Exception as e:
    print(f"Unreliable function failed: {e}")
```

### Advanced Decorators

```python
def memoize(func):
    """Memoization decorator for caching function results."""
    cache = {}
    
    def wrapper(*args, **kwargs):
        # Create cache key
        key = str(args) + str(sorted(kwargs.items()))
        
        if key in cache:
            return cache[key]
        
        result = func(*args, **kwargs)
        cache[key] = result
        return result
    
    wrapper.cache = cache
    wrapper.clear_cache = lambda: cache.clear()
    return wrapper

def validate_types(**expected_types):
    """Decorator that validates function parameter types."""
    def decorator(func):
        def wrapper(*args, **kwargs):
            # Get function parameter names
            import inspect
            sig = inspect.signature(func)
            bound_args = sig.bind(*args, **kwargs)
            bound_args.apply_defaults()
            
            # Validate types
            for param_name, expected_type in expected_types.items():
                if param_name in bound_args.arguments:
                    value = bound_args.arguments[param_name]
                    if not isinstance(value, expected_type):
                        raise TypeError(f"Parameter '{param_name}' must be of type {expected_type.__name__}")
            
            return func(*args, **kwargs)
        return wrapper
    return decorator

def rate_limit(calls_per_second=1):
    """Decorator that rate limits function calls."""
    import time
    last_called = [0.0]
    
    def decorator(func):
        def wrapper(*args, **kwargs):
            now = time.time()
            time_passed = now - last_called[0]
            min_interval = 1.0 / calls_per_second
            
            if time_passed < min_interval:
                sleep_time = min_interval - time_passed
                time.sleep(sleep_time)
            
            last_called[0] = time.time()
            return func(*args, **kwargs)
        return wrapper
    return decorator

def singleton(cls):
    """Class decorator that makes a class singleton."""
    instances = {}
    
    def get_instance(*args, **kwargs):
        if cls not in instances:
            instances[cls] = cls(*args, **kwargs)
        return instances[cls]
    
    return get_instance

# Using advanced decorators
print("\n=== Advanced Decorators Demo ===")

@memoize
def fibonacci(n):
    """Fibonacci function with memoization."""
    if n <= 1:
        return n
    return fibonacci(n - 1) + fibonacci(n - 2)

@validate_types(x=int, y=int)
def add_integers(x, y):
    """Function that only accepts integers."""
    return x + y

@rate_limit(calls_per_second=2)
def api_call():
    """Simulated API call with rate limiting."""
    return "API response"

@singleton
class DatabaseConnection:
    """Singleton database connection."""
    
    def __init__(self):
        self.connection_id = id(self)
        print(f"Creating database connection: {self.connection_id}")

# Memoization demo
print("Fibonacci with memoization:")
print(f"fibonacci(10): {fibonacci(10)}")
print(f"fibonacci(10): {fibonacci(10)}")  # Should use cache
print(f"Cache size: {len(fibonacci.cache)}")

# Type validation demo
try:
    result = add_integers(5, 3)
    print(f"add_integers(5, 3): {result}")
    
    # This will raise a TypeError
    # add_integers(5, "3")
except TypeError as e:
    print(f"Type error: {e}")

# Rate limiting demo
print("Rate limited API calls:")
for i in range(3):
    print(f"Call {i + 1}: {api_call()}")

# Singleton demo
db1 = DatabaseConnection()
db2 = DatabaseConnection()
print(f"db1 is db2: {db1 is db2}")
```

## Functional Programming Tools

### functools Module

```python
from functools import partial, reduce, wraps, lru_cache
import functools

# Partial function application
def multiply(x, y, z):
    """Function that multiplies three numbers."""
    return x * y * z

# Create partial functions
multiply_by_2_and_3 = partial(multiply, 2, 3)
multiply_by_5 = partial(multiply, 5, 1)

print("=== functools Demo ===")
print(f"multiply_by_2_and_3(4): {multiply_by_2_and_3(4)}")
print(f"multiply_by_5(10): {multiply_by_5(10)}")

# Using partial with built-in functions
numbers = [1, 2, 3, 4, 5]
double_numbers = list(map(partial(multiply, 2, 1), numbers))
print(f"Double numbers: {double_numbers}")

# LRU Cache decorator
@lru_cache(maxsize=128)
def expensive_function(n):
    """Expensive function with caching."""
    print(f"Computing for {n}")
    if n <= 1:
        return n
    return expensive_function(n - 1) + expensive_function(n - 2)

print("\nLRU Cache demo:")
print(f"expensive_function(10): {expensive_function(10)}")
print(f"expensive_function(10): {expensive_function(10)}")  # Should use cache
print(f"Cache info: {expensive_function.cache_info()}")

# Wraps decorator (preserves function metadata)
def my_decorator(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        print(f"Calling {func.__name__}")
        return func(*args, **kwargs)
    return wrapper

@my_decorator
def example_function():
    """This is an example function."""
    return "Hello World"

print(f"\nFunction name: {example_function.__name__}")
print(f"Function docstring: {example_function.__doc__}")

# Reduce with custom operations
def custom_reduce_examples():
    """Examples of using reduce with custom operations."""
    
    # Find maximum
    numbers = [3, 7, 2, 9, 1, 5]
    max_num = reduce(lambda x, y: x if x > y else y, numbers)
    print(f"Maximum number: {max_num}")
    
    # Concatenate strings
    words = ["Hello", " ", "World", "!"]
    sentence = reduce(lambda x, y: x + y, words)
    print(f"Concatenated: {sentence}")
    
    # Custom operation: find longest string
    strings = ["short", "medium length", "very long string", "tiny"]
    longest = reduce(lambda x, y: x if len(x) > len(y) else y, strings)
    print(f"Longest string: {longest}")

custom_reduce_examples()
```

### itertools Module

```python
import itertools

def itertools_demo():
    """Demonstrate itertools functionality."""
    
    # Infinite iterators
    print("=== itertools Demo ===")
    
    # Count - infinite counter
    counter = itertools.count(start=10, step=2)
    print(f"First 5 count values: {[next(counter) for _ in range(5)]}")
    
    # Cycle - cycle through iterable infinitely
    cycle_iter = itertools.cycle(['A', 'B', 'C'])
    print(f"First 7 cycle values: {[next(cycle_iter) for _ in range(7)]}")
    
    # Repeat - repeat value infinitely or n times
    repeat_iter = itertools.repeat('Hello', 3)
    print(f"Repeat values: {list(repeat_iter)}")
    
    # Combinatoric iterators
    print("\nCombinatoric iterators:")
    
    # Product - Cartesian product
    colors = ['red', 'blue']
    sizes = ['S', 'M', 'L']
    products = list(itertools.product(colors, sizes))
    print(f"Product: {products}")
    
    # Permutations - all possible arrangements
    items = ['A', 'B', 'C']
    perms = list(itertools.permutations(items, 2))
    print(f"Permutations of 2: {perms}")
    
    # Combinations - all possible selections
    combos = list(itertools.combinations(items, 2))
    print(f"Combinations of 2: {combos}")
    
    # Combinations with replacement
    combos_wr = list(itertools.combinations_with_replacement(items, 2))
    print(f"Combinations with replacement: {combos_wr}")
    
    # Iterators on iterators
    print("\nIterators on iterators:")
    
    # Chain - chain multiple iterables
    list1 = [1, 2, 3]
    list2 = [4, 5, 6]
    list3 = [7, 8, 9]
    chained = list(itertools.chain(list1, list2, list3))
    print(f"Chained lists: {chained}")
    
    # Groupby - group consecutive elements
    data = [('A', 1), ('A', 2), ('B', 3), ('B', 4), ('C', 5)]
    grouped = {key: list(group) for key, group in itertools.groupby(data, key=lambda x: x[0])}
    print(f"Grouped data: {grouped}")
    
    # Tee - split iterator into multiple iterators
    original = [1, 2, 3, 4, 5]
    iter1, iter2 = itertools.tee(original, 2)
    print(f"First tee: {list(iter1)}")
    print(f"Second tee: {list(iter2)}")
    
    # Filtering iterators
    print("\nFiltering iterators:")
    
    # Dropwhile - drop elements while condition is true
    numbers = [1, 4, 6, 4, 1]
    dropped = list(itertools.dropwhile(lambda x: x < 5, numbers))
    print(f"Dropwhile < 5: {dropped}")
    
    # Takewhile - take elements while condition is true
    taken = list(itertools.takewhile(lambda x: x < 5, numbers))
    print(f"Takewhile < 5: {taken}")
    
    # Filterfalse - filter elements where condition is false
    filtered_false = list(itertools.filterfalse(lambda x: x % 2 == 0, numbers))
    print(f"Filterfalse (odd numbers): {filtered_false}")

itertools_demo()
```

## Functional Programming Patterns

### Function Composition

```python
def compose(*functions):
    """Compose multiple functions into a single function."""
    def composed(x):
        result = x
        for func in reversed(functions):
            result = func(result)
        return result
    return composed

def pipe(*functions):
    """Pipe functions from left to right."""
    def piped(x):
        result = x
        for func in functions:
            result = func(result)
        return result
    return piped

# Example functions for composition
def add_one(x):
    return x + 1

def multiply_by_two(x):
    return x * 2

def square(x):
    return x ** 2

def format_result(x):
    return f"Result: {x}"

# Using function composition
print("=== Function Composition Demo ===")

# Compose functions (right to left)
composed_func = compose(format_result, square, multiply_by_two, add_one)
result1 = composed_func(3)
print(f"Composed result: {result1}")
# Equivalent to: format_result(square(multiply_by_two(add_one(3))))

# Pipe functions (left to right)
piped_func = pipe(add_one, multiply_by_two, square, format_result)
result2 = piped_func(3)
print(f"Piped result: {result2}")

# Manual composition for clarity
manual_result = format_result(square(multiply_by_two(add_one(3))))
print(f"Manual composition: {manual_result}")
```

### Currying and Partial Application

```python
def curry(func, arity=None):
    """Curry a function to allow partial application."""
    if arity is None:
        arity = func.__code__.co_argcount
    
    def curried(*args):
        if len(args) >= arity:
            return func(*args[:arity])
        else:
            return curry(lambda *more_args: func(*(args + more_args)), arity - len(args))
    
    return curried

def uncurry(func):
    """Convert a curried function back to normal function."""
    def uncurried(*args):
        result = func
        for arg in args:
            result = result(arg)
        return result
    return uncurried

# Example function to curry
def add_three_numbers(a, b, c):
    """Function that adds three numbers."""
    return a + b + c

# Using currying
print("\n=== Currying Demo ===")

curried_add = curry(add_three_numbers)
add_5 = curried_add(5)
add_5_and_3 = add_5(3)

print(f"add_5_and_3(2): {add_5_and_3(2)}")
print(f"curried_add(1)(2)(3): {curried_add(1)(2)(3)}")

# Uncurrying
uncurried_add = uncurry(curried_add)
print(f"uncurried_add(1, 2, 3): {uncurried_add(1, 2, 3)}")
```

### Monads and Functors (Conceptual)

```python
class Maybe:
    """Simple Maybe monad implementation."""
    
    def __init__(self, value=None):
        self.value = value
        self.is_nothing = value is None
    
    def bind(self, func):
        """Bind operation for Maybe monad."""
        if self.is_nothing:
            return Maybe()
        try:
            result = func(self.value)
            return Maybe(result)
        except Exception:
            return Maybe()
    
    def map(self, func):
        """Map operation for Maybe monad."""
        return self.bind(lambda x: func(x))
    
    def get_or_default(self, default):
        """Get value or return default."""
        return default if self.is_nothing else self.value
    
    def __str__(self):
        return f"Maybe({self.value})" if not self.is_nothing else "Maybe(Nothing)"

def safe_divide(a, b):
    """Safely divide two numbers."""
    if b == 0:
        return Maybe()
    return Maybe(a / b)

def safe_sqrt(x):
    """Safely calculate square root."""
    if x < 0:
        return Maybe()
    import math
    return Maybe(math.sqrt(x))

# Using Maybe monad
print("\n=== Maybe Monad Demo ===")

# Successful operations
result1 = Maybe(16).map(lambda x: x ** 2).bind(safe_sqrt)
print(f"Maybe(16) -> square -> sqrt: {result1}")

# Safe division
result2 = safe_divide(10, 2).map(lambda x: x * 3)
print(f"safe_divide(10, 2) -> multiply by 3: {result2}")

# Failed operations
result3 = safe_divide(10, 0).map(lambda x: x * 3)
print(f"safe_divide(10, 0) -> multiply by 3: {result3}")

result4 = Maybe(-4).bind(safe_sqrt)
print(f"Maybe(-4) -> sqrt: {result4}")

# Chaining operations
chain_result = (Maybe(4)
                .bind(safe_sqrt)
                .map(lambda x: x * 2)
                .bind(lambda x: safe_divide(x, 2)))
print(f"Chain: Maybe(4) -> sqrt -> *2 -> /2: {chain_result}")
```

## Practical Functional Programming Examples

### Data Processing Pipeline

```python
def create_data_processing_pipeline():
    """Create a functional data processing pipeline."""
    
    # Data transformation functions
    def clean_data(data):
        """Clean data by removing None values and empty strings."""
        return [item for item in data if item is not None and item != ""]
    
    def normalize_data(data):
        """Normalize data to lowercase."""
        return [str(item).lower().strip() for item in data]
    
    def filter_length(data, min_length=3):
        """Filter items by minimum length."""
        return [item for item in data if len(item) >= min_length]
    
    def count_occurrences(data):
        """Count occurrences of each item."""
        from collections import Counter
        return dict(Counter(data))
    
    def sort_by_count(counts, reverse=True):
        """Sort items by count."""
        return sorted(counts.items(), key=lambda x: x[1], reverse=reverse)
    
    def format_results(sorted_items):
        """Format results for display."""
        return [f"{item}: {count}" for item, count in sorted_items]
    
    # Create pipeline
    pipeline = compose(
        format_results,
        sort_by_count,
        count_occurrences,
        lambda data: filter_length(data, 3),
        normalize_data,
        clean_data
    )
    
    return pipeline

# Using the data processing pipeline
print("\n=== Data Processing Pipeline Demo ===")

# Sample data
raw_data = [
    "Python", "python", "Java", "JavaScript", "", "Python",
    None, "java", "C++", "Python", "JavaScript", "Go",
    "  PYTHON  ", "Java", "Rust", "JavaScript"
]

pipeline = create_data_processing_pipeline()
results = pipeline(raw_data)

print("Raw data:")
print(raw_data)
print("\nProcessed results:")
for result in results:
    print(f"  {result}")

# Alternative pipeline using partial application
from functools import partial

def create_flexible_pipeline(min_length=3, top_n=5):
    """Create a flexible pipeline with parameters."""
    
    pipeline = compose(
        lambda items: items[:top_n],  # Take top N
        sort_by_count,
        count_occurrences,
        partial(filter_length, min_length=min_length),
        normalize_data,
        clean_data
    )
    
    return pipeline

flexible_pipeline = create_flexible_pipeline(min_length=2, top_n=3)
flexible_results = flexible_pipeline(raw_data)

print(f"\nFlexible pipeline (min_length=2, top_n=3):")
for result in flexible_results:
    print(f"  {result}")
```

### Configuration Management

```python
def create_config_manager():
    """Create a functional configuration manager."""
    
    def load_config(config_data):
        """Load configuration data."""
        return config_data.copy()
    
    def validate_config(config):
        """Validate configuration."""
        required_keys = ['host', 'port', 'timeout']
        missing_keys = [key for key in required_keys if key not in config]
        if missing_keys:
            raise ValueError(f"Missing required config keys: {missing_keys}")
        return config
    
    def set_defaults(config):
        """Set default values for missing keys."""
        defaults = {
            'timeout': 30,
            'retries': 3,
            'debug': False
        }
        return {**defaults, **config}
    
    def normalize_config(config):
        """Normalize configuration values."""
        normalized = config.copy()
        if 'port' in normalized:
            normalized['port'] = int(normalized['port'])
        if 'timeout' in normalized:
            normalized['timeout'] = float(normalized['timeout'])
        if 'debug' in normalized:
            normalized['debug'] = str(normalized['debug']).lower() in ['true', '1', 'yes']
        return normalized
    
    def create_config_pipeline():
        """Create configuration processing pipeline."""
        return compose(
            normalize_config,
            set_defaults,
            validate_config,
            load_config
        )
    
    return create_config_pipeline

# Using configuration manager
print("\n=== Configuration Management Demo ===")

config_pipeline = create_config_manager()()

# Valid configuration
valid_config = {
    'host': 'localhost',
    'port': '8080',
    'timeout': '30.5',
    'debug': 'true'
}

try:
    processed_config = config_pipeline(valid_config)
    print("Valid config processed:")
    for key, value in processed_config.items():
        print(f"  {key}: {value} ({type(value).__name__})")
except ValueError as e:
    print(f"Config error: {e}")

# Invalid configuration
invalid_config = {
    'host': 'localhost'
    # Missing required keys
}

try:
    processed_config = config_pipeline(invalid_config)
    print("Invalid config processed:")
    for key, value in processed_config.items():
        print(f"  {key}: {value} ({type(value).__name__})")
except ValueError as e:
    print(f"Config error: {e}")
```

## Key Takeaways

1. **Pure functions** are predictable and easier to test
2. **Higher-order functions** enable powerful abstractions
3. **Closures** capture and preserve state in functions
4. **Decorators** add functionality without modifying original code
5. **Function composition** builds complex operations from simple ones
6. **Functional tools** like map, filter, reduce simplify data processing
7. **Currying** enables partial function application
8. **Functional patterns** make code more modular and reusable

## Next Steps

In the next lesson, we'll explore Concurrency & Parallelism - threading, multiprocessing, and asyncio for writing efficient concurrent and parallel programs in Python.
