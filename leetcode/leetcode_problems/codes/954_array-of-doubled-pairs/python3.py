"""
Problem: Array of Doubled Pairs
Difficulty: Medium
Tags: array, greedy, hash, sort

Approach: Sort and use greedy matching - for each number, try to match with its double
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for counter
"""

from collections import Counter

class Solution:
    def canReorderDoubled(self, arr: List[int]) -> bool:
        count = Counter(arr)
        
        # Process negative numbers first (in descending order), then positive (in ascending order)
        for num in sorted(count.keys(), key=abs):
            if count[num] == 0:
                continue
            if count[2 * num] < count[num]:
                return False
            count[2 * num] -= count[num]
        
        return True