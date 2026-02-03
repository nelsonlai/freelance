empty_list = list() # this is an empty list, no item in the list
empty_list = []
print(len(empty_list)) # 0

a_string = "This is a string"

fruits = ['banana', 'orange', 'mango', 'lemon']                     # list of fruits
vegetables = ['Tomato', 'Potato', 'Cabbage','Onion', 'Carrot']      # list of vegetables
animal_products = ['milk', 'meat', 'butter', 'yogourt']             # list of animal products
web_techs = ['HTML', 'CSS', 'JS', 'React','Redux', 'Node', 'MongDB'] # list of web technologies
countries = ['Finland', 'Estonia', 'Denmark', 'Sweden', 'Norway']

list_aa = [1, 2, 3, [4, 5], 4, 5, 'ABC', [1, 'XYZ', 3]]

# Print the lists and it length
print('Fruits:', fruits)
print('Number of fruits:', len(fruits)) # length -> len
print('list_aa:', len(list_aa)) # length -> len (8)
print('Vegetables:', vegetables)
print('Number of vegetables:', len(vegetables))
print('Animal products:',animal_products)
print('Number of animal products:', len(animal_products))
print('Web technologies:', web_techs)
print('Number of web technologies:', len(web_techs))
print('Number of countries:', len(countries))   # How many countries in this list

# Modifying list

fruits = ['banana', 'orange', 'mango', 'lemon'] 
list_aa = [1, 2, 3, [4, 5], 4, 5, 'ABC', [1, 'XYZ', 3]]
x = list_aa[0]  # 1
x = list_aa[3] # [4, 5]
x = list_aa[3][0] # 4
x = list_aa[7] # [1, 'XYZ', 3]
x = list_aa[7][1] # 'XYZ'
first_fruit = fruits[0] # we are accessing the first item using its index
print(first_fruit)      # banana
second_fruit = fruits[1]
print(second_fruit)     # orange
last_fruit = fruits[3]
print(last_fruit) # lemon
# Last index
last_index = len(fruits) - 1
last_fruit = fruits[last_index]

# Accessing items
fruits = ['banana', 'orange', 'mango', 'lemon'] 
length = len(fruits)
last_fruit = fruits[length - 1]
last_fruit = fruits[-1]
second_last = fruits[-2]
print(last_fruit)       # lemon
print(second_last)      # mango

# Slicing items
fruits = ['banana', 'orange', 'mango', 'lemon'] 
all_fruits = fruits[0:4] # it returns all the fruits
# this is also give the same result as the above
all_fruits = fruits[2:] # if we don't set where to stop it takes all the rest
orange_and_mango = fruits[1:3] # it does not include the end index # 1, 2
orange_mango_lemon = fruits[1:]

fruits = ['banana', 'orange', 'mango', 'lemon'] 
all_fruits = fruits[-4:] # it returns all the fruits
# this is also give the same result as the above
orange_and_mango = fruits[-3:-1] # it does not include the end index
x = fruits[2:]
x = fruits[-2:]  #
orange_mango_lemon = fruits[-3:]


fruits = ['banana', 'orange', 'mango', 'lemon'] 
fruits[0] = 'Avocado' 
print(fruits)       #  ['avocado', 'orange', 'mango', 'lemon']
fruits[1] = 'apple'
print(fruits)       #  ['avocado', 'apple', 'mango', 'lemon']
last_index = len(fruits) - 1
fruits[last_index] = 'lime'
fruits[-1] = 'lime'
print(fruits)        #  ['avocado', 'apple', 'mango', 'lime']

# checking items
fruits = ['banana', 'orange', 'mango', 'lemon']

if 'banana' in fruits:
    print('banana is in the list')
else:
    print('banana is not in the list')

does_exist = 'banana' in fruits     # True or False
print(does_exist)  # True
does_exist = 'lime' in fruits
print(does_exist)  # False

# Append
fruits = ['banana', 'orange', 'mango', 'lemon']
fruits.append('apple')
print(fruits)           # ['banana', 'orange', 'mango', 'lemon', 'apple']
fruits.append('lime')   # ['banana', 'orange', 'mango', 'lemon', 'apple', 'lime]
print(fruits)

# insert
fruits = ['banana', 'orange', 'mango', 'lemon']
fruits.insert(2, 'apple') # insert apple between orange and mango
print(fruits)           # ['banana', 'orange', 'apple', 'mango', 'lemon']
fruits.insert(3, 'lime')   # ['banana', 'orange', 'apple', 'lime', 'mango','lemon',]
print(fruits)
fruits.insert(0, 'kiwi')
print(fruits)           # ['kiwi', 'banana', 'orange', 'apple', 'lime', 'mango', 'lemon']

# What are the built-in methods for strings -> Homework #1
# What are the built-in functions for list -> Homework #2
# remove
fruits = ['banana', 'orange', 'mango', 'lemon']
fruits.remove('banana') # "Banana", "banaNa" are different
fruits.remove('kiwi')  # ValueError: list.remove(x): x not in list
print(fruits)  # ['orange', 'mango', 'lemon']
fruits.remove('lemon')
print(fruits)  # ['orange', 'mango']

# pop
fruits = ['banana', 'orange', 'mango', 'lemon']
fruits.pop()        # removes a random item from the list
x = fruits.pop()    # removes a random item from the list
x = 'orange'
['banana', 'mango', 'lemon']
print(fruits)       # ['banana', 'orange', 'mango']

fruits.pop(0)     
print(fruits)       # ['orange', 'mango'] 

# del 
fruits = ['banana', 'orange', 'mango', 'lemon']
del fruits[0]     
print(fruits)       # ['orange', 'mango', 'lemon']

del fruits[1]     
print(fruits)       # ['orange', 'lemon']
del fruits
print(fruits)       # This should give: NameError: name 'fruits' is not defined

# clear
fruits = ['banana', 'orange', 'mango', 'lemon']
fruits.clear()     
print(fruits)       # []

# copying a lits

fruits = ['banana', 'orange', 'mango', 'lemon']
fruits_shallow_copy = fruits
fruits_deep_copy = fruits.copy()         ## shallow copy v.s deep copy
fruits[0] = 'apple'
print(fruits_deep_copy)       # ['banana', 'orange', 'mango', 'lemon']

# join
positive_numbers = [1, 2, 3,4,5]
zero = [0]
negative_numbers = [-5,-4,-3,-2,-1]
integers = negative_numbers + zero + positive_numbers
print(integers)
fruits = ['banana', 'orange', 'mango', 'lemon']
vegetables = ['Tomato', 'Potato', 'Cabbage','Onion', 'Carrot'] 
fruits_and_vegetables = fruits + vegetables
print(fruits_and_vegetables )

# join with extend
num1 = [0, 1, 2, 3]
num2= [4, 5,6]
num1.extend(num2)   # add num2 to num1

print('Numbers:', num1)
negative_numbers = [-5,-4,-3,-2,-1]
positive_numbers = [1, 2, 3,4,5]
zero = [0]

negative_numbers.extend(zero)
negative_numbers.extend(positive_numbers)
print('Integers:', negative_numbers)
fruits = ['banana', 'orange', 'mango', 'lemon']
vegetables = ['Tomato', 'Potato', 'Cabbage','Onion', 'Carrot'] 
fruits.extend(vegetables)
print('Fruits and vegetables:', fruits )

# count
fruits = ['banana', 'orange', 'mango', 'lemon']
print(fruits.count('orange'))   # 1
ages = [22, 19, 24, 25, 26, 24, 25, 24] # length for numbers of items
print(ages.count(24))           # 3

# index
fruits = ['banana', 'orange', 'mango', 'lemon']
print(fruits.index('orange'))   # 1
ages = [22, 19, 24, 25, 26, 24, 25, 24]
print(ages.index(24))           # 2
# Reverse
fruits = ['banana', 'orange', 'mango', 'lemon']
fruits.reverse()
print(fruits)   # ['lemon', 'mango', 'orange', 'banana']
ages = [22, 19, 24, 25, 26, 24, 25, 24]
ages.reverse()
print(ages) 

# sort
fruits = ['banana', 'orange', 'mango', 'lemon']
fruits.sort()
print(fruits) 
fruits.sort(reverse=True)
print(fruits)
ages = [22, 19, 24, 25, 26, 24, 25, 24]
ages.sort()
print(ages) 
ages.sort(reverse=True)
print(ages)

## In python, tell me all the bult-in methods for list -> Homework #1