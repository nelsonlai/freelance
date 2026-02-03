"""
Problem: Count Largest Group
Difficulty: Easy
Tags: math, hash

Approach: Use hash map for O(1) lookups
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(n) for hash map
"""

from collections import defaultdict

class Solution:
    def countLargestGroup(self, n: int) -> int:
        def digit_sum(num):
            total = 0
            while num:
                total += num % 10
                num //= 10
            return total
        
        groups = defaultdict(int)
        for i in range(1, n + 1):
            groups[digit_sum(i)] += 1
        
        max_size = max(groups.values())
        return sum(1 for size in groups.values() if size == max_size)