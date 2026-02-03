# 4. Data Structures - Organizing and Storing Data

Data structures are ways of organizing and storing data in a computer so that it can be accessed and modified efficiently. Python provides several built-in data structures that are essential for programming.

## Strings - Text Data

Strings are sequences of characters and are one of the most commonly used data types in Python.

### String Creation and Basics

```python
# Different ways to create strings
single_quote = 'Hello World'
double_quote = "Hello World"
triple_quote = """This is a
multi-line string"""
raw_string = r"This is a raw string\nNo escape sequences"

print(single_quote)
print(double_quote)
print(triple_quote)
print(raw_string)
```

### String Indexing and Slicing

```python
text = "Python Programming"

# Indexing (accessing individual characters)
print(f"First character: {text[0]}")
print(f"Last character: {text[-1]}")
print(f"Character at index 7: {text[7]}")

# Slicing (accessing substrings)
print(f"First 6 characters: {text[0:6]}")
print(f"Characters 7 to end: {text[7:]}")
print(f"Last 11 characters: {text[-11:]}")
print(f"Every 2nd character: {text[::2]}")

# Reverse string
print(f"Reversed: {text[::-1]}")
```

### String Methods

```python
text = "  Hello World  "
name = "john doe"

# Case methods
print(f"Upper: '{text.upper()}'")
print(f"Lower: '{text.lower()}'")
print(f"Title: '{name.title()}'")
print(f"Capitalize: '{name.capitalize()}'")

# Whitespace methods
print(f"Stripped: '{text.strip()}'")
print(f"Left stripped: '{text.lstrip()}'")
print(f"Right stripped: '{text.rstrip()}'")

# Search and replace
sentence = "Python is great. Python is powerful."
print(f"Replace: {sentence.replace('Python', 'Java')}")
print(f"Count 'is': {sentence.count('is')}")
print(f"Find 'great': {sentence.find('great')}")

# Split and join
words = sentence.split()
print(f"Split words: {words}")
joined = "-".join(words)
print(f"Joined with '-': {joined}")

# String formatting
name = "Alice"
age = 25
score = 87.5

# Old style formatting
print("Name: %s, Age: %d, Score: %.2f" % (name, age, score))

# New style formatting
print("Name: {}, Age: {}, Score: {:.2f}".format(name, age, score))

# f-string formatting (Python 3.6+)
print(f"Name: {name}, Age: {age}, Score: {score:.2f}")

# String validation
email = "user@example.com"
print(f"Is alpha: {name.isalpha()}")
print(f"Is digit: {'123'.isdigit()}")
print(f"Is alphanumeric: {'abc123'.isalnum()}")
print(f"Starts with 'Py': {'Python'.startswith('Py')}")
print(f"Ends with 'on': {'Python'.endswith('on')}")
```

## Lists - Ordered Collections

Lists are ordered, mutable collections that can store different types of data.

### List Creation and Basics

```python
# Different ways to create lists
empty_list = []
numbers = [1, 2, 3, 4, 5]
mixed_list = [1, "hello", 3.14, True]
nested_list = [[1, 2], [3, 4], [5, 6]]

print(f"Empty list: {empty_list}")
print(f"Numbers: {numbers}")
print(f"Mixed list: {mixed_list}")
print(f"Nested list: {nested_list}")

# List from string
text = "Python"
char_list = list(text)
print(f"Characters: {char_list}")

# List comprehension (basic)
squares = [x**2 for x in range(1, 6)]
print(f"Squares: {squares}")
```

### List Indexing and Slicing

```python
fruits = ["apple", "banana", "orange", "grape", "kiwi"]

# Indexing
print(f"First fruit: {fruits[0]}")
print(f"Last fruit: {fruits[-1]}")
print(f"Second fruit: {fruits[1]}")

# Slicing
print(f"First 3 fruits: {fruits[0:3]}")
print(f"Last 2 fruits: {fruits[-2:]}")
print(f"Every other fruit: {fruits[::2]}")

# Negative slicing
print(f"Reverse: {fruits[::-1]}")
```

### List Methods

```python
fruits = ["apple", "banana"]

# Adding elements
fruits.append("orange")  # Add to end
print(f"After append: {fruits}")

fruits.insert(1, "grape")  # Insert at specific position
print(f"After insert: {fruits}")

fruits.extend(["kiwi", "mango"])  # Add multiple elements
print(f"After extend: {fruits}")

# Removing elements
removed = fruits.pop()  # Remove and return last element
print(f"Removed: {removed}, List: {fruits}")

fruits.remove("banana")  # Remove first occurrence
print(f"After remove: {fruits}")

# Other methods
numbers = [3, 1, 4, 1, 5, 9, 2, 6]
print(f"Length: {len(numbers)}")
print(f"Count of 1: {numbers.count(1)}")
print(f"Index of 5: {numbers.index(5)}")

# Sorting
numbers.sort()  # In-place sorting
print(f"Sorted: {numbers}")

numbers.sort(reverse=True)  # Reverse sorting
print(f"Reverse sorted: {numbers}")

# Create new sorted list
original = [3, 1, 4, 1, 5]
sorted_copy = sorted(original)
print(f"Original: {original}")
print(f"Sorted copy: {sorted_copy}")

# Reversing
numbers.reverse()
print(f"Reversed: {numbers}")
```

## Tuples - Immutable Collections

Tuples are ordered, immutable collections similar to lists but cannot be modified after creation.

```python
# Tuple creation
empty_tuple = ()
single_tuple = (42,)  # Note the comma for single element
coordinates = (10, 20)
mixed_tuple = (1, "hello", 3.14, True)
nested_tuple = ((1, 2), (3, 4))

print(f"Coordinates: {coordinates}")
print(f"Mixed tuple: {mixed_tuple}")

# Tuple unpacking
x, y = coordinates
print(f"X: {x}, Y: {y}")

# Multiple assignment
a, b, c = 1, 2, 3
print(f"A: {a}, B: {b}, C: {c}")

# Tuple methods
numbers = (1, 2, 3, 2, 4, 2)
print(f"Count of 2: {numbers.count(2)}")
print(f"Index of 3: {numbers.index(3)}")

# Converting between list and tuple
list_from_tuple = list(coordinates)
tuple_from_list = tuple([1, 2, 3])
print(f"List from tuple: {list_from_tuple}")
print(f"Tuple from list: {tuple_from_list}")

# Tuples are immutable
# coordinates[0] = 15  # This would cause an error
```

## Dictionaries - Key-Value Pairs

Dictionaries store data as key-value pairs and are unordered, mutable collections.

### Dictionary Creation and Basics

```python
# Different ways to create dictionaries
empty_dict = {}
student = {"name": "Alice", "age": 20, "grade": "A"}
mixed_dict = {1: "one", "two": 2, 3.14: "pi"}

print(f"Student: {student}")
print(f"Mixed dict: {mixed_dict}")

# Dictionary comprehension
squares_dict = {x: x**2 for x in range(1, 6)}
print(f"Squares dict: {squares_dict}")

# Accessing values
print(f"Student name: {student['name']}")
print(f"Student age: {student.get('age')}")
print(f"Student city: {student.get('city', 'Not specified')}")
```

### Dictionary Operations

```python
student = {"name": "Alice", "age": 20}

# Adding and updating
student["grade"] = "A"
student["city"] = "New York"
print(f"After adding: {student}")

student.update({"major": "Computer Science", "year": 3})
print(f"After update: {student}")

# Removing items
removed_grade = student.pop("grade")
print(f"Removed grade: {removed_grade}")
print(f"After pop: {student}")

del student["city"]
print(f"After del: {student}")

# Dictionary methods
print(f"Keys: {list(student.keys())}")
print(f"Values: {list(student.values())}")
print(f"Items: {list(student.items())}")

# Iterating over dictionaries
for key in student:
    print(f"{key}: {student[key]}")

for key, value in student.items():
    print(f"{key}: {value}")

# Dictionary methods
print(f"Length: {len(student)}")
print(f"Has 'age' key: {'age' in student}")
print(f"Has 'city' key: {'city' in student}")
```

## Sets - Unique Collections

Sets are unordered collections of unique elements.

```python
# Set creation
empty_set = set()
numbers = {1, 2, 3, 4, 5}
mixed_set = {1, "hello", 3.14}
from_list = set([1, 2, 2, 3, 3, 4])  # Duplicates removed

print(f"Numbers: {numbers}")
print(f"From list: {from_list}")

# Set operations
set1 = {1, 2, 3, 4, 5}
set2 = {4, 5, 6, 7, 8}

# Union
union = set1 | set2
print(f"Union: {union}")

# Intersection
intersection = set1 & set2
print(f"Intersection: {intersection}")

# Difference
difference = set1 - set2
print(f"Difference (set1 - set2): {difference}")

# Symmetric difference
symmetric_diff = set1 ^ set2
print(f"Symmetric difference: {symmetric_diff}")

# Set methods
fruits = {"apple", "banana", "orange"}

# Adding elements
fruits.add("grape")
print(f"After add: {fruits}")

fruits.update(["kiwi", "mango"])
print(f"After update: {fruits}")

# Removing elements
fruits.remove("banana")  # Raises error if not found
print(f"After remove: {fruits}")

fruits.discard("cherry")  # Doesn't raise error if not found
print(f"After discard: {fruits}")

# Other methods
print(f"Length: {len(fruits)}")
print(f"Contains 'apple': {'apple' in fruits}")
```

## Practical Examples

### Example 1: Student Grade Manager

```python
def student_grade_manager():
    """Manage student grades using dictionaries and lists."""
    
    students = {}
    
    while True:
        print("\n=== Student Grade Manager ===")
        print("1. Add student")
        print("2. Add grade")
        print("3. View student grades")
        print("4. Calculate average")
        print("5. View all students")
        print("6. Exit")
        
        choice = input("Enter your choice: ")
        
        if choice == "1":
            name = input("Enter student name: ")
            students[name] = []
            print(f"Student {name} added!")
            
        elif choice == "2":
            name = input("Enter student name: ")
            if name in students:
                grade = float(input("Enter grade: "))
                students[name].append(grade)
                print(f"Grade {grade} added for {name}")
            else:
                print("Student not found!")
                
        elif choice == "3":
            name = input("Enter student name: ")
            if name in students:
                grades = students[name]
                print(f"{name}'s grades: {grades}")
                if grades:
                    average = sum(grades) / len(grades)
                    print(f"Average: {average:.2f}")
            else:
                print("Student not found!")
                
        elif choice == "4":
            name = input("Enter student name: ")
            if name in students and students[name]:
                grades = students[name]
                average = sum(grades) / len(grades)
                print(f"{name}'s average: {average:.2f}")
            else:
                print("No grades found for this student!")
                
        elif choice == "5":
            if students:
                print("\nAll students:")
                for name, grades in students.items():
                    if grades:
                        avg = sum(grades) / len(grades)
                        print(f"{name}: {grades} (Avg: {avg:.2f})")
                    else:
                        print(f"{name}: No grades")
            else:
                print("No students added yet!")
                
        elif choice == "6":
            print("Goodbye!")
            break
            
        else:
            print("Invalid choice!")
```

### Example 2: Word Frequency Counter

```python
def word_frequency_counter():
    """Count word frequency in text using dictionaries."""
    
    text = input("Enter text to analyze: ").lower()
    
    # Remove punctuation and split into words
    import string
    translator = str.maketrans('', '', string.punctuation)
    clean_text = text.translate(translator)
    words = clean_text.split()
    
    # Count word frequency
    word_count = {}
    for word in words:
        word_count[word] = word_count.get(word, 0) + 1
    
    # Display results
    print(f"\nTotal words: {len(words)}")
    print(f"Unique words: {len(word_count)}")
    
    # Show most common words
    sorted_words = sorted(word_count.items(), key=lambda x: x[1], reverse=True)
    print("\nMost common words:")
    for word, count in sorted_words[:10]:
        print(f"{word}: {count}")
```

### Example 3: Shopping Cart

```python
def shopping_cart():
    """A simple shopping cart using lists and dictionaries."""
    
    # Available products
    products = {
        "apple": 1.50,
        "banana": 0.80,
        "orange": 2.00,
        "grape": 3.50,
        "mango": 2.50
    }
    
    cart = []
    
    while True:
        print("\n=== Shopping Cart ===")
        print("Available products:")
        for product, price in products.items():
            print(f"{product}: ${price}")
        
        print("\n1. Add item to cart")
        print("2. Remove item from cart")
        print("3. View cart")
        print("4. Checkout")
        print("5. Exit")
        
        choice = input("Enter your choice: ")
        
        if choice == "1":
            item = input("Enter item name: ").lower()
            if item in products:
                quantity = int(input("Enter quantity: "))
                cart.append({"item": item, "quantity": quantity, "price": products[item]})
                print(f"Added {quantity} {item}(s) to cart")
            else:
                print("Item not available!")
                
        elif choice == "2":
            if cart:
                print("Current cart:")
                for i, item in enumerate(cart):
                    print(f"{i+1}. {item['quantity']} x {item['item']}")
                
                try:
                    index = int(input("Enter item number to remove: ")) - 1
                    if 0 <= index < len(cart):
                        removed = cart.pop(index)
                        print(f"Removed {removed['quantity']} x {removed['item']}")
                    else:
                        print("Invalid item number!")
                except ValueError:
                    print("Please enter a valid number!")
            else:
                print("Cart is empty!")
                
        elif choice == "3":
            if cart:
                print("\nCurrent cart:")
                total = 0
                for item in cart:
                    subtotal = item['quantity'] * item['price']
                    total += subtotal
                    print(f"{item['quantity']} x {item['item']}: ${subtotal:.2f}")
                print(f"Total: ${total:.2f}")
            else:
                print("Cart is empty!")
                
        elif choice == "4":
            if cart:
                total = sum(item['quantity'] * item['price'] for item in cart)
                print(f"\nTotal amount: ${total:.2f}")
                print("Thank you for your purchase!")
                cart.clear()
            else:
                print("Cart is empty!")
                
        elif choice == "5":
            print("Goodbye!")
            break
            
        else:
            print("Invalid choice!")
```

## Key Takeaways

1. **Strings** are sequences of characters with many useful methods
2. **Lists** are ordered, mutable collections that can hold different data types
3. **Tuples** are immutable lists, useful for fixed data
4. **Dictionaries** store key-value pairs for efficient data lookup
5. **Sets** store unique elements and support mathematical set operations
6. **Indexing and slicing** work similarly across strings, lists, and tuples
7. **Comprehensions** provide concise ways to create data structures
8. **Each data structure** has specific methods for common operations

## Next Steps

In the next lesson, we'll explore functions - how to create reusable code blocks and organize our programs better.
