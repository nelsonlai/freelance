"""
Problem: Brick Wall
Difficulty: Medium
Tags: array, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import defaultdict

class Solution:
    def leastBricks(self, wall: List[List[int]]) -> int:
        count = defaultdict(int)
        
        for row in wall:
            prefix = 0
            for i in range(len(row) - 1):
                prefix += row[i]
                count[prefix] += 1
        
        max_count = max(count.values()) if count else 0
        return len(wall) - max_count