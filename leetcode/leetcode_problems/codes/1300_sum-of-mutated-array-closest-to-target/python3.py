"""
Problem: Sum of Mutated Array Closest to Target
Difficulty: Medium
Tags: array, sort, search

Approach: Binary search on value, calculate sum for each value
Time Complexity: O(n * log(max(arr)))
Space Complexity: O(1)
"""

class Solution:
    def findBestValue(self, arr: List[int], target: int) -> int:
        def sum_with_value(value):
            return sum(min(num, value) for num in arr)
        
        left, right = 0, max(arr)
        best_value = 0
        min_diff = float('inf')
        
        while left <= right:
            mid = (left + right) // 2
            total = sum_with_value(mid)
            diff = abs(total - target)
            
            if diff < min_diff or (diff == min_diff and mid < best_value):
                min_diff = diff
                best_value = mid
            
            if total < target:
                left = mid + 1
            else:
                right = mid - 1
        
        return best_value