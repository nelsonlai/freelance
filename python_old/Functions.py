
# syntax
# Declaring a function
def function_name(parameter, parameter2):
    codes = parameter + parameter2
    codey = parameter - parameter2
    codex = parameter * parameter2
    codez = parameter / parameter2
    return codes, codey, codex, codez

# Calling a function
s, y, x, z = function_name(10, 20)
s, y, _, z = function_name(10, 20) # _ is used to ignore a value
print(s, y, x, z)
s, y, x, z = function_name(32, 12)

# Comprehensive function declaration
def function_comprehensive (param1: str, param2: int, param3: dict) -> bool, int, dict:
    pass
# Calling a function
boolX, intY, dictZ = function_comprehensive("test", 123, {"key": "value"})
boolX, intY, dictZ = function_comprehensive(123, "XYZ", {"key": "value"})
function_name()
Function without Parameters
Function can be declared without parameters.


def weight_of_object (mass, gravity = 9.81):
    weight = str(mass * gravity)+ ' N' # the value has to be changed to string first
    return weight
print('Weight of an object in Newtons: ', weight_of_object(100)) # 9.81 - average gravity on Earth's surface
print('Weight of an object in Newtons: ', weight_of_object(100, 1.62)) # gravity on the surface of the Moon

def weight_of_object (mass=100, gravity):
    weight = str(mass * gravity)+ ' N' # the value has to be changed to string first
    return weight
print('Weight of an object in Newtons: ', weight_of_object(_, 9.81))

# Function with variable number of arguments for adding all parameters
def add_all(*args):
    sum = 0
    for i in args:
        print(i)
        sum += i    # sum = sum + i
    return sum

print(add_all(1, 2, 3))         # ➜ 6
print(add_all(5, 10, 15, 20))   # ➜ 50
🧠 Explanation:
*args collects all positional arguments into a tuple.

You can loop through or manipulate args like a normal tuple.

🔹 Example 2: Using **kwargs

# print_profile(name="Alice", age=30, country="Canada")
# implement print_profile function
def print_profile(**kwargs):        # kwargs is a dictionary, kw = key word
    for key, value in kwargs.items():
        print(f"{key}: {value}")
        if key == "age":
            print(f"Age is: {value}")
        elif key == "country":
            print(f"Country is: {value}")
        elif key == "name":
            print(f"Name is: {value}")
        else:
            print(f"Unknown key: {key}")

print_profile(name="Alice", age=30, country="Canada")
print_profile(name="Bob", age=25, country="Toronto")
print_profile(country="Toronto", name="Bob", age=25)
🧠 Explanation:
**kwargs collects all keyword arguments into a dictionary.

Useful when function arguments may vary.

🔹 Example 3: Combined *args and **kwargs

def demo_function(*args, **kwargs):         # positional arguments and keyword arguments
    print("Positional args:", args)
    print("Keyword args:", kwargs)

demo_function(1, 2, 3, name="Bob", age=25)

def myFunction (param1 = 9.18, *args, **kwargs):
    print("Positional args:", args)
    print("Keyword args:", kwargs)

myFunction(1.62, 1, 2, 3, 5, 7, name="Bob", age=25)
Positional args: (1, 2, 3)
Keyword args: {'name': 'Bob', 'age': 25}
🔹 Example 4: Forwarding args/kwargs to another function
def greet(name, message):
    print(f"{message}, {name}!")

def wrapper(*args, **kwargs):
    greet(*args, **kwargs)

wrapper("Alice", message="Hello")
📦 Summary
Use Case	Syntax	Type
Positional args	*args	tuple
Keyword args	**kwargs	dict
Forwarding	func(*args, **kwargs)	expands arguments

# lambda expression
# lambda arguments : expression
def sum(x: int, y: int) -> int:
    return x + y

total = sum(1, 2)

sum = lambda x, y: x + y
total = sum(1, 2)
total = sum(lambda x, y: x + y)

square_number = lambda n: n * n
print(square_number(3))
print((lambda n: n * n)(3))  # Immediate invocation

def square_number(n):
    return n * n

print(square_number(3))


def show_arguments(*args, **kwargs):
    print("Positional arguments (*args):")
    for i, value in enumerate(args):
        print(f"  args[{i}] = {value}")
    
    print("\nKeyword arguments (**kwargs):")
    for key, value in kwargs.items():
        print(f"  kwargs['{key}'] = {value}")

# Call the function with different arguments
show_arguments(10, 20, 30, name="Alice", age=12, city="Toronto")


# Option Homework #1
https://www.geeksforgeeks.org/python/functools-module-in-python/

# Explain map function - https://www.programiz.com/python-programming/methods/built-in/map
map(function, iterable)
✅ What it does:
Applies a function to each item in an iterable (like a list) and returns a new iterable (map object).

✅ Example:
numbers = [1, 2, 3, 4, 5]
squares = list(map(lambda x: x**2, numbers))
print(squares)

# Explain filter function - https://www.programiz.com/python-programming/methods/built-in/filter
filter(function, iterable)
✅ What it does:
Filters elements from an iterable where the function returns True.

✅ Example:
numbers = [1, 2, 3, 4, 5, 6]
evens = list(filter(lambda x: x % 2 == 0, numbers))
print(evens)

# Explain reduce function - https://www.programiz.com/python-programming/methods/built-in/reduce
reduce(function, iterable)
✅ What it does:
Performs a rolling computation on the iterable. It takes two elements at a time and reduces them to one value.

You need to import it from functools:

from functools import reduce
✅ Example:

from functools import reduce

numbers = [1, 2, 3, 4, 5]
sum_all = reduce(lambda x, y: x + y, numbers)
print(sum_all)