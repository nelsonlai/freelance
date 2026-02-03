# 6. Error Handling - Making Programs Robust

Error handling is crucial for creating robust, user-friendly programs. Python provides several mechanisms to handle errors gracefully and prevent programs from crashing unexpectedly.

## Understanding Errors and Exceptions

### Types of Errors

1. **Syntax Errors** - Errors in the code structure (caught before execution)
2. **Runtime Errors (Exceptions)** - Errors that occur during program execution
3. **Logical Errors** - Bugs in program logic (program runs but produces wrong results)

### Common Python Exceptions

```python
# Common exceptions and when they occur

# ZeroDivisionError
# result = 10 / 0  # This would raise ZeroDivisionError

# ValueError
# number = int("abc")  # This would raise ValueError

# TypeError
# result = "hello" + 5  # This would raise TypeError

# IndexError
# my_list = [1, 2, 3]
# value = my_list[5]  # This would raise IndexError

# KeyError
# my_dict = {"a": 1, "b": 2}
# value = my_dict["c"]  # This would raise KeyError

# FileNotFoundError
# with open("nonexistent.txt", "r") as file:  # This would raise FileNotFoundError
#     content = file.read()

# AttributeError
# my_string = "hello"
# my_string.append("world")  # This would raise AttributeError
```

## Basic Exception Handling (try/except)

### Simple try/except Block

```python
def safe_divide(a, b):
    """Safely divide two numbers."""
    try:
        result = a / b
        return result
    except ZeroDivisionError:
        return "Error: Cannot divide by zero"

# Test the function
print(safe_divide(10, 2))  # Output: 5.0
print(safe_divide(10, 0))  # Output: Error: Cannot divide by zero
```

### Handling Multiple Exceptions

```python
def get_user_input():
    """Get and validate user input."""
    try:
        age = int(input("Enter your age: "))
        return age
    except ValueError:
        print("Error: Please enter a valid number")
        return None
    except KeyboardInterrupt:
        print("\nOperation cancelled by user")
        return None

# Test the function
# age = get_user_input()
# if age is not None:
#     print(f"You are {age} years old")
```

### Catching Multiple Exception Types

```python
def process_data(data, index):
    """Process data with multiple possible errors."""
    try:
        value = data[index]
        result = value * 2
        return result
    except (IndexError, TypeError):
        print("Error: Invalid index or data type")
        return None
    except Exception as e:
        print(f"Unexpected error: {e}")
        return None

# Test the function
numbers = [1, 2, 3, 4, 5]
print(process_data(numbers, 2))  # Output: 6
print(process_data(numbers, 10))  # Output: Error: Invalid index or data type
```

## Advanced Exception Handling

### try/except/else Block

```python
def read_file_safely(filename):
    """Read a file with proper error handling."""
    try:
        with open(filename, 'r') as file:
            content = file.read()
    except FileNotFoundError:
        print(f"Error: File '{filename}' not found")
        return None
    except PermissionError:
        print(f"Error: Permission denied to read '{filename}'")
        return None
    except Exception as e:
        print(f"Unexpected error: {e}")
        return None
    else:
        print("File read successfully")
        return content

# Test the function
# content = read_file_safely("example.txt")
# if content:
#     print(f"Content length: {len(content)}")
```

### try/except/finally Block

```python
def process_file(filename):
    """Process a file with cleanup in finally block."""
    file = None
    try:
        file = open(filename, 'r')
        content = file.read()
        print(f"File content: {content}")
        return content
    except FileNotFoundError:
        print(f"Error: File '{filename}' not found")
        return None
    except Exception as e:
        print(f"Error processing file: {e}")
        return None
    finally:
        if file:
            file.close()
            print("File closed successfully")

# Test the function
# result = process_file("example.txt")
```

### Using with Statement (Context Manager)

```python
def read_file_with_context(filename):
    """Read file using context manager (recommended approach)."""
    try:
        with open(filename, 'r') as file:
            content = file.read()
            return content
    except FileNotFoundError:
        print(f"Error: File '{filename}' not found")
        return None
    except Exception as e:
        print(f"Error reading file: {e}")
        return None

# Test the function
# content = read_file_with_context("example.txt")
# if content:
#     print(f"Content: {content}")
```

## Custom Exceptions

### Creating Custom Exception Classes

```python
class CustomError(Exception):
    """Base class for custom exceptions."""
    pass

class ValidationError(CustomError):
    """Raised when validation fails."""
    def __init__(self, message, field=None):
        self.message = message
        self.field = field
        super().__init__(self.message)

class InsufficientFundsError(CustomError):
    """Raised when account has insufficient funds."""
    def __init__(self, balance, amount):
        self.balance = balance
        self.amount = amount
        self.message = f"Insufficient funds. Balance: {balance}, Required: {amount}"
        super().__init__(self.message)

# Using custom exceptions
def validate_age(age):
    """Validate age input."""
    if not isinstance(age, int):
        raise ValidationError("Age must be an integer", "age")
    if age < 0:
        raise ValidationError("Age cannot be negative", "age")
    if age > 150:
        raise ValidationError("Age cannot exceed 150", "age")
    return True

def withdraw_money(balance, amount):
    """Withdraw money from account."""
    if amount <= 0:
        raise ValidationError("Withdrawal amount must be positive")
    if balance < amount:
        raise InsufficientFundsError(balance, amount)
    return balance - amount

# Test custom exceptions
try:
    validate_age(-5)
except ValidationError as e:
    print(f"Validation error: {e.message} (Field: {e.field})")

try:
    new_balance = withdraw_money(100, 150)
except InsufficientFundsError as e:
    print(f"Transaction failed: {e.message}")
```

## Practical Examples

### Example 1: Robust Calculator

```python
def robust_calculator():
    """A calculator with comprehensive error handling."""
    
    def safe_divide(a, b):
        """Safely divide two numbers."""
        try:
            return a / b
        except ZeroDivisionError:
            raise ValueError("Cannot divide by zero")
        except TypeError:
            raise ValueError("Both arguments must be numbers")
    
    def safe_power(base, exponent):
        """Safely calculate power."""
        try:
            result = base ** exponent
            if not isinstance(result, (int, float)):
                raise ValueError("Result is not a valid number")
            return result
        except (OverflowError, ZeroDivisionError):
            raise ValueError("Result is too large or invalid")
        except TypeError:
            raise ValueError("Both arguments must be numbers")
    
    while True:
        print("\n=== Robust Calculator ===")
        print("1. Add")
        print("2. Subtract")
        print("3. Multiply")
        print("4. Divide")
        print("5. Power")
        print("6. Square root")
        print("7. Exit")
        
        choice = input("Enter your choice: ")
        
        if choice == "7":
            print("Goodbye!")
            break
        
        if choice in ["1", "2", "3", "4", "5", "6"]:
            try:
                if choice == "6":  # Square root only needs one number
                    num = float(input("Enter number: "))
                else:
                    num1 = float(input("Enter first number: "))
                    num2 = float(input("Enter second number: "))
                
                if choice == "1":
                    result = num1 + num2
                elif choice == "2":
                    result = num1 - num2
                elif choice == "3":
                    result = num1 * num2
                elif choice == "4":
                    result = safe_divide(num1, num2)
                elif choice == "5":
                    result = safe_power(num1, num2)
                elif choice == "6":
                    if num < 0:
                        raise ValueError("Cannot calculate square root of negative number")
                    result = num ** 0.5
                
                print(f"Result: {result}")
                
            except ValueError as e:
                print(f"Error: {e}")
            except KeyboardInterrupt:
                print("\nOperation cancelled by user")
            except Exception as e:
                print(f"Unexpected error: {e}")
        
        else:
            print("Invalid choice!")
```

### Example 2: File Processing with Error Handling

```python
def file_processor():
    """Process files with comprehensive error handling."""
    
    def read_file(filename):
        """Read file content safely."""
        try:
            with open(filename, 'r', encoding='utf-8') as file:
                return file.read()
        except FileNotFoundError:
            raise FileNotFoundError(f"File '{filename}' not found")
        except PermissionError:
            raise PermissionError(f"Permission denied to read '{filename}'")
        except UnicodeDecodeError:
            raise UnicodeDecodeError(f"Cannot decode file '{filename}'")
        except Exception as e:
            raise Exception(f"Unexpected error reading '{filename}': {e}")
    
    def write_file(filename, content):
        """Write content to file safely."""
        try:
            with open(filename, 'w', encoding='utf-8') as file:
                file.write(content)
            return True
        except PermissionError:
            raise PermissionError(f"Permission denied to write '{filename}'")
        except Exception as e:
            raise Exception(f"Unexpected error writing '{filename}': {e}")
    
    def process_text_file(filename):
        """Process a text file with various operations."""
        try:
            # Read file
            content = read_file(filename)
            
            # Process content
            lines = content.split('\n')
            word_count = len(content.split())
            char_count = len(content)
            
            # Create report
            report = f"""
File Analysis Report for: {filename}
================================
Lines: {len(lines)}
Words: {word_count}
Characters: {char_count}
First 100 characters: {content[:100]}...
"""
            
            # Write report
            report_filename = filename.replace('.txt', '_report.txt')
            write_file(report_filename, report)
            
            print(f"File processed successfully!")
            print(f"Report saved as: {report_filename}")
            
        except (FileNotFoundError, PermissionError, UnicodeDecodeError) as e:
            print(f"File error: {e}")
        except Exception as e:
            print(f"Processing error: {e}")
    
    # Interactive file processor
    while True:
        print("\n=== File Processor ===")
        print("1. Process text file")
        print("2. Exit")
        
        choice = input("Enter your choice: ")
        
        if choice == "1":
            filename = input("Enter filename (e.g., example.txt): ")
            process_text_file(filename)
        
        elif choice == "2":
            print("Goodbye!")
            break
        
        else:
            print("Invalid choice!")
```

### Example 3: Data Validation System

```python
class ValidationError(Exception):
    """Custom exception for validation errors."""
    def __init__(self, message, field=None):
        self.message = message
        self.field = field
        super().__init__(self.message)

def validate_email(email):
    """Validate email format."""
    import re
    pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    if not re.match(pattern, email):
        raise ValidationError("Invalid email format", "email")
    return True

def validate_phone(phone):
    """Validate phone number format."""
    import re
    # Remove all non-digit characters
    digits_only = re.sub(r'\D', '', phone)
    if len(digits_only) != 10:
        raise ValidationError("Phone number must have exactly 10 digits", "phone")
    return True

def validate_age(age):
    """Validate age."""
    try:
        age = int(age)
        if age < 0:
            raise ValidationError("Age cannot be negative", "age")
        if age > 150:
            raise ValidationError("Age cannot exceed 150", "age")
        return True
    except ValueError:
        raise ValidationError("Age must be a number", "age")

def user_registration():
    """User registration with comprehensive validation."""
    
    user_data = {}
    
    print("=== User Registration ===")
    
    # Name validation
    while True:
        try:
            name = input("Enter full name: ").strip()
            if not name or len(name) < 2:
                raise ValidationError("Name must be at least 2 characters long", "name")
            if not name.replace(" ", "").isalpha():
                raise ValidationError("Name can only contain letters and spaces", "name")
            user_data['name'] = name
            break
        except ValidationError as e:
            print(f"Error: {e.message}")
    
    # Email validation
    while True:
        try:
            email = input("Enter email: ").strip()
            validate_email(email)
            user_data['email'] = email
            break
        except ValidationError as e:
            print(f"Error: {e.message}")
    
    # Phone validation
    while True:
        try:
            phone = input("Enter phone number: ").strip()
            validate_phone(phone)
            user_data['phone'] = phone
            break
        except ValidationError as e:
            print(f"Error: {e.message}")
    
    # Age validation
    while True:
        try:
            age = input("Enter age: ").strip()
            validate_age(age)
            user_data['age'] = int(age)
            break
        except ValidationError as e:
            print(f"Error: {e.message}")
    
    # Password validation
    while True:
        try:
            password = input("Enter password: ")
            if len(password) < 8:
                raise ValidationError("Password must be at least 8 characters long", "password")
            if not any(c.isupper() for c in password):
                raise ValidationError("Password must contain at least one uppercase letter", "password")
            if not any(c.islower() for c in password):
                raise ValidationError("Password must contain at least one lowercase letter", "password")
            if not any(c.isdigit() for c in password):
                raise ValidationError("Password must contain at least one digit", "password")
            
            confirm_password = input("Confirm password: ")
            if password != confirm_password:
                raise ValidationError("Passwords do not match", "password")
            
            user_data['password'] = password
            break
        except ValidationError as e:
            print(f"Error: {e.message}")
    
    print("\nRegistration successful!")
    print(f"User data: {user_data}")
    
    return user_data

# Test the registration system
# user_data = user_registration()
```

## Best Practices for Error Handling

### 1. Specific Exception Handling

```python
# Good: Specific exception handling
try:
    value = my_dict["key"]
except KeyError:
    print("Key not found")

# Avoid: Catching all exceptions
try:
    value = my_dict["key"]
except Exception:  # Too broad
    print("Something went wrong")
```

### 2. Meaningful Error Messages

```python
def divide_numbers(a, b):
    """Divide two numbers with meaningful error messages."""
    try:
        return a / b
    except ZeroDivisionError:
        raise ValueError(f"Cannot divide {a} by zero")
    except TypeError:
        raise TypeError(f"Both arguments must be numbers, got {type(a)} and {type(b)}")
```

### 3. Logging Errors

```python
import logging

# Configure logging
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

def process_data(data):
    """Process data with logging."""
    try:
        result = data * 2
        logging.info(f"Data processed successfully: {result}")
        return result
    except Exception as e:
        logging.error(f"Error processing data: {e}")
        raise
```

### 4. Using Context Managers

```python
# Good: Using context managers
def read_file(filename):
    try:
        with open(filename, 'r') as file:
            return file.read()
    except FileNotFoundError:
        print(f"File {filename} not found")

# Avoid: Manual file handling
def read_file_manual(filename):
    file = None
    try:
        file = open(filename, 'r')
        return file.read()
    except FileNotFoundError:
        print(f"File {filename} not found")
    finally:
        if file:
            file.close()
```

## Key Takeaways

1. **Exception handling** prevents programs from crashing unexpectedly
2. **try/except blocks** catch and handle specific exceptions
3. **else clause** runs when no exceptions occur
4. **finally clause** always runs for cleanup operations
5. **Custom exceptions** provide specific error information
6. **Context managers** (with statement) automatically handle resources
7. **Specific exception handling** is better than catching all exceptions
8. **Meaningful error messages** help users understand what went wrong
9. **Logging** helps track errors in production applications
10. **Validation** prevents errors before they occur

## Next Steps

You've completed the Beginner Level! You now have a solid foundation in Python programming. You can:

1. **Practice** with the exercises and examples provided
2. **Build projects** using the concepts you've learned
3. **Move to Intermediate Level** to learn advanced functions, file handling, modules, and object-oriented programming

The Intermediate Level will cover:
- Advanced function concepts
- File handling and data persistence
- Modules and packages
- Object-oriented programming
- Advanced data structures
- Testing basics
