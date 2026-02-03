"""
Problem: Split Array Largest Sum
Difficulty: Hard
Tags: array, dp, greedy, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def splitArray(self, nums: List[int], k: int) -> int:
        def canSplit(max_sum):
            splits = 1
            current_sum = 0
            for num in nums:
                if current_sum + num > max_sum:
                    splits += 1
                    current_sum = num
                else:
                    current_sum += num
            return splits <= k
        
        left, right = max(nums), sum(nums)
        
        while left < right:
            mid = (left + right) // 2
            if canSplit(mid):
                right = mid
            else:
                left = mid + 1
        
        return left