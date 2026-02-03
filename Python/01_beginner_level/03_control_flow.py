"""
Control Flow - Making Decisions and Repeating Actions
This file contains all the example code from the Control Flow lesson.
"""

# Conditional Statements (if/elif/else)

# Basic if Statement
age = 19
score = 75
print("=== If Statement ===")

if age == 18:
    print("You are 18 years old.") ## True
else:
    print("You are not 18 years old.") ## False

# if/else Statement
age = 16

if age >= 18:
    print("You are an adult!")
else:
    print("You are a minor!")

# if/elif/else Statement
score = 85

if score >= 90:
    grade = "A"
elif score >= 80:
    grade = "B"
elif score >= 70:
    grade = "C"
elif score >= 60:
    grade = "D"
else:
    grade = "F"

print(f"Your grade is: {grade}")

# Nested Conditions
age = 16
has_license = False

if age >= 18:
    if has_license:
        print("You can drive!")
    else:
        print("You can get a license but can't drive yet!")
else:
    print("You are too young to drive!")

# Multiple Conditions
temperature = 25
is_sunny = True
is_weekend = False

if temperature > 20 and is_sunny:
    if is_weekend:
        print("Perfect day for a picnic!")
    else:
        print("Great weather for outdoor activities!")
elif temperature < 10:
    print("Stay warm inside!")
else:
    print("Moderate weather today.")

# Loops

# for Loops - Basic
print("\n=== For Loops ===")

# Iterating over a range
for i in range(5):  # 0, 1, 2, 3, 4
    print(f"Number: {i}")

# Iterating over a list
fruits = ["apple", "banana", "orange"]
for fruit in fruits:
    print(f"Fruit: {fruit}")

# Iterating with index
for index, fruit in enumerate(fruits):
    print(f"{index}: {fruit}")

# Range Function Examples
print("\n=== Range Function ===")

# range(stop)
print("range(5):")
for i in range(5):
    print(i)  # 0, 1, 2, 3, 4

# range(start, stop)
print("\nrange(2, 7):") # 2, 3, 4, 5, 6
for i in range(2, 7):
    print(i)  # 2, 3, 4, 5, 6

# range(start, stop, step)
print("\nrange(0, 10, 3):")
for i in range(0, 10, 3):
    print(i)  # 0, 3, 6, 9

# Negative step
print("\nrange(10, 0, -2):")
for i in range(10, 0, -2):
    print(i)  # 10, 8, 6, 4, 2

# Iterating over Different Data Types
print("\n=== Iterating over Different Data Types ===")

# String
name = "Python"
print("String iteration:")
for char in name:
    print(char)

# Dictionary
student = {"name": "Alice", "age": 20, "grade": "A"}
print("\nDictionary iteration (keys):")
for key in student:
    print(f"{key}: {student[key]}")

# Dictionary items
print("\nDictionary iteration (items):")
for key, value in student.items():
    print(f"{key}: {value}")

# while Loops
print("\n=== While Loops ===")

# Basic while loop
count = 0
while count < 5:
    print(f"Count: {count}")
    count += 1

# Counter with condition
number = 1
while number <= 10:
    print(f"Number: {number}")
    number += 1

# Loop Control Statements
print("\n=== Loop Control Statements ===")

# break Statement
print("Break example:")
for i in range(10): # 0, 1, 2, ..., 9
    if i == 5:
        break
    print(i)  # Prints 0, 1, 2, 3, 4

# continue Statement
print("\nContinue example:")
for i in range(10): # 0, 1, 2, ..., 9
    if i % 2 == 0:
        continue
    print(i)  # Prints 1, 3, 5, 7, 9

# pass Statement
print("\nPass example:")
for i in range(5):
    if i == 2:
        pass
    else:
        print(i)

# Breaking out of nested loops
print("\nNested loops with break:")
for i in range(3):
    for j in range(3):
        if i == 1 and j == 1:
            break  # Only breaks inner loop
        print(f"({i}, {j})")

# Practical Examples

# Example 1: Number Guessing Game
import random   # get random number

def number_guessing_game(): # a simple number guessing game
    """A simple number guessing game."""
    
    secret_number = random.randint(1, 100)
    attempts = 0
    max_attempts = 7
    
    print("Welcome to the Number Guessing Game!")
    print("I'm thinking of a number between 1 and 100.")
    print(f"You have {max_attempts} attempts to guess it!")
    
    while attempts < max_attempts:
        try:
            guess = int(input(f"\nAttempt {attempts + 1}: Enter your guess: "))
            attempts += 1
            
            if guess == secret_number:
                print(f"Congratulations! You guessed it in {attempts} attempts!")
                break
            elif guess < secret_number:
                print("Too low! Try a higher number.")
            else:
                print("Too high! Try a lower number.")
                
        except ValueError:
            print("Please enter a valid number!")
            attempts -= 1  # Don't count invalid attempts
    
    if attempts >= max_attempts:
        print(f"Game over! The secret number was {secret_number}")

# Example 2: Grade Calculator
def grade_calculator():
    """Calculate and display student grades."""
    
    students = []
    
    print("=== Grade Calculator ===")
    
    # Get number of students
    num_students = int(input("How many students? "))
    
    # Get student data
    for i in range(num_students):
        name = input(f"Enter student {i+1} name: ")
        score = float(input(f"Enter {name}'s score (0-100): "))
        students.append({"name": name, "score": score})
    
    # Calculate and display grades
    print("\n=== Results ===")
    total_score = 0
    
    for student in students:
        score = student["score"]
        total_score += score
        
        if score >= 90:
            grade = "A"
        elif score >= 80:
            grade = "B"
        elif score >= 70:
            grade = "C"
        elif score >= 60:
            grade = "D"
        else:
            grade = "F"
        
        print(f"{student['name']}: {score} - Grade {grade}")
    
    # Calculate class average
    average = total_score / num_students
    print(f"\nClass Average: {average:.2f}")

# Example 3: Multiplication Table Generator
def multiplication_table():
    """Generate multiplication tables."""
    
    print("=== Multiplication Table Generator ===")
    
    # Get table size
    size = int(input("Enter table size (e.g., 10 for 10x10): "))
    
    # Generate table
    print(f"\nMultiplication Table ({size}x{size}):")
    print("   ", end="")
    
    # Print header
    for i in range(1, size + 1):
        print(f"{i:4}", end="")
    print()
    
    # Print separator
    print("   " + "-" * (size * 4))
    
    # Print rows
    for i in range(1, size + 1):
        print(f"{i:2}|", end="")
        for j in range(1, size + 1):
            print(f"{i*j:4}", end="")
        print()

# Example 4: Text Analyzer
def text_analyzer():
    """Analyze text for various statistics."""
    
    print("=== Text Analyzer ===")
    text = input("Enter text to analyze: ")
    
    # Initialize counters
    char_count = len(text)
    word_count = len(text.split())
    sentence_count = text.count('.') + text.count('!') + text.count('?')
    vowel_count = 0
    consonant_count = 0
    digit_count = 0
    
    vowels = "aeiouAEIOU"
    
    # Analyze characters
    for char in text:
        if char.isalpha():
            if char in vowels:
                vowel_count += 1
            else:
                consonant_count += 1
        elif char.isdigit():
            digit_count += 1
    
    # Display results
    print(f"\n=== Analysis Results ===")
    print(f"Character count: {char_count}")
    print(f"Word count: {word_count}")
    print(f"Sentence count: {sentence_count}")
    print(f"Vowel count: {vowel_count}")
    print(f"Consonant count: {consonant_count}")
    print(f"Digit count: {digit_count}")
    
    if word_count > 0:
        avg_word_length = char_count / word_count
        print(f"Average word length: {avg_word_length:.2f}")

# Example 5: Simple Menu System
def menu_system():
    """A simple menu system demonstrating control flow."""
    
    while True:
        print("\n=== Main Menu ===")
        print("1. Calculator")
        print("2. Text Analyzer")
        print("3. Number Guessing Game")
        print("4. Exit")
        
        choice = input("Enter your choice (1-4): ")
        
        if choice == "1":
            # Simple calculator
            num1 = float(input("Enter first number: "))
            operation = input("Enter operation (+, -, *, /): ")
            num2 = float(input("Enter second number: "))
            
            if operation == "+":
                result = num1 + num2
            elif operation == "-":
                result = num1 - num2
            elif operation == "*":
                result = num1 * num2
            elif operation == "/":
                if num2 != 0:
                    result = num1 / num2
                else:
                    print("Error: Division by zero!")
                    continue
            else:
                print("Invalid operation!")
                continue
            
            print(f"Result: {num1} {operation} {num2} = {result}")
            
        elif choice == "2":
            text_analyzer()
            
        elif choice == "3":
            number_guessing_game()
            
        elif choice == "4":
            print("Goodbye!")
            break
            
        else:
            print("Invalid choice! Please enter 1-4.")

# Demonstrate the examples (commented out to avoid interactive input)
print("Control flow examples completed!")

# Uncomment any of these to run the interactive examples:
# number_guessing_game()
# grade_calculator()
# multiplication_table()
# text_analyzer()
# menu_system()
