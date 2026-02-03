# Recursive function to calculate Fibonacci number
# F(0) = 0, F(1) = 1
# F(n) = F(n - 1) + F(n - 2)
# Given n, find F(n)
# What is recursion?
# Recursion is a process in which a function calls itself as a subroutine.
# This allows the function to be repeated several times, as it can call itself during its execution.
def fibonacci_recursive(n):
    if n <= 0:
        return 0
    elif n == 1:
        return 1
    else:
        return fibonacci_recursive(n - 2) + fibonacci_recursive(n - 1)

if __name__ == "__main__":
    # Ask user for number of terms
    num_terms = 40

    for i in range(num_terms):
        print(fibonacci_recursive(i), end=" ")
