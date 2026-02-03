"""
Problem: Find Two Non-overlapping Sub-arrays Each With Target Sum
Difficulty: Medium
Tags: array, dp, hash, search

Approach: Use prefix sum to find subarrays, track best length before each position
Time Complexity: O(n) where n is length of arr
Space Complexity: O(n) for prefix and best array
"""

class Solution:
    def minSumOfLengths(self, arr: List[int], target: int) -> int:
        n = len(arr)
        prefix = {0: -1}
        best = [float('inf')] * n
        best_so_far = float('inf')
        result = float('inf')
        current_sum = 0
        
        for i in range(n):
            current_sum += arr[i]
            if current_sum - target in prefix:
                start = prefix[current_sum - target]
                length = i - start
                if start >= 0:
                    result = min(result, best[start] + length)
                best_so_far = min(best_so_far, length)
            
            best[i] = best_so_far
            prefix[current_sum] = i
        
        return result if result != float('inf') else -1