"""
Getting Started with Python - Example Code
This file contains all the example code from the Getting Started lesson.
"""

# Hello World Program
print("Hello, World!")
print("Welcome to Python programming!")

# Comments Examples
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

# PEP 8 Style Examples

# Use meaningful variable names
student_name = "Alice"
student_age = 20

# Use snake_case for variables and functions
def calculate_average(numbers):
    """Calculate the average of a list of numbers."""
    return sum(numbers) / len(numbers)

# Use PascalCase for classes
class Student:
    """A simple Student class example."""
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
math_score = 85
english_score = 92
science_score = 78
history_score = 88
art_score = 95

total_score = math_score + english_score + science_score + \
              history_score + art_score

print(f"Total score: {total_score}")

# First Program Exercise
def first_program():
    """Interactive program that greets user and calculates age in days."""
    
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

# Example usage of the greet function
print(greet("Python"))

# Example usage of the Student class
student = Student("Bob", 22)
print(f"Student: {student.name}, Age: {student.age}")

# Example usage of calculate_average function
grades = [85, 92, 78, 88, 95]
average = calculate_average(grades)
print(f"Average grade: {average}")

# Uncomment the line below to run the interactive program
# first_program()
