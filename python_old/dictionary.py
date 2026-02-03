'''
Dictionaries
A dictionary is a collection of unordered, modifiable(mutable) paired (key: value) data type.

Creating a Dictionary
To create a dictionary we use curly brackets, {} or the dict() built-in function.
'''

# syntax
empty_dict = {}
empty_dict = dict()
# Dictionary with data values
dct = {'key1':'value1', 'key2':'value2', 'key3':'value3', 'key4':'value4'}

person = {
    'first_name':'Chih Huang',
    'last_name':'Nyugen',
    'age':25,
    'country':'Finland',
    'is_marred':False,
    'skills':['JavaScript', 'React', 'Node', 'MongoDB', 'Python'],
    'address':{
        'street':'123 Space street',
        'zipcode':'02210'
    }
}

# Dictionary Length
# It checks the number of 'key: value' pairs in the dictionary.
# syntax
dct = {'key1':'value1', 'key2':'value2', 'key3':'value3', 'key4':'value4'}
print(len(dct)) # 4

person = {
    'first_name':'Asabeneh',
    'last_name':'Yetayeh',
    'age':250,
    'country':'Finland',
    'is_married':True,
    'skills':['JavaScript', 'React', 'Node', 'MongoDB', 'Python'],
    'address':{
        'street':'Space street',
        'zipcode':'02210'
    }
    }
print(len(person)) # 7

# Accessing Dictionary Items

# syntax
dct = {'key1':'value1', 'key2':'value2', 'key3':'value3', 'key4':'value4'}
print(dct['key1']) # value1
print(dct['key4']) # value4

person = {
    'first_name':'Asabeneh',
    'last_name':'Yetayeh',
    'age':250,
    'country':'Finland',
    'is_marred':True,
    'skills':['JavaScript', 'React', 'Node', 'MongoDB', 'Python'],
    'address':{
        'street':'Space street',
        'zipcode':'02210'
    }
}
print(person['first_name']) # Asabeneh
print(person['age'])  # 250
print(person['country'])    # Finland
print(person['skills'])     # ['JavaScript', 'React', 'Node', 'MongoDB', 'Python']
print(person['skills'][0])  # JavaScript
print(person['address']) # address
print(person['address']['street']) # Space street
print(person['city'])       # Error         # Exception handling

person = {
    'first_name':'Asabeneh',
    'last_name':'Yetayeh',
    'age':250,
    'country':'Finland',
    'is_marred':True,
    'skills':['JavaScript', 'React', 'Node', 'MongoDB', 'Python'],
    'address':{
        'street':'Space street',
        'zipcode':'02210'
    }
    }
print(person.get('first_name')) # Asabeneh
print(person.get('country'))    # Finland
print(person.get('skills')) #['HTML','CSS','JavaScript', 'React', 'Node', 'MongoDB', 'Python']
print(person.get('city'))   # Error
print(person.get('city', 'Not Found')) # Not Found
print(person.get('city', None)) # None
print(person['address']['street']) # Space street
print(person['address']['zipcode'])       # 02210

# Adding Items to a Dictionary

# syntax
dct = {'key1':'value1', 'key2':'value2', 'key3':'value3', 'key4':'value4'}
dct['key4'] = 'valuexx'     # key4 is updated
dct['key5'] = 'value5'      # key5 is added

person = {
    'first_name':'Asabeneh',
    'last_name':'Yetayeh',
    'age':250,
    'country':'Finland',
    'is_marred':True,
    'skills':['JavaScript', 'React', 'Node', 'MongoDB', 'Python'],
    'address':{
        'street':'Space street',
        'zipcode':'02210'
        }
}
person['last_name'] = 'LIN'
person['myKey'] = 'myValue'
person['job_title'] = 'Instructor'
person['skills'].append('HTML')
print(person)

# Modifying Items in a Dictionary

# syntax
dct = {'key1':'value1', 'key2':'value2', 'key3':'value3', 'key4':'value4'}
dct['key1'] = 'value-one'

person = {
    'first_name':'Asabeneh',
    'last_name':'Yetayeh',
    'age':250,
    'country':'Finland',
    'is_marred':True,
    'skills':['JavaScript', 'React', 'Node', 'MongoDB', 'Python'],
    'address':{
        'street':'Space street',
        'zipcode':'02210'
    }
    }
person['first_name'] = 'Eyob'
person['age'] = 255

# Checking Keys in a Dictionary

# syntax
dct = {'key1':'value1', 'key2':'value2', 'key3':'value3', 'key4':'value4'}
print('key2' in dct) # True
print('key5' in dct) # False

# Removing Key and Value Pairs from a Dictionary
# pop(key): removes the item with the specified key name:
# popitem(): removes the last item

# del: removes an item with specified key name
# syntax
dct = {'key1':'value1', 'key2':'value2', 'key3':'value3', 'key4':'value4'}
dct.pop('key9') # removes key1 item
dct = {'key1':'value1', 'key2':'value2', 'key3':'value3', 'key4':'value4'}
dct.popitem() # removes the last item
del dct['key7'] # removes key2 item

# del, pop

person = {
    'first_name':'Asabeneh',
    'last_name':'Yetayeh',
    'age':250,
    'country':'Finland',
    'is_marred':True,
    'skills':['JavaScript', 'React', 'Node', 'MongoDB', 'Python'],
    'address':{
        'street':'Space street',
        'zipcode':'02210'
    }
}
person.pop('first_name')        # Removes the firstname item
person.popitem()                # Removes the address item
del person['is_married']        # Removes the is_married item

# Changing Dictionary to a List of Items
# The items() method changes dictionary to a list of tuples.

# syntax
dct = {'key1':'value1', 'key2':'value2', 'key3':'value3', 'key4':'value4'}
key, value = dct.items()        # Homework #1 What are the built-in functions of the dictionary in Python
print(dct.items()) # dict_items([('key1', 'value1'), ('key2', 'value2'), ('key3', 'value3'), ('key4', 'value4')])

for key, value in dct.items():
# Clearing a Dictionary
# If we don't want the items in a dictionary we can clear them using clear() method

# syntax
dct = {'key1':'value1', 'key2':'value2', 'key3':'value3', 'key4':'value4'}
print(dct.clear()) # {}

# Deleting a Dictionary
# If we do not use the dictionary we can delete it completely

# syntax
dct = {'key1':'value1', 'key2':'value2', 'key3':'value3', 'key4':'value4'}
del dct # None

# Copy a Dictionary
# We can copy a dictionary using a copy() method. Using copy we can avoid mutation of the original dictionary.

# syntax
dct = {'key1':'value1', 'key2':'value2', 'key3':'value3', 'key4':'value4'}
dct_copy = dct.copy() # {'key1':'value1', 'key2':'value2', 'key3':'value3', 'key4':'value4'} # deep copy
dct_copy2 = dct     # shallow copy
dct['key2'] = 'value2'
dct['key5'] = 'value5'
print (dct_copy)
print (dct_copy2)
# shallow copy, deep copy

# Getting Dictionary Keys as a List
# The keys() method gives us all the keys of a a dictionary as a list.

# syntax
dct = {'key1':'value1', 'key2':'value2', 'key3':'value3', 'key4':'value4'}
keys = dct.keys()
print(keys)     # dict_keys(['key1', 'key2', 'key3', 'key4'])

# Getting Dictionary Values as a List
# The values method gives us all the values of a a dictionary as a list.

# syntax
dct = {'key1':'value1', 'key2':'value2', 'key3':'value3', 'key4':'value4'}
values = dct.values()
print(values)     # dict_values(['value1', 'value2', 'value3', 'value4'])

keys, values = dct.items()


############# Home work ############
Homework 1: Library Book Tracker
Objective: Use dictionary, list, and control flow.

Task:

Create a system to track library books.

Each book has: title, author, genre, and status ("available" or "checked out").

Use a list of dictionaries to represent the library.

Functions to:

Add a new book.

Search for books by genre or author.

Mark a book as checked out or returned.

Print all available books.

Concepts Practiced:

Dictionary structure

if/else to update status

Loops for searching/filtering

