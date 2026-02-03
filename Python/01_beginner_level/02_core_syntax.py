"""
Core Syntax - Variables, Data Types, and Operators
This file contains all the example code from the Core Syntax lesson.
"""

# Variables in Python

# Valid variable names
name = "Alice"  # string
age = 25        # integer
student_id = "S12345"  # string
my_variable = 100      # integer
_variable = 200        # integer
variable123 = 300      # integer
xyz = 400.12           # float
# Variable Assignment
# Single assignment
x = 10  # integer
y = 20  # integer

# Multiple assignment
a, b, c = 10, 20, 30

# Same value to multiple variables
x = y = z = 100

# Swapping variables
a, b = b, a  # Pythonic way to swap
t = a
a = b
b = t

a = 10
b = 20

print(f"Result: a = {a}, b = {b}")

# Data Types Examples

# 1. Numbers - Integers
age = 25
negative_number = -10
large_number = 1000000

# Binary, octal, hexadecimal
binary_num = 0b1010  # Binary (10)
octal_num = 0o755    # Octal (493)
hex_num = 0xFF       # Hexadecimal (255)

print(f"Age: {age}")    ## f-string format string
print(f"{age}")
print(f"Hello, World! {age}")
print("Age:", age)
print(f"Binary: {binary_num}")
print(f"Octal: {octal_num}")
print(f"Hex: {hex_num}")

# Floating Point Numbers
pi = 3.14159
temperature = -5.5
scientific_notation = 1.23e4  # 12300.0

print(f"Pi: {pi}")
print(f"Temperature: {temperature}")
print(f"Scientific notation: {scientific_notation}")

# Complex Numbers
complex_num = 3 + 4j
print(f"Complex number: {complex_num}")
print(f"Real part: {complex_num.real}")
print(f"Imaginary part: {complex_num.imag}")

# 2. Strings
# Different ways to create strings
single_quote = 'Hello'
double_quote = "World"
morelines_quote = """This is a
first line
second line
multi-line string"""

# String operations
name = "Alice"
greeting = "Hello, " + name + "!" ## Hello, Alice!
formatted_greeting = f"Hello, {name}!" ## Hello, Alice!

print(f"String concatenation: {greeting}")
print(f"Formatted string: {formatted_greeting}")

# String methods
text = "  Hello World  "
print(f"Original: '{text}'")
print(f"Stripped: '{text.strip()}'")
print(f"Lowercase: '{text.lower()}'")
print(f"Uppercase: '{text.upper()}'")
print(f"Replaced: '{text.replace('World', 'Python')}'")

# 3. Booleans
is_student = True
is_graduated = False

print(f"Is student: {is_student}")
print(f"Is graduated: {is_graduated}")
print(f"Not graduated: {not is_graduated}")

# Input/Output Examples

def demonstrate_input_output():
    """Demonstrate input and output functions."""
    
    # Basic input (commented out to avoid blocking in example)
    name = input("Enter your name: ")
    age = input("Enter your age: ")
    
    # For demonstration, we'll use example values
    # name = "Alice"
    # age = "25"
    
    # Input with type conversion
    age_int = int(age)
    height_float = 5.8
    
    print(f"Name: {name}, Age: {age_int}, Height: {height_float}")

# Print function examples
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

# Operators Examples

# Arithmetic Operators
a = 10
b = 3

print(f"\nArithmetic Operators:")
print(f"Addition: {a} + {b} = {a + b}")
print(f"Subtraction: {a} - {b} = {a - b}")
print(f"Multiplication: {a} * {b} = {a * b}")
print(f"Division: {a} / {b} = {a / b}")
print(f"Floor Division: {a} // {b} = {a // b}") # 10 // 3 = 3
print(f"Modulus: {a} % {b} = {a % b}") # 10 % 3 = 1
print(f"Exponentiation: {a} ** {b} = {a ** b}") # 2 ** 3 = 8

# String operations
greeting = "Hello"
name = "World"
full_greeting = greeting + " " + name
repeat_greeting = greeting * 3 # "HelloHelloHello"

print(f"String concatenation: {full_greeting}")
print(f"String repetition: {repeat_greeting}")

# Comparison Operators
x = 10
y = 5
print(f"\n=== Comparison Operators ===")
print(f"\nComparison Operators:")
print(f"Equal: {x} == {y} is {x == y}") # Equal: 10 == 5 is False
print(f"Not equal: {x} != {y} is {x != y}")
print(f"Greater than: {x} > {y} is {x > y}")
print(f"Less than: {x} < {y} is {x < y}")
print(f"Greater or equal: {x} >= {y} is {x >= y}")
print(f"Less or equal: {x} <= {y} is {x <= y}")

# String comparison
name1 = "Alice"
name2 = "Bob"
print(f"String comparison: '{name1}' < '{name2}' is {name1 < name2}")

# Logical Operators
is_student = True
has_id = False
age = 20

print(f"\nLogical Operators:")
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

# Assignment Operators
x = 10
print(f"\nAssignment Operators:")
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

# Type Conversion
print(f"\nType Conversion:")
# Implicit type conversion
x = 10      # int
y = 3.14    # float
result = x + y  # float (13.14)

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

# Practical Exercise: Calculator Program
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

# Demonstrate input/output
demonstrate_input_output()

# Uncomment to run the interactive calculator
# simple_calculator()
