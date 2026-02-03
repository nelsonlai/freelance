# Advanced Object-Oriented Programming Examples
from abc import ABC, abstractmethod     # Abstract Base Classes
from typing import List, Dict, Any
import time

print("Advanced Object-Oriented Programming Examples")
print("=" * 50)

# 1. Abstract Classes and Interfaces
print("1. Abstract Classes and Interfaces")
print("-" * 35)

class Shape(ABC):
    """Abstract base class for shapes."""
    
    def __init__(self, name: str):
        self.name = name
    
    @abstractmethod
    def area(self) -> float:
        """Calculate the area of the shape."""
        pass
    
    @abstractmethod
    def perimeter(self) -> float:
        """Calculate the perimeter of the shape."""
        pass
    
    def describe(self) -> str:
        """Describe the shape."""
        return f"{self.name} with area {self.area():.2f} and perimeter {self.perimeter():.2f}"

class Rectangle(Shape):
    """Rectangle implementation."""
    
    def __init__(self, width: float, height: float):
        super().__init__("Rectangle")
        self.width = width
        self.height = height
    
    def area(self) -> float:
        return self.width * self.height
    
    def perimeter(self) -> float:
        return 2 * (self.width + self.height)

class Circle(Shape):
    """Circle implementation."""
    
    def __init__(self, radius: float):
        super().__init__("Circle")
        self.radius = radius
    
    def area(self) -> float:
        import math
        return math.pi * self.radius ** 2
    
    def perimeter(self) -> float:
        import math
        return 2 * math.pi * self.radius

# Test abstract classes
rectangle = Rectangle(5, 3)
circle = Circle(4)

print(f"Rectangle: {rectangle.describe()}")
print(f"Circle: {circle.describe()}")

# 2. Multiple Inheritance and Mixins
print("\n2. Multiple Inheritance and Mixins")
print("-" * 35)

class Flyable:
    """Mixin for flying capability."""
    
    def fly(self) -> str:
        return "Flying through the air"

class Swimmable:
    """Mixin for swimming capability."""
    
    def swim(self) -> str:
        return "Swimming in water"

class Animal:
    """Base animal class."""
    
    def __init__(self, name: str):
        self.name = name
    
    def speak(self) -> str:
        return f"{self.name} makes a sound"

class Duck(Animal, Flyable, Swimmable):
    """Duck class with multiple capabilities."""
    
    def speak(self) -> str:
        return f"{self.name} quacks"

class Fish(Animal, Swimmable):
    """Fish class with swimming capability."""
    
    def speak(self) -> str:
        return f"{self.name} bubbles"

# Test multiple inheritance
duck = Duck("Donald")
fish = Fish("Nemo")

print(f"Duck: {duck.speak()}, {duck.fly()}, {duck.swim()}")
print(f"Fish: {fish.speak()}, {fish.swim()}")

# 3. Magic Methods and Operator Overloading
print("\n3. Magic Methods and Operator Overloading")
print("-" * 40)

class Vector:
    """Vector class with operator overloading."""
    
    def __init__(self, x: float, y: float):
        self.x = x
        self.y = y
    
    def __str__(self) -> str:
        return f"Vector({self.x}, {self.y})"
    
    def __repr__(self) -> str:
        return f"Vector({self.x}, {self.y})"
    
    def __add__(self, other: 'Vector') -> 'Vector':
        return Vector(self.x + other.x, self.y + other.y)
    
    def __sub__(self, other: 'Vector') -> 'Vector':
        return Vector(self.x - other.x, self.y - other.y)
    
    def __mul__(self, scalar: float) -> 'Vector':
        return Vector(self.x * scalar, self.y * scalar)
    
    def __eq__(self, other: 'Vector') -> bool:
        return self.x == other.x and self.y == other.y
    
    def __len__(self) -> int:
        return 2
    
    def __getitem__(self, index: int) -> float:
        if index == 0:
            return self.x
        elif index == 1:
            return self.y
        else:
            raise IndexError("Vector index out of range")
    
    def __setitem__(self, index: int, value: float):
        if index == 0:
            self.x = value
        elif index == 1:
            self.y = value
        else:
            raise IndexError("Vector index out of range")

# Test operator overloading
v1 = Vector(3, 4)
v2 = Vector(1, 2)

print(f"v1: {v1}")
print(f"v2: {v2}")
print(f"v1 + v2: {v1 + v2}")
print(f"v1 - v2: {v1 - v2}")
print(f"v1 * 2: {v1 * 2}")
print(f"v1 == v2: {v1 == v2}")
print(f"len(v1): {len(v1)}")
print(f"v1[0]: {v1[0]}, v1[1]: {v1[1]}")

# 4. Design Patterns
print("\n4. Design Patterns")
print("-" * 20)

# Singleton Pattern
class Singleton:
    """Singleton pattern implementation."""
    
    _instance = None
    _initialized = False
    
    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
        return cls._instance
    
    def __init__(self):
        if not self._initialized:
            self.value = 0
            self._initialized = True
    
    def increment(self):
        self.value += 1
        return self.value

# Test singleton
s1 = Singleton()
s2 = Singleton()
print(f"s1 is s2: {s1 is s2}")
print(f"s1.value: {s1.value}")
s1.increment()
print(f"s2.value: {s2.value}")

# Factory Pattern
class AnimalFactory:
    """Factory for creating animals."""
    
    @staticmethod
    def create_animal(animal_type: str, name: str) -> Animal:
        if animal_type == "dog":
            return Dog(name)
        elif animal_type == "cat":
            return Cat(name)
        else:
            raise ValueError(f"Unknown animal type: {animal_type}")

class Dog(Animal):
    """Dog class."""
    
    def speak(self) -> str:
        return f"{self.name} barks"

class Cat(Animal):
    """Cat class."""
    
    def speak(self) -> str:
        return f"{self.name} meows"

# Test factory pattern
dog = AnimalFactory.create_animal("dog", "Buddy")
cat = AnimalFactory.create_animal("cat", "Whiskers")

print(f"Dog: {dog.speak()}")
print(f"Cat: {cat.speak()}")

# Observer Pattern
class Subject:
    """Subject in observer pattern."""
    
    def __init__(self):
        self._observers = []
        self._state = None
    
    def attach(self, observer):
        self._observers.append(observer)
    
    def detach(self, observer):
        self._observers.remove(observer)
    
    def notify(self):
        for observer in self._observers:
            observer.update(self)
    
    def set_state(self, state):
        self._state = state
        self.notify()
    
    def get_state(self):
        return self._state

class Observer:
    """Observer in observer pattern."""
    
    def __init__(self, name: str):
        self.name = name
    
    def update(self, subject: Subject):
        print(f"{self.name} received update: {subject.get_state()}")

# Test observer pattern
subject = Subject()
observer1 = Observer("Observer 1")
observer2 = Observer("Observer 2")

subject.attach(observer1)
subject.attach(observer2)

subject.set_state("State 1")
subject.set_state("State 2")

# 5. Properties and Descriptors
print("\n5. Properties and Descriptors")
print("-" * 30)

class Temperature:
    """Temperature class with property validation."""
    
    def __init__(self, celsius: float = 0):
        self._celsius = celsius
        self.fahrenheit = self.celsius * 9/5 + 32
    
    @property
    def celsius(self) -> float:
        return self._celsius
    
    @celsius.setter
    def celsius(self, value: float):
        if value < -273.15:
            raise ValueError("Temperature cannot be below absolute zero")
        self._celsius = value
    
    @property
    def fahrenheit(self) -> float:
        return self._celsius * 9/5 + 32
    
    @fahrenheit.setter
    def fahrenheit(self, value: float):
        self.celsius = (value - 32) * 5/9

# Test properties
temp = Temperature(25)
print(f"Celsius: {temp.celsius}, Fahrenheit: {temp.fahrenheit}")
temp.fahrenheit = 86
print(f"Celsius: {temp.celsius}, Fahrenheit: {temp.fahrenheit}")

# Descriptor
class ValidatedAttribute:
    """Descriptor for validated attributes."""
    
    def __init__(self, min_value: float = None, max_value: float = None):
        self.min_value = min_value
        self.max_value = max_value
        self.name = None
    
    def __set_name__(self, owner, name):
        self.name = name
    
    def __get__(self, instance, owner):
        if instance is None:
            return self
        return instance.__dict__.get(self.name)
    
    def __set__(self, instance, value):
        if self.min_value is not None and value < self.min_value:
            raise ValueError(f"{self.name} must be >= {self.min_value}")
        if self.max_value is not None and value > self.max_value:
            raise ValueError(f"{self.name} must be <= {self.max_value}")
        instance.__dict__[self.name] = value

class Person:
    """Person class with validated attributes."""
    
    age = ValidatedAttribute(min_value=0, max_value=150)
    height = ValidatedAttribute(min_value=0, max_value=300)
    
    def __init__(self, name: str, age: int, height: float):
        self.name = name
        self.age = age
        self.height = height

# Test descriptors
person = Person("Alice", 25, 165.5)
print(f"Person: {person.name}, Age: {person.age}, Height: {person.height}")

# 6. Metaclasses
print("\n6. Metaclasses")
print("-" * 15)

class SingletonMeta(type):
    """Metaclass for singleton pattern."""
    
    _instances = {}
    
    def __call__(cls, *args, **kwargs):
        if cls not in cls._instances:
            cls._instances[cls] = super().__call__(*args, **kwargs)
        return cls._instances[cls]

class DatabaseConnection(metaclass=SingletonMeta):
    """Database connection singleton."""
    
    def __init__(self):
        self.connected = False
    
    def connect(self):
        self.connected = True
        return "Connected to database"

# Test metaclass
db1 = DatabaseConnection()
db2 = DatabaseConnection()
print(f"db1 is db2: {db1 is db2}")
print(f"db1.connect(): {db1.connect()}")
print(f"db2.connected: {db2.connected}")

# 7. Context Managers
print("\n7. Context Managers")
print("-" * 20)

class FileManager:
    """Context manager for file operations."""
    
    def __init__(self, filename: str, mode: str = 'r'):
        self.filename = filename
        self.mode = mode
        self.file = None
    
    def __enter__(self):        ## start of with block
        self.file = open(self.filename, self.mode)
        return self.file
    
    def __exit__(self, exc_type, exc_val, exc_tb):  ## end of with block
        if self.file:
            self.file.close()
        if exc_type:
            print(f"Exception occurred: {exc_type.__name__}: {exc_val}")
        return False  # Don't suppress exceptions

# Test context manager
try:
    with FileManager('test.txt', 'w') as f:
        f.write('Hello, World!')
    print("File written successfully")
except Exception as e:
    print(f"Error: {e}")

# 8. Decorators
print("\n8. Decorators")
print("-" * 15)

def timing_decorator(func):
    """Decorator to measure function execution time."""
    def wrapper(*args, **kwargs):
        start_time = time.time()
        result = func(*args, **kwargs)
        end_time = time.time()
        print(f"{func.__name__} took {end_time - start_time:.4f} seconds")
        return result
    return wrapper

def retry_decorator(max_attempts: int = 3):
    """Decorator to retry function on failure."""
    def decorator(func):
        def wrapper(*args, **kwargs):
            for attempt in range(max_attempts):
                try:
                    return func(*args, **kwargs)
                except Exception as e:
                    if attempt == max_attempts - 1:
                        raise e
                    print(f"Attempt {attempt + 1} failed: {e}")
            return None
        return wrapper
    return decorator

@timing_decorator
@retry_decorator(max_attempts=2)
def risky_operation():
    """A risky operation that might fail."""
    import random
    if random.random() < 0.5:
        raise Exception("Random failure")
    return "Success!"

# Test decorators
try:
    result = risky_operation()
    print(f"Result: {result}")
except Exception as e:
    print(f"Final failure: {e}")

# 9. Class Methods and Static Methods
print("\n9. Class Methods and Static Methods")
print("-" * 35)

class MathUtils:
    """Math utilities class."""
    
    PI = 3.14159
    
    @staticmethod
    def add(a: float, b: float) -> float:
        """Static method for addition."""
        return a + b
    
    @staticmethod
    def multiply(a: float, b: float) -> float:
        """Static method for multiplication."""
        return a * b
    
    @classmethod
    def circle_area(cls, radius: float) -> float:
        """Class method for circle area."""
        return cls.PI * radius ** 2
    
    @classmethod
    def circle_circumference(cls, radius: float) -> float:
        """Class method for circle circumference."""
        return 2 * cls.PI * radius

# Test class methods and static methods
print(f"Add: {MathUtils.add(5, 3)}")
print(f"Multiply: {MathUtils.multiply(4, 6)}")
print(f"Circle area: {MathUtils.circle_area(5):.2f}")
print(f"Circle circumference: {MathUtils.circle_circumference(5):.2f}")

# 10. Advanced Inheritance
print("\n10. Advanced Inheritance")
print("-" * 25)

class BaseClass:
    """Base class with common functionality."""
    
    def __init__(self, name: str):
        self.name = name
        self._private_var = "private"
    
    def common_method(self) -> str:
        return f"Common method from {self.name}"
    
    def _protected_method(self) -> str:
        return f"Protected method from {self.name}"
    
    def __private_method(self) -> str:
        return f"Private method from {self.name}"

class DerivedClass(BaseClass):
    """Derived class with additional functionality."""
    
    def __init__(self, name: str, value: int):
        super().__init__(name)
        self.value = value
    
    def common_method(self) -> str:
        base_result = super().common_method()
        return f"{base_result} with value {self.value}"
    
    def new_method(self) -> str:
        return f"New method from {self.name}"

# Test advanced inheritance
derived = DerivedClass("Derived", 42)
print(f"Common method: {derived.common_method()}")
print(f"New method: {derived.new_method()}")
print(f"Protected method: {derived._protected_method()}")

print("\nAdvanced Object-Oriented Programming examples completed!")