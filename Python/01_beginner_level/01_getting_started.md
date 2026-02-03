# 1. Getting Started with Python

## What is Python?

Python is a high-level, interpreted programming language known for its simplicity and readability. Created by Guido van Rossum and first released in 1991, Python has become one of the most popular programming languages worldwide.

### Why Python?
- **Easy to Learn**: Python's syntax is designed to be readable and straightforward
- **Versatile**: Used in web development, data science, artificial intelligence, automation, and more
- **Large Community**: Extensive libraries and active community support
- **Cross-Platform**: Runs on Windows, macOS, Linux, and other operating systems

## Installation & Setup

### Installing Python

1. **Visit the official Python website**: https://www.python.org/downloads/
2. **Download the latest version** (Python 3.11 or newer recommended)
3. **Run the installer** and make sure to check "Add Python to PATH"

### Verification
After installation, verify Python is working:

```bash
python --version
# or
python3 --version
```

## Integrated Development Environments (IDEs)

### 1. IDLE (Python's Built-in IDE)
- Comes with Python installation
- Simple and lightweight
- Good for beginners

### 2. VS Code (Visual Studio Code)
- Free, powerful, and widely used
- Excellent Python extension
- Great for learning and professional development

### 3. PyCharm
- Full-featured IDE by JetBrains
- Professional version available
- Excellent debugging tools

### 4. Jupyter Notebook
- Interactive coding environment
- Great for data science and learning
- Web-based interface

## Writing Your First Python Script

### Hello World Program

```python
# hello_world.py
print("Hello, World!")
print("Welcome to Python programming!")
```

### Running Python Scripts

#### Method 1: Command Line
```bash
python hello_world.py
# or
python3 hello_world.py
```

#### Method 2: Interactive Mode
```bash
python
# Then type:
print("Hello, World!")
```

## Comments & Code Style

### Comments in Python

```python
# This is a single-line comment

"""
This is a multi-line comment
It can span multiple lines
"""

def greet(name):
    """
    This is a docstring - used to document functions
    """
    return f"Hello, {name}!"
```

### PEP 8 Style Guidelines

PEP 8 is Python's official style guide. Key rules:

```python
# Good style examples:

# Use meaningful variable names
student_name = "Alice"
student_age = 20

# Use snake_case for variables and functions
def calculate_average(numbers):
    return sum(numbers) / len(numbers)

# Use PascalCase for classes
class Student:
    def __init__(self, name, age):
        self.name = name
        self.age = age

# Indentation: 4 spaces (never tabs)
if student_age >= 18:
    print("Adult student")
else:
    print("Minor student")

# Line length: maximum 79 characters
# If line is too long, break it:
total_score = math_score + english_score + science_score + \
              history_score + art_score
```

## Exercise: First Python Program

Create a program that:
1. Asks for the user's name
2. Asks for their age
3. Greets them and tells them their age in days

```python
# first_program.py

# Get user input
name = input("What is your name? ")
age = input("What is your age? ")

# Convert age to integer and calculate days
age_in_days = int(age) * 365

# Display results
print(f"Hello, {name}!")
print(f"You are {age} years old.")
print(f"That's approximately {age_in_days} days!")

# Add some personality
if int(age) >= 18:
    print("You are an adult!")
else:
    print("You are still growing up!")
```

## Key Takeaways

1. **Python is beginner-friendly** with readable syntax
2. **Multiple IDEs available** - choose one that feels comfortable
3. **Comments help** document your code and make it readable
4. **Follow PEP 8** for consistent, professional code style
5. **Start simple** with basic programs and gradually add complexity

## Next Steps

In the next lesson, we'll explore Python's core syntax including variables, data types, and operators.
