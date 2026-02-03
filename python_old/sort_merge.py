'''
Merge Sort 
Time Complexity
Case    Time
Best    O(n log n)
Average O(n log n)
Worst   O(n log n)

Space Complexity
O(n) (for auxiliary arrays L[] and R[])

Merge Sort is not in-place - it requires extra space proportional to the size of the array.

https://visualgo.net/en/sorting
'''

def merge_sort(arr):
    if len(arr) > 1:
        # Find the middle point and divide the array
        mid = len(arr) // 2
        L = arr[:mid]   # Left half
        R = arr[mid:]   # Right half

        # Sort the two halves
        merge_sort(L)
        merge_sort(R)

        # Merge the sorted halves
        i = j = k = 0

        # Compare elements from L and R and build the sorted array
        while i < len(L) and j < len(R):
            if L[i] < R[j]:
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1

        # Check if any elements were left in L
        while i < len(L):
            arr[k] = L[i]
            i += 1
            k += 1

        # Check if any elements were left in R
        while j < len(R):
            arr[k] = R[j]
            j += 1
            k += 1

# Example usage:
arr = [38, 27, 1, 43, 3, 9, 82, 10, 7, 2, 5]
print("Original array:", arr)
merge_sort(arr)
print("Sorted array:  ", arr)