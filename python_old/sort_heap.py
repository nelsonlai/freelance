'''
Heap Sort

Time Complexity of Heap Sort
Operation   Time Complexity
Building the heap   O(n)
Heapify (per call)  O(log n)
Extract elements    O(n log n)
Total   O(n log n)

Space Complexity
O(1)

https://www.youtube.com/watch?v=mgUiY8CVDhU
'''

def heapify(arr, n, i):
    largest = i          # Initialize largest as root
    left = 2 * i + 1     # left child = 2*i + 1
    right = 2 * i + 2    # right child = 2*i + 2

    # If left child exists and is greater than root
    if left < n and arr[left] > arr[largest]:
        largest = left

    # If right child exists and is greater than current largest
    if right < n and arr[right] > arr[largest]:
        largest = right

    # If largest is not the root
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]  # Swap
        heapify(arr, n, largest)  # Recursively heapify the affected subtree

def heap_sort(arr):
    n = len(arr)

    # Step 1: Build a maxheap
    for i in range(n // 2 - 1, -1, -1):  # Start from the last non-leaf node
        heapify(arr, n, i)

    # Step 2: Extract elements from heap one by one
    for i in range(n - 1, 0, -1):
        arr[0], arr[i] = arr[i], arr[0]  # Swap current root to end
        heapify(arr, i, 0)  # Heapify reduced heap

# Example usage:
arr = [12, 11, 13, 5, 6, 7, 22, 2, 3, 4, 10, 9, 8, 1]
print("Original array:", arr)
heap_sort(arr)
print("Sorted array:  ", arr)