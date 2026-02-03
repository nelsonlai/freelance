"""
Problem: Max Consecutive Ones II
Difficulty: Medium
Tags: array, dp

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def findMaxConsecutiveOnes(self, nums: List[int]) -> int:
        max_count = 0
        count = 0
        prev_count = 0
        
        for num in nums:
            if num == 1:
                count += 1
            else:
                prev_count = count
                count = 0
            max_count = max(max_count, prev_count + count + 1)
        
        return min(max_count, len(nums))