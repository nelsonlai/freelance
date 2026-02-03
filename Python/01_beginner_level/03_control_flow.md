# 3. Control Flow - Making Decisions and Repeating Actions

Control flow determines the order in which statements are executed in a program. Python provides several control flow structures to make decisions and repeat actions.

## Conditional Statements (if/elif/else)

Conditional statements allow your program to make decisions based on certain conditions.

### Basic if Statement

```python
age = 18

if age >= 18:
    print("You are an adult!")
```

### if/else Statement

```python
age = 16

if age >= 18:
    print("You are an adult!")
else:
    print("You are a minor!")
```

### if/elif/else Statement

```python
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
```

### Nested Conditions

```python
age = 20
has_license = True

if age >= 18:
    if has_license:
        print("You can drive!")
    else:
        print("You can get a license but can't drive yet!")
else:
    print("You are too young to drive!")
```

### Multiple Conditions

```python
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
```

## Loops

Loops allow you to repeat a block of code multiple times.

### for Loops

#### Basic for Loop

```python
# Iterating over a range
for i in range(5):
    print(f"Number: {i}")

# Iterating over a list
fruits = ["apple", "banana", "orange"]
for fruit in fruits:
    print(f"Fruit: {fruit}")

# Iterating with index
for index, fruit in enumerate(fruits):
    print(f"{index}: {fruit}")
```

#### Range Function

```python
# range(stop)
for i in range(5):
    print(i)  # 0, 1, 2, 3, 4

# range(start, stop)
for i in range(2, 7):
    print(i)  # 2, 3, 4, 5, 6

# range(start, stop, step)
for i in range(0, 10, 2):
    print(i)  # 0, 2, 4, 6, 8

# Negative step
for i in range(10, 0, -1):
    print(i)  # 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
```

#### Iterating over Different Data Types

```python
# String
name = "Python"
for char in name:
    print(char)

# Dictionary
student = {"name": "Alice", "age": 20, "grade": "A"}
for key in student:
    print(f"{key}: {student[key]}")

# Dictionary items
for key, value in student.items():
    print(f"{key}: {value}")
```

### while Loops

while loops continue as long as a condition is true.

```python
# Basic while loop
count = 0
while count < 5:
    print(f"Count: {count}")
    count += 1

# User input loop
user_input = ""
while user_input.lower() != "quit":
    user_input = input("Enter something (or 'quit' to exit): ")
    print(f"You entered: {user_input}")

# Counter with condition
number = 1
while number <= 10:
    print(f"Number: {number}")
    number += 1
```

## Loop Control Statements

### break Statement

The `break` statement exits the loop immediately.

```python
# Breaking out of a loop
for i in range(10):
    if i == 5:
        break
    print(i)  # Prints 0, 1, 2, 3, 4

# Breaking out of nested loops
for i in range(3):
    for j in range(3):
        if i == 1 and j == 1:
            break  # Only breaks inner loop
        print(f"({i}, {j})")
```

### continue Statement

The `continue` statement skips the rest of the current iteration and continues with the next one.

```python
# Skipping even numbers
for i in range(10):
    if i % 2 == 0:
        continue
    print(i)  # Prints 1, 3, 5, 7, 9

# Skipping specific values
numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
for num in numbers:
    if num == 5:
        continue
    print(f"Number: {num}")
```

### pass Statement

The `pass` statement is a null operation - it does nothing but is useful as a placeholder.

```python
# Using pass as placeholder
age = 20

if age >= 18:
    pass  # TODO: Add adult logic here
else:
    print("You are a minor!")

# Using pass in loops
for i in range(5):
    if i == 2:
        pass  # Do nothing for this iteration
    else:
        print(i)
```

## Practical Examples

### Example 1: Number Guessing Game

```python
import random

def number_guessing_game():
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
```

### Example 2: Grade Calculator

```python
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
    average = total_score / len(students)
    print(f"\nClass Average: {average:.2f}")
```

### Example 3: Multiplication Table Generator

```python
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
```

### Example 4: Text Analyzer

```python
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
```

## Key Takeaways

1. **Conditional statements** (if/elif/else) allow programs to make decisions
2. **for loops** are used when you know how many times to repeat
3. **while loops** continue until a condition becomes false
4. **break** exits a loop completely
5. **continue** skips to the next iteration
6. **pass** is a placeholder that does nothing
7. **Nested structures** allow complex logic
8. **User input validation** is important for robust programs

## Next Steps

In the next lesson, we'll explore Python's data structures including strings, lists, tuples, dictionaries, and sets.
