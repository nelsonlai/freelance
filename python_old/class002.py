
first_name = 'TEN EN'
last_name = 'LIN'
country = 'Taiwan'
city = 'Taipei'
age = 25
is_married = True
skills = ['HTML', 'CSS', 'JS', 'React', 'Python']   # List
person_info = {                # Dictionary
    'firstname':'Evan',
    'lastname':'Hsieh',
    'country':'Taiwan',
    'city':'Taipei',
    'age':25
}

first_name, last_name, country, age, is_married = 'Evan', 'Hsieh', 'Taiwan', 25, False
a = b = c = d = e = 10

print(first_name, last_name, country, age, is_married)
print(f'First name: {first_name}')  # format-string
print("First name: " + first_name)
print("First name: ", first_name)
print(f'Last name: {last_name}')
print(f'Country: {country}')
print(f'Age: {age}')
print(f'Married: {is_married}')

first_name = input('What is your name: ')
age = int (input('How old are you? '))

print(first_name)
print(age)

# int to float
num_int = 10
print('num_int',num_int)         # 10
print(f'num_int {num_int}')
num_float = float(num_int)
print('num_float:', num_float)   # 10.0
print(f'num_float: {num_float}')

# float to int
gravity = 9.81
print(int(gravity))             # 9

# int to str
num_int = 10
print(num_int)                  # 10
num_str = str(num_int)
print(num_str)                  # '10'

# str to int or float
num_str = '10.6'    # string "10.6"
num_float = float(num_str)
print('num_float', float(num_str))  # 10.6
num_int = int(num_float)
print('num_int', int(num_int))      # 10

# str to list
first_name = 'Asabeneh'
print(first_name)               # 'Asabeneh'
first_name_to_list = list(first_name)
print(first_name_to_list)            # ['A', 's', 'a', 'b', 'e', 'n', 'e', 'h']
