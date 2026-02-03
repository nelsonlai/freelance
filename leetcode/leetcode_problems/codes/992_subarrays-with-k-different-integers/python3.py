"""
Problem: Subarrays with K Different Integers
Difficulty: Hard
Tags: array, hash

Approach: Sliding window - count subarrays with at most K distinct, subtract at most K-1
Time Complexity: O(n)
Space Complexity: O(k) for hash map
"""

from collections import defaultdict

class Solution:
    def subarraysWithKDistinct(self, nums: List[int], k: int) -> int:
        def atMostK(k_val):
            count = defaultdict(int)
            left = 0
            result = 0
            
            for right in range(len(nums)):
                if count[nums[right]] == 0:
                    k_val -= 1
                count[nums[right]] += 1
                
                while k_val < 0:
                    count[nums[left]] -= 1
                    if count[nums[left]] == 0:
                        k_val += 1
                    left += 1
                
                result += right - left + 1
            
            return result
        
        return atMostK(k) - atMostK(k - 1)