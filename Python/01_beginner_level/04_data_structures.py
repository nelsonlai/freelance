"""
Data Structures - Organizing and Storing Data
This file contains all the example code from the Data Structures lesson.
"""

# Strings - Text Data

# Different ways to create strings
from typing import Any


single_quote = 'Hello World'    # ['H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd']
double_quote = "Hello World"    # ['H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd']
triple_quote = """This is a
multi-line string"""    # ['T', 'h', 'i', 's', ' ', 'i', 's', ' ', 'a', ' ', 'm', 'u', 'l', 't', 'i', '-', 'l', 'i', 'n', 'e', ' ', 's', 't', 'r', 'i', 'n', 'g']
raw_string = r"This is a raw string\nNo escape sequences"

print("=== String Creation ===")
print(single_quote)
print(double_quote)
print(triple_quote)
print(raw_string)

# String Indexing and Slicing
text = "Python Programming" ##  ['P', 'y', 't', 'h', 'o', 'n', ' ', 'P', 'r', 'o', 'g', 'r', 'a', 'm', 'm', 'i', 'n', 'g']

print("\n=== String Indexing and Slicing ===")
# Indexing (accessing individual characters)
print(f"First character: {text[0]}")     # P
print(f"Last character: {text[-1]}")     # g
print(f"Character at index 7: {text[7]}") # P

text = "Python Programming"    # ['P', 'y', 't', 'h', 'o', 'n', ' ', 'P', 'r', 'o', 'g', 'r', 'a', 'm', 'm', 'i', 'n', 'g']
# Slicing (accessing substrings)
print(f"First 6 characters: {text[0:6]}")    # ['P', 'y', 't', 'h', 'o', 'n']
print(f"Characters 7 to end: {text[7:]}")    # ['P', 'r', 'o', 'g', 'r', 'a', 'm', 'm', 'i', 'n', 'g']
print(f"Last 11 characters: {text[-11:]}")    # ['P', 'r', 'o', 'g', 'r', 'a', 'm', 'm', 'i', 'n', 'g']
print(f"Every 2nd character: {text[::2]}")  # step of 2    ['P', 't', 'o', ' ', 'r', 'g', 'a', 'm', 'i', 'n']

# Reverse string
print(f"Reversed: {text[::-1]}") # ['g', 'n', 'i', 'm', 'm', 'a', 'r', 'g', 'o', 'r', 'P', ' ', 'n', 'o', 'h', 't', 'y', 'p']

# String Methods/Functions
text = "  Hello World  "
name = "john doe"

print("\n=== String Methods ===")
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

print("\n=== String Formatting ===")
# Old style formatting
print("Name: %s, Age: %d, Score: %.2f" % (name, age, score))

# New style formatting
print("Name: {}, Age: {}, Score: {:.2f}".format(name, age, score))

# f-string formatting (Python 3.6+)
print(f"Name: {name}, Age: {age}, Score: {score:.2f}")

# String validation
email = "user@example.com"
print(f"\n=== String Validation ===")
print(f"Is alpha: {name.isalpha()}")
print(f"Is digit: {'123'.isdigit()}")
print(f"Is alphanumeric: {'abc123'.isalnum()}")
print(f"Starts with 'Py': {'Python'.startswith('Py')}")
print(f"Ends with 'on': {'Python'.endswith('on')}")

# Lists - Ordered Collections

print("\n=== Lists ===")
# Different ways to create lists
empty_list = []
empty_list = list()
numbers = [1, 2, 3, 4, 5]   # list of integers
mixed_list = [1, "hello", 3.14, True]   # boolean is True or False
nested_list = [[1, 2], [3, 4], [5, 6], "Python", 7.89, False]   # nested list

print(f"Empty list: {empty_list}")
print(f"Numbers: {numbers}")
print(f"Mixed list: {mixed_list}")
print(f"Nested list: {nested_list}")

# List from string
text = "Python" # text_list = ['P', 'y', 't', 'h', 'o', 'n']
char_list = list(text)
print(f"Characters: {char_list}")


# List Indexing and Slicing
fruits = ["apple", "banana", "orange", "grape", "kiwi"]

print("\n=== List Indexing and Slicing ===")
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

# List Methods
fruits = ["apple", "banana"]

print("\n=== List Methods ===")
# Adding elements
fruits.append("orange")  # Add one element to end
print(f"After append: {fruits}")

fruits.insert(1, "grape")  # Insert one element at specific position
print(f"After insert: {fruits}")

fruits.extend(["kiwi", "mango"])  # Add multiple elements
print(f"After extend: {fruits}")

# Removing elements
removed = fruits.pop()  # Remove and return last element
print(f"Removed: {removed}, List: {fruits}")

fruits.remove("banana")  # Remove first occurrence, raises error if not found
print(f"After remove: {fruits}")

# Other methods
numbers = [3, 1, 4, 1, 5, 9, 2, 6, 5]
print(f"Length: {len(numbers)}")
print(f"Count of 1: {numbers.count(1)}")
print(f"Index of 5: {numbers.index(5)}") # first occurrence

# Sorting
numbers.sort()  # In-place sorting - ascending order
print(f"Sorted: {numbers}")

numbers.sort(reverse=True)  # Reverse sorting - descending order
print(f"Reverse sorted: {numbers}")

# Create new sorted list
original = [3, 1, 4, 1, 5]
sorted_copy = sorted(original)  # sorted() returns a new list
print(f"Original: {original}")
print(f"Sorted copy: {sorted_copy}")

# Reversing
numbers.reverse()
print(f"Reversed: {numbers}")

# List comprehension (basic)
squares = []
for x in range(1, 6):
    y = x**2
    squares.append(y)

squares = [x**2 for x in range(1, 6)]
print(f"Squares: {squares}")


# Tuples - Immutable Collections of lists

print("\n=== Tuples ===")
# Tuple creation (immutable)
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

# Dictionaries - Key-Value Pairs

print("\n=== Dictionaries ===")
# Different ways to create dictionaries
empty_dict = {}
student = {"name": "Alice", "age": 20, "grade": "A"}
mixed_dict = {1: "one", "two": 2, 3.14: "pi"}

print(f"Student: {student}")
print(f"Mixed dict: {mixed_dict}")

# Dictionary comprehension
squares_dict = {x: x**2 for x in range(1, 6)} # {1: 1, 2: 4, 3: 9, 4: 16, 5: 25}
print(f"Squares dict: {squares_dict}")

# Accessing values
print(f"Student name: {student['name']}")
print(f"Student age: {student.get('age', 18)}") # student['get']
print(f"Student city: {student.get('city', 'Not specified')}") # student['city'] # raises error if not found

# Dictionary Operations
student = {"name": "Alice", "age": 20}

print("\n=== Dictionary Operations ===")
# Adding and updating
student["grade"] = "B"
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
print(f"Items: {list[tuple[Any, Any]](student.items())}") # [('name', 'Alice'), ('age', 20), ('major', 'Computer Science'), ('year', 3)]

# Iterating over dictionaries
print("\nIterating over dictionary:")
for key in student:
    print(f"{key}: {student[key]}")

print("\nIterating over items:")
for key, value in student.items():
    print(f"{key}: {value}")

# Dictionary methods
print(f"\nLength: {len(student)}")
print(f"Has 'age' key: {'age' in student}") # True
print(f"Has 'city' key: {'city' in student}") # False

# Sets - Unique Collections

print("\n=== Sets ===")
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

print(f"Set1: {set1}")
print(f"Set2: {set2}")

# Union
union_set = set1 | set2 ## | pipe operator is used to union two sets
print(f"Union: {union_set}")    # {1, 2, 3, 4, 5, 6, 7, 8}

# Intersection
intersection = set1 & set2
print(f"Intersection: {intersection}")    # {4, 5}

# Difference
difference = set1 - set2
print(f"Difference (set1 - set2): {difference}") # {1, 2, 3}

# Symmetric difference
symmetric_diff = set1 ^ set2
print(f"Symmetric difference: {symmetric_diff}")    # {1, 2, 3, 6, 7, 8}

# Set methods
fruits = {"apple", "banana", "orange"}

print(f"Original fruits: {fruits}")

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

# Practical Examples

# Example 1: Student Grade Manager
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
                if grades:  # if name in students:
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

# Example 2: Word Frequency Counter
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

# Example 3: Shopping Cart
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

# Example 4: Contact Book
def contact_book():
    """A simple contact book using dictionaries."""
    
    contacts = {}
    
    while True:
        print("\n=== Contact Book ===")
        print("1. Add contact")
        print("2. Search contact")
        print("3. Update contact")
        print("4. Delete contact")
        print("5. List all contacts")
        print("6. Exit")
        
        choice = input("Enter your choice: ")
        
        if choice == "1":
            name = input("Enter name: ")
            phone = input("Enter phone: ")
            email = input("Enter email: ")
            contacts[name] = {"phone": phone, "email": email}
            print(f"Contact {name} added!")
            
        elif choice == "2":
            name = input("Enter name to search: ")
            if name in contacts:
                contact = contacts[name]
                print(f"Name: {name}")
                print(f"Phone: {contact['phone']}")
                print(f"Email: {contact['email']}")
            else:
                print("Contact not found!")
                
        elif choice == "3":
            name = input("Enter name to update: ")
            if name in contacts:
                phone = input(f"Enter new phone (current: {contacts[name]['phone']}): ")
                email = input(f"Enter new email (current: {contacts[name]['email']}): ")
                if phone:
                    contacts[name]['phone'] = phone
                if email:
                    contacts[name]['email'] = email
                print(f"Contact {name} updated!")
            else:
                print("Contact not found!")
                
        elif choice == "4":
            name = input("Enter name to delete: ")
            if name in contacts:
                del contacts[name]
                print(f"Contact {name} deleted!")
            else:
                print("Contact not found!")
                
        elif choice == "5":
            if contacts:
                print("\nAll contacts:")
                for name, contact in contacts.items():
                    print(f"{name}: {contact['phone']}, {contact['email']}")
            else:
                print("No contacts found!")
                
        elif choice == "6":
            print("Goodbye!")
            break
            
        else:
            print("Invalid choice!")

# Uncomment to run any of the interactive examples:
# student_grade_manager()
# word_frequency_counter()
# shopping_cart()
# contact_book()

