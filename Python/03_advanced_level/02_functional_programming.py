# Functional Programming Examples
from functools import reduce, partial, wraps
from typing import List, Callable, Any, Iterator
import operator

print("Functional Programming Examples")
print("=" * 35)

# 1. Higher-Order Functions
print("1. Higher-Order Functions")
print("-" * 25)

def apply_operation(numbers: List[int], operation: Callable[[int], int]) -> List[int]:
    """Apply an operation to each number in the list."""
    return [operation(x) for x in numbers]

def square(x: int) -> int:
    return x ** 2

def cube(x: int) -> int:
    return x ** 3

def double(x: int) -> int:
    return x * 2

# Test higher-order functions
numbers = [1, 2, 3, 4, 5]
print(f"Original numbers: {numbers}")
print(f"Squared: {apply_operation(numbers, square)}")
print(f"Cubed: {apply_operation(numbers, cube)}")
print(f"Doubled: {apply_operation(numbers, double)}")

# 2. Lambda Functions
print("\n2. Lambda Functions")
print("-" * 20)

# Lambda functions for common operations
'''
def add(x, y):
    return x + y

def multiply(x, y):
    return x * y

def is_even(x):
    return x % 2 == 0

def is_positive(x):
    return x > 0
'''
add = lambda x, y: x + y
multiply = lambda x, y: x * y
is_even = lambda x: x % 2 == 0
is_positive = lambda x: x > 0

# Test lambda functions
print(f"Add 5 + 3: {add(5, 3)}")
print(f"Multiply 4 * 6: {multiply(4, 6)}")
print(f"Is 7 even? {is_even(7)}")
print(f"Is -5 positive? {is_positive(-5)}")

# Lambda with map, filter, reduce
numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

# higher-order function example
# Map with lambda
squared = list(map(lambda x: x ** 2, numbers))
## [1, 4, 9, 16, 25, 36, 49, 64, 81, 100] -- squared list
print(f"Squared numbers: {squared}")

# Filter with lambda
even_numbers = list(filter(lambda x: x % 2 == 0, numbers))
print(f"Even numbers: {even_numbers}")

# Reduce with lambda
sum_of_squares = reduce(lambda x, y: x + y, squared)
print(f"Sum of squares: {sum_of_squares}")

# 3. Map, Filter, and Reduce
print("\n3. Map, Filter, and Reduce")
print("-" * 25)

# Map examples
def square(x):
    return x ** 2

def to_string(x):
    return str(x)

numbers = [1, 2, 3, 4, 5]

# Map with named function
squared = list(map(square, numbers))
print(f"Squared: {squared}")

# Map with lambda
strings = list(map(lambda x: str(x), numbers))
print(f"Strings: {strings}")

# Map with multiple iterables
list1 = [1, 2, 3]
list2 = [4, 5, 6]
sums = list(map(lambda x, y: x + y, list1, list2))
print(f"Sums: {sums}")

# Filter examples
def is_even(x):
    return x % 2 == 0

def is_positive(x):
    return x > 0

numbers = [-2, -1, 0, 1, 2, 3, 4, 5]

# Filter with named function
even_numbers = list(filter(is_even, numbers))
print(f"Even numbers: {even_numbers}")

# Filter with lambda
positive_numbers = list(filter(lambda x: x > 0, numbers))
print(f"Positive numbers: {positive_numbers}")

# Filter with None (removes falsy values)
mixed_values = [0, 1, None, 2, "", 3, False, 4]
truthy_values = list(filter(None, mixed_values))
print(f"Truthy values: {truthy_values}")

# Reduce examples
def add(x, y):
    return x + y

def multiply(x, y):
    return x * y

def find_max(x, y):
    return x if x > y else y

numbers = [1, 2, 3, 4, 5]

# Reduce with named function
sum_result = reduce(add, numbers)
print(f"Sum: {sum_result}")

# Reduce with lambda
product = reduce(lambda x, y: x * y, numbers)
print(f"Product: {product}")

# Reduce with initial value
sum_with_initial = reduce(add, numbers, 10)
print(f"Sum with initial 10: {sum_with_initial}")

# Reduce to find maximum
max_value = reduce(find_max, numbers)
print(f"Maximum: {max_value}")

# 4. Function Composition
print("\n4. Function Composition")
print("-" * 22)

def compose(*functions):
    """Compose multiple functions."""
    def composed(x):
        for func in reversed(functions):
            x = func(x)
        return x
    return composed

def add_one(x):
    return x + 1

def multiply_by_two(x):
    return x * 2

def square(x):
    return x ** 2

# Compose functions
composed_func = compose(square, multiply_by_two, add_one)
result = composed_func(3)
print(f"Compose result: {result}")

# Manual composition
manual_result = square(multiply_by_two(add_one(3)))
print(f"Manual composition: {manual_result}")

# 5. Partial Functions
print("\n5. Partial Functions")
print("-" * 20)

def multiply(x, y):
    return x * y

# Create partial functions
double = partial(multiply, 2)
triple = partial(multiply, 3)

print(f"Double 5: {double(5)}")
print(f"Triple 4: {triple(4)}")

# Partial with keyword arguments
def power(base, exponent):
    return base ** exponent

square = partial(power, exponent=2)
cube = partial(power, exponent=3)

print(f"Square of 4: {square(4)}")
print(f"Cube of 3: {cube(3)}")

# 6. Closures
print("\n6. Closures")
print("-" * 12)

def create_multiplier(factor):
    """Create a multiplier function."""
    def multiplier(x):
        return x * factor
    return multiplier

# Create multiplier functions
double = create_multiplier(2)
triple = create_multiplier(3)
quadruple = create_multiplier(4)

print(f"Double 5: {double(5)}")
print(f"Triple 4: {triple(4)}")
print(f"Quadruple 3: {quadruple(3)}")

# Closure with mutable state
def create_counter():
    """Create a counter function."""
    count = 0
    
    def counter():
        nonlocal count
        count += 1
        return count
    
    return counter

# Create counter instances
counter1 = create_counter()
counter2 = create_counter()

print(f"Counter1: {counter1()}, {counter1()}, {counter1()}")
print(f"Counter2: {counter2()}, {counter2()}")

# 7. Generator Functions
print("\n7. Generator Functions")
print("-" * 20)

def fibonacci_generator(n):
    """Generate Fibonacci numbers up to n."""
    a, b = 0, 1
    while a < n:
        yield a
        a, b = b, a + b

def squares_generator(n):
    """Generate squares up to n."""
    for i in range(n):
        yield i ** 2

# Test generators
print("Fibonacci numbers:")
for num in fibonacci_generator(20):
    print(num, end=" ")
print()

print("Squares:")
for square in squares_generator(10):
    print(square, end=" ")
print()

# Generator expressions
squares_gen = (x ** 2 for x in range(10))
print(f"Generator expression: {list(squares_gen)}")

# 8. Iterators and Iterables
print("\n8. Iterators and Iterables")
print("-" * 25)

class NumberRange:
    """Custom iterable class."""
    
    def __init__(self, start, stop, step=1):
        self.start = start
        self.stop = stop
        self.step = step
    
    def __iter__(self):
        return NumberRangeIterator(self.start, self.stop, self.step)

class NumberRangeIterator:
    """Iterator for NumberRange."""
    
    def __init__(self, start, stop, step):
        self.current = start
        self.stop = stop
        self.step = step
    
    def __iter__(self):
        return self
    
    def __next__(self):
        if self.current >= self.stop:
            raise StopIteration
        value = self.current
        self.current += self.step
        return value

# Test custom iterable
number_range = NumberRange(0, 10, 2)
print(f"Custom range: {list(number_range)}")

# 9. Functional Data Structures
print("\n9. Functional Data Structures")
print("-" * 30)

class ImmutableList:
    """Immutable list implementation."""
    
    def __init__(self, items=None):
        self._items = tuple(items) if items else ()
    
    def __getitem__(self, index):
        return self._items[index]
    
    def __len__(self):
        return len(self._items)
    
    def __iter__(self):
        return iter(self._items)
    
    def __repr__(self):
        return f"ImmutableList({list(self._items)})"
    
    def append(self, item):
        return ImmutableList(self._items + (item,))
    
    def prepend(self, item):
        return ImmutableList((item,) + self._items)
    
    def map(self, func):
        return ImmutableList(func(x) for x in self._items)
    
    def filter(self, func):
        return ImmutableList(x for x in self._items if func(x))
    
    def reduce(self, func, initial=None):
        if initial is None:
            return reduce(func, self._items)
        return reduce(func, self._items, initial)

# Test immutable list
immutable_list = ImmutableList([1, 2, 3, 4, 5])
print(f"Original: {immutable_list}")

# Operations return new instances
doubled = immutable_list.map(lambda x: x * 2)
print(f"Doubled: {doubled}")

evens = immutable_list.filter(lambda x: x % 2 == 0)
print(f"Evens: {evens}")

sum_result = immutable_list.reduce(lambda x, y: x + y)
print(f"Sum: {sum_result}")

# 10. Advanced Functional Patterns
print("\n10. Advanced Functional Patterns")
print("-" * 35)

# Memoization
def memoize(func):
    """Memoization decorator."""
    cache = {}
    
    @wraps(func)
    def wrapper(*args):
        if args in cache:
            return cache[args]
        result = func(*args)
        cache[args] = result
        return result
    
    return wrapper

@memoize
def fibonacci(n):
    """Memoized Fibonacci function."""
    if n < 2:
        return n
    return fibonacci(n - 1) + fibonacci(n - 2)

# Test memoization
print(f"Fibonacci(10): {fibonacci(10)}")
print(f"Fibonacci(20): {fibonacci(20)}")

# Currying
def curry(func):
    """Curry a function."""
    def curried(*args):
        if len(args) >= func.__code__.co_argcount:
            return func(*args)
        return lambda *more_args: curried(*(args + more_args))
    return curried

@curry
def add_three_numbers(a, b, c):
    return a + b + c

# Test currying
add_5_and_3 = add_three_numbers(5)(3)
result = add_5_and_3(2)
print(f"Curried addition: {result}")

# Function pipelines
def pipeline(*functions):
    """Create a pipeline of functions."""
    def piped(value):
        for func in functions:
            value = func(value)
        return value
    return piped

# Create pipeline
process_numbers = pipeline(
    lambda x: x * 2,      # double
    lambda x: x + 1,      # add one
    lambda x: x ** 2,     # square
    lambda x: x - 1       # subtract one
)

# Test pipeline
result = process_numbers(3)
print(f"Pipeline result: {result}")

# Manual pipeline
manual_result = 3
manual_result = manual_result * 2
manual_result = manual_result + 1
manual_result = manual_result ** 2
manual_result = manual_result - 1
print(f"Manual pipeline: {manual_result}")

print("\nFunctional Programming examples completed!")