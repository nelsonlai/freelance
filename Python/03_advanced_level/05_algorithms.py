# Algorithms Examples
import time
import random
from typing import List, Tuple, Optional
from collections import deque, defaultdict
import heapq

print("Algorithms Examples")
print("=" * 20)

# 1. Sorting Algorithms
print("1. Sorting Algorithms")
print("-" * 20)

def bubble_sort(arr: List[int]) -> List[int]:
    """Bubble sort algorithm."""
    arr = arr.copy()
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr

def selection_sort(arr: List[int]) -> List[int]:
    """Selection sort algorithm."""
    arr = arr.copy()
    n = len(arr)
    for i in range(n):
        min_idx = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_idx]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]
    return arr

def insertion_sort(arr: List[int]) -> List[int]:
    """Insertion sort algorithm."""
    arr = arr.copy()
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
    return arr

def merge_sort(arr: List[int]) -> List[int]:
    """Merge sort algorithm."""
    if len(arr) <= 1:
        return arr
    
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])
    
    return merge(left, right)

def merge(left: List[int], right: List[int]) -> List[int]:
    """Merge two sorted arrays."""
    result = []
    i = j = 0
    
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    
    result.extend(left[i:])
    result.extend(right[j:])
    return result

def quick_sort(arr: List[int]) -> List[int]:
    """Quick sort algorithm."""
    if len(arr) <= 1:
        return arr
    
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    
    return quick_sort(left) + middle + quick_sort(right)

def heap_sort(arr: List[int]) -> List[int]:
    """Heap sort algorithm."""
    arr = arr.copy()
    n = len(arr)
    
    # Build max heap
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)
    
    # Extract elements from heap
    for i in range(n - 1, 0, -1):
        arr[0], arr[i] = arr[i], arr[0]
        heapify(arr, i, 0)
    
    return arr

def heapify(arr: List[int], n: int, i: int):
    """Heapify a subtree rooted at index i."""
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2
    
    if left < n and arr[left] > arr[largest]:
        largest = left
    
    if right < n and arr[right] > arr[largest]:
        largest = right
    
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)

# Test sorting algorithms
test_array = [64, 34, 25, 12, 22, 11, 90, 5]
print(f"Original array: {test_array}")

print(f"Bubble sort: {bubble_sort(test_array)}")
print(f"Selection sort: {selection_sort(test_array)}")
print(f"Insertion sort: {insertion_sort(test_array)}")
print(f"Merge sort: {merge_sort(test_array)}")
print(f"Quick sort: {quick_sort(test_array)}")
print(f"Heap sort: {heap_sort(test_array)}")

# Performance comparison
def time_sorting_algorithm(sort_func, arr: List[int]) -> float:
    """Time a sorting algorithm."""
    start_time = time.time()
    sort_func(arr)
    return time.time() - start_time

# Create large array for performance testing
large_array = [random.randint(1, 1000) for _ in range(1000)]

print(f"\nPerformance comparison (1000 elements):")
print(f"Bubble sort: {time_sorting_algorithm(bubble_sort, large_array):.4f} seconds")
print(f"Selection sort: {time_sorting_algorithm(selection_sort, large_array):.4f} seconds")
print(f"Insertion sort: {time_sorting_algorithm(insertion_sort, large_array):.4f} seconds")
print(f"Merge sort: {time_sorting_algorithm(merge_sort, large_array):.4f} seconds")
print(f"Quick sort: {time_sorting_algorithm(quick_sort, large_array):.4f} seconds")
print(f"Heap sort: {time_sorting_algorithm(heap_sort, large_array):.4f} seconds")

# 2. Searching Algorithms
print("\n2. Searching Algorithms")
print("-" * 22)

def linear_search(arr: List[int], target: int) -> int:
    """Linear search algorithm."""
    for i, value in enumerate(arr):
        if value == target:
            return i
    return -1

def binary_search(arr: List[int], target: int) -> int:
    """Binary search algorithm."""
    left, right = 0, len(arr) - 1
    
    while left <= right:
        mid = (left + right) // 2
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    
    return -1

def binary_search_recursive(arr: List[int], target: int, left: int = 0, right: int = None) -> int:
    """Recursive binary search algorithm."""
    if right is None:
        right = len(arr) - 1
    
    if left > right:
        return -1
    
    mid = (left + right) // 2
    if arr[mid] == target:
        return mid
    elif arr[mid] < target:
        return binary_search_recursive(arr, target, mid + 1, right)
    else:
        return binary_search_recursive(arr, target, left, mid - 1)

# Test searching algorithms
sorted_array = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19]
target = 7

print(f"Array: {sorted_array}")
print(f"Target: {target}")
print(f"Linear search result: {linear_search(sorted_array, target)}")
print(f"Binary search result: {binary_search(sorted_array, target)}")
print(f"Recursive binary search result: {binary_search_recursive(sorted_array, target)}")

# 3. Graph Algorithms
print("\n3. Graph Algorithms")
print("-" * 18)

class Graph:
    """Graph class for graph algorithms."""
    
    def __init__(self):
        self.graph = defaultdict(list)
    
    def add_edge(self, u: int, v: int):
        """Add an edge to the graph."""
        self.graph[u].append(v)
        self.graph[v].append(u)  # For undirected graph
    
    def bfs(self, start: int) -> List[int]:
        """Breadth-First Search."""
        visited = set()
        queue = deque([start])
        result = []
        
        while queue:
            vertex = queue.popleft()
            if vertex not in visited:
                visited.add(vertex)
                result.append(vertex)
                
                for neighbor in self.graph[vertex]:
                    if neighbor not in visited:
                        queue.append(neighbor)
        
        return result
    
    def dfs(self, start: int, visited: set = None) -> List[int]:
        """Depth-First Search."""
        if visited is None:
            visited = set()
        
        result = []
        if start not in visited:
            visited.add(start)
            result.append(start)
            
            for neighbor in self.graph[start]:
                if neighbor not in visited:
                    result.extend(self.dfs(neighbor, visited))
        
        return result
    
    def shortest_path(self, start: int, end: int) -> List[int]:
        """Find shortest path using BFS."""
        if start == end:
            return [start]
        
        visited = set()
        queue = deque([(start, [start])])
        
        while queue:
            vertex, path = queue.popleft()
            
            if vertex not in visited:
                visited.add(vertex)
                
                for neighbor in self.graph[vertex]:
                    if neighbor == end:
                        return path + [neighbor]
                    
                    if neighbor not in visited:
                        queue.append((neighbor, path + [neighbor]))
        
        return []  # No path found

# Test graph algorithms
graph = Graph()
graph.add_edge(0, 1)
graph.add_edge(0, 2)
graph.add_edge(1, 2)
graph.add_edge(2, 3)
graph.add_edge(3, 4)

print(f"Graph: {dict(graph.graph)}")
print(f"BFS from 0: {graph.bfs(0)}")
print(f"DFS from 0: {graph.dfs(0)}")
print(f"Shortest path from 0 to 4: {graph.shortest_path(0, 4)}")

# 4. Dynamic Programming
print("\n4. Dynamic Programming")
print("-" * 22)

def fibonacci_dp(n: int) -> int:
    """Fibonacci using dynamic programming."""
    if n <= 1:
        return n
    
    dp = [0] * (n + 1)
    dp[1] = 1
    
    for i in range(2, n + 1):
        dp[i] = dp[i - 1] + dp[i - 2]
    
    return dp[n]

def longest_common_subsequence(text1: str, text2: str) -> int:
    """Longest Common Subsequence using DP."""
    m, n = len(text1), len(text2)
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if text1[i - 1] == text2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1] + 1
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
    
    return dp[m][n]

def coin_change(coins: List[int], amount: int) -> int:
    """Coin Change problem using DP."""
    dp = [float('inf')] * (amount + 1)
    dp[0] = 0
    
    for coin in coins:
        for i in range(coin, amount + 1):
            dp[i] = min(dp[i], dp[i - coin] + 1)
    
    return dp[amount] if dp[amount] != float('inf') else -1

# Test dynamic programming
print(f"Fibonacci(10): {fibonacci_dp(10)}")
print(f"LCS of 'ABCDGH' and 'AEDFHR': {longest_common_subsequence('ABCDGH', 'AEDFHR')}")
print(f"Coin change for amount 11 with coins [1, 3, 4]: {coin_change([1, 3, 4], 11)}")

# 5. Greedy Algorithms
print("\n5. Greedy Algorithms")
print("-" * 20)

def fractional_knapsack(weights: List[int], values: List[int], capacity: int) -> float:
    """Fractional Knapsack using greedy approach."""
    items = list(zip(weights, values))
    items.sort(key=lambda x: x[1] / x[0], reverse=True)  # Sort by value/weight ratio
    
    total_value = 0.0
    remaining_capacity = capacity
    
    for weight, value in items:
        if remaining_capacity >= weight:
            total_value += value
            remaining_capacity -= weight
        else:
            fraction = remaining_capacity / weight
            total_value += value * fraction
            break
    
    return total_value

def activity_selection(activities: List[Tuple[int, int]]) -> List[Tuple[int, int]]:
    """Activity Selection problem using greedy approach."""
    activities.sort(key=lambda x: x[1])  # Sort by finish time
    
    selected = [activities[0]]
    last_finish_time = activities[0][1]
    
    for start, finish in activities[1:]:
        if start >= last_finish_time:
            selected.append((start, finish))
            last_finish_time = finish
    
    return selected

# Test greedy algorithms
weights = [10, 20, 30]
values = [60, 100, 120]
capacity = 50
print(f"Fractional knapsack value: {fractional_knapsack(weights, values, capacity)}")

activities = [(1, 3), (2, 5), (0, 6), (5, 7), (8, 9), (5, 9)]
print(f"Selected activities: {activity_selection(activities)}")

# 6. Backtracking
print("\n6. Backtracking")
print("-" * 15)

def n_queens(n: int) -> List[List[int]]:
    """N-Queens problem using backtracking."""
    def is_safe(board: List[int], row: int, col: int) -> bool:
        for i in range(row):
            if board[i] == col or abs(board[i] - col) == abs(i - row):
                return False
        return True
    
    def solve(board: List[int], row: int) -> bool:
        if row == n:
            return True
        
        for col in range(n):
            if is_safe(board, row, col):
                board[row] = col
                if solve(board, row + 1):
                    return True
                board[row] = -1
        
        return False
    
    board = [-1] * n
    if solve(board, 0):
        return board
    return []

def sudoku_solver(grid: List[List[int]]) -> bool:
    """Sudoku solver using backtracking."""
    def is_valid(grid: List[List[int]], row: int, col: int, num: int) -> bool:
        # Check row
        for x in range(9):
            if grid[row][x] == num:
                return False
        
        # Check column
        for x in range(9):
            if grid[x][col] == num:
                return False
        
        # Check 3x3 box
        start_row, start_col = 3 * (row // 3), 3 * (col // 3)
        for i in range(3):
            for j in range(3):
                if grid[start_row + i][start_col + j] == num:
                    return False
        
        return True
    
    def solve(grid: List[List[int]]) -> bool:
        for row in range(9):
            for col in range(9):
                if grid[row][col] == 0:
                    for num in range(1, 10):
                        if is_valid(grid, row, col, num):
                            grid[row][col] = num
                            if solve(grid):
                                return True
                            grid[row][col] = 0
                    return False
        return True
    
    return solve(grid)

# Test backtracking
print(f"4-Queens solution: {n_queens(4)}")

# Sample Sudoku grid (0 represents empty cells)
sudoku_grid = [
    [5, 3, 0, 0, 7, 0, 0, 0, 0],
    [6, 0, 0, 1, 9, 5, 0, 0, 0],
    [0, 9, 8, 0, 0, 0, 0, 6, 0],
    [8, 0, 0, 0, 6, 0, 0, 0, 3],
    [4, 0, 0, 8, 0, 3, 0, 0, 1],
    [7, 0, 0, 0, 2, 0, 0, 0, 6],
    [0, 6, 0, 0, 0, 0, 2, 8, 0],
    [0, 0, 0, 4, 1, 9, 0, 0, 5],
    [0, 0, 0, 0, 8, 0, 0, 7, 9]
]

if sudoku_solver(sudoku_grid):
    print("Sudoku solved successfully!")
    for row in sudoku_grid:
        print(row)
else:
    print("No solution found for Sudoku")

# 7. Tree Algorithms
print("\n7. Tree Algorithms")
print("-" * 18)

class TreeNode:
    """Tree node class."""
    
    def __init__(self, val: int):
        self.val = val
        self.left = None
        self.right = None

def insert_bst(root: TreeNode, val: int) -> TreeNode:
    """Insert a value into BST."""
    if not root:
        return TreeNode(val)
    
    if val < root.val:
        root.left = insert_bst(root.left, val)
    else:
        root.right = insert_bst(root.right, val)
    
    return root

def search_bst(root: TreeNode, val: int) -> bool:
    """Search a value in BST."""
    if not root:
        return False
    
    if root.val == val:
        return True
    elif val < root.val:
        return search_bst(root.left, val)
    else:
        return search_bst(root.right, val)

def inorder_traversal(root: TreeNode) -> List[int]:
    """Inorder traversal of BST."""
    result = []
    
    def traverse(node):
        if node:
            traverse(node.left)
            result.append(node.val)
            traverse(node.right)
    
    traverse(root)
    return result

def preorder_traversal(root: TreeNode) -> List[int]:
    """Preorder traversal of BST."""
    result = []
    
    def traverse(node):
        if node:
            result.append(node.val)
            traverse(node.left)
            traverse(node.right)
    
    traverse(root)
    return result

def postorder_traversal(root: TreeNode) -> List[int]:
    """Postorder traversal of BST."""
    result = []
    
    def traverse(node):
        if node:
            traverse(node.left)
            traverse(node.right)
            result.append(node.val)
    
    traverse(root)
    return result

# Test tree algorithms
root = None
values = [5, 3, 7, 1, 9, 4, 6]

for val in values:
    root = insert_bst(root, val)

print(f"BST values: {values}")
print(f"Inorder traversal: {inorder_traversal(root)}")
print(f"Preorder traversal: {preorder_traversal(root)}")
print(f"Postorder traversal: {postorder_traversal(root)}")
print(f"Search 7: {search_bst(root, 7)}")
print(f"Search 10: {search_bst(root, 10)}")

# 8. String Algorithms
print("\n8. String Algorithms")
print("-" * 20)

def kmp_search(text: str, pattern: str) -> List[int]:
    """KMP string search algorithm."""
    def compute_lps(pattern: str) -> List[int]:
        lps = [0] * len(pattern)
        length = 0
        i = 1
        
        while i < len(pattern):
            if pattern[i] == pattern[length]:
                length += 1
                lps[i] = length
                i += 1
            else:
                if length != 0:
                    length = lps[length - 1]
                else:
                    lps[i] = 0
                    i += 1
        
        return lps
    
    lps = compute_lps(pattern)
    i = j = 0
    result = []
    
    while i < len(text):
        if pattern[j] == text[i]:
            i += 1
            j += 1
        
        if j == len(pattern):
            result.append(i - j)
            j = lps[j - 1]
        elif i < len(text) and pattern[j] != text[i]:
            if j != 0:
                j = lps[j - 1]
            else:
                i += 1
    
    return result

def rabin_karp_search(text: str, pattern: str) -> List[int]:
    """Rabin-Karp string search algorithm."""
    def hash_string(s: str) -> int:
        hash_value = 0
        for char in s:
            hash_value = (hash_value * 256 + ord(char)) % 101
        return hash_value
    
    pattern_hash = hash_string(pattern)
    result = []
    
    for i in range(len(text) - len(pattern) + 1):
        text_hash = hash_string(text[i:i + len(pattern)])
        if text_hash == pattern_hash and text[i:i + len(pattern)] == pattern:
            result.append(i)
    
    return result

# Test string algorithms
text = "ABABDABACDABABCABAB"
pattern = "ABABCABAB"

print(f"Text: {text}")
print(f"Pattern: {pattern}")
print(f"KMP search result: {kmp_search(text, pattern)}")
print(f"Rabin-Karp search result: {rabin_karp_search(text, pattern)}")

# 9. Mathematical Algorithms
print("\n9. Mathematical Algorithms")
print("-" * 28)

def gcd(a: int, b: int) -> int:
    """Greatest Common Divisor using Euclidean algorithm."""
    while b:
        a, b = b, a % b
    return a

def lcm(a: int, b: int) -> int:
    """Least Common Multiple."""
    return abs(a * b) // gcd(a, b)

def is_prime(n: int) -> bool:
    """Check if a number is prime."""
    if n < 2:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False
    
    for i in range(3, int(n ** 0.5) + 1, 2):
        if n % i == 0:
            return False
    
    return True

def sieve_of_eratosthenes(n: int) -> List[int]:
    """Sieve of Eratosthenes to find all primes up to n."""
    if n < 2:
        return []
    
    is_prime = [True] * (n + 1)
    is_prime[0] = is_prime[1] = False
    
    for i in range(2, int(n ** 0.5) + 1):
        if is_prime[i]:
            for j in range(i * i, n + 1, i):
                is_prime[j] = False
    
    return [i for i in range(2, n + 1) if is_prime[i]]

def power_mod(base: int, exponent: int, modulus: int) -> int:
    """Modular exponentiation."""
    result = 1
    base = base % modulus
    
    while exponent > 0:
        if exponent % 2 == 1:
            result = (result * base) % modulus
        exponent = exponent >> 1
        base = (base * base) % modulus
    
    return result

# Test mathematical algorithms
print(f"GCD of 48 and 18: {gcd(48, 18)}")
print(f"LCM of 12 and 18: {lcm(12, 18)}")
print(f"Is 17 prime? {is_prime(17)}")
print(f"Is 25 prime? {is_prime(25)}")
print(f"Primes up to 30: {sieve_of_eratosthenes(30)}")
print(f"2^10 mod 7: {power_mod(2, 10, 7)}")

# 10. Algorithm Complexity Analysis
print("\n10. Algorithm Complexity Analysis")
print("-" * 35)

def analyze_time_complexity():
    """Analyze time complexity of different algorithms."""
    
    # O(1) - Constant time
    def constant_time(n):
        return n * 2
    
    # O(log n) - Logarithmic time
    def logarithmic_time(n):
        result = 0
        while n > 1:
            n = n // 2
            result += 1
        return result
    
    # O(n) - Linear time
    def linear_time(n):
        total = 0
        for i in range(n):
            total += i
        return total
    
    # O(n log n) - Linearithmic time
    def linearithmic_time(n):
        total = 0
        for i in range(n):
            j = n
            while j > 1:
                j = j // 2
                total += 1
        return total
    
    # O(n²) - Quadratic time
    def quadratic_time(n):
        total = 0
        for i in range(n):
            for j in range(n):
                total += i * j
        return total
    
    # Test with different input sizes
    sizes = [10, 100, 1000]
    
    for size in sizes:
        print(f"\nInput size: {size}")
        
        start_time = time.time()
        constant_time(size)
        print(f"O(1): {time.time() - start_time:.6f} seconds")
        
        start_time = time.time()
        logarithmic_time(size)
        print(f"O(log n): {time.time() - start_time:.6f} seconds")
        
        start_time = time.time()
        linear_time(size)
        print(f"O(n): {time.time() - start_time:.6f} seconds")
        
        start_time = time.time()
        linearithmic_time(size)
        print(f"O(n log n): {time.time() - start_time:.6f} seconds")
        
        start_time = time.time()
        quadratic_time(size)
        print(f"O(n²): {time.time() - start_time:.6f} seconds")

# Run complexity analysis
analyze_time_complexity()

print("\nAlgorithms examples completed!")