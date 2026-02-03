'''
Loops
Life is full of routines. In programming we also do lots of repetitive tasks. In order to handle repetitive task programming languages use loops. Python programming language also provides the following types of two loops:

while loop
for loop
While Loop
We use the reserved word while to make a while loop. It is used to execute a block of statements repeatedly until a given condition is satisfied. When the condition becomes false, the lines of code after the loop will be continued to be executed.

# syntax
while condition:
    code goes here
'''

count = 0
while count < 5:
    print(count)    # 0, 1, 2, 3, 4
    count = count + 1   # count += 1
else:
    print(count)    # 5

while count < 5:
    print(count)    # 0, 1, 2, 3, 4
    count = count + 1   # count += 1

'''
syntax
while condition:
    code goes here
else:
    code goes here
'''


'''
# syntax
while condition:
    code goes here
    if another_condition:
        break
'''

count = 0
while count < 5:
    print(count)    # 0, 1, 2
    count = count + 1
    if count == 3:
        break

# The above while loop only prints 0, 1, 2, but when it reaches 3 it stops.

'''
# syntax
while condition:
    code goes here
    if another_condition:
        continue
'''

count = 0
while count < 5:
    if count == 3:
        count = count + 1
        continue
    print(count)    # 0, 1, 2, 4
    count = count + 1

'''
For loop with list
# syntax
for iterator in lst:
    code goes here
'''

numbers = [0, 1, 2, 3, 4, 5]    # List
number = 13
if number in numbers:
    print(f"{number} is in the list")
else:
    print(f"{number} is not in the list")

for number in numbers: # number is a temporary name to refer to the list's items, valid only inside this loop, the numbers will be printed line by line, from 0 to 5
    print(number)      # 0, 1, 2, 3, 4, 5

'''
For loop with string
# syntax
for iterator in string:
    code goes here
'''

language = 'Python'
for letter in language:
    print(letter)

# range is a python built-in function that returns a sequence of numbers
for i in range(6):  # range(6) returns [0, 1, 2, 3, 4, 5]
    print(i)        # 0, 1, 2, 3, 4, 5

'''
For loop with tuple
# syntax
for iterator in tpl:
    code goes here
'''
numbers = [0, 1, 2, 3, 4, 5] # List

numbers = (0, 1, 2, 3, 4, 5) # Tuple
for number in numbers:
    print(number)

'''
For loop with dictionary Looping through a dictionary gives you the key of the dictionary.
  # syntax
for iterator in dct:
    code goes here
'''

person = {
    'first_name':'Chih Huang',
    'last_name':'Nguyen',
    'age':9,
    'country':'Vietnam',
    'is_marred':True,
    'skills':['JavaScript', 'React', 'Node', 'MongoDB', 'Python'],
    'address':{
        'street':'Space street',
        'zipcode':'02210'
        }
}

it_companies = {'Facebook', 'Google', 'Microsoft', 'Apple', 'IBM', 'Oracle', 'Amazon'}
for company in it_companies:
    print(company)
    
for key in person:
    print(key)

for key, value in person.items():
    print(key, value) # this way we get both keys and values printed out

'''
Loops in set
# syntax
for iterator in st:
    code goes here
'''

it_companies = {'Facebook', 'Google', 'Microsoft', 'Apple', 'IBM', 'Oracle', 'Amazon'}
for company in it_companies:
    print(company)

'''
Break: We use break when we like to stop the iteration of the loop.
# syntax
for iterator in sequence:
    code goes here
    if condition:
        break
'''

numbers = (0,1,2,3,4,5)
for number in numbers:  # 0, 1, 2
    print(number)
    if number == 3:
        break

'''
Continue: We use continue when we like to skip some of the steps in the iteration of the loop.

  # syntax
for iterator in sequence:
    code goes here
    if condition:
        continue
'''

numbers = (0,1,2,3,4,5)
for number in numbers:  # 0, 1, 2, 4, 5
    print(number)
    if number == 3:
        continue
    print('Next number should be ', number + 1) if number != 5 else print("loop's end") # for short hand conditions need both if and else statements
print('outside the loop')


# The Range Function
The range() function is used list of numbers. The range(start, end, step) takes three parameters: 
starting, ending and increment. By default it starts from 0 and the increment is 1. 
The range sequence needs at least 1 argument (end). Creating sequences using range

lst = list(range(11)) 
print(lst) # [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
st = set(range(2, 11))    # 2 arguments indicate start and end of the sequence, step set to default 1
print(st) # {2, 3, 4, 5, 6, 7, 8, 9, 10}

lst = list(range(0,11,2))
print(lst) # [0, 2, 4, 6, 8, 10]
st = set(range(0,11,2))
print(st) #  {0, 2, 4, 6, 8, 10}

'''
# syntax
for iterator in range(start, end, step):
'''

for number in range(11):
    print(number)   # prints 0 to 10, not including 11

'''
# syntax
for x in y:
    for t in x:
        print(t)
'''

person = {
    'first_name': 'Asabeneh',
    'last_name': 'Yetayeh',
    'age': 250,
    'country': 'Finland',
    'is_marred': True,
    'skills': ['JavaScript', 'React', 'Node', 'MongoDB', 'Python'],
    'address': {
        'street': 'Space street',
        'zipcode': '02210'
    }
}
for key in person:
    if key == 'skills':
        for skill in person['skills']:
            print(skill)

'''
# syntax
for iterator in range(start, end, step):
    do something
else:
    print('The loop ended')
'''

for number in range(11):
    print(number)   # prints 0 to 10, not including 11
else:
    print('The loop stops at', number)
Pass

if condition:
    code ...
    code ...
else:
    pass
'''
In python when statement is required (after semicolon), but we don't like to execute any code there, we can write the word pass to avoid errors. Also we can use it as a placeholder, for future statements.

Example:

for number in range(6):
    pass
🌕 You established a big milestone, you are unstoppable. Keep going! You have just completed day 10 challenges and you are 10 steps a head in to your way to greatness. Now do some exercises for your brain and muscles.
''' 

'''
Exercises:

Write a loop that makes seven calls to print(), so we get on the output the following triangle:
  #
  ##
  ###
  ####
  #####
  ######
  #######
  
Use nested loops to create the following:

# # # # # # # #
# # # # # # # #
# # # # # # # #
# # # # # # # #
# # # # # # # #
# # # # # # # #
# # # # # # # #
# # # # # # # #
Print the following pattern:

0 x 0 = 0
1 x 1 = 1
2 x 2 = 4
3 x 3 = 9
4 x 4 = 16
5 x 5 = 25
6 x 6 = 36
7 x 7 = 49
8 x 8 = 64
9 x 9 = 81
10 x 10 = 100

Use for loop to iterate from 0 to 100 and print only odd numbers

Exercises:
Use for loop to iterate from 0 to 100 and print the sum of all numbers.
The sum of all numbers is 5050.
Use for loop to iterate from 0 to 100 and print the sum of all evens and the sum of all odds.

The sum of all evens is 2550. And the sum of all odds is 2500.
Exercises: Level 3
'''