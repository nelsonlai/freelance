"""
Problem: Online Majority Element In Subarray
Difficulty: Hard
Tags: array, tree, search

Approach: Boyer-Moore voting algorithm with random sampling for verification
Time Complexity: O(n) per query in worst case
Space Complexity: O(n) for storing array
"""

class MajorityChecker:

    def __init__(self, arr: List[int]):
        self.arr = arr
        self.index_map = {}
        for i, num in enumerate(arr):
            if num not in self.index_map:
                self.index_map[num] = []
            self.index_map[num].append(i)

    def query(self, left: int, right: int, threshold: int) -> int:
        # Boyer-Moore voting to find candidate
        candidate = None
        count = 0
        
        for i in range(left, right + 1):
            if count == 0:
                candidate = self.arr[i]
                count = 1
            elif self.arr[i] == candidate:
                count += 1
            else:
                count -= 1
        
        # Verify candidate
        if candidate is not None:
            indices = self.index_map.get(candidate, [])
            # Count occurrences in range using binary search
            import bisect
            left_idx = bisect.bisect_left(indices, left)
            right_idx = bisect.bisect_right(indices, right)
            actual_count = right_idx - left_idx
            
            if actual_count >= threshold:
                return candidate
        
        return -1