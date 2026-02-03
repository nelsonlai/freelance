# 1. Advanced Object-Oriented Programming - Professional Design Patterns

Building on intermediate OOP concepts, this lesson explores advanced object-oriented programming techniques including abstract classes, multiple inheritance, advanced magic methods, decorators, and design patterns used in professional Python development.

## Abstract Classes and Interfaces

### Understanding Abstract Base Classes (ABCs)

Abstract classes define a blueprint for other classes but cannot be instantiated themselves. They enforce that subclasses implement specific methods.

```python
from abc import ABC, abstractmethod
import math

class Shape(ABC):
    """Abstract base class for geometric shapes."""
    
    def __init__(self, name):
        self.name = name
    
    @abstractmethod
    def area(self):
        """Calculate the area of the shape."""
        pass
    
    @abstractmethod
    def perimeter(self):
        """Calculate the perimeter of the shape."""
        pass
    
    def describe(self):
        """Concrete method available to all subclasses."""
        return f"This is a {self.name} with area {self.area():.2f} and perimeter {self.perimeter():.2f}"

class Rectangle(Shape):
    """Rectangle implementation of Shape."""
    
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
    """Circle implementation of Shape."""
    
    def __init__(self, radius):
        super().__init__("Circle")
        self.radius = radius
    
    def area(self):
        """Calculate circle area."""
        return math.pi * self.radius ** 2
    
    def perimeter(self):
        """Calculate circle perimeter (circumference)."""
        return 2 * math.pi * self.radius

# Using abstract classes
print("=== Abstract Classes Demo ===")
shapes = [
    Rectangle(5, 3),
    Circle(4),
    Rectangle(10, 2)
]

for shape in shapes:
    print(shape.describe())

# This would raise an error:
# shape = Shape("Generic")  # TypeError: Can't instantiate abstract class
```

### Advanced Abstract Classes with Properties

```python
from abc import ABC, abstractmethod, abstractproperty

class Animal(ABC):
    """Abstract base class for animals."""
    
    def __init__(self, name, species):
        self.name = name
        self.species = species
        self._energy = 100
    
    @abstractmethod
    def make_sound(self):
        """Every animal must be able to make a sound."""
        pass
    
    @abstractmethod
    def move(self):
        """Every animal must be able to move."""
        pass
    
    @property
    @abstractmethod
    def habitat(self):
        """Every animal has a habitat."""
        pass
    
    @property
    def energy(self):
        """Get current energy level."""
        return self._energy
    
    @energy.setter
    def energy(self, value):
        """Set energy level with validation."""
        if 0 <= value <= 100:
            self._energy = value
        else:
            raise ValueError("Energy must be between 0 and 100")
    
    def sleep(self):
        """Restore energy."""
        self.energy = min(100, self.energy + 20)
        return f"{self.name} is sleeping and restoring energy"

class Dog(Animal):
    """Dog implementation of Animal."""
    
    def __init__(self, name, breed):
        super().__init__(name, "Canine")
        self.breed = breed
    
    def make_sound(self):
        """Dog makes a barking sound."""
        self.energy -= 5
        return f"{self.name} barks: Woof! Woof!"
    
    def move(self):
        """Dog runs."""
        if self.energy >= 10:
            self.energy -= 10
            return f"{self.name} runs around the yard"
        else:
            return f"{self.name} is too tired to move"
    
    @property
    def habitat(self):
        """Dog's natural habitat."""
        return "Domestic environment"
    
    def fetch(self):
        """Dog-specific method."""
        if self.energy >= 15:
            self.energy -= 15
            return f"{self.name} fetches the ball"
        else:
            return f"{self.name} is too tired to fetch"

# Using the abstract animal class
print("\n=== Advanced Abstract Classes Demo ===")
dog = Dog("Buddy", "Golden Retriever")
print(dog.make_sound())
print(dog.move())
print(f"Energy: {dog.energy}")
print(f"Habitat: {dog.habitat}")
print(dog.sleep())
print(f"Energy after sleep: {dog.energy}")
print(dog.fetch())
```

## Multiple Inheritance and Method Resolution Order (MRO)

### Understanding MRO

Python uses the C3 Linearization algorithm to determine the order in which methods are resolved in multiple inheritance.

```python
class Flyable:
    """Mixin for flying capability."""
    
    def fly(self):
        return f"{self.name} is flying high!"
    
    def land(self):
        return f"{self.name} lands safely"

class Swimmable:
    """Mixin for swimming capability."""
    
    def swim(self):
        return f"{self.name} is swimming gracefully"
    
    def dive(self):
        return f"{self.name} dives deep into the water"

class Walkable:
    """Mixin for walking capability."""
    
    def walk(self):
        return f"{self.name} is walking on land"
    
    def run(self):
        return f"{self.name} is running fast"

class Duck(Walkable, Swimmable, Flyable):
    """Duck with multiple capabilities."""
    
    def __init__(self, name):
        self.name = name
    
    def quack(self):
        return f"{self.name} quacks: Quack! Quack!"

class Penguin(Walkable, Swimmable):
    """Penguin that can walk and swim but not fly."""
    
    def __init__(self, name):
        self.name = name
    
    def waddle(self):
        return f"{self.name} waddles cutely"

# Demonstrating MRO
print("=== Multiple Inheritance Demo ===")

duck = Duck("Donald")
print(duck.quack())
print(duck.walk())
print(duck.swim())
print(duck.fly())
print(duck.dive())
print(duck.land())

penguin = Penguin("Pingu")
print(penguin.waddle())
print(penguin.swim())
print(penguin.dive())

# Check Method Resolution Order
print(f"\nDuck MRO: {Duck.__mro__}")
print(f"Penguin MRO: {Penguin.__mro__}")

# Demonstrate method resolution
print(f"Duck's walk method comes from: {Duck.__mro__[1].__name__}")
print(f"Duck's swim method comes from: {Duck.__mro__[2].__name__}")
```

### Complex Multiple Inheritance Example

```python
class Animal:
    """Base animal class."""
    
    def __init__(self, name, species):
        self.name = name
        self.species = species
        self.energy = 100
    
    def eat(self):
        self.energy = min(100, self.energy + 20)
        return f"{self.name} is eating and gaining energy"
    
    def sleep(self):
        self.energy = min(100, self.energy + 30)
        return f"{self.name} is sleeping and restoring energy"

class Carnivore:
    """Mixin for carnivorous animals."""
    
    def hunt(self):
        return f"{self.name} is hunting for prey"
    
    def eat_meat(self):
        return f"{self.name} is eating meat"

class Herbivore:
    """Mixin for herbivorous animals."""
    
    def graze(self):
        return f"{self.name} is grazing on plants"
    
    def eat_plants(self):
        return f"{self.name} is eating plants"

class Aquatic:
    """Mixin for aquatic animals."""
    
    def swim(self):
        return f"{self.name} is swimming in water"
    
    def dive(self):
        return f"{self.name} is diving deep"

class Terrestrial:
    """Mixin for terrestrial animals."""
    
    def walk(self):
        return f"{self.name} is walking on land"
    
    def run(self):
        return f"{self.name} is running"

class Lion(Animal, Carnivore, Terrestrial):
    """Lion - carnivorous terrestrial animal."""
    
    def __init__(self, name):
        super().__init__(name, "Lion")
    
    def roar(self):
        return f"{self.name} roars loudly!"

class Elephant(Animal, Herbivore, Terrestrial):
    """Elephant - herbivorous terrestrial animal."""
    
    def __init__(self, name):
        super().__init__(name, "Elephant")
    
    def trumpet(self):
        return f"{self.name} trumpets with its trunk!"

class Shark(Animal, Carnivore, Aquatic):
    """Shark - carnivorous aquatic animal."""
    
    def __init__(self, name):
        super().__init__(name, "Shark")
    
    def attack(self):
        return f"{self.name} attacks with its sharp teeth!"

# Using complex multiple inheritance
print("\n=== Complex Multiple Inheritance Demo ===")

lion = Lion("Simba")
print(lion.roar())
print(lion.hunt())
print(lion.walk())
print(lion.eat_meat())

elephant = Elephant("Dumbo")
print(elephant.trumpet())
print(elephant.graze())
print(elephant.walk())
print(elephant.eat_plants())

shark = Shark("Jaws")
print(shark.attack())
print(shark.hunt())
print(shark.swim())
print(shark.dive())

# Check MRO for complex inheritance
print(f"\nLion MRO: {[cls.__name__ for cls in Lion.__mro__]}")
print(f"Elephant MRO: {[cls.__name__ for cls in Elephant.__mro__]}")
print(f"Shark MRO: {[cls.__name__ for cls in Shark.__mro__]}")
```

## Advanced Magic Methods

### Context Managers with __enter__ and __exit__

```python
class DatabaseConnection:
    """Database connection with context manager support."""
    
    def __init__(self, connection_string):
        self.connection_string = connection_string
        self.connection = None
        self.is_connected = False
    
    def __enter__(self):
        """Enter the context manager."""
        print(f"Connecting to database: {self.connection_string}")
        self.connection = f"Connection to {self.connection_string}"
        self.is_connected = True
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        """Exit the context manager."""
        if self.is_connected:
            print(f"Closing connection to: {self.connection_string}")
            self.connection = None
            self.is_connected = False
        
        if exc_type is not None:
            print(f"Exception occurred: {exc_type.__name__}: {exc_val}")
            # Return False to propagate the exception
            # Return True to suppress the exception
            return False
        
        return True
    
    def execute_query(self, query):
        """Execute a database query."""
        if not self.is_connected:
            raise RuntimeError("Not connected to database")
        return f"Executed: {query}"

# Using context managers
print("=== Context Manager Demo ===")

try:
    with DatabaseConnection("postgresql://localhost:5432/mydb") as db:
        result1 = db.execute_query("SELECT * FROM users")
        print(result1)
        
        result2 = db.execute_query("INSERT INTO users VALUES (1, 'John')")
        print(result2)
        
        # This will cause an exception
        # raise ValueError("Simulated database error")
        
except Exception as e:
    print(f"Caught exception: {e}")

# Custom context manager with multiple resources
class FileProcessor:
    """File processor with context manager support."""
    
    def __init__(self, input_file, output_file):
        self.input_file = input_file
        self.output_file = output_file
        self.input_handle = None
        self.output_handle = None
    
    def __enter__(self):
        """Open both files."""
        print(f"Opening input file: {self.input_file}")
        self.input_handle = open(self.input_file, 'r')
        
        print(f"Opening output file: {self.output_file}")
        self.output_handle = open(self.output_file, 'w')
        
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        """Close both files."""
        if self.input_handle:
            self.input_handle.close()
            print(f"Closed input file: {self.input_file}")
        
        if self.output_handle:
            self.output_handle.close()
            print(f"Closed output file: {self.output_file}")
        
        if exc_type is not None:
            print(f"Exception in file processing: {exc_type.__name__}")
        
        return False  # Propagate exceptions
    
    def process_line(self, line):
        """Process a line from input file."""
        processed = line.strip().upper()
        self.output_handle.write(processed + '\n')
        return processed

# Using file processor context manager
print("\n=== File Processor Context Manager Demo ===")

# Create test files
with open('test_input.txt', 'w') as f:
    f.write("hello world\n")
    f.write("python programming\n")
    f.write("advanced oop\n")

try:
    with FileProcessor('test_input.txt', 'test_output.txt') as processor:
        with open('test_input.txt', 'r') as input_file:
            for line in input_file:
                processed = processor.process_line(line)
                print(f"Processed: {processed}")
except Exception as e:
    print(f"Error: {e}")

# Clean up test files
import os
try:
    os.remove('test_input.txt')
    os.remove('test_output.txt')
except FileNotFoundError:
    pass
```

### Advanced Magic Methods for Custom Collections

```python
class CustomList:
    """Custom list implementation with advanced magic methods."""
    
    def __init__(self, items=None):
        self._items = list(items) if items else []
    
    def __len__(self):
        """Return length of the list."""
        return len(self._items)
    
    def __getitem__(self, index):
        """Get item at index (supports slicing)."""
        if isinstance(index, slice):
            return CustomList(self._items[index])
        return self._items[index]
    
    def __setitem__(self, index, value):
        """Set item at index."""
        self._items[index] = value
    
    def __delitem__(self, index):
        """Delete item at index."""
        del self._items[index]
    
    def __iter__(self):
        """Return iterator."""
        return iter(self._items)
    
    def __contains__(self, item):
        """Check if item is in list."""
        return item in self._items
    
    def __add__(self, other):
        """Add two lists together."""
        if isinstance(other, CustomList):
            return CustomList(self._items + other._items)
        elif isinstance(other, list):
            return CustomList(self._items + other)
        return NotImplemented
    
    def __mul__(self, n):
        """Multiply list by a number."""
        if isinstance(n, int):
            return CustomList(self._items * n)
        return NotImplemented
    
    def __str__(self):
        """String representation."""
        return f"CustomList({self._items})"
    
    def __repr__(self):
        """Developer representation."""
        return f"CustomList({self._items!r})"
    
    def __bool__(self):
        """Boolean representation (empty list is False)."""
        return bool(self._items)
    
    def __eq__(self, other):
        """Check equality with another list."""
        if isinstance(other, CustomList):
            return self._items == other._items
        elif isinstance(other, list):
            return self._items == other
        return False
    
    def __lt__(self, other):
        """Less than comparison."""
        if isinstance(other, (CustomList, list)):
            return self._items < other._items
        return NotImplemented
    
    def __le__(self, other):
        """Less than or equal comparison."""
        if isinstance(other, (CustomList, list)):
            return self._items <= other._items
        return NotImplemented
    
    def __gt__(self, other):
        """Greater than comparison."""
        if isinstance(other, (CustomList, list)):
            return self._items > other._items
        return NotImplemented
    
    def __ge__(self, other):
        """Greater than or equal comparison."""
        if isinstance(other, (CustomList, list)):
            return self._items >= other._items
        return NotImplemented
    
    def append(self, item):
        """Append item to list."""
        self._items.append(item)
    
    def extend(self, items):
        """Extend list with items."""
        self._items.extend(items)
    
    def insert(self, index, item):
        """Insert item at index."""
        self._items.insert(index, item)
    
    def remove(self, item):
        """Remove first occurrence of item."""
        self._items.remove(item)
    
    def pop(self, index=-1):
        """Pop item at index."""
        return self._items.pop(index)
    
    def index(self, item):
        """Get index of item."""
        return self._items.index(item)
    
    def count(self, item):
        """Count occurrences of item."""
        return self._items.count(item)

# Using the custom list
print("=== Custom List Demo ===")

# Create custom lists
list1 = CustomList([1, 2, 3, 4, 5])
list2 = CustomList([6, 7, 8])

print(f"list1: {list1}")
print(f"list2: {list2}")
print(f"Length of list1: {len(list1)}")

# Indexing and slicing
print(f"list1[0]: {list1[0]}")
print(f"list1[1:3]: {list1[1:3]}")
print(f"list1[-1]: {list1[-1]}")

# Iteration
print("Iterating over list1:")
for item in list1:
    print(f"  {item}")

# Membership
print(f"3 in list1: {3 in list1}")
print(f"10 in list1: {10 in list1}")

# Addition
list3 = list1 + list2
print(f"list1 + list2: {list3}")

# Multiplication
list4 = list2 * 3
print(f"list2 * 3: {list4}")

# Comparison
print(f"list1 == [1, 2, 3, 4, 5]: {list1 == [1, 2, 3, 4, 5]}")
print(f"list1 < list2: {list1 < list2}")

# Boolean conversion
empty_list = CustomList()
print(f"bool(list1): {bool(list1)}")
print(f"bool(empty_list): {bool(empty_list)}")

# List methods
list1.append(6)
print(f"After append(6): {list1}")

list1.extend([7, 8, 9])
print(f"After extend([7, 8, 9]): {list1}")

list1.insert(0, 0)
print(f"After insert(0, 0): {list1}")

list1.remove(5)
print(f"After remove(5): {list1}")

popped = list1.pop()
print(f"Popped: {popped}, list1: {list1}")

print(f"Index of 3: {list1.index(3)}")
print(f"Count of 2: {list1.count(2)}")
```

## Class Decorators and Metaclasses

### Class Decorators

```python
def singleton(cls):
    """Class decorator that makes a class a singleton."""
    instances = {}
    
    def get_instance(*args, **kwargs):
        if cls not in instances:
            instances[cls] = cls(*args, **kwargs)
        return instances[cls]
    
    return get_instance

def debug_methods(cls):
    """Class decorator that adds debug logging to all methods."""
    for attr_name in dir(cls):
        attr = getattr(cls, attr_name)
        if callable(attr) and not attr_name.startswith('_'):
            def make_wrapper(func):
                def wrapper(*args, **kwargs):
                    print(f"DEBUG: Calling {cls.__name__}.{func.__name__} with args={args}, kwargs={kwargs}")
                    result = func(*args, **kwargs)
                    print(f"DEBUG: {cls.__name__}.{func.__name__} returned: {result}")
                    return result
                return wrapper
            
            setattr(cls, attr_name, make_wrapper(attr))
    
    return cls

def validate_types(**expected_types):
    """Class decorator that validates method parameter types."""
    def decorator(cls):
        original_init = cls.__init__
        
        def new_init(self, *args, **kwargs):
            # Validate types for __init__ parameters
            for i, (param_name, expected_type) in enumerate(expected_types.items()):
                if i < len(args):
                    if not isinstance(args[i], expected_type):
                        raise TypeError(f"{param_name} must be of type {expected_type.__name__}")
            
            original_init(self, *args, **kwargs)
        
        cls.__init__ = new_init
        return cls
    
    return decorator

# Using class decorators
@singleton
class DatabaseConnection:
    """Singleton database connection."""
    
    def __init__(self):
        self.connection_id = id(self)
        print(f"Creating database connection with ID: {self.connection_id}")
    
    def query(self, sql):
        return f"Executing query with connection {self.connection_id}: {sql}"

@debug_methods
class Calculator:
    """Calculator with debug logging."""
    
    def add(self, a, b):
        return a + b
    
    def multiply(self, a, b):
        return a * b
    
    def divide(self, a, b):
        if b == 0:
            raise ValueError("Cannot divide by zero")
        return a / b

@validate_types(name=str, age=int, email=str)
class Person:
    """Person with type validation."""
    
    def __init__(self, name, age, email):
        self.name = name
        self.age = age
        self.email = email
    
    def __str__(self):
        return f"Person(name='{self.name}', age={self.age}, email='{self.email}')"

# Using the decorated classes
print("=== Class Decorators Demo ===")

# Singleton demo
db1 = DatabaseConnection()
db2 = DatabaseConnection()
print(f"db1 is db2: {db1 is db2}")
print(f"db1.connection_id: {db1.connection_id}")
print(f"db2.connection_id: {db2.connection_id}")

# Debug methods demo
calc = Calculator()
result1 = calc.add(5, 3)
result2 = calc.multiply(4, 7)
try:
    result3 = calc.divide(10, 0)
except ValueError as e:
    print(f"Caught error: {e}")

# Type validation demo
try:
    person1 = Person("Alice", 25, "alice@example.com")
    print(f"Created person: {person1}")
    
    person2 = Person("Bob", "30", "bob@example.com")  # This will raise an error
except TypeError as e:
    print(f"Type error: {e}")
```

### Metaclasses

```python
class SingletonMeta(type):
    """Metaclass that creates singleton classes."""
    
    _instances = {}
    
    def __call__(cls, *args, **kwargs):
        if cls not in cls._instances:
            cls._instances[cls] = super().__call__(*args, **kwargs)
        return cls._instances[cls]

class AutoRegisterMeta(type):
    """Metaclass that automatically registers classes."""
    
    registry = {}
    
    def __new__(mcs, name, bases, namespace):
        cls = super().__new__(mcs, name, bases, namespace)
        if name != 'BasePlugin':
            mcs.registry[name.lower()] = cls
        return cls

class ValidationMeta(type):
    """Metaclass that adds validation to class attributes."""
    
    def __new__(mcs, name, bases, namespace):
        # Add validation methods to the class
        def validate_positive(self, value, attr_name):
            if value <= 0:
                raise ValueError(f"{attr_name} must be positive")
            return value
        
        def validate_non_empty(self, value, attr_name):
            if not value or (isinstance(value, str) and not value.strip()):
                raise ValueError(f"{attr_name} cannot be empty")
            return value
        
        namespace['_validate_positive'] = validate_positive
        namespace['_validate_non_empty'] = validate_non_empty
        
        return super().__new__(mcs, name, bases, namespace)

# Using metaclasses
class Logger(metaclass=SingletonMeta):
    """Singleton logger using metaclass."""
    
    def __init__(self):
        self.logs = []
    
    def log(self, message):
        self.logs.append(message)
        print(f"LOG: {message}")
    
    def get_logs(self):
        return self.logs.copy()

class BasePlugin(metaclass=AutoRegisterMeta):
    """Base plugin class that auto-registers subclasses."""
    
    def __init__(self, name):
        self.name = name
    
    def execute(self):
        raise NotImplementedError("Subclasses must implement execute")

class TextPlugin(BasePlugin):
    """Text processing plugin."""
    
    def execute(self, text):
        return f"Processing text '{text}' with {self.name}"

class ImagePlugin(BasePlugin):
    """Image processing plugin."""
    
    def execute(self, image_path):
        return f"Processing image '{image_path}' with {self.name}"

class Product(metaclass=ValidationMeta):
    """Product with validation using metaclass."""
    
    def __init__(self, name, price, quantity):
        self.name = self._validate_non_empty(name, "name")
        self.price = self._validate_positive(price, "price")
        self.quantity = self._validate_positive(quantity, "quantity")
    
    def __str__(self):
        return f"Product(name='{self.name}', price={self.price}, quantity={self.quantity})"

# Using the metaclass-based classes
print("\n=== Metaclasses Demo ===")

# Singleton metaclass
logger1 = Logger()
logger2 = Logger()
print(f"logger1 is logger2: {logger1 is logger2}")

logger1.log("First log message")
logger2.log("Second log message")
print(f"All logs: {logger1.get_logs()}")

# Auto-register metaclass
print(f"Registered plugins: {AutoRegisterMeta.registry}")

text_plugin = TextPlugin("TextProcessor")
image_plugin = ImagePlugin("ImageProcessor")

print(text_plugin.execute("Hello World"))
print(image_plugin.execute("/path/to/image.jpg"))

# Validation metaclass
try:
    product1 = Product("Laptop", 999.99, 10)
    print(f"Created product: {product1}")
    
    product2 = Product("", -100, 5)  # This will raise validation errors
except ValueError as e:
    print(f"Validation error: {e}")
```

## Design Patterns in Python

### Factory Pattern

```python
from abc import ABC, abstractmethod

class Animal(ABC):
    """Abstract animal class."""
    
    @abstractmethod
    def make_sound(self):
        pass

class Dog(Animal):
    def make_sound(self):
        return "Woof!"

class Cat(Animal):
    def make_sound(self):
        return "Meow!"

class Bird(Animal):
    def make_sound(self):
        return "Tweet!"

class AnimalFactory:
    """Factory for creating animals."""
    
    _animals = {
        'dog': Dog,
        'cat': Cat,
        'bird': Bird
    }
    
    @classmethod
    def create_animal(cls, animal_type):
        """Create an animal of the specified type."""
        animal_class = cls._animals.get(animal_type.lower())
        if animal_class:
            return animal_class()
        else:
            raise ValueError(f"Unknown animal type: {animal_type}")
    
    @classmethod
    def get_available_animals(cls):
        """Get list of available animal types."""
        return list(cls._animals.keys())

# Using the factory pattern
print("=== Factory Pattern Demo ===")

factory = AnimalFactory()
print(f"Available animals: {factory.get_available_animals()}")

animals = []
for animal_type in ['dog', 'cat', 'bird']:
    animal = factory.create_animal(animal_type)
    animals.append(animal)
    print(f"{animal_type.capitalize()}: {animal.make_sound()}")

try:
    unknown = factory.create_animal('dragon')
except ValueError as e:
    print(f"Error: {e}")
```

### Observer Pattern

```python
class Subject:
    """Subject in observer pattern."""
    
    def __init__(self):
        self._observers = []
        self._state = None
    
    def attach(self, observer):
        """Attach an observer."""
        if observer not in self._observers:
            self._observers.append(observer)
    
    def detach(self, observer):
        """Detach an observer."""
        if observer in self._observers:
            self._observers.remove(observer)
    
    def notify(self):
        """Notify all observers."""
        for observer in self._observers:
            observer.update(self)
    
    def set_state(self, state):
        """Set state and notify observers."""
        self._state = state
        self.notify()
    
    def get_state(self):
        """Get current state."""
        return self._state

class Observer(ABC):
    """Abstract observer class."""
    
    @abstractmethod
    def update(self, subject):
        pass

class ConcreteObserver(Observer):
    """Concrete observer implementation."""
    
    def __init__(self, name):
        self.name = name
        self.state = None
    
    def update(self, subject):
        """Update when subject changes."""
        self.state = subject.get_state()
        print(f"{self.name} received update: {self.state}")

# Using the observer pattern
print("\n=== Observer Pattern Demo ===")

subject = Subject()

observer1 = ConcreteObserver("Observer 1")
observer2 = ConcreteObserver("Observer 2")
observer3 = ConcreteObserver("Observer 3")

subject.attach(observer1)
subject.attach(observer2)
subject.attach(observer3)

subject.set_state("State 1")
subject.set_state("State 2")

subject.detach(observer2)
subject.set_state("State 3")
```

### Strategy Pattern

```python
from abc import ABC, abstractmethod

class PaymentStrategy(ABC):
    """Abstract payment strategy."""
    
    @abstractmethod
    def pay(self, amount):
        pass

class CreditCardPayment(PaymentStrategy):
    """Credit card payment strategy."""
    
    def __init__(self, card_number, cvv):
        self.card_number = card_number
        self.cvv = cvv
    
    def pay(self, amount):
        return f"Paid ${amount} using Credit Card ending in {self.card_number[-4:]}"

class PayPalPayment(PaymentStrategy):
    """PayPal payment strategy."""
    
    def __init__(self, email):
        self.email = email
    
    def pay(self, amount):
        return f"Paid ${amount} using PayPal account {self.email}"

class BankTransferPayment(PaymentStrategy):
    """Bank transfer payment strategy."""
    
    def __init__(self, account_number):
        self.account_number = account_number
    
    def pay(self, amount):
        return f"Paid ${amount} using Bank Transfer to account {self.account_number}"

class PaymentProcessor:
    """Payment processor using strategy pattern."""
    
    def __init__(self):
        self.payment_strategy = None
    
    def set_payment_strategy(self, strategy):
        """Set the payment strategy."""
        self.payment_strategy = strategy
    
    def process_payment(self, amount):
        """Process payment using current strategy."""
        if self.payment_strategy is None:
            raise ValueError("No payment strategy set")
        
        return self.payment_strategy.pay(amount)

# Using the strategy pattern
print("\n=== Strategy Pattern Demo ===")

processor = PaymentProcessor()

# Credit card payment
processor.set_payment_strategy(CreditCardPayment("1234567890123456", "123"))
print(processor.process_payment(100.50))

# PayPal payment
processor.set_payment_strategy(PayPalPayment("user@example.com"))
print(processor.process_payment(75.25))

# Bank transfer payment
processor.set_payment_strategy(BankTransferPayment("9876543210"))
print(processor.process_payment(200.00))
```

## Key Takeaways

1. **Abstract classes** enforce contracts and provide common interfaces
2. **Multiple inheritance** requires understanding of Method Resolution Order (MRO)
3. **Advanced magic methods** enable custom behavior for built-in operations
4. **Context managers** provide safe resource management
5. **Class decorators** modify class behavior without inheritance
6. **Metaclasses** control class creation and behavior
7. **Design patterns** provide proven solutions to common problems
8. **Professional OOP** involves proper abstraction and encapsulation

## Next Steps

In the next lesson, we'll explore Functional Programming - higher-order functions, closures, decorators, and functional programming paradigms that make Python code more elegant and efficient.
