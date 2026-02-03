'''
Quick Sort 
Time Complexity of Quick Sort
Case    Time Complexity
Best Case   O(n log n) → Balanced partitions
Average Case    O(n log n) → Random inputs
Worst Case  O(n²) → Already sorted or reversed (bad pivot)

Space Complexity
O(log n) → Recursion stack

https://visualgo.net/en/sorting
'''

def quick_sort(arr):
    if len(arr) <= 1:
        return arr  # Base case: already sorted

    pivot = arr[len(arr) // 2]  # Choose the middle element as pivot
    left = [x for x in arr if x < pivot]       # Elements less than pivot
    # print('Left: ', left)
    middle = [x for x in arr if x == pivot]    # Elements equal to pivot
    # print('Middle: ', middle)
    right = [x for x in arr if x > pivot]      # Elements greater than pivot
    # print('Right: ', right)

    # Recursively sort left and right, then combine
    return quick_sort(left) + middle + quick_sort(right)

# Example usage:
arr = [47, 2, 10, 7, 22, 8, 9, 1, 13, 5, 7, 4, 32, 6]
print("Original array:", arr)
sorted_arr = quick_sort(arr)
print("Sorted array:  ", sorted_arr)