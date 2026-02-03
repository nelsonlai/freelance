def add(a, b):
    return a + b

def div(a, b):
    if b == 0:
        raise ValueError("b must be non-zero")
    return a / b

def reciprocal(x):
    if x == 0:
        raise ValueError("x must be non-zero")
    return 1 / x

# TODO: Exercise A
# Implement subtract(a, b) to return a - b
# def subtract(a, b):
#     ...
