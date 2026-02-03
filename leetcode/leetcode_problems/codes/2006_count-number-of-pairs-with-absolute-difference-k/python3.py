"""
Problem: Count Number of Pairs With Absolute Difference K
Difficulty: Easy
Tags: array, hash

Approach: Use hash map to count occurrences, check for nums[i] ± k
Time Complexity: O(n) where n is length
Space Complexity: O(n) for hash map
"""

from collections import Counter

class Solution:
    def countKDifference(self, nums: List[int], k: int) -> int:
        count = Counter(nums)
        result = 0
        
        for num in count:
            if num + k in count:
                result += count[num] * count[num + k]
        
        return result