# Prompt the user for input
num1 = int(input("Enter first number: "))
num2 = int(input("Enter second number: "))
operator = input("Enter operator (+, -, *, /): ")

# Perform calculation
if operator == '+':
    result = num1 + num2
elif operator == '-':
    result = num1 - num2
elif operator == '*':
    result = num1 * num2
elif operator == '/':
    '''
    if num2 != 0:
        result = num1 / num2
    else:
        result = "Error: Cannot divide by zero"
    '''
    try:
        result = num1 / num2
    except ZeroDivisionError:
        result = "Error: Cannot divide by zero"

else:
    result = "Invalid operator"

# Print the result
print("Result:", result)