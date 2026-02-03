'''
# syntax
What is condition? Condition is a statement that is evaluated as true or false. 
If the condition is true, the block code will be executed. 
If the condition is false, the block code will not be executed.

if condition:
    this part of code runs for truthy conditions
else:
     this part of code runs for false conditions

'''
a = 3
if a < 0:
    print('A is a negative number')
else:
    print('A is a positive number')

'''
# syntax
if condition_a:
    code_a--1
    code_a--2
    code_a--3
elif condition_b:
    code_b-1
    code_b-2
elif condition_c:
    code_c
else:
    pass
'''
a = 0
if a > 0:
    print('A is a positive number')
elif a < 0:
    print('A is a negative number')
else:
    print('A is zero')

'''
Short Hand
# syntax
code if condition else code
'''
a = 3
print('A is a positive number') if a > 0 else print('A is a negative number')

if a > 0:
    print('A is a positive number')
else:
    print('A is a negative number')

'''
Conditions can be nested

# syntax    # Nested if ...
if condition:
    code
    if condition:
    code
'''
a = 0
if a > 0:
    if a % 2 == 0: 
        print('A is a positive and even integer')
        ...
        ...
    else:
        print('A is a positive number')
elif a == 0:
    print('A is zero')
else:
    print('A is a negative number')

'''
If Condition and Logical Operators
# syntax
if condition and condition:
    code
'''

a = 7
if a > 0 and a % 2 == 0:    # or a % 2 != 0
    print('A is an even and positive integer')
elif a > 0 and a % 2 !=  0:
    print('A is a positive integer')
elif a == 0:
    print('A is zero')
else:
    print('A is negative')

'''
If and Or Logical Operators
# syntax
if condition or condition:
    code
'''

user = 'James'
access_level = 3
if user == 'admin' or access_level >= 4:
    print('Access granted!')
else:
    print('Access denied!')

'''
Exercises: Level 1
Get user input using input(“Enter your age: ”). If user is 18 or older, give feedback: You are old enough to drive. If below 18 give feedback to wait for the missing amount of years. Output:

Enter your age: 30
You are old enough to learn to drive.
Output:
Enter your age: 15
You need 3 more years to learn to drive.
'''
age = int(input('Enter your age: '))

'''
Exercises: Level 2 -- Home Work #3
Write a code which gives grade to students according to theirs scores:

80-100, A
70-89, B
60-69, C
50-59, D
0-49, F
'''
score = int(input('Enter your score: '))