"""
Problem: K Radius Subarray Averages
Difficulty: Medium
Tags: array, sliding window, prefix sum

Approach: Use sliding window to calculate averages
Time Complexity: O(n) where n is array length
Space Complexity: O(n)
"""

class Solution:
    def getAverages(self, nums: List[int], k: int) -> List[int]:
        n = len(nums)
        result = [-1] * n
        window_size = 2 * k + 1
        
        if window_size > n:
            return result
        
        window_sum = sum(nums[:window_size])
        result[k] = window_sum // window_size
        
        for i in range(k + 1, n - k):
            window_sum = window_sum - nums[i - k - 1] + nums[i + k]
            result[i] = window_sum // window_size
        
        return result