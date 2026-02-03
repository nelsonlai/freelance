# 5. Functions - Reusable Code Blocks

Functions are reusable blocks of code that perform specific tasks. They help organize code, avoid repetition, and make programs more modular and maintainable.

## Defining Functions

### Basic Function Structure

```python
def function_name(parameters):
    """
    Docstring - describes what the function does
    """
    # Function body
    return result  # Optional return statement
```

### Simple Functions

```python
# Function without parameters
def greet():
    """Print a greeting message."""
    print("Hello, World!")

# Function with parameters
def greet_person(name):
    """Print a personalized greeting."""
    print(f"Hello, {name}!")

# Function with return value
def add_numbers(a, b):
    """Add two numbers and return the result."""
    result = a + b
    return result

# Function with multiple return values
def get_name_and_age():
    """Get user's name and age."""
    name = input("Enter your name: ")
    age = int(input("Enter your age: "))
    return name, age

# Using the functions
greet()
greet_person("Alice")
sum_result = add_numbers(5, 3)
print(f"Sum: {sum_result}")

name, age = get_name_and_age()
print(f"Name: {name}, Age: {age}")
```

## Parameters and Arguments

### Positional Arguments

```python
def calculate_area(length, width):
    """Calculate the area of a rectangle."""
    return length * width

# Positional arguments
area1 = calculate_area(5, 3)  # length=5, width=3
area2 = calculate_area(3, 5)  # length=3, width=5
print(f"Area 1: {area1}, Area 2: {area2}")
```

### Keyword Arguments

```python
def create_profile(name, age, city, country="USA"):
    """Create a user profile."""
    return {
        "name": name,
        "age": age,
        "city": city,
        "country": country
    }

# Using keyword arguments
profile1 = create_profile(name="Alice", age=25, city="New York")
profile2 = create_profile(city="London", name="Bob", age=30, country="UK")
print(f"Profile 1: {profile1}")
print(f"Profile 2: {profile2}")
```

### Default Parameters

```python
def greet_with_title(name, title="Mr./Ms."):
    """Greet someone with a title."""
    return f"Hello, {title} {name}!"

# Using default parameter
greeting1 = greet_with_title("Smith")
print(greeting1)

# Overriding default parameter
greeting2 = greet_with_title("Johnson", "Dr.")
print(greeting2)
```

### Variable-length Arguments

#### *args (Arbitrary Positional Arguments)

```python
def calculate_sum(*args):
    """Calculate the sum of any number of arguments."""
    total = 0
    for num in args:
        total += num
    return total

# Using *args
sum1 = calculate_sum(1, 2, 3)
sum2 = calculate_sum(1, 2, 3, 4, 5)
sum3 = calculate_sum()  # No arguments

print(f"Sum 1: {sum1}")
print(f"Sum 2: {sum2}")
print(f"Sum 3: {sum3}")

# Another example with *args
def print_info(*args):
    """Print information about multiple items."""
    for i, item in enumerate(args, 1):
        print(f"{i}. {item}")

print_info("Apple", "Banana", "Orange")
```

#### **kwargs (Arbitrary Keyword Arguments)

```python
def create_user_profile(**kwargs):
    """Create a user profile with any number of keyword arguments."""
    profile = {}
    for key, value in kwargs.items():
        profile[key] = value
    return profile

# Using **kwargs
profile1 = create_user_profile(name="Alice", age=25, city="New York")
profile2 = create_user_profile(name="Bob", age=30, city="London", country="UK", occupation="Developer")

print(f"Profile 1: {profile1}")
print(f"Profile 2: {profile2}")

# Combining *args and **kwargs
def flexible_function(*args, **kwargs):
    """A function that accepts both positional and keyword arguments."""
    print(f"Positional arguments: {args}")
    print(f"Keyword arguments: {kwargs}")

flexible_function(1, 2, 3, name="Alice", age=25)
```

## Scope and Lifetime of Variables

### Local vs Global Variables

```python
# Global variable
global_var = "I am global"

def demonstrate_scope():
    """Demonstrate variable scope."""
    # Local variable
    local_var = "I am local"
    
    # Accessing global variable
    print(f"Global variable: {global_var}")
    print(f"Local variable: {local_var}")
    
    # Modifying global variable
    global global_var
    global_var = "I am modified global"

# Before function call
print(f"Before: {global_var}")

# Call function
demonstrate_scope()

# After function call
print(f"After: {global_var}")
# print(local_var)  # This would cause an error - local_var is not accessible here
```

### Enclosing Scope (Nested Functions)

```python
def outer_function(x):
    """Outer function with nested function."""
    def inner_function(y):
        """Inner function that can access outer function's variables."""
        return x + y  # x is from enclosing scope
    
    return inner_function(10)  # Call inner function

result = outer_function(5)
print(f"Result: {result}")

# Another example with nested functions
def create_multiplier(factor):
    """Create a function that multiplies by a factor."""
    def multiplier(number):
        return number * factor
    return multiplier

# Create specific multiplier functions
double = create_multiplier(2)
triple = create_multiplier(3)

print(f"Double 5: {double(5)}")
print(f"Triple 5: {triple(5)}")
```

## Lambda Functions

Lambda functions are small, anonymous functions defined with the `lambda` keyword.

```python
# Basic lambda function
square = lambda x: x ** 2
print(f"Square of 5: {square(5)}")

# Lambda with multiple parameters
add = lambda a, b: a + b
print(f"Add 3 and 4: {add(3, 4)}")

# Using lambda with built-in functions
numbers = [1, 2, 3, 4, 5]

# Using map with lambda
squared_numbers = list(map(lambda x: x**2, numbers))
print(f"Squared numbers: {squared_numbers}")

# Using filter with lambda
even_numbers = list(filter(lambda x: x % 2 == 0, numbers))
print(f"Even numbers: {even_numbers}")

# Using sorted with lambda
students = [
    {"name": "Alice", "grade": 85},
    {"name": "Bob", "grade": 92},
    {"name": "Charlie", "grade": 78}
]

# Sort by grade
sorted_by_grade = sorted(students, key=lambda student: student["grade"], reverse=True)
print("Sorted by grade:", sorted_by_grade)

# Sort by name
sorted_by_name = sorted(students, key=lambda student: student["name"])
print("Sorted by name:", sorted_by_name)
```

## Practical Examples

### Example 1: Calculator Functions

```python
def calculator():
    """A calculator with various mathematical operations."""
    
    def add(a, b):
        """Add two numbers."""
        return a + b
    
    def subtract(a, b):
        """Subtract b from a."""
        return a - b
    
    def multiply(a, b):
        """Multiply two numbers."""
        return a * b
    
    def divide(a, b):
        """Divide a by b."""
        if b != 0:
            return a / b
        else:
            return "Error: Division by zero"
    
    def power(a, b):
        """Raise a to the power of b."""
        return a ** b
    
    # Calculator menu
    while True:
        print("\n=== Calculator ===")
        print("1. Add")
        print("2. Subtract")
        print("3. Multiply")
        print("4. Divide")
        print("5. Power")
        print("6. Exit")
        
        choice = input("Enter your choice: ")
        
        if choice in ["1", "2", "3", "4", "5"]:
            try:
                num1 = float(input("Enter first number: "))
                num2 = float(input("Enter second number: "))
                
                if choice == "1":
                    result = add(num1, num2)
                elif choice == "2":
                    result = subtract(num1, num2)
                elif choice == "3":
                    result = multiply(num1, num2)
                elif choice == "4":
                    result = divide(num1, num2)
                elif choice == "5":
                    result = power(num1, num2)
                
                print(f"Result: {result}")
                
            except ValueError:
                print("Please enter valid numbers!")
        
        elif choice == "6":
            print("Goodbye!")
            break
        
        else:
            print("Invalid choice!")
```

### Example 2: Text Processing Functions

```python
def text_processor():
    """Various text processing functions."""
    
    def count_words(text):
        """Count the number of words in text."""
        return len(text.split())
    
    def count_characters(text):
        """Count characters (with and without spaces)."""
        with_spaces = len(text)
        without_spaces = len(text.replace(" ", ""))
        return with_spaces, without_spaces
    
    def reverse_text(text):
        """Reverse the text."""
        return text[::-1]
    
    def capitalize_words(text):
        """Capitalize the first letter of each word."""
        return text.title()
    
    def remove_punctuation(text):
        """Remove punctuation from text."""
        import string
        translator = str.maketrans('', '', string.punctuation)
        return text.translate(translator)
    
    def find_longest_word(text):
        """Find the longest word in text."""
        words = text.split()
        if words:
            return max(words, key=len)
        return ""
    
    # Interactive text processor
    while True:
        print("\n=== Text Processor ===")
        print("1. Count words")
        print("2. Count characters")
        print("3. Reverse text")
        print("4. Capitalize words")
        print("5. Remove punctuation")
        print("6. Find longest word")
        print("7. Exit")
        
        choice = input("Enter your choice: ")
        
        if choice == "7":
            print("Goodbye!")
            break
        
        if choice in ["1", "2", "3", "4", "5", "6"]:
            text = input("Enter text: ")
            
            if choice == "1":
                word_count = count_words(text)
                print(f"Word count: {word_count}")
            
            elif choice == "2":
                with_spaces, without_spaces = count_characters(text)
                print(f"Characters with spaces: {with_spaces}")
                print(f"Characters without spaces: {without_spaces}")
            
            elif choice == "3":
                reversed_text = reverse_text(text)
                print(f"Reversed: {reversed_text}")
            
            elif choice == "4":
                capitalized = capitalize_words(text)
                print(f"Capitalized: {capitalized}")
            
            elif choice == "5":
                no_punctuation = remove_punctuation(text)
                print(f"Without punctuation: {no_punctuation}")
            
            elif choice == "6":
                longest = find_longest_word(text)
                print(f"Longest word: {longest}")
        
        else:
            print("Invalid choice!")
```

### Example 3: Data Analysis Functions

```python
def data_analyzer():
    """Functions for analyzing numerical data."""
    
    def get_stats(numbers):
        """Get basic statistics for a list of numbers."""
        if not numbers:
            return "No data provided"
        
        total = sum(numbers)
        count = len(numbers)
        average = total / count
        minimum = min(numbers)
        maximum = max(numbers)
        
        return {
            "count": count,
            "total": total,
            "average": average,
            "minimum": minimum,
            "maximum": maximum
        }
    
    def find_outliers(numbers):
        """Find outliers in a list of numbers using IQR method."""
        if len(numbers) < 4:
            return []
        
        sorted_numbers = sorted(numbers)
        n = len(sorted_numbers)
        
        # Calculate quartiles
        q1_index = n // 4
        q3_index = 3 * n // 4
        q1 = sorted_numbers[q1_index]
        q3 = sorted_numbers[q3_index]
        
        # Calculate IQR
        iqr = q3 - q1
        
        # Define outlier bounds
        lower_bound = q1 - 1.5 * iqr
        upper_bound = q3 + 1.5 * iqr
        
        # Find outliers
        outliers = [num for num in numbers if num < lower_bound or num > upper_bound]
        
        return outliers
    
    def correlation_coefficient(x_values, y_values):
        """Calculate Pearson correlation coefficient."""
        if len(x_values) != len(y_values):
            return "Error: Lists must have the same length"
        
        n = len(x_values)
        
        # Calculate means
        mean_x = sum(x_values) / n
        mean_y = sum(y_values) / n
        
        # Calculate correlation coefficient
        numerator = sum((x - mean_x) * (y - mean_y) for x, y in zip(x_values, y_values))
        denominator_x = sum((x - mean_x) ** 2 for x in x_values)
        denominator_y = sum((y - mean_y) ** 2 for y in y_values)
        
        if denominator_x == 0 or denominator_y == 0:
            return "Error: Cannot calculate correlation (no variation in data)"
        
        correlation = numerator / (denominator_x * denominator_y) ** 0.5
        return correlation
    
    # Interactive data analyzer
    while True:
        print("\n=== Data Analyzer ===")
        print("1. Basic statistics")
        print("2. Find outliers")
        print("3. Correlation coefficient")
        print("4. Exit")
        
        choice = input("Enter your choice: ")
        
        if choice == "4":
            print("Goodbye!")
            break
        
        if choice in ["1", "2"]:
            try:
                data_input = input("Enter numbers separated by spaces: ")
                numbers = [float(x) for x in data_input.split()]
                
                if choice == "1":
                    stats = get_stats(numbers)
                    if isinstance(stats, dict):
                        print(f"\nStatistics:")
                        for key, value in stats.items():
                            print(f"{key.capitalize()}: {value}")
                    else:
                        print(stats)
                
                elif choice == "2":
                    outliers = find_outliers(numbers)
                    if outliers:
                        print(f"Outliers: {outliers}")
                    else:
                        print("No outliers found")
            
            except ValueError:
                print("Please enter valid numbers!")
        
        elif choice == "3":
            try:
                x_input = input("Enter x values separated by spaces: ")
                y_input = input("Enter y values separated by spaces: ")
                
                x_values = [float(x) for x in x_input.split()]
                y_values = [float(y) for y in y_input.split()]
                
                correlation = correlation_coefficient(x_values, y_values)
                print(f"Correlation coefficient: {correlation}")
            
            except ValueError:
                print("Please enter valid numbers!")
        
        else:
            print("Invalid choice!")
```

## Key Takeaways

1. **Functions** are reusable blocks of code that perform specific tasks
2. **Parameters** are variables defined in the function signature
3. **Arguments** are values passed to the function when calling it
4. **Default parameters** provide default values for optional arguments
5. ***args** allows functions to accept any number of positional arguments
6. ****kwargs** allows functions to accept any number of keyword arguments
7. **Scope** determines where variables can be accessed
8. **Lambda functions** are concise anonymous functions
9. **Functions** can return single values, multiple values, or no value
10. **Docstrings** document what functions do

## Next Steps

In the next lesson, we'll explore error handling - how to handle exceptions and make our programs more robust.
