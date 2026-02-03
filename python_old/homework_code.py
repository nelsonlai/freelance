# Paste your code here
#String Case Methods
str.lower() # Convert to lowercase.
str.upper() # Convert to uppercase.
str.capitalize() # Capitalize first character.
str.title() # Capitalize the first character of each word.
str.swapcase() # Swap case of each character.
str.casefold() # Aggressive lowercasing (for caseless matching).

#String Measurement & Checks
str.isalpha() # Check if all characters are alphabetic.
str.isdigit() # Check if all characters are digits.
str.isalnum() # Check if all characters are alphanumeric.
str.islower() # Check if all characters are lowercase.
str.isupper() # Check if all characters are uppercase.
str.isspace() # Check if all characters are whitespace.
str.istitle() # Check if string is title-cased.
str.startswith(prefix) # Check if string starts with prefix.
str.endswith(suffix) # Check if string ends with suffix.

# Searching and Finding**
str.find(sub) # Find first occurrence; returns -1 if not found.
str.rfind(sub) # Find last occurrence.
str.index(sub) # Like `find()`, but raises `ValueError` if not found.
str.rindex(sub) # Like `rfind()`, but raises `ValueError`.
str.count(sub) # Count occurrences of `sub`.

# Modification Methods**
str.replace(old, new) # Replace all occurrences of `old` with `new`.
str.strip() # Remove leading/trailing whitespace.
str.lstrip() # Remove leading whitespace.
str.rstrip() # Remove trailing whitespace.
str.ljust(width) # Left-justify in a string of given width.
str.rjust(width) # Right-justify.
str.center(width) # Center string.
str.zfill(width) # Pad with leading zeros.

# Joining and Splitting**
str.split(sep) # Split string into list.
str.rsplit(sep) # Split from the right.
str.splitlines() # Split by line breaks.
str.join(iterable) #Join elements using string as separator.
str.partition(sep) # Split into 3 parts: before, sep, after.
str.rpartition(sep) # Same as above, but from the right.

# Encoding & Formatting**
str.encode() # Encode string to bytes.
str.format() # Format string with placeholders.
str.format_map(dict) # Format using a dictionary.
str.maketrans() # Create a translation table.
str.translate(table) #Apply translation table.

#Character Class Checks (Unicode-aware)** These check Unicode character properties:
str.isdecimal() # Check for decimal characters.
str.isnumeric() # Check for numeric characters.
str.isidentifier() # Check for valid Python identifier.
str.isprintable() # Check if all characters are printable.

## Homework #2
# Get user input for age
age = int(input("Enter your age: "))

# Check if age is 18 or older
if age >= 18:
    print("You are old enough to learn to drive.")
else:
    # Calculate years needed
    years_needed = 18 - age
    print(f"You need {years_needed} more years to learn to drive.")

## Homework #3
# Get user input for score
score = int(input("Enter your score: "))


#score = int(input("Enter the student's score (0-100): "))

def get_grade(score):
    if 80 <= score <= 100:
        return 'A'
    elif 70 <= score <= 79:
        return 'B'
    elif 60 <= score <= 69:
        return 'C'
    elif 50 <= score <= 59:
        return 'D'
    elif 0 <= score <= 49:
        return 'F'
    else:
        return 'Invalid score'

print(f"The student's grade is: {get_grade(score)}")

for i in range(1, 8):
    print("#" * i)