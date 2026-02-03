# 4. Object-Oriented Programming (OOP) - Classes and Objects

Object-Oriented Programming is a programming paradigm that uses objects and classes to organize code. This lesson covers creating classes, working with objects, inheritance, polymorphism, and encapsulation.

## Understanding Classes and Objects

### What is a Class?

A class is a blueprint for creating objects. It defines the attributes (data) and methods (functions) that objects of that class will have.

### What is an Object?

An object is an instance of a class. It has its own set of attributes and can use the methods defined in the class.

```python
# Simple class example
class Dog:
    """A simple Dog class."""
    
    # Class attribute (shared by all instances)
    species = "Canis familiaris"
    
    def __init__(self, name, age, breed):
        """Initialize a new Dog instance."""
        # Instance attributes (unique to each instance)
        self.name = name
        self.age = age
        self.breed = breed
        self.is_hungry = True
    
    def bark(self):
        """Make the dog bark."""
        return f"{self.name} says: Woof!"
    
    def eat(self):
        """Feed the dog."""
        if self.is_hungry:
            self.is_hungry = False
            return f"{self.name} is eating and is no longer hungry."
        else:
            return f"{self.name} is not hungry right now."
    
    def sleep(self):
        """Make the dog sleep."""
        return f"{self.name} is sleeping peacefully."
    
    def __str__(self):
        """String representation of the dog."""
        return f"{self.name} is a {self.age}-year-old {self.breed}"

# Creating objects (instances)
dog1 = Dog("Buddy", 3, "Golden Retriever")
dog2 = Dog("Max", 5, "German Shepherd")

print("=== Dog Class Demo ===")
print(dog1)
print(dog2)
print(f"Species: {Dog.species}")  # Class attribute

print(dog1.bark())
print(dog1.eat())
print(dog1.eat())  # Already fed
print(dog2.sleep())
```

## Class Attributes and Methods

### Instance vs Class Attributes

```python
class Student:
    """A Student class demonstrating different types of attributes."""
    
    # Class attribute (shared by all instances)
    school_name = "Python Academy"
    total_students = 0
    
    def __init__(self, name, student_id, grade):
        """Initialize a new Student instance."""
        # Instance attributes (unique to each instance)
        self.name = name
        self.student_id = student_id
        self.grade = grade
        self.courses = []
        
        # Increment class attribute
        Student.total_students += 1
    
    def add_course(self, course):
        """Add a course to the student's schedule."""
        if course not in self.courses:
            self.courses.append(course)
            return f"Added {course} to {self.name}'s schedule."
        else:
            return f"{course} is already in {self.name}'s schedule."
    
    def get_gpa(self):
        """Calculate GPA based on grade."""
        grade_points = {
            'A': 4.0, 'B': 3.0, 'C': 2.0, 'D': 1.0, 'F': 0.0
        }
        return grade_points.get(self.grade, 0.0)
    
    @classmethod
    def get_total_students(cls):
        """Class method to get total number of students."""
        return cls.total_students
    
    @classmethod
    def create_from_string(cls, student_string):
        """Class method to create student from string."""
        name, student_id, grade = student_string.split(',')
        return cls(name.strip(), student_id.strip(), grade.strip())
    
    @staticmethod
    def is_passing_grade(grade):
        """Static method to check if grade is passing."""
        return grade in ['A', 'B', 'C']
    
    def __str__(self):
        """String representation of the student."""
        return f"Student: {self.name} (ID: {self.student_id}, Grade: {self.grade})"

# Using the Student class
print("\n=== Student Class Demo ===")

student1 = Student("Alice", "S001", "A")
student2 = Student("Bob", "S002", "B")
student3 = Student("Charlie", "S003", "C")

print(student1)
print(f"GPA: {student1.get_gpa()}")

print(student1.add_course("Python Programming"))
print(student1.add_course("Data Science"))
print(student1.add_course("Python Programming"))  # Duplicate

print(f"Courses: {student1.courses}")
print(f"Total students: {Student.get_total_students()}")

# Using class method
student4 = Student.create_from_string("Diana, S004, A")
print(f"Created from string: {student4}")

# Using static method
print(f"Is 'B' passing? {Student.is_passing_grade('B')}")
print(f"Is 'F' passing? {Student.is_passing_grade('F')}")

print(f"School: {Student.school_name}")
```

## Special Methods (Magic Methods)

### Common Magic Methods

```python
class Book:
    """A Book class demonstrating magic methods."""
    
    def __init__(self, title, author, pages, price):
        """Initialize a new Book instance."""
        self.title = title
        self.author = author
        self.pages = pages
        self.price = price
        self.is_available = True
    
    def __str__(self):
        """String representation for users."""
        return f'"{self.title}" by {self.author}'
    
    def __repr__(self):
        """String representation for developers."""
        return f"Book('{self.title}', '{self.author}', {self.pages}, {self.price})"
    
    def __len__(self):
        """Return the number of pages."""
        return self.pages
    
    def __add__(self, other):
        """Add two books (combine pages)."""
        if isinstance(other, Book):
            return Book(
                f"{self.title} & {other.title}",
                f"{self.author} & {other.author}",
                self.pages + other.pages,
                self.price + other.price
            )
        return NotImplemented
    
    def __lt__(self, other):
        """Compare books by price (less than)."""
        if isinstance(other, Book):
            return self.price < other.price
        return NotImplemented
    
    def __eq__(self, other):
        """Check if two books are equal."""
        if isinstance(other, Book):
            return (self.title == other.title and 
                   self.author == other.author)
        return False
    
    def __hash__(self):
        """Make book hashable."""
        return hash((self.title, self.author))
    
    def borrow(self):
        """Borrow the book."""
        if self.is_available:
            self.is_available = False
            return f"'{self.title}' has been borrowed."
        else:
            return f"'{self.title}' is not available."
    
    def return_book(self):
        """Return the book."""
        if not self.is_available:
            self.is_available = True
            return f"'{self.title}' has been returned."
        else:
            return f"'{self.title}' is already available."

# Using magic methods
print("\n=== Magic Methods Demo ===")

book1 = Book("Python Programming", "John Doe", 350, 29.99)
book2 = Book("Data Science", "Jane Smith", 280, 34.99)
book3 = Book("Python Programming", "John Doe", 350, 29.99)

print(f"String representation: {book1}")
print(f"Developer representation: {repr(book1)}")
print(f"Number of pages: {len(book1)}")

# Comparison
print(f"Is book1 cheaper than book2? {book1 < book2}")
print(f"Are book1 and book3 equal? {book1 == book3}")
print(f"Are book1 and book2 equal? {book1 == book2}")

# Addition
combined_book = book1 + book2
print(f"Combined book: {combined_book}")

# Book borrowing
print(book1.borrow())
print(book1.borrow())  # Already borrowed
print(book1.return_book())
print(book1.return_book())  # Already returned
```

## Inheritance

### Basic Inheritance

```python
class Animal:
    """Base class for all animals."""
    
    def __init__(self, name, species, age):
        self.name = name
        self.species = species
        self.age = age
        self.is_alive = True
    
    def eat(self):
        """Animal eats."""
        return f"{self.name} is eating."
    
    def sleep(self):
        """Animal sleeps."""
        return f"{self.name} is sleeping."
    
    def make_sound(self):
        """Make a generic animal sound."""
        return f"{self.name} makes a sound."
    
    def __str__(self):
        return f"{self.name} is a {self.age}-year-old {self.species}"

class Dog(Animal):
    """Dog class inheriting from Animal."""
    
    def __init__(self, name, age, breed):
        # Call parent class constructor
        super().__init__(name, "Canine", age)
        self.breed = breed
        self.tricks = []
    
    def make_sound(self):
        """Override parent method."""
        return f"{self.name} barks: Woof! Woof!"
    
    def learn_trick(self, trick):
        """Dog-specific method."""
        if trick not in self.tricks:
            self.tricks.append(trick)
            return f"{self.name} learned {trick}!"
        else:
            return f"{self.name} already knows {trick}."
    
    def perform_trick(self, trick):
        """Perform a learned trick."""
        if trick in self.tricks:
            return f"{self.name} performs {trick}!"
        else:
            return f"{self.name} doesn't know {trick} yet."

class Cat(Animal):
    """Cat class inheriting from Animal."""
    
    def __init__(self, name, age, color):
        super().__init__(name, "Feline", age)
        self.color = color
        self.lives = 9
    
    def make_sound(self):
        """Override parent method."""
        return f"{self.name} meows: Meow! Meow!"
    
    def climb(self):
        """Cat-specific method."""
        return f"{self.name} climbs up high!"
    
    def lose_life(self):
        """Cat loses a life."""
        if self.lives > 1:
            self.lives -= 1
            return f"{self.name} has {self.lives} lives left."
        else:
            self.is_alive = False
            return f"{self.name} has used all 9 lives."

# Using inheritance
print("\n=== Inheritance Demo ===")

# Create animals
dog = Dog("Buddy", 3, "Golden Retriever")
cat = Cat("Whiskers", 2, "Orange")

print(dog)
print(cat)

# Inherited methods
print(dog.eat())
print(cat.sleep())

# Overridden methods
print(dog.make_sound())
print(cat.make_sound())

# Dog-specific methods
print(dog.learn_trick("sit"))
print(dog.learn_trick("roll over"))
print(dog.perform_trick("sit"))
print(dog.perform_trick("fetch"))

# Cat-specific methods
print(cat.climb())
print(cat.lose_life())
```

### Multiple Inheritance

```python
class Flyable:
    """Mixin class for flying ability."""
    
    def fly(self):
        return f"{self.name} is flying!"

class Swimmable:
    """Mixin class for swimming ability."""
    
    def swim(self):
        return f"{self.name} is swimming!"

class Duck(Animal, Flyable, Swimmable):
    """Duck class with multiple inheritance."""
    
    def __init__(self, name, age, color):
        super().__init__(name, "Duck", age)
        self.color = color
    
    def make_sound(self):
        return f"{self.name} quacks: Quack! Quack!"
    
    def waddle(self):
        return f"{self.name} waddles around."

# Using multiple inheritance
print("\n=== Multiple Inheritance Demo ===")

duck = Duck("Donald", 1, "White")
print(duck)

# Inherited methods from Animal
print(duck.eat())
print(duck.make_sound())

# Methods from Flyable mixin
print(duck.fly())

# Methods from Swimmable mixin
print(duck.swim())

# Duck-specific method
print(duck.waddle())
```

## Polymorphism

### Method Overriding and Duck Typing

```python
class Shape:
    """Base class for shapes."""
    
    def __init__(self, name):
        self.name = name
    
    def area(self):
        """Calculate area - to be overridden by subclasses."""
        raise NotImplementedError("Subclass must implement area method")
    
    def perimeter(self):
        """Calculate perimeter - to be overridden by subclasses."""
        raise NotImplementedError("Subclass must implement perimeter method")
    
    def describe(self):
        """Describe the shape."""
        return f"This is a {self.name} with area {self.area():.2f} and perimeter {self.perimeter():.2f}"

class Rectangle(Shape):
    """Rectangle class."""
    
    def __init__(self, width, height):
        super().__init__("Rectangle")
        self.width = width
        self.height = height
    
    def area(self):
        """Calculate rectangle area."""
        return self.width * self.height
    
    def perimeter(self):
        """Calculate rectangle perimeter."""
        return 2 * (self.width + self.height)

class Circle(Shape):
    """Circle class."""
    
    def __init__(self, radius):
        super().__init__("Circle")
        self.radius = radius
    
    def area(self):
        """Calculate circle area."""
        import math
        return math.pi * self.radius ** 2
    
    def perimeter(self):
        """Calculate circle perimeter (circumference)."""
        import math
        return 2 * math.pi * self.radius

class Triangle(Shape):
    """Triangle class."""
    
    def __init__(self, base, height, side1, side2):
        super().__init__("Triangle")
        self.base = base
        self.height = height
        self.side1 = side1
        self.side2 = side2
    
    def area(self):
        """Calculate triangle area."""
        return 0.5 * self.base * self.height
    
    def perimeter(self):
        """Calculate triangle perimeter."""
        return self.base + self.side1 + self.side2

# Polymorphism demonstration
print("\n=== Polymorphism Demo ===")

shapes = [
    Rectangle(5, 3),
    Circle(4),
    Triangle(6, 4, 5, 5)
]

# Same interface, different implementations
for shape in shapes:
    print(shape.describe())

# Duck typing example
class Calculator:
    """Calculator that works with any object that has area() method."""
    
    @staticmethod
    def calculate_total_area(shapes):
        """Calculate total area of all shapes."""
        total = 0
        for shape in shapes:
            # Duck typing: if it has area() method, we can use it
            if hasattr(shape, 'area'):
                total += shape.area()
        return total
    
    @staticmethod
    def find_largest_area(shapes):
        """Find the shape with the largest area."""
        if not shapes:
            return None
        
        largest = shapes[0]
        for shape in shapes[1:]:
            if hasattr(shape, 'area') and shape.area() > largest.area():
                largest = shape
        return largest

print(f"\nTotal area: {Calculator.calculate_total_area(shapes):.2f}")
largest = Calculator.find_largest_area(shapes)
print(f"Largest area shape: {largest.name} with area {largest.area():.2f}")
```

## Encapsulation

### Private and Protected Attributes

```python
class BankAccount:
    """Bank account class demonstrating encapsulation."""
    
    def __init__(self, account_holder, initial_balance=0):
        # Public attributes
        self.account_holder = account_holder
        self.account_number = self._generate_account_number()
        
        # Protected attributes (convention: single underscore)
        self._balance = initial_balance
        self._transaction_history = []
        
        # Private attributes (convention: double underscore)
        self.__pin = self._generate_pin()
        self.__is_locked = False
    
    def _generate_account_number(self):
        """Protected method to generate account number."""
        import random
        return f"ACC{random.randint(100000, 999999)}"
    
    def _generate_pin(self):
        """Protected method to generate PIN."""
        import random
        return f"{random.randint(1000, 9999)}"
    
    def __validate_pin(self, pin):
        """Private method to validate PIN."""
        return pin == self.__pin
    
    def deposit(self, amount, pin):
        """Deposit money into account."""
        if self.__is_locked:
            return "Account is locked. Contact customer service."
        
        if not self.__validate_pin(pin):
            return "Invalid PIN."
        
        if amount <= 0:
            return "Deposit amount must be positive."
        
        self._balance += amount
        self._transaction_history.append(f"Deposit: +${amount}")
        return f"Deposited ${amount}. New balance: ${self._balance}"
    
    def withdraw(self, amount, pin):
        """Withdraw money from account."""
        if self.__is_locked:
            return "Account is locked. Contact customer service."
        
        if not self.__validate_pin(pin):
            return "Invalid PIN."
        
        if amount <= 0:
            return "Withdrawal amount must be positive."
        
        if amount > self._balance:
            return "Insufficient funds."
        
        self._balance -= amount
        self._transaction_history.append(f"Withdrawal: -${amount}")
        return f"Withdrew ${amount}. New balance: ${self._balance}"
    
    def get_balance(self, pin):
        """Get account balance."""
        if self.__is_locked:
            return "Account is locked. Contact customer service."
        
        if not self.__validate_pin(pin):
            return "Invalid PIN."
        
        return f"Balance: ${self._balance}"
    
    def get_transaction_history(self, pin):
        """Get transaction history."""
        if self.__is_locked:
            return "Account is locked. Contact customer service."
        
        if not self.__validate_pin(pin):
            return "Invalid PIN."
        
        return self._transaction_history.copy()
    
    def lock_account(self, pin):
        """Lock the account."""
        if self.__validate_pin(pin):
            self.__is_locked = True
            return "Account has been locked."
        else:
            return "Invalid PIN. Cannot lock account."
    
    def unlock_account(self, pin):
        """Unlock the account."""
        if self.__validate_pin(pin):
            self.__is_locked = False
            return "Account has been unlocked."
        else:
            return "Invalid PIN. Cannot unlock account."
    
    def change_pin(self, old_pin, new_pin):
        """Change account PIN."""
        if not self.__validate_pin(old_pin):
            return "Invalid current PIN."
        
        if len(new_pin) != 4 or not new_pin.isdigit():
            return "New PIN must be 4 digits."
        
        self.__pin = new_pin
        return "PIN changed successfully."
    
    def __str__(self):
        return f"Account: {self.account_number}, Holder: {self.account_holder}, Balance: ${self._balance}"

# Using encapsulation
print("\n=== Encapsulation Demo ===")

account = BankAccount("John Doe", 1000)
print(account)

# Access public attributes
print(f"Account holder: {account.account_holder}")
print(f"Account number: {account.account_number}")

# Try to access protected attribute (works but not recommended)
print(f"Balance (protected): ${account._balance}")

# Try to access private attribute (will be mangled)
print(f"PIN (private): {account._BankAccount__pin}")  # Name mangling

# Use proper methods
print(account.deposit(500, account._BankAccount__pin))  # Using mangled name for demo
print(account.withdraw(200, account._BankAccount__pin))
print(account.get_balance(account._BankAccount__pin))

# Get transaction history
history = account.get_transaction_history(account._BankAccount__pin)
print(f"Transaction history: {history}")

# Lock and unlock account
print(account.lock_account(account._BankAccount__pin))
print(account.deposit(100, account._BankAccount__pin))  # Should fail
print(account.unlock_account(account._BankAccount__pin))

# Change PIN
print(account.change_pin(account._BankAccount__pin, "1234"))
```

## Property Decorators

### Using @property for Controlled Access

```python
class Temperature:
    """Temperature class using property decorators."""
    
    def __init__(self, celsius=0):
        self._celsius = celsius
    
    @property
    def celsius(self):
        """Get temperature in Celsius."""
        return self._celsius
    
    @celsius.setter
    def celsius(self, value):
        """Set temperature in Celsius."""
        if value < -273.15:
            raise ValueError("Temperature cannot be below absolute zero (-273.15°C)")
        self._celsius = value
    
    @property
    def fahrenheit(self):
        """Get temperature in Fahrenheit."""
        return self._celsius * 9/5 + 32
    
    @fahrenheit.setter
    def fahrenheit(self, value):
        """Set temperature in Fahrenheit."""
        celsius = (value - 32) * 5/9
        if celsius < -273.15:
            raise ValueError("Temperature cannot be below absolute zero")
        self._celsius = celsius
    
    @property
    def kelvin(self):
        """Get temperature in Kelvin."""
        return self._celsius + 273.15
    
    @kelvin.setter
    def kelvin(self, value):
        """Set temperature in Kelvin."""
        if value < 0:
            raise ValueError("Temperature cannot be below absolute zero (0K)")
        self._celsius = value - 273.15
    
    def __str__(self):
        return f"{self._celsius}°C ({self.fahrenheit}°F, {self.kelvin}K)"

# Using property decorators
print("\n=== Property Decorators Demo ===")

temp = Temperature(25)
print(f"Initial: {temp}")

# Using setters
temp.celsius = 30
print(f"Set to 30°C: {temp}")

temp.fahrenheit = 86
print(f"Set to 86°F: {temp}")

temp.kelvin = 300
print(f"Set to 300K: {temp}")

# Validation example
try:
    temp.celsius = -300  # Below absolute zero
except ValueError as e:
    print(f"Error: {e}")

try:
    temp.kelvin = -10  # Below absolute zero
except ValueError as e:
    print(f"Error: {e}")
```

## Practical Examples

### Example 1: Library Management System

```python
class LibraryItem:
    """Base class for library items."""
    
    def __init__(self, title, author, item_id):
        self.title = title
        self.author = author
        self.item_id = item_id
        self.is_borrowed = False
        self.borrower = None
        self.due_date = None
    
    def borrow(self, borrower, due_date):
        """Borrow the item."""
        if self.is_borrowed:
            return f"'{self.title}' is already borrowed."
        
        self.is_borrowed = True
        self.borrower = borrower
        self.due_date = due_date
        return f"'{self.title}' has been borrowed by {borrower}."
    
    def return_item(self):
        """Return the item."""
        if not self.is_borrowed:
            return f"'{self.title}' is not currently borrowed."
        
        borrower = self.borrower
        self.is_borrowed = False
        self.borrower = None
        self.due_date = None
        return f"'{self.title}' has been returned by {borrower}."
    
    def __str__(self):
        status = f"Borrowed by {self.borrower}" if self.is_borrowed else "Available"
        return f"{self.title} by {self.author} - {status}"

class Book(LibraryItem):
    """Book class."""
    
    def __init__(self, title, author, item_id, isbn, pages):
        super().__init__(title, author, item_id)
        self.isbn = isbn
        self.pages = pages
        self.borrow_period = 14  # days
    
    def get_info(self):
        """Get detailed book information."""
        return f"Book: {self.title}, ISBN: {self.isbn}, Pages: {self.pages}"

class DVD(LibraryItem):
    """DVD class."""
    
    def __init__(self, title, director, item_id, duration):
        super().__init__(title, director, item_id)
        self.director = director
        self.duration = duration  # minutes
        self.borrow_period = 7  # days
    
    def get_info(self):
        """Get detailed DVD information."""
        return f"DVD: {self.title}, Director: {self.director}, Duration: {self.duration} minutes"

class Library:
    """Library management system."""
    
    def __init__(self, name):
        self.name = name
        self.items = {}
        self.borrowers = {}
    
    def add_item(self, item):
        """Add an item to the library."""
        self.items[item.item_id] = item
        return f"Added '{item.title}' to the library."
    
    def remove_item(self, item_id):
        """Remove an item from the library."""
        if item_id in self.items:
            item = self.items.pop(item_id)
            return f"Removed '{item.title}' from the library."
        return "Item not found."
    
    def borrow_item(self, item_id, borrower_name):
        """Borrow an item."""
        if item_id not in self.items:
            return "Item not found."
        
        item = self.items[item_id]
        from datetime import datetime, timedelta
        
        due_date = datetime.now() + timedelta(days=item.borrow_period)
        return item.borrow(borrower_name, due_date)
    
    def return_item(self, item_id):
        """Return an item."""
        if item_id not in self.items:
            return "Item not found."
        
        item = self.items[item_id]
        return item.return_item()
    
    def search_items(self, query):
        """Search for items by title or author."""
        results = []
        query = query.lower()
        
        for item in self.items.values():
            if (query in item.title.lower() or 
                query in item.author.lower()):
                results.append(item)
        
        return results
    
    def get_available_items(self):
        """Get all available items."""
        return [item for item in self.items.values() if not item.is_borrowed]
    
    def get_borrowed_items(self):
        """Get all borrowed items."""
        return [item for item in self.items.values() if item.is_borrowed]

# Using the library system
print("\n=== Library Management System Demo ===")

library = Library("Python Public Library")

# Add items
book1 = Book("Python Programming", "John Doe", "B001", "978-0123456789", 350)
book2 = Book("Data Science", "Jane Smith", "B002", "978-0123456790", 280)
dvd1 = DVD("Python Tutorial", "Tech Academy", "D001", 120)

print(library.add_item(book1))
print(library.add_item(book2))
print(library.add_item(dvd1))

# Borrow items
print(library.borrow_item("B001", "Alice"))
print(library.borrow_item("D001", "Bob"))

# Search items
search_results = library.search_items("python")
print(f"\nSearch results for 'python':")
for item in search_results:
    print(f"  - {item}")

# Show available items
available = library.get_available_items()
print(f"\nAvailable items ({len(available)}):")
for item in available:
    print(f"  - {item}")

# Show borrowed items
borrowed = library.get_borrowed_items()
print(f"\nBorrowed items ({len(borrowed)}):")
for item in borrowed:
    print(f"  - {item}")
```

## Key Takeaways

1. **Classes** are blueprints for creating objects
2. **Objects** are instances of classes with their own attributes and methods
3. **Inheritance** allows classes to inherit attributes and methods from parent classes
4. **Polymorphism** enables the same interface to work with different types of objects
5. **Encapsulation** protects data through private and protected attributes
6. **Magic methods** provide special functionality for classes
7. **Property decorators** provide controlled access to attributes
8. **Method overriding** allows subclasses to provide their own implementations

## Next Steps

In the next lesson, we'll explore Advanced Data Structures - stacks, queues, comprehensions, and nested data structures.
