'''
Radix Sort
Time Complexity
Radix Sort runs in:

O(d * (n + k))
Where:

n = number of elements

d = number of digits in the maximum number

k = range of digits (base, usually 10)

Space Complexity
O(n + k):

O(n) for the output array

O(k) for the count array (usually size 10 for base 10 digits)

https://visualgo.net/en/sorting
'''

def counting_sort(arr, exp):
    n = len(arr)
    output = [0] * n       # Output array
    count = [0] * 10       # Count array for digits (0 to 9)

    # Count the occurrences of each digit at current exponent (place)
    for i in range(n):
        index = (arr[i] // exp) % 10
        count[index] += 1

    # Update count[i] to be the position of this digit in output[]
    for i in range(1, 10):
        count[i] += count[i - 1]

    # Build output[] using count[] (traverse input in reverse for stability)
    i = n - 1
    while i >= 0:
        index = (arr[i] // exp) % 10
        output[count[index] - 1] = arr[i]
        count[index] -= 1
        i -= 1

    # Copy sorted digits back to original array
    for i in range(n):
        arr[i] = output[i]

def radix_sort(arr):
    if not arr:
        return

    # Find the maximum number to know the number of digits
    max_num = max(arr)

    # Apply counting_sort to each digit place (1s, 10s, 100s, etc.)
    exp = 1
    while max_num // exp > 0:
        counting_sort(arr, exp)
        exp *= 10

# Example usage:
arr = [170, 45, 75, 90, 802, 24, 2, 66, 131, 582, 974, 138, 151, 555, 77, 123, 456, 999, 1]
print("Original array:", arr)
radix_sort(arr)
print("Sorted array:  ", arr)