"""
Problem: Sum of Even Numbers After Queries
Difficulty: Medium
Tags: array

Approach: Track sum of even numbers, update incrementally after each query
Time Complexity: O(n + m) where n is nums length, m is queries length
Space Complexity: O(1) excluding output
"""

class Solution:
    def sumEvenAfterQueries(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        even_sum = sum(x for x in nums if x % 2 == 0)
        result = []
        
        for val, idx in queries:
            old_val = nums[idx]
            nums[idx] += val
            
            if old_val % 2 == 0:
                even_sum -= old_val
            if nums[idx] % 2 == 0:
                even_sum += nums[idx]
            
            result.append(even_sum)
        
        return result