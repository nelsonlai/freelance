'''
Bubble Sort 
Time Complexity of Bubble Sort
Case    Comparisons/Swaps   Time Complexity
Best Case   No swaps needed (already sorted)    O(n)
Average Case    Regular comparisons/swaps   O(n²)
Worst Case  Reverse sorted array    O(n²)

Space Complexity
O(1) Bubble sort is an in-place sorting algorithm (uses no extra space except a few variables).

https://visualgo.net/en/sorting
'''

def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        # Track whether any swap was made in this pass
        swapped = False
        for j in range(0, n - i - 1):  # Last i elements are already sorted
            if arr[j] > arr[j + 1]:
                # Swap if the current item is greater than the next
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                swapped = True
        # If no swaps were made, the list is already sorted
        if not swapped:
            break

# Example usage:
arr = [64, 34, 25, 12, 22, 11, 1, 23, 7, 5, 9]
print("Original array:", arr)
bubble_sort(arr)
print("Sorted array:  ", arr)
