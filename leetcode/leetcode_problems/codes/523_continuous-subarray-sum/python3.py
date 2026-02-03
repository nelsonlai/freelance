"""
Problem: Continuous Subarray Sum
Difficulty: Medium
Tags: array, math, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        remainder_map = {0: -1}
        prefix_sum = 0
        
        for i, num in enumerate(nums):
            prefix_sum += num
            remainder = prefix_sum % k
            
            if remainder in remainder_map:
                if i - remainder_map[remainder] >= 2:
                    return True
            else:
                remainder_map[remainder] = i
        
        return False