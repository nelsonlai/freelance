"""
Problem: Check If It Is a Good Array
Difficulty: Hard
Tags: array, math

Approach: Use Bézout's identity - array is good if GCD of all numbers is 1
Time Complexity: O(n * log(max(nums))) for GCD calculations
Space Complexity: O(1)
"""

import math

class Solution:
    def isGoodArray(self, nums: List[int]) -> bool:
        gcd = nums[0]
        for num in nums[1:]:
            gcd = math.gcd(gcd, num)
            if gcd == 1:
                return True
        return gcd == 1