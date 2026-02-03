# 2. Core Syntax - Variables, Data Types, and Operators

## Variables in Python

Variables are containers for storing data values. In Python, you don't need to declare variables with a specific type - Python automatically determines the type based on the value assigned.

### Variable Naming Rules

```python
# Valid variable names
name = "Alice"
age = 25
student_id = "S12345"
my_variable = 100
_variable = 200
variable123 = 300

# Invalid variable names (will cause errors)
# 123variable = 100  # Cannot start with number
# my-variable = 100   # Cannot contain hyphens
# class = "student"   # Cannot use reserved words
```

### Variable Assignment

```python
# Single assignment
x = 10
y = 20

# Multiple assignment
a, b, c = 10, 20, 30

# Same value to multiple variables
x = y = z = 100

# Swapping variables
a, b = b, a  # Pythonic way to swap
```

## Data Types in Python

Python has several built-in data types. Let's explore the fundamental ones:

### 1. Numbers

#### Integers (int)
```python
age = 25
negative_number = -10
large_number = 1000000

# Binary, octal, hexadecimal
binary_num = 0b1010  # Binary
octal_num = 0o755    # Octal
hex_num = 0xFF       # Hexadecimal

print(f"Age: {age}")
print(f"Binary: {binary_num}")
```

#### Floating Point Numbers (float)
```python
pi = 3.14159
temperature = -5.5
scientific_notation = 1.23e4  # 12300.0

print(f"Pi: {pi}")
print(f"Temperature: {temperature}")
```

#### Complex Numbers (complex)
```python
complex_num = 3 + 4j
print(f"Complex number: {complex_num}")
print(f"Real part: {complex_num.real}")
print(f"Imaginary part: {complex_num.imag}")
```

### 2. Strings (str)

Strings are sequences of characters enclosed in quotes.

```python
# Different ways to create strings
single_quote = 'Hello'
double_quote = "World"
triple_quote = """This is a
multi-line string"""

# String operations
name = "Alice"
greeting = "Hello, " + name + "!"
formatted_greeting = f"Hello, {name}!"

# String methods
text = "  Hello World  "
print(f"Original: '{text}'")
print(f"Stripped: '{text.strip()}'")
print(f"Lowercase: '{text.lower()}'")
print(f"Uppercase: '{text.upper()}'")
print(f"Replaced: '{text.replace('World', 'Python')}'")
```

### 3. Booleans (bool)

Boolean values represent truth values: `True` or `False`.

```python
is_student = True
is_graduated = False

# Boolean operations
print(f"Is student: {is_student}")
print(f"Is graduated: {is_graduated}")
print(f"Not graduated: {not is_graduated}")
```

## Input/Output Operations

### Input Function

```python
# Basic input
name = input("Enter your name: ")
age = input("Enter your age: ")

# Input with type conversion
age_int = int(input("Enter your age: "))
height_float = float(input("Enter your height (meters): "))

print(f"Name: {name}, Age: {age_int}, Height: {height_float}")
```

### Print Function

```python
# Basic print
print("Hello, World!")

# Multiple values
name = "Alice"
age = 25
print("Name:", name, "Age:", age)

# Formatted output
print(f"Name: {name}, Age: {age}")

# Print with separators
print("Python", "is", "awesome", sep="-")

# Print without newline
print("Loading", end="...")
print("Complete!")

# Print multiple lines
print("""Line 1
Line 2
Line 3""")
```

## Operators in Python

### Arithmetic Operators

```python
a = 10
b = 3

print(f"Addition: {a} + {b} = {a + b}")
print(f"Subtraction: {a} - {b} = {a - b}")
print(f"Multiplication: {a} * {b} = {a * b}")
print(f"Division: {a} / {b} = {a / b}")
print(f"Floor Division: {a} // {b} = {a // b}")
print(f"Modulus: {a} % {b} = {a % b}")
print(f"Exponentiation: {a} ** {b} = {a ** b}")

# String operations
greeting = "Hello"
name = "World"
full_greeting = greeting + " " + name
repeat_greeting = greeting * 3

print(f"String concatenation: {full_greeting}")
print(f"String repetition: {repeat_greeting}")
```

### Comparison Operators

```python
x = 10
y = 5

print(f"Equal: {x} == {y} is {x == y}")
print(f"Not equal: {x} != {y} is {x != y}")
print(f"Greater than: {x} > {y} is {x > y}")
print(f"Less than: {x} < {y} is {x < y}")
print(f"Greater or equal: {x} >= {y} is {x >= y}")
print(f"Less or equal: {x} <= {y} is {x <= y}")

# String comparison
name1 = "Alice"
name2 = "Bob"
print(f"String comparison: '{name1}' < '{name2}' is {name1 < name2}")
```

### Logical Operators

```python
is_student = True
has_id = False
age = 20

# AND operator
can_enter = is_student and has_id
print(f"Can enter (AND): {can_enter}")

# OR operator
can_register = is_student or age >= 18
print(f"Can register (OR): {can_register}")

# NOT operator
not_student = not is_student
print(f"Not a student: {not_student}")

# Complex logical expression
eligible = (age >= 18) and (is_student or has_id)
print(f"Eligible: {eligible}")
```

### Assignment Operators

```python
x = 10
print(f"Initial value: {x}")

x += 5  # x = x + 5
print(f"After += 5: {x}")

x -= 3  # x = x - 3
print(f"After -= 3: {x}")

x *= 2  # x = x * 2
print(f"After *= 2: {x}")

x /= 4  # x = x / 4
print(f"After /= 4: {x}")

x //= 2  # x = x // 2
print(f"After //= 2: {x}")

x %= 3  # x = x % 3
print(f"After %= 3: {x}")

x **= 2  # x = x ** 2
print(f"After **= 2: {x}")
```

## Type Conversion

```python
# Implicit type conversion
x = 10      # int
y = 3.14    # float
result = x + y  # float (10.14)

print(f"Type of result: {type(result)}")

# Explicit type conversion
age_str = "25"
age_int = int(age_str)
height_str = "5.8"
height_float = float(height_str)
score_int = 95
score_str = str(score_int)

print(f"Age as int: {age_int}")
print(f"Height as float: {height_float}")
print(f"Score as string: '{score_str}'")

# Type checking
print(f"Type of age_int: {type(age_int)}")
print(f"Is age_int an integer? {isinstance(age_int, int)}")
```

## Practical Exercise: Calculator Program

```python
def simple_calculator():
    """A simple calculator program demonstrating core syntax."""
    
    print("=== Simple Calculator ===")
    
    # Get input from user
    num1 = float(input("Enter first number: "))
    operation = input("Enter operation (+, -, *, /, **): ")
    num2 = float(input("Enter second number: "))
    
    # Perform calculation based on operation
    if operation == "+":
        result = num1 + num2
    elif operation == "-":
        result = num1 - num2
    elif operation == "*":
        result = num1 * num2
    elif operation == "/":
        if num2 != 0:
            result = num1 / num2
        else:
            print("Error: Division by zero!")
            return
    elif operation == "**":
        result = num1 ** num2
    else:
        print("Error: Invalid operation!")
        return
    
    # Display result
    print(f"{num1} {operation} {num2} = {result}")
    
    # Additional information
    print(f"Result type: {type(result)}")
    print(f"Is result an integer? {result.is_integer() if isinstance(result, float) else isinstance(result, int)}")

# Uncomment to run the calculator
# simple_calculator()
```

## Key Takeaways

1. **Variables** store data and don't need explicit type declaration
2. **Data types** include numbers (int, float, complex), strings, and booleans
3. **Input/Output** functions allow user interaction
4. **Operators** perform mathematical, comparison, and logical operations
5. **Type conversion** allows changing between different data types
6. **Python is dynamically typed** - variable types are determined at runtime

## Next Steps

In the next lesson, we'll explore control flow structures including if/elif/else statements and loops.
