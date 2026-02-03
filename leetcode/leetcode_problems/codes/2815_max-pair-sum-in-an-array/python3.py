"""
Problem: Max Pair Sum in an Array
Difficulty: Easy
Tags: array, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def maxSum(self, nums: List[int]) -> int:
        def max_digit(num):
            max_d = 0
            while num:
                max_d = max(max_d, num % 10)
                num //= 10
            return max_d
        
        max_digit_to_nums = {}
        result = -1
        
        for num in nums:
            md = max_digit(num)
            if md in max_digit_to_nums:
                result = max(result, max_digit_to_nums[md] + num)
                max_digit_to_nums[md] = max(max_digit_to_nums[md], num)
            else:
                max_digit_to_nums[md] = num
        
        return result