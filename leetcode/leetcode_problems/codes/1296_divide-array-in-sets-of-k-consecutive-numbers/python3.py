"""
Problem: Divide Array in Sets of K Consecutive Numbers
Difficulty: Medium
Tags: array, greedy, hash, sort

Approach: Count frequencies, greedily form groups starting from smallest
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for frequency map
"""

from collections import Counter

class Solution:
    def isPossibleDivide(self, nums: List[int], k: int) -> bool:
        if len(nums) % k != 0:
            return False
        
        count = Counter(nums)
        sorted_nums = sorted(count.keys())
        
        for num in sorted_nums:
            if count[num] > 0:
                freq = count[num]
                for i in range(k):
                    if count[num + i] < freq:
                        return False
                    count[num + i] -= freq
        
        return True