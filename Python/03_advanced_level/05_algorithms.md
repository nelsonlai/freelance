# 5. Algorithms and Problem Solving - Efficient Solutions

Algorithms are the foundation of efficient programming. This lesson covers essential algorithms including sorting, searching, recursion, dynamic programming, and graph algorithms used in professional software development.

## Sorting Algorithms

### Comparison-Based Sorting

```python
import random
import time
from typing import List

def bubble_sort(arr: List[int]) -> List[int]:
    """Bubble sort algorithm - O(n²) time complexity."""
    arr = arr.copy()
    n = len(arr)
    
    for i in range(n):
        swapped = False
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                swapped = True
        
        if not swapped:
            break
    
    return arr

def selection_sort(arr: List[int]) -> List[int]:
    """Selection sort algorithm - O(n²) time complexity."""
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
    """Insertion sort algorithm - O(n²) time complexity."""
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
    """Merge sort algorithm - O(n log n) time complexity."""
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
    """Quick sort algorithm - O(n log n) average, O(n²) worst case."""
    if len(arr) <= 1:
        return arr
    
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    
    return quick_sort(left) + middle + quick_sort(right)

# Sorting algorithm comparison
def compare_sorting_algorithms():
    """Compare different sorting algorithms."""
    print("=== Sorting Algorithm Comparison ===")
    
    # Test with different array sizes
    sizes = [100, 1000, 5000]
    algorithms = {
        'Bubble Sort': bubble_sort,
        'Selection Sort': selection_sort,
        'Insertion Sort': insertion_sort,
        'Merge Sort': merge_sort,
        'Quick Sort': quick_sort
    }
    
    for size in sizes:
        print(f"\nArray size: {size}")
        test_array = [random.randint(1, 1000) for _ in range(size)]
        
        for name, algorithm in algorithms.items():
            start_time = time.time()
            sorted_array = algorithm(test_array)
            end_time = time.time()
            
            # Verify sorting is correct
            is_sorted = all(sorted_array[i] <= sorted_array[i + 1] for i in range(len(sorted_array) - 1))
            
            print(f"{name}: {end_time - start_time:.4f}s {'✓' if is_sorted else '✗'}")

# Run comparison
compare_sorting_algorithms()
```

### Non-Comparison Sorting

```python
def counting_sort(arr: List[int], max_val: int) -> List[int]:
    """Counting sort - O(n + k) time complexity."""
    count = [0] * (max_val + 1)
    
    # Count occurrences
    for num in arr:
        count[num] += 1
    
    # Build output array
    output = []
    for i in range(max_val + 1):
        output.extend([i] * count[i])
    
    return output

def radix_sort(arr: List[int]) -> List[int]:
    """Radix sort - O(d(n + k)) time complexity."""
    if not arr:
        return arr
    
    # Find maximum number to determine number of digits
    max_num = max(arr)
    exp = 1
    
    while max_num // exp > 0:
        arr = counting_sort_by_digit(arr, exp)
        exp *= 10
    
    return arr

def counting_sort_by_digit(arr: List[int], exp: int) -> List[int]:
    """Helper function for radix sort."""
    n = len(arr)
    output = [0] * n
    count = [0] * 10
    
    # Store count of occurrences
    for i in range(n):
        index = (arr[i] // exp) % 10
        count[index] += 1
    
    # Change count[i] so that count[i] contains actual position
    for i in range(1, 10):
        count[i] += count[i - 1]
    
    # Build output array
    for i in range(n - 1, -1, -1):
        index = (arr[i] // exp) % 10
        output[count[index] - 1] = arr[i]
        count[index] -= 1
    
    return output

# Test non-comparison sorts
print("\n=== Non-Comparison Sorting ===")
test_array = [170, 45, 75, 90, 2, 802, 24, 66]
print(f"Original: {test_array}")

# Counting sort
max_val = max(test_array)
counting_result = counting_sort(test_array, max_val)
print(f"Counting sort: {counting_result}")

# Radix sort
radix_result = radix_sort(test_array)
print(f"Radix sort: {radix_result}")
```

## Searching Algorithms

### Linear and Binary Search

```python
def linear_search(arr: List[int], target: int) -> int:
    """Linear search - O(n) time complexity."""
    for i, num in enumerate(arr):
        if num == target:
            return i
    return -1

def binary_search(arr: List[int], target: int) -> int:
    """Binary search - O(log n) time complexity."""
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
    """Recursive binary search."""
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

# Search algorithm comparison
def compare_search_algorithms():
    """Compare linear and binary search."""
    print("\n=== Search Algorithm Comparison ===")
    
    # Create sorted array
    sorted_array = sorted([random.randint(1, 1000) for _ in range(1000)])
    targets = [sorted_array[0], sorted_array[500], sorted_array[-1], 9999]  # First, middle, last, not found
    
    for target in targets:
        print(f"\nSearching for {target}:")
        
        # Linear search
        start_time = time.time()
        linear_result = linear_search(sorted_array, target)
        linear_time = time.time() - start_time
        
        # Binary search
        start_time = time.time()
        binary_result = binary_search(sorted_array, target)
        binary_time = time.time() - start_time
        
        print(f"Linear search: {linear_result} ({linear_time:.6f}s)")
        print(f"Binary search: {binary_result} ({binary_time:.6f}s)")

compare_search_algorithms()
```

### Advanced Searching

```python
def find_first_occurrence(arr: List[int], target: int) -> int:
    """Find first occurrence of target in sorted array."""
    left, right = 0, len(arr) - 1
    result = -1
    
    while left <= right:
        mid = (left + right) // 2
        
        if arr[mid] == target:
            result = mid
            right = mid - 1  # Continue searching left
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    
    return result

def find_last_occurrence(arr: List[int], target: int) -> int:
    """Find last occurrence of target in sorted array."""
    left, right = 0, len(arr) - 1
    result = -1
    
    while left <= right:
        mid = (left + right) // 2
        
        if arr[mid] == target:
            result = mid
            left = mid + 1  # Continue searching right
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    
    return result

def count_occurrences(arr: List[int], target: int) -> int:
    """Count occurrences of target in sorted array."""
    first = find_first_occurrence(arr, target)
    if first == -1:
        return 0
    
    last = find_last_occurrence(arr, target)
    return last - first + 1

# Test advanced searching
print("\n=== Advanced Searching ===")
test_array = [1, 2, 2, 2, 3, 3, 4, 5, 5, 5, 5, 6]
target = 2

print(f"Array: {test_array}")
print(f"Target: {target}")
print(f"First occurrence: {find_first_occurrence(test_array, target)}")
print(f"Last occurrence: {find_last_occurrence(test_array, target)}")
print(f"Count: {count_occurrences(test_array, target)}")
```

## Recursion

### Basic Recursion

```python
def factorial(n: int) -> int:
    """Calculate factorial using recursion."""
    if n <= 1:
        return 1
    return n * factorial(n - 1)

def fibonacci(n: int) -> int:
    """Calculate Fibonacci number using recursion."""
    if n <= 1:
        return n
    return fibonacci(n - 1) + fibonacci(n - 2)

def fibonacci_memoized(n: int, memo: dict = None) -> int:
    """Fibonacci with memoization to avoid redundant calculations."""
    if memo is None:
        memo = {}
    
    if n in memo:
        return memo[n]
    
    if n <= 1:
        return n
    
    memo[n] = fibonacci_memoized(n - 1, memo) + fibonacci_memoized(n - 2, memo)
    return memo[n]

def tower_of_hanoi(n: int, source: str, destination: str, auxiliary: str):
    """Solve Tower of Hanoi puzzle."""
    if n == 1:
        print(f"Move disk 1 from {source} to {destination}")
        return
    
    tower_of_hanoi(n - 1, source, auxiliary, destination)
    print(f"Move disk {n} from {source} to {destination}")
    tower_of_hanoi(n - 1, auxiliary, destination, source)

# Test recursion
print("\n=== Recursion Examples ===")
print(f"Factorial of 5: {factorial(5)}")
print(f"Fibonacci of 10: {fibonacci(10)}")
print(f"Fibonacci of 10 (memoized): {fibonacci_memoized(10)}")

print("\nTower of Hanoi (3 disks):")
tower_of_hanoi(3, 'A', 'C', 'B')
```

### Advanced Recursion

```python
def permute(arr: List[int]) -> List[List[int]]:
    """Generate all permutations of an array."""
    if len(arr) <= 1:
        return [arr]
    
    result = []
    for i in range(len(arr)):
        rest = arr[:i] + arr[i+1:]
        for p in permute(rest):
            result.append([arr[i]] + p)
    
    return result

def combinations(arr: List[int], k: int) -> List[List[int]]:
    """Generate all combinations of k elements from array."""
    if k == 0:
        return [[]]
    if not arr:
        return []
    
    result = []
    for i in range(len(arr)):
        for combo in combinations(arr[i+1:], k-1):
            result.append([arr[i]] + combo)
    
    return result

def subset_sum(arr: List[int], target: int) -> bool:
    """Check if any subset sums to target."""
    if target == 0:
        return True
    if not arr:
        return False
    
    # Include current element or exclude it
    return (subset_sum(arr[1:], target - arr[0]) or 
            subset_sum(arr[1:], target))

# Test advanced recursion
print("\n=== Advanced Recursion ===")
test_array = [1, 2, 3]

print(f"Permutations of {test_array}:")
for perm in permute(test_array):
    print(perm)

print(f"\nCombinations of {test_array} (2 elements):")
for combo in combinations(test_array, 2):
    print(combo)

print(f"\nSubset sum of {test_array} = 5: {subset_sum(test_array, 5)}")
print(f"Subset sum of {test_array} = 7: {subset_sum(test_array, 7)}")
```

## Dynamic Programming

### Basic Dynamic Programming

```python
def fibonacci_dp(n: int) -> int:
    """Fibonacci using dynamic programming."""
    if n <= 1:
        return n
    
    dp = [0] * (n + 1)
    dp[0] = 0
    dp[1] = 1
    
    for i in range(2, n + 1):
        dp[i] = dp[i - 1] + dp[i - 2]
    
    return dp[n]

def longest_common_subsequence(text1: str, text2: str) -> int:
    """Find length of longest common subsequence."""
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
    """Minimum number of coins to make amount."""
    dp = [float('inf')] * (amount + 1)
    dp[0] = 0
    
    for coin in coins:
        for i in range(coin, amount + 1):
            dp[i] = min(dp[i], dp[i - coin] + 1)
    
    return dp[amount] if dp[amount] != float('inf') else -1

def knapsack(weights: List[int], values: List[int], capacity: int) -> int:
    """0/1 Knapsack problem."""
    n = len(weights)
    dp = [[0] * (capacity + 1) for _ in range(n + 1)]
    
    for i in range(1, n + 1):
        for w in range(capacity + 1):
            if weights[i - 1] <= w:
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], 
                              dp[i - 1][w])
            else:
                dp[i][w] = dp[i - 1][w]
    
    return dp[n][capacity]

# Test dynamic programming
print("\n=== Dynamic Programming ===")
print(f"Fibonacci of 10 (DP): {fibonacci_dp(10)}")

text1, text2 = "ABCDGH", "AEDFHR"
print(f"LCS of '{text1}' and '{text2}': {longest_common_subsequence(text1, text2)}")

coins, amount = [1, 3, 4], 6
print(f"Coin change for {amount} with coins {coins}: {coin_change(coins, amount)}")

weights, values, capacity = [10, 20, 30], [60, 100, 120], 50
print(f"Knapsack (weights: {weights}, values: {values}, capacity: {capacity}): {knapsack(weights, values, capacity)}")
```

## Graph Algorithms

### Graph Representation and Basic Algorithms

```python
from collections import defaultdict, deque
from typing import Dict, List, Set

class Graph:
    """Graph representation using adjacency list."""
    
    def __init__(self):
        self.graph = defaultdict(list)
    
    def add_edge(self, u: int, v: int):
        """Add an edge to the graph."""
        self.graph[u].append(v)
    
    def add_undirected_edge(self, u: int, v: int):
        """Add an undirected edge."""
        self.add_edge(u, v)
        self.add_edge(v, u)
    
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
    
    def dfs(self, start: int, visited: Set[int] = None) -> List[int]:
        """Depth-First Search."""
        if visited is None:
            visited = set()
        
        visited.add(start)
        result = [start]
        
        for neighbor in self.graph[start]:
            if neighbor not in visited:
                result.extend(self.dfs(neighbor, visited))
        
        return result
    
    def has_cycle(self) -> bool:
        """Check if graph has cycle using DFS."""
        visited = set()
        rec_stack = set()
        
        def dfs_cycle(node):
            visited.add(node)
            rec_stack.add(node)
            
            for neighbor in self.graph[node]:
                if neighbor not in visited:
                    if dfs_cycle(neighbor):
                        return True
                elif neighbor in rec_stack:
                    return True
            
            rec_stack.remove(node)
            return False
        
        for node in self.graph:
            if node not in visited:
                if dfs_cycle(node):
                    return True
        
        return False

def topological_sort(graph: Graph) -> List[int]:
    """Topological sort using DFS."""
    visited = set()
    stack = []
    
    def dfs(node):
        visited.add(node)
        for neighbor in graph.graph[node]:
            if neighbor not in visited:
                dfs(neighbor)
        stack.append(node)
    
    for node in graph.graph:
        if node not in visited:
            dfs(node)
    
    return stack[::-1]

def dijkstra(graph: Graph, start: int) -> Dict[int, int]:
    """Dijkstra's shortest path algorithm."""
    import heapq
    
    distances = {node: float('inf') for node in graph.graph}
    distances[start] = 0
    heap = [(0, start)]
    
    while heap:
        current_dist, current = heapq.heappop(heap)
        
        if current_dist > distances[current]:
            continue
        
        for neighbor in graph.graph[current]:
            distance = current_dist + 1  # Assuming unit weights
            
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                heapq.heappush(heap, (distance, neighbor))
    
    return distances

# Test graph algorithms
print("\n=== Graph Algorithms ===")
g = Graph()
g.add_undirected_edge(0, 1)
g.add_undirected_edge(0, 2)
g.add_undirected_edge(1, 2)
g.add_undirected_edge(2, 3)
g.add_undirected_edge(3, 4)

print("Graph structure:")
for node, neighbors in g.graph.items():
    print(f"{node}: {neighbors}")

print(f"\nBFS from 0: {g.bfs(0)}")
print(f"DFS from 0: {g.dfs(0)}")
print(f"Has cycle: {g.has_cycle()}")

# Directed graph for topological sort
dg = Graph()
dg.add_edge(5, 2)
dg.add_edge(5, 0)
dg.add_edge(4, 0)
dg.add_edge(4, 1)
dg.add_edge(2, 3)
dg.add_edge(3, 1)

print(f"\nTopological sort: {topological_sort(dg)}")
print(f"Dijkstra from 0: {dijkstra(g, 0)}")
```

## Performance Analysis

```python
def analyze_algorithm_performance():
    """Analyze performance of different algorithms."""
    print("\n=== Algorithm Performance Analysis ===")
    
    # Test different array sizes
    sizes = [100, 1000, 5000]
    
    for size in sizes:
        print(f"\nArray size: {size}")
        
        # Generate test data
        arr = [random.randint(1, 1000) for _ in range(size)]
        sorted_arr = sorted(arr)
        
        # Test sorting algorithms
        algorithms = {
            'Bubble Sort': bubble_sort,
            'Insertion Sort': insertion_sort,
            'Merge Sort': merge_sort,
            'Quick Sort': quick_sort
        }
        
        for name, algorithm in algorithms.items():
            start_time = time.time()
            algorithm(arr)
            end_time = time.time()
            print(f"{name}: {(end_time - start_time) * 1000:.2f}ms")
        
        # Test search algorithms
        target = sorted_arr[size // 2]
        
        start_time = time.time()
        linear_search(sorted_arr, target)
        linear_time = (time.time() - start_time) * 1000
        
        start_time = time.time()
        binary_search(sorted_arr, target)
        binary_time = (time.time() - start_time) * 1000
        
        print(f"Linear Search: {linear_time:.4f}ms")
        print(f"Binary Search: {binary_time:.4f}ms")

analyze_algorithm_performance()
```

## Key Takeaways

1. **Sorting algorithms** have different time complexities and use cases
2. **Search algorithms** trade space for time efficiency
3. **Recursion** provides elegant solutions but can be inefficient without optimization
4. **Dynamic programming** optimizes recursive solutions by avoiding redundant calculations
5. **Graph algorithms** solve complex connectivity and pathfinding problems
6. **Algorithm analysis** helps choose the right approach for each problem
7. **Space-time tradeoffs** are fundamental in algorithm design
8. **Problem decomposition** is key to solving complex algorithms

## Next Steps

In the next lesson, we'll explore Web Development and APIs - building web applications, working with REST APIs, and using frameworks like Flask and FastAPI.
