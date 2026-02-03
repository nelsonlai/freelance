'''
Selection Sort
Time and Space Complexity
Case    Time Complexity
Best Case   O(n²)
Average O(n²)
Worst Case  O(n²)

Space Complexity    O(1)

https://visualgo.net/en/sorting
'''

def insertion_sort(arr):
    # Traverse from index 1 to end of the array
    for i in range(1, len(arr)):
        key = arr[i]  # Current element to be inserted in sorted part
        j = i - 1

        # Move elements of arr[0..i-1] that are greater than key one position ahead
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        
        # Insert the key at its correct position
        arr[j + 1] = key

# Example usage:
arr = [12, 11, 13, 5, 6, 2, 1, 17, 29, 10]
print("Original array:", arr)
insertion_sort(arr)
print("Sorted array:  ", arr)