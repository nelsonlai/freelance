# Give me the example of decorators in python

def TimeElapsed(original_function):     # Decorator to measure time taken by a function. Decorator function
    def wrapper_function(*args, **kwargs):
        start_time = time.perf_counter()
        result = original_function(*args, **kwargs)
        end_time = time.perf_counter()
        print(f"Time taken by {original_function.__name__}: {end_time - start_time} seconds")
        return result
    return wrapper_function

def decorator_B(original_function):
    def wrapper_function(*args, **kwargs):
        print('I am decorator_B - before')
        result = original_function(*args, **kwargs)
        print('I am decorator_B - after')
        return result
    return wrapper_function


@TimeElapsed
@decorator_B
def display_1(arg1, arg2, arg3, alice=32):
    # Display triangle graphic
    print("Displaying triangle graphic")
    return None

@TimeElapsed
@decorator_B
def display_2(arg1, arg2, arg3, alice=32):
    # Display square graphic
    print("Displaying square graphic")
    return None

result = display_1(10, 20, 30, alice=32)
