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

def subtract(a, b):
    return a - b
