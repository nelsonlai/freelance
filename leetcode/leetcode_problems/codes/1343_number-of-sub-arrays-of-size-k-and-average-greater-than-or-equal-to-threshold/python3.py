"""
Problem: Number of Sub-arrays of Size K and Average Greater than or Equal to Threshold
Difficulty: Medium
Tags: array

Approach: Sliding window - maintain sum of window of size k
Time Complexity: O(n) where n is length of arr
Space Complexity: O(1)
"""

class Solution:
    def numOfSubarrays(self, arr: List[int], k: int, threshold: int) -> int:
        window_sum = sum(arr[:k])
        count = 1 if window_sum >= threshold * k else 0
        
        for i in range(k, len(arr)):
            window_sum = window_sum - arr[i - k] + arr[i]
            if window_sum >= threshold * k:
                count += 1
        
        return count