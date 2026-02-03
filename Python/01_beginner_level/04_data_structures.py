"""
Data Structures - Organizing and Storing Data
This file contains all the example code from the Data Structures lesson.
"""

# Strings - Text Data

# Different ways to create strings
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
print(f"Character at index 7: {text[7]}") # p

text = "Python Programming"    # ['P', 'y', 't', 'h', 'o', 'n', ' ', 'P', 'r', 'o', 'g', 'r', 'a', 'm', 'm', 'i', 'n', 'g']
# Slicing (accessing substrings)
print(f"First 6 characters: {text[0:6]}")    # ['P', 'y', 't', 'h', 'o', 'n']
print(f"Characters 7 to end: {text[7:]}")    # ['P', 'r', 'o', 'g', 'r', 'a', 'm', 'm', 'i', 'n', 'g']
print(f"Last 11 characters: {text[-11:]}")    # ['P', 'r', 'o', 'g', 'r', 'a', 'm', 'm', 'i', 'n', 'g']
print(f"Every 2nd character: {text[::2]}")  # step of 2    ['P', 't', 'o', ' ', 'r', 'g', 'a', 'm', 'i', 'g']

# Reverse string
print(f"Reversed: {text[::-1]}")

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

# List comprehension (basic)
squares = []
for x in range(1, 6):
    y = x**2
    squares.append(y)

squares = [x**2 for x in range(1, 6)]
print(f"Squares: {squares}")

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
numbers = [3, 1, 4, 1, 5, 9, 2, 6]
print(f"Length: {len(numbers)}")
print(f"Count of 1: {numbers.count(1)}")
print(f"Index of 5: {numbers.index(5)}")

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
squares_dict = {x: x**2 for x in range(1, 6)}
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
print(f"Items: {list(student.items())}")

# Iterating over dictionaries
print("\nIterating over dictionary:")
for key in student:
    print(f"{key}: {student[key]}")

print("\nIterating over items:")
for key, value in student.items():
    print(f"{key}: {value}")

# Dictionary methods
print(f"\nLength: {len(student)}")
print(f"Has 'age' key: {'age' in student}")
print(f"Has 'city' key: {'city' in student}")

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
print(f"Union: {union_set}")

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

# ============================================================================
# Balanced Binary Trees - AVL and Red-Black Trees
# ============================================================================

print("\n" + "="*80)
print("BALANCED BINARY TREES - AVL AND RED-BLACK TREES")
print("="*80)

# ============================================================================
# AVL Tree Implementation
# ============================================================================

class AVLNode:
    """Node for AVL Tree with height tracking."""
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None
        self.height = 1

class AVLTree:
    """AVL Tree - Self-balancing binary search tree."""
    
    def __init__(self):
        self.root = None
    
    def get_height(self, node):
        """Get height of a node."""
        if node is None:
            return 0
        return node.height
    
    def get_balance(self, node):
        """Get balance factor of a node (difference between left and right subtree heights)."""
        if node is None:
            return 0
        return self.get_height(node.left) - self.get_height(node.right)
    
    def update_height(self, node):
        """Update height of a node."""
        if node:
            node.height = 1 + max(self.get_height(node.left), self.get_height(node.right))
    
    def rotate_right(self, y):
        """Right rotation to balance the tree."""
        x = y.left
        T2 = x.right
        
        # Perform rotation
        x.right = y
        y.left = T2
        
        # Update heights
        self.update_height(y)
        self.update_height(x)
        
        return x
    
    def rotate_left(self, x):
        """Left rotation to balance the tree."""
        y = x.right
        T2 = y.left
        
        # Perform rotation
        y.left = x
        x.right = T2
        
        # Update heights
        self.update_height(x)
        self.update_height(y)
        
        return y
    
    def insert(self, key):
        """Insert a key into the AVL tree."""
        self.root = self._insert(self.root, key)
    
    def _insert(self, node, key):
        """Recursive helper to insert a key."""
        # 1. Perform normal BST insertion
        if node is None:
            return AVLNode(key)
        
        if key < node.key:
            node.left = self._insert(node.left, key)
        elif key > node.key:
            node.right = self._insert(node.right, key)
        else:
            return node  # Duplicate keys not allowed
        
        # 2. Update height of ancestor node
        self.update_height(node)
        
        # 3. Get balance factor
        balance = self.get_balance(node)
        
        # 4. If unbalanced, perform rotations
        # Left Left Case
        if balance > 1 and key < node.left.key:
            return self.rotate_right(node)
        
        # Right Right Case
        if balance < -1 and key > node.right.key:
            return self.rotate_left(node)
        
        # Left Right Case
        if balance > 1 and key > node.left.key:
            node.left = self.rotate_left(node.left)
            return self.rotate_right(node)
        
        # Right Left Case
        if balance < -1 and key < node.right.key:
            node.right = self.rotate_right(node.right)
            return self.rotate_left(node)
        
        return node
    
    def delete(self, key):
        """Delete a key from the AVL tree."""
        self.root = self._delete(self.root, key)
    
    def _delete(self, node, key):
        """Recursive helper to delete a key."""
        # 1. Perform standard BST delete
        if node is None:
            return node
        
        if key < node.key:
            node.left = self._delete(node.left, key)
        elif key > node.key:
            node.right = self._delete(node.right, key)
        else:
            # Node to be deleted found
            if node.left is None:
                return node.right
            elif node.right is None:
                return node.left
            
            # Node with two children: get inorder successor
            temp = self._min_value_node(node.right)
            node.key = temp.key
            node.right = self._delete(node.right, temp.key)
        
        # 2. Update height
        self.update_height(node)
        
        # 3. Get balance factor
        balance = self.get_balance(node)
        
        # 4. If unbalanced, perform rotations
        # Left Left Case
        if balance > 1 and self.get_balance(node.left) >= 0:
            return self.rotate_right(node)
        
        # Left Right Case
        if balance > 1 and self.get_balance(node.left) < 0:
            node.left = self.rotate_left(node.left)
            return self.rotate_right(node)
        
        # Right Right Case
        if balance < -1 and self.get_balance(node.right) <= 0:
            return self.rotate_left(node)
        
        # Right Left Case
        if balance < -1 and self.get_balance(node.right) > 0:
            node.right = self.rotate_right(node.right)
            return self.rotate_left(node)
        
        return node
    
    def _min_value_node(self, node):
        """Find node with minimum key value."""
        current = node
        while current.left is not None:
            current = current.left
        return current
    
    def search(self, key):
        """Search for a key in the AVL tree."""
        return self._search(self.root, key)
    
    def _search(self, node, key):
        """Recursive helper to search for a key."""
        if node is None or node.key == key:
            return node
        
        if key < node.key:
            return self._search(node.left, key)
        return self._search(node.right, key)
    
    def inorder_traversal(self):
        """Inorder traversal of the tree."""
        result = []
        self._inorder(self.root, result)
        return result
    
    def _inorder(self, node, result):
        """Recursive helper for inorder traversal."""
        if node:
            self._inorder(node.left, result)
            result.append(node.key)
            self._inorder(node.right, result)
    
    def print_tree(self):
        """Print tree structure."""
        self._print_tree(self.root, "", True)
    
    def _print_tree(self, node, indent, last):
        """Recursive helper to print tree structure."""
        if node:
            print(indent, end="")
            if last:
                print("└── ", end="")
                indent += "    "
            else:
                print("├── ", end="")
                indent += "│   "
            
            print(f"{node.key} (h:{node.height}, b:{self.get_balance(node)})")
            
            self._print_tree(node.left, indent, node.right is None)
            self._print_tree(node.right, indent, True)


# ============================================================================
# Red-Black Tree Implementation
# ============================================================================

class Color:
    """Color constants for Red-Black Tree."""
    RED = 1
    BLACK = 0

class RBNode:
    """Node for Red-Black Tree with color tracking."""
    def __init__(self, key, color=Color.RED):
        self.key = key
        self.left = None
        self.right = None
        self.parent = None
        self.color = color

class RedBlackTree:
    """Red-Black Tree - Self-balancing binary search tree."""
    
    def __init__(self):
        self.NIL = RBNode(0, Color.BLACK)  # Sentinel node
        self.root = self.NIL
    
    def left_rotate(self, x):
        """Left rotation."""
        y = x.right
        x.right = y.left
        
        if y.left != self.NIL:
            y.left.parent = x
        
        y.parent = x.parent
        
        if x.parent is None:
            self.root = y
        elif x == x.parent.left:
            x.parent.left = y
        else:
            x.parent.right = y
        
        y.left = x
        x.parent = y
    
    def right_rotate(self, x):
        """Right rotation."""
        y = x.left
        x.left = y.right
        
        if y.right != self.NIL:
            y.right.parent = x
        
        y.parent = x.parent
        
        if x.parent is None:
            self.root = y
        elif x == x.parent.right:
            x.parent.right = y
        else:
            x.parent.left = y
        
        y.right = x
        x.parent = y
    
    def insert(self, key):
        """Insert a key into the Red-Black tree."""
        node = RBNode(key)
        node.left = self.NIL
        node.right = self.NIL
        
        y = None
        x = self.root
        
        # Find insertion point
        while x != self.NIL:
            y = x
            if node.key < x.key:
                x = x.left
            else:
                x = x.right
        
        node.parent = y
        
        if y is None:
            self.root = node
        elif node.key < y.key:
            y.left = node
        else:
            y.right = node
        
        if node.parent is None:
            node.color = Color.BLACK
            return
        
        if node.parent.parent is None:
            return
        
        self._fix_insert(node)
    
    def _fix_insert(self, k):
        """Fix Red-Black tree properties after insertion."""
        while k.parent.color == Color.RED:
            if k.parent == k.parent.parent.right:
                u = k.parent.parent.left  # Uncle
                if u.color == Color.RED:
                    # Case 1: Uncle is red
                    u.color = Color.BLACK
                    k.parent.color = Color.BLACK
                    k.parent.parent.color = Color.RED
                    k = k.parent.parent
                else:
                    # Case 2: Uncle is black
                    if k == k.parent.left:
                        k = k.parent
                        self.right_rotate(k)
                    # Case 3: Uncle is black, k is right child
                    k.parent.color = Color.BLACK
                    k.parent.parent.color = Color.RED
                    self.left_rotate(k.parent.parent)
            else:
                u = k.parent.parent.right  # Uncle
                if u.color == Color.RED:
                    # Case 1: Uncle is red
                    u.color = Color.BLACK
                    k.parent.color = Color.BLACK
                    k.parent.parent.color = Color.RED
                    k = k.parent.parent
                else:
                    # Case 2: Uncle is black
                    if k == k.parent.right:
                        k = k.parent
                        self.left_rotate(k)
                    # Case 3: Uncle is black, k is left child
                    k.parent.color = Color.BLACK
                    k.parent.parent.color = Color.RED
                    self.right_rotate(k.parent.parent)
            
            if k == self.root:
                break
        
        self.root.color = Color.BLACK
    
    def delete(self, key):
        """Delete a key from the Red-Black tree."""
        z = self._search_node(self.root, key)
        if z == self.NIL:
            return
        
        y = z
        y_original_color = y.color
        
        if z.left == self.NIL:
            x = z.right
            self._rb_transplant(z, z.right)
        elif z.right == self.NIL:
            x = z.left
            self._rb_transplant(z, z.left)
        else:
            y = self._minimum(z.right)
            y_original_color = y.color
            x = y.right
            if y.parent == z:
                x.parent = y
            else:
                self._rb_transplant(y, y.right)
                y.right = z.right
                y.right.parent = y
            
            self._rb_transplant(z, y)
            y.left = z.left
            y.left.parent = y
            y.color = z.color
        
        if y_original_color == Color.BLACK:
            self._fix_delete(x)
    
    def _rb_transplant(self, u, v):
        """Replace subtree rooted at u with subtree rooted at v."""
        if u.parent is None:
            self.root = v
        elif u == u.parent.left:
            u.parent.left = v
        else:
            u.parent.right = v
        v.parent = u.parent
    
    def _minimum(self, node):
        """Find minimum node in subtree."""
        while node.left != self.NIL:
            node = node.left
        return node
    
    def _fix_delete(self, x):
        """Fix Red-Black tree properties after deletion."""
        while x != self.root and x.color == Color.BLACK:
            if x == x.parent.left:
                s = x.parent.right  # Sibling
                if s.color == Color.RED:
                    # Case 1: Sibling is red
                    s.color = Color.BLACK
                    x.parent.color = Color.RED
                    self.left_rotate(x.parent)
                    s = x.parent.right
                
                if s.left.color == Color.BLACK and s.right.color == Color.BLACK:
                    # Case 2: Both children of sibling are black
                    s.color = Color.RED
                    x = x.parent
                else:
                    if s.right.color == Color.BLACK:
                        # Case 3: Right child of sibling is black
                        s.left.color = Color.BLACK
                        s.color = Color.RED
                        self.right_rotate(s)
                        s = x.parent.right
                    
                    # Case 4: Right child of sibling is red
                    s.color = x.parent.color
                    x.parent.color = Color.BLACK
                    s.right.color = Color.BLACK
                    self.left_rotate(x.parent)
                    x = self.root
            else:
                s = x.parent.left  # Sibling
                if s.color == Color.RED:
                    # Case 1: Sibling is red
                    s.color = Color.BLACK
                    x.parent.color = Color.RED
                    self.right_rotate(x.parent)
                    s = x.parent.left
                
                if s.right.color == Color.BLACK and s.left.color == Color.BLACK:
                    # Case 2: Both children of sibling are black
                    s.color = Color.RED
                    x = x.parent
                else:
                    if s.left.color == Color.BLACK:
                        # Case 3: Left child of sibling is black
                        s.right.color = Color.BLACK
                        s.color = Color.RED
                        self.left_rotate(s)
                        s = x.parent.left
                    
                    # Case 4: Left child of sibling is red
                    s.color = x.parent.color
                    x.parent.color = Color.BLACK
                    s.left.color = Color.BLACK
                    self.right_rotate(x.parent)
                    x = self.root
        
        x.color = Color.BLACK
    
    def search(self, key):
        """Search for a key in the Red-Black tree."""
        node = self._search_node(self.root, key)
        return node != self.NIL
    
    def _search_node(self, node, key):
        """Recursive helper to search for a key."""
        if node == self.NIL or key == node.key:
            return node
        
        if key < node.key:
            return self._search_node(node.left, key)
        return self._search_node(node.right, key)
    
    def inorder_traversal(self):
        """Inorder traversal of the tree."""
        result = []
        self._inorder(self.root, result)
        return result
    
    def _inorder(self, node, result):
        """Recursive helper for inorder traversal."""
        if node != self.NIL:
            self._inorder(node.left, result)
            result.append(node.key)
            self._inorder(node.right, result)
    
    def print_tree(self):
        """Print tree structure."""
        self._print_tree(self.root, "", True)
    
    def _print_tree(self, node, indent, last):
        """Recursive helper to print tree structure."""
        if node != self.NIL:
            print(indent, end="")
            if last:
                print("└── ", end="")
                indent += "    "
            else:
                print("├── ", end="")
                indent += "│   "
            
            color_str = "R" if node.color == Color.RED else "B"
            print(f"{node.key} ({color_str})")
            
            self._print_tree(node.left, indent, node.right == self.NIL)
            self._print_tree(node.right, indent, True)


# ============================================================================
# Demonstration of Balanced Binary Trees
# ============================================================================

print("\n" + "-"*80)
print("AVL TREE DEMONSTRATION")
print("-"*80)

# Create AVL tree
avl = AVLTree()

# Insert elements
print("\n1. Inserting elements: [10, 20, 30, 40, 50, 25]")
values = [10, 20, 30, 40, 50, 25]
for val in values:
    avl.insert(val)
    print(f"   Inserted {val}")

print("\n2. AVL Tree Structure:")
avl.print_tree()

print("\n3. Inorder Traversal (sorted order):")
print(f"   {avl.inorder_traversal()}")

print("\n4. Searching for keys:")
test_keys = [20, 35, 25, 50]
for key in test_keys:
    result = avl.search(key)
    if result:
        print(f"   Key {key}: Found (height: {result.height}, balance: {avl.get_balance(result)})")
    else:
        print(f"   Key {key}: Not found")

print("\n5. Deleting elements: [30, 40]")
avl.delete(30)
print("   Deleted 30")
avl.delete(40)
print("   Deleted 40")

print("\n6. AVL Tree after deletion:")
avl.print_tree()

print("\n7. Inorder Traversal after deletion:")
print(f"   {avl.inorder_traversal()}")

print("\n" + "-"*80)
print("RED-BLACK TREE DEMONSTRATION")
print("-"*80)

# Create Red-Black tree
rb_tree = RedBlackTree()

# Insert elements
print("\n1. Inserting elements: [7, 3, 18, 10, 22, 8, 11, 26]")
rb_values = [7, 3, 18, 10, 22, 8, 11, 26]
for val in rb_values:
    rb_tree.insert(val)
    print(f"   Inserted {val}")

print("\n2. Red-Black Tree Structure:")
print("   (R = Red, B = Black)")
rb_tree.print_tree()

print("\n3. Inorder Traversal (sorted order):")
print(f"   {rb_tree.inorder_traversal()}")

print("\n4. Searching for keys:")
rb_test_keys = [10, 5, 18, 26]
for key in rb_test_keys:
    result = rb_tree.search(key)
    print(f"   Key {key}: {'Found' if result else 'Not found'}")

print("\n5. Deleting elements: [18, 11]")
rb_tree.delete(18)
print("   Deleted 18")
rb_tree.delete(11)
print("   Deleted 11")

print("\n6. Red-Black Tree after deletion:")
rb_tree.print_tree()

print("\n7. Inorder Traversal after deletion:")
print(f"   {rb_tree.inorder_traversal()}")

print("\n" + "-"*80)
print("COMPARISON: AVL vs RED-BLACK TREE")
print("-"*80)

print("\nAVL Tree Characteristics:")
print("  - Strictly balanced (height difference ≤ 1)")
print("  - Faster lookups due to better balance")
print("  - More rotations during insert/delete")
print("  - Better for read-heavy workloads")

print("\nRed-Black Tree Characteristics:")
print("  - Loosely balanced (longest path ≤ 2 × shortest path)")
print("  - Fewer rotations during insert/delete")
print("  - Better for write-heavy workloads")
print("  - Used in many standard libraries (C++ std::map, Java TreeMap)")

print("\n" + "="*80)
print("Both trees guarantee O(log n) time complexity for:")
print("  - Insert: O(log n)")
print("  - Delete: O(log n)")
print("  - Search: O(log n)")
print("="*80)
