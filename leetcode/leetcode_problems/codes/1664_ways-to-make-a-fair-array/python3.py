"""
Problem: Ways to Make a Fair Array
Difficulty: Medium
Tags: array, prefix sum

Approach: Calculate prefix sums for odd/even indices, check if removing element makes array fair
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def waysToMakeFair(self, nums: List[int]) -> int:
        odd_sum = sum(nums[i] for i in range(1, len(nums), 2))
        even_sum = sum(nums[i] for i in range(0, len(nums), 2))
        
        result = 0
        prev_odd = 0
        prev_even = 0
        
        for i in range(len(nums)):
            if i % 2 == 0:
                even_after = prev_even + (odd_sum - prev_odd)
                odd_after = prev_odd + (even_sum - prev_even - nums[i])
            else:
                even_after = prev_even + (odd_sum - prev_odd - nums[i])
                odd_after = prev_odd + (even_sum - prev_even)
            
            if even_after == odd_after:
                result += 1
            
            if i % 2 == 0:
                prev_even += nums[i]
            else:
                prev_odd += nums[i]
        
        return result