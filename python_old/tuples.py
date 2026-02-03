# syntax
empty_tuple = ()
# or using the tuple constructor
empty_tuple = tuple()

# Tuple with initial values
# syntax
tpl = ('item1', 'item2','item3')
fruits = ('banana', 'orange', 'mango', 'lemon')


# We use the len() method to get the length of a tuple.

# syntax
tpl = ('item1', 'item2', 'item3')
len(tpl)

# Syntax
tpl = ('item1', 'item2', 'item3','item4')
first_item = tpl[0]
second_item = tpl[1]

# Syntax
tpl = ('item1', 'item2', 'item3','item4')
all_items = tpl[0:4]         # all items
all_items = tpl[0:]         # all items
middle_two_items = tpl[1:3]  # does not include item at index 3

## slicing
fruits = ('banana', 'orange', 'mango', 'lemon')
all_fruits = fruits[0:4]    # all items
all_fruits= fruits[0:]      # all items
orange_mango = fruits[1:3]  # doesn't include item at index 3
orange_to_the_rest = fruits[1:]

## Changing Tuples to Lists
# Syntax
tpl = ('item1', 'item2', 'item3','item4')
lst = list(tpl)
fruits = ('banana', 'orange', 'mango', 'lemon')
fruits = list(fruits)
fruits[0] = 'apple'
print(fruits)     # ['apple', 'orange', 'mango', 'lemon']
fruits = tuple(fruits)
print(fruits)     # ('apple', 'orange', 'mango', 'lemon')

# Checking an Item in a Tuple
# Syntax
tpl = ('item1', 'item2', 'item3','item4')
'item2' in tpl # True
fruits = ('banana', 'orange', 'mango', 'lemon')
print('orange' in fruits) # True
print('apple' in fruits) # False
fruits[0] = 'apple' # TypeError: 'tuple' object does not support item assignment

# Joining Tuples
# syntax
tpl1 = ('item1', 'item2', 'item3')
tpl2 = ('item4', 'item5','item6')
tpl3 = tpl1 + tpl2
fruits = ('banana', 'orange', 'mango', 'lemon')
vegetables = ('Tomato', 'Potato', 'Cabbage','Onion', 'Carrot')
fruits_and_vegetables = fruits + vegetables

# Deleting Tuples
# syntax
tpl1 = ('item1', 'item2', 'item3')
del tpl1
fruits = ('banana', 'orange', 'mango', 'lemon')
del fruits
