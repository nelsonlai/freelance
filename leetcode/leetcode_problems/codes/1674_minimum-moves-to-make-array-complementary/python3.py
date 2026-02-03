"""
Problem: Minimum Moves to Make Array Complementary
Difficulty: Medium
Tags: array, hash, difference array

Approach: Use difference array to track moves needed for each target sum
Time Complexity: O(n + limit) where n is length
Space Complexity: O(limit)
"""

class Solution:
    def minMoves(self, nums: List[int], limit: int) -> int:
        n = len(nums)
        diff = [0] * (2 * limit + 2)
        
        for i in range(n // 2):
            a, b = nums[i], nums[n - 1 - i]
            min_sum = min(a, b) + 1
            max_sum = max(a, b) + limit
            target = a + b
            
            diff[min_sum] += 1
            diff[target] -= 1
            diff[target + 1] += 1
            diff[max_sum + 1] -= 1
        
        result = n
        current = 0
        
        for target in range(2, 2 * limit + 1):
            current += diff[target]
            result = min(result, current)
        
        return result