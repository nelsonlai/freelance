# 3. Modules & Packages - Organizing and Reusing Code

Modules and packages are essential for organizing code into reusable components. This lesson covers creating your own modules, working with Python's standard library, and managing dependencies with virtual environments.

## Understanding Modules

### What are Modules?

A module is a file containing Python definitions and statements. The file name is the module name with the suffix `.py` added.

```python
# Example: math_utils.py (this would be a module)
def add(a, b):
    """Add two numbers."""
    return a + b

def multiply(a, b):
    """Multiply two numbers."""
    return a * b

def power(base, exponent):
    """Calculate base raised to the power of exponent."""
    return base ** exponent

# Constants
PI = 3.14159
E = 2.71828
```

### Importing Modules

```python
# Different ways to import modules
import math                    # Import entire module
from math import sqrt, pi     # Import specific functions/constants
from math import *            # Import everything (not recommended)
import math as m              # Import with alias

# Using imported modules
print(math.sqrt(16))          # Using full module name
print(sqrt(16))               # Using imported function directly
print(pi)                     # Using imported constant
print(m.sqrt(25))             # Using alias

# Import your own module
import math_utils
result = math_utils.add(5, 3)
print(f"Result: {result}")
```

## Creating Your Own Modules

### Simple Module Example

```python
# File: calculator.py
"""
A simple calculator module with basic operations.
"""

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
        raise ValueError("Cannot divide by zero")

def power(base, exponent):
    """Calculate base raised to the power of exponent."""
    return base ** exponent

# Constants
OPERATORS = ['+', '-', '*', '/', '**']

# Module-level code (runs when imported)
print("Calculator module loaded successfully")
```

### Using Your Module

```python
# File: main.py
import calculator

# Use functions from the module
result1 = calculator.add(10, 5)
result2 = calculator.multiply(4, 3)
result3 = calculator.power(2, 8)

print(f"Addition: {result1}")
print(f"Multiplication: {result2}")
print(f"Power: {result3}")

# Access constants
print(f"Available operators: {calculator.OPERATORS}")

# Import specific functions
from calculator import add, multiply
result4 = add(20, 30)
result5 = multiply(6, 7)

print(f"Direct import - Add: {result4}")
print(f"Direct import - Multiply: {result5}")
```

## Module Attributes and Special Variables

### Understanding `__name__`

```python
# File: module_demo.py
def greet(name):
    """Greet someone."""
    return f"Hello, {name}!"

def goodbye(name):
    """Say goodbye to someone."""
    return f"Goodbye, {name}!"

# This code runs when the module is imported
print("Module is being imported")

# This code only runs when the module is run directly
if __name__ == "__main__":
    print("This module is being run directly")
    print(greet("World"))
    print(goodbye("World"))
else:
    print("This module is being imported by another module")
```

### Module Documentation and Metadata

```python
# File: student_manager.py
"""
Student Management Module

This module provides functionality to manage student records,
including adding, updating, and querying student information.
"""

__version__ = "1.0.0"
__author__ = "Python Instructor"
__email__ = "instructor@example.com"

class Student:
    """A simple Student class."""
    
    def __init__(self, name, student_id, grade):
        self.name = name
        self.student_id = student_id
        self.grade = grade
    
    def __str__(self):
        return f"Student({self.name}, ID: {self.student_id}, Grade: {self.grade})"

def create_student(name, student_id, grade):
    """Create a new student."""
    return Student(name, student_id, grade)

def get_student_info(student):
    """Get formatted student information."""
    return f"Name: {student.name}, ID: {student.student_id}, Grade: {student.grade}"

# Module-level variables
DEFAULT_GRADE = "A"
MAX_STUDENTS = 100

if __name__ == "__main__":
    # Test the module
    student = create_student("Alice", "S001", "A")
    print(get_student_info(student))
```

## Working with Python's Standard Library

### Common Standard Library Modules

```python
# File: standard_library_demo.py
import os
import sys
import datetime
import random
import json
import csv
import math
import statistics
from collections import Counter, defaultdict
import urllib.request
import re

def demonstrate_os_module():
    """Demonstrate the os module."""
    print("=== OS Module ===")
    print(f"Current working directory: {os.getcwd()}")
    print(f"Platform: {os.name}")
    print(f"Environment variables: {len(os.environ)}")
    
    # List files in current directory
    files = os.listdir('.')
    print(f"Files in current directory: {len(files)}")

def demonstrate_datetime_module():
    """Demonstrate the datetime module."""
    print("\n=== Datetime Module ===")
    now = datetime.datetime.now()
    print(f"Current date and time: {now}")
    print(f"Year: {now.year}, Month: {now.month}, Day: {now.day}")
    
    # Format dates
    formatted = now.strftime("%Y-%m-%d %H:%M:%S")
    print(f"Formatted: {formatted}")
    
    # Calculate time differences
    tomorrow = now + datetime.timedelta(days=1)
    print(f"Tomorrow: {tomorrow}")

def demonstrate_random_module():
    """Demonstrate the random module."""
    print("\n=== Random Module ===")
    print(f"Random integer (1-10): {random.randint(1, 10)}")
    print(f"Random float (0-1): {random.random()}")
    print(f"Random choice: {random.choice(['apple', 'banana', 'orange'])}")
    
    # Shuffle a list
    numbers = [1, 2, 3, 4, 5]
    random.shuffle(numbers)
    print(f"Shuffled numbers: {numbers}")

def demonstrate_collections_module():
    """Demonstrate the collections module."""
    print("\n=== Collections Module ===")
    
    # Counter
    text = "hello world"
    counter = Counter(text)
    print(f"Letter counts: {counter}")
    print(f"Most common: {counter.most_common(3)}")
    
    # DefaultDict
    dd = defaultdict(list)
    dd['fruits'].append('apple')
    dd['fruits'].append('banana')
    dd['vegetables'].append('carrot')
    print(f"DefaultDict: {dict(dd)}")

def demonstrate_regex_module():
    """Demonstrate the re (regex) module."""
    print("\n=== Regex Module ===")
    text = "Contact us at support@example.com or call 555-123-4567"
    
    # Find email
    email_pattern = r'\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b'
    emails = re.findall(email_pattern, text)
    print(f"Emails found: {emails}")
    
    # Find phone numbers
    phone_pattern = r'\b\d{3}-\d{3}-\d{4}\b'
    phones = re.findall(phone_pattern, text)
    print(f"Phone numbers found: {phones}")

# Run demonstrations
demonstrate_os_module()
demonstrate_datetime_module()
demonstrate_random_module()
demonstrate_collections_module()
demonstrate_regex_module()
```

## Packages

### Creating a Package

A package is a collection of modules organized in directories.

```
my_package/
├── __init__.py
├── math_utils.py
├── string_utils.py
└── data_utils.py
```

### Package Structure Example

```python
# File: my_package/__init__.py
"""
My Package - A collection of utility modules.

This package provides various utility functions for common programming tasks.
"""

__version__ = "1.0.0"
__author__ = "Python Instructor"

# Import key functions to make them available at package level
from .math_utils import add, multiply, power
from .string_utils import format_name, count_words
from .data_utils import process_list, save_data

# Package-level variables
PACKAGE_NAME = "My Utility Package"
SUPPORTED_FORMATS = ['txt', 'csv', 'json']

# This runs when the package is imported
print(f"{PACKAGE_NAME} v{__version__} loaded successfully")

# File: my_package/math_utils.py
def add(a, b):
    """Add two numbers."""
    return a + b

def multiply(a, b):
    """Multiply two numbers."""
    return a * b

def power(base, exponent):
    """Calculate power."""
    return base ** exponent

def factorial(n):
    """Calculate factorial."""
    if n <= 1:
        return 1
    return n * factorial(n - 1)

# File: my_package/string_utils.py
def format_name(first, last):
    """Format a full name."""
    return f"{first.title()} {last.title()}"

def count_words(text):
    """Count words in text."""
    return len(text.split())

def reverse_string(text):
    """Reverse a string."""
    return text[::-1]

# File: my_package/data_utils.py
import json
import csv

def process_list(data, operation="sum"):
    """Process a list with various operations."""
    if operation == "sum":
        return sum(data)
    elif operation == "average":
        return sum(data) / len(data)
    elif operation == "max":
        return max(data)
    elif operation == "min":
        return min(data)
    else:
        return data

def save_data(data, filename, format="json"):
    """Save data to file in specified format."""
    if format == "json":
        with open(filename, 'w') as f:
            json.dump(data, f, indent=2)
    elif format == "csv":
        with open(filename, 'w', newline='') as f:
            writer = csv.writer(f)
            if isinstance(data, list) and len(data) > 0:
                if isinstance(data[0], dict):
                    writer.writerow(data[0].keys())
                    for row in data:
                        writer.writerow(row.values())
                else:
                    writer.writerows(data)
```

### Using Your Package

```python
# File: package_demo.py
# Import the entire package
import my_package

# Use functions imported in __init__.py
result1 = my_package.add(5, 3)
result2 = my_package.format_name("john", "doe")
print(f"Add: {result1}")
print(f"Formatted name: {result2}")

# Import specific modules
from my_package import math_utils, string_utils

result3 = math_utils.factorial(5)
result4 = string_utils.reverse_string("Python")
print(f"Factorial: {result3}")
print(f"Reversed: {result4}")

# Import specific functions
from my_package.math_utils import factorial
from my_package.string_utils import count_words

result5 = factorial(6)
result6 = count_words("Hello world from Python")
print(f"Factorial 6: {result5}")
print(f"Word count: {result6}")

# Access package-level variables
print(f"Package: {my_package.PACKAGE_NAME}")
print(f"Supported formats: {my_package.SUPPORTED_FORMATS}")
```

## Virtual Environments

### Why Use Virtual Environments?

Virtual environments allow you to:
- Isolate project dependencies
- Use different Python versions
- Avoid conflicts between packages
- Reproduce exact development environments

### Creating and Using Virtual Environments

```python
# File: venv_demo.py
"""
Demonstration of virtual environment concepts and usage.
Note: This is educational content - actual venv commands are run in terminal.
"""

def explain_virtual_environments():
    """Explain virtual environment concepts."""
    print("=== Virtual Environments ===")
    print("""
    Virtual environments are isolated Python environments that allow you to:
    
    1. Install packages without affecting system Python
    2. Use different package versions for different projects
    3. Avoid dependency conflicts
    4. Reproduce exact development environments
    
    Common commands:
    - python -m venv myenv          # Create virtual environment
    - source myenv/bin/activate     # Activate (Linux/Mac)
    - myenv\\Scripts\\activate       # Activate (Windows)
    - deactivate                    # Deactivate
    - pip freeze > requirements.txt # Save dependencies
    - pip install -r requirements.txt # Install dependencies
    """)

def demonstrate_requirements():
    """Show how to manage project dependencies."""
    print("\n=== Requirements Management ===")
    
    # Example requirements.txt content
    requirements = """
    # Core dependencies
    requests>=2.25.0
    pandas>=1.3.0
    numpy>=1.21.0
    
    # Development dependencies
    pytest>=6.0.0
    black>=21.0.0
    flake8>=3.9.0
    
    # Optional dependencies
    matplotlib>=3.4.0
    jupyter>=1.0.0
    """
    
    print("Example requirements.txt:")
    print(requirements)
    
    print("""
    To use requirements.txt:
    1. Create virtual environment: python -m venv venv
    2. Activate environment: source venv/bin/activate (or venv\\Scripts\\activate on Windows)
    3. Install dependencies: pip install -r requirements.txt
    4. Save current environment: pip freeze > requirements.txt
    """)

# Run the demonstration
explain_virtual_environments()
demonstrate_requirements()
```

## Practical Examples

### Example 1: Text Processing Package

```python
# File: text_processor/__init__.py
"""
Text Processing Package

A comprehensive package for text manipulation and analysis.
"""

from .analyzer import TextAnalyzer
from .formatter import TextFormatter
from .validator import TextValidator

__version__ = "1.0.0"

# File: text_processor/analyzer.py
import re
from collections import Counter

class TextAnalyzer:
    """Analyze text for various statistics."""
    
    def __init__(self, text):
        self.text = text
    
    def word_count(self):
        """Count total words."""
        return len(self.text.split())
    
    def character_count(self, include_spaces=True):
        """Count characters."""
        if include_spaces:
            return len(self.text)
        return len(self.text.replace(" ", ""))
    
    def sentence_count(self):
        """Count sentences."""
        sentences = re.split(r'[.!?]+', self.text)
        return len([s for s in sentences if s.strip()])
    
    def most_common_words(self, n=5):
        """Find most common words."""
        words = re.findall(r'\b\w+\b', self.text.lower())
        return Counter(words).most_common(n)
    
    def average_word_length(self):
        """Calculate average word length."""
        words = self.text.split()
        if not words:
            return 0
        return sum(len(word) for word in words) / len(words)

# File: text_processor/formatter.py
class TextFormatter:
    """Format text in various ways."""
    
    @staticmethod
    def title_case(text):
        """Convert to title case."""
        return text.title()
    
    @staticmethod
    def reverse_text(text):
        """Reverse the text."""
        return text[::-1]
    
    @staticmethod
    def remove_punctuation(text):
        """Remove punctuation from text."""
        import string
        return text.translate(str.maketrans('', '', string.punctuation))
    
    @staticmethod
    def add_line_numbers(text):
        """Add line numbers to text."""
        lines = text.split('\n')
        return '\n'.join(f"{i+1:3d}: {line}" for i, line in enumerate(lines))

# File: text_processor/validator.py
import re

class TextValidator:
    """Validate text for various criteria."""
    
    @staticmethod
    def is_email(text):
        """Check if text is a valid email."""
        pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
        return bool(re.match(pattern, text))
    
    @staticmethod
    def is_phone(text):
        """Check if text is a valid phone number."""
        pattern = r'^\+?1?[-.\s]?\(?[0-9]{3}\)?[-.\s]?[0-9]{3}[-.\s]?[0-9]{4}$'
        return bool(re.match(pattern, text))
    
    @staticmethod
    def is_palindrome(text):
        """Check if text is a palindrome."""
        clean_text = re.sub(r'[^a-zA-Z0-9]', '', text.lower())
        return clean_text == clean_text[::-1]
    
    @staticmethod
    def has_minimum_length(text, min_length=8):
        """Check if text meets minimum length requirement."""
        return len(text) >= min_length
```

### Example 2: Using the Text Processor Package

```python
# File: text_demo.py
from text_processor import TextAnalyzer, TextFormatter, TextValidator

def demonstrate_text_processing():
    """Demonstrate the text processing package."""
    
    sample_text = """
    Python is a powerful programming language. It's widely used in data science,
    web development, and automation. Python's syntax is clean and readable,
    making it great for beginners and experts alike.
    
    Contact us at: support@python.org or call (555) 123-4567
    """
    
    print("=== Text Processing Demo ===")
    
    # Text Analysis
    analyzer = TextAnalyzer(sample_text)
    print(f"Word count: {analyzer.word_count()}")
    print(f"Character count: {analyzer.character_count()}")
    print(f"Sentence count: {analyzer.sentence_count()}")
    print(f"Average word length: {analyzer.average_word_length():.2f}")
    print(f"Most common words: {analyzer.most_common_words(3)}")
    
    # Text Formatting
    print(f"\nTitle case: {TextFormatter.title_case('hello world')}")
    print(f"Reversed: {TextFormatter.reverse_text('Python')}")
    clean_text = TextFormatter.remove_punctuation("Hello, World!")
    print(f"Clean text: {clean_text}")
    numbered = TextFormatter.add_line_numbers("Line 1\nLine 2\nLine 3")
    print(f"Numbered lines:\n{numbered}")
    
    # Text Validation
    print(f"\nEmail validation: {TextValidator.is_email('support@python.org')}")
    print(f"Phone validation: {TextValidator.is_phone('(555) 123-4567')}")
    print(f"Palindrome check: {TextValidator.is_palindrome('racecar')}")
    print(f"Minimum length: {TextValidator.has_minimum_length('password123', 8)}")

# Run the demonstration
demonstrate_text_processing()
```

## Best Practices

### Module Organization

```python
# File: best_practices_demo.py
"""
Demonstrate best practices for module organization.
"""

# 1. Use clear, descriptive module names
# Good: user_authentication.py, data_validation.py
# Bad: utils.py, helper.py, stuff.py

# 2. Include comprehensive docstrings
def process_user_data(user_data):
    """
    Process and validate user data.
    
    Args:
        user_data (dict): Dictionary containing user information
        
    Returns:
        dict: Processed and validated user data
        
    Raises:
        ValueError: If required fields are missing
        TypeError: If user_data is not a dictionary
    """
    if not isinstance(user_data, dict):
        raise TypeError("user_data must be a dictionary")
    
    required_fields = ['name', 'email', 'age']
    for field in required_fields:
        if field not in user_data:
            raise ValueError(f"Missing required field: {field}")
    
    # Process the data
    processed_data = user_data.copy()
    processed_data['name'] = processed_data['name'].title()
    processed_data['email'] = processed_data['email'].lower()
    
    return processed_data

# 3. Use constants for configuration
DEFAULT_TIMEOUT = 30
MAX_RETRIES = 3
SUPPORTED_FORMATS = ['json', 'csv', 'xml']

# 4. Organize imports properly
import os
import sys
import json
from datetime import datetime
from typing import Dict, List, Optional

# Local imports
from .utils import validate_email, format_phone
from .exceptions import ValidationError, ProcessingError

# 5. Use type hints for better code clarity
def calculate_statistics(data: List[float]) -> Dict[str, float]:
    """Calculate basic statistics for a list of numbers."""
    if not data:
        return {}
    
    return {
        'mean': sum(data) / len(data),
        'min': min(data),
        'max': max(data),
        'count': len(data)
    }

# 6. Handle errors gracefully
def safe_file_operation(filename: str, operation: str) -> Optional[str]:
    """Safely perform file operations."""
    try:
        if operation == 'read':
            with open(filename, 'r') as f:
                return f.read()
        elif operation == 'write':
            with open(filename, 'w') as f:
                f.write("Sample content")
                return "File written successfully"
        else:
            raise ValueError(f"Unknown operation: {operation}")
    
    except FileNotFoundError:
        print(f"File not found: {filename}")
        return None
    except PermissionError:
        print(f"Permission denied for file: {filename}")
        return None
    except Exception as e:
        print(f"Unexpected error: {e}")
        return None

# 7. Use __all__ to control what gets imported
__all__ = [
    'process_user_data',
    'calculate_statistics',
    'safe_file_operation',
    'DEFAULT_TIMEOUT',
    'MAX_RETRIES',
    'SUPPORTED_FORMATS'
]
```

## Key Takeaways

1. **Modules** are single files containing Python code
2. **Packages** are collections of modules organized in directories
3. **Import statements** allow you to use code from other modules/packages
4. **`__name__`** helps distinguish between direct execution and import
5. **Virtual environments** isolate project dependencies
6. **Requirements files** help manage and reproduce environments
7. **Standard library** provides many useful modules out of the box
8. **Best practices** include clear naming, documentation, and error handling

## Next Steps

In the next lesson, we'll explore Object-Oriented Programming - how to create classes, work with objects, and implement inheritance and polymorphism.
