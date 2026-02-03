# What is a regular expression?

What is regex?
A pattern-matching tool for text.
Used for search, validation, and text manipulation (replace).
Why use regex instead of string methods?
More powerful and flexible.

import re   # Importing the regex module
pattern = r"\d+"
text = "My phone is 41655X51234"
print(re.findall(pattern, text))  # ['41655', '51234']

Basic Regex Syntax
Literals:
re.search("cat", "The cat is here")

Character classes:
\d (digit), \w (word), \s (space)

. matches any character (except newline)

Quantifiers:
+ one or more
* zero or more
? zero or one
{m,n} specific count {3,6}

Anchors:
^ start of string
$ end of string

Example:
import re
re.findall(r"\d{3}", "abc 123 4567 89")  # ['123', '456']

import re
text = "Order 12 apples and 345 bananas"
print(re.findall(r"\d+", text))
# Output: ['12', '345']

Find "ab" followed by zero or more "c":
import re
text = "abc abcc abccc ab"
print(re.findall(r"abc*", text))
# Output: ['abc', 'abcc', 'abccc', 'ab']

Find "colour" or "color":

text = "I like color and colour."
print(re.findall(r"colou?r", text))
# Output: ['color', 'colour']

Find exactly 3 digits:
text = "abc 123 4567 89"
print(re.findall(r"\d{3}", text))
# Output: ['123', '456']

Find 2 to 4 letters:
text = "go to USA and UK and Canada"
print(re.findall(r"[A-Za-z]{2,4}", text))
# Output: ['go', 'to', 'USA', 'and', 'UK', 'and']

Check if a string starts with a capital letter:
text = "Hello world"
print(bool(re.match(r"^[A-Z]", text)))
# Output: True

.* is greedy; .*? is lazy:
text = "<tag>content</tag><tag>another</tag>"
print(re.findall(r"<tag>.*</tag>", text))
# Greedy: ['<tag>content</tag><tag>another</tag>']

print(re.findall(r"<tag>.*?</tag>", text))
# Lazy: ['<tag>content</tag>', '<tag>another</tag>']/

pattern = r"^[A-Za-z]\d[A-Za-z]\d[A-Za-z]\d$"   # Postal Code, Zip Code
codes = ["L4J2K4", "L4J 2K4", "123ABC"]
for code in codes:
    print(code, bool(re.match(pattern, code)))
# Output:
# L4J2K4 True
# L4J 2K4 False
# 123ABC False

Check if a string ends with a number:
text = "Invoice number is 12345"
print(bool(re.search(r"\d+$", text)))
# Output: True

Python Regex Functions
Explain and demonstrate:
re.search(pattern, text)
re.match(pattern, text)
re.findall(pattern, text)
re.sub(pattern, replacement, text)

Quick exercise:

import re
email = "contact me at test@example.com"
pattern = r"\w+@\w+\.\w+"
print(re.findall(pattern, email))  # ['test@example.com']

Grouping and Capturing
Parentheses () to capture parts.

m = re.search(r"(\d{3})-(\d{3})-(\d{4})", "Call 416-555-1234")
if m:
    print(m.group(1), m.group(2), m.group(3))

Practice Exercises
Hands-on exercises:

Find all phone numbers:


Text: "Call 416-555-1234 or 905-666-7890 "
Extract all words starting with capital letters.
ans: r"\d{3}-\d{3}-\d{4}"
Replace multiple spaces with one.

Validate postal code (e.g., L4J 2K4):

Pattern: r"[A-Za-z]\d[A-Za-z] ?\d[A-Za-z]\d"

Wrap-up & Homework
Summarize:

Regex basics

Python re module

Homework:

Write a regex to validate email addresses.

Extract hashtags from a sentence like:
"Loving #Python and #Regex today!"

Write a regex to find all numbers in a sentence like:
"Call 416-555-1234 or 905-666-7890"