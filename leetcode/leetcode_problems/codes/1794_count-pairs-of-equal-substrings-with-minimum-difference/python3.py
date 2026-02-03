"""
Problem: Count Pairs of Equal Substrings With Minimum Difference
Difficulty: Medium
Tags: string, hash

Approach: For each character, find positions in both strings, count pairs
Time Complexity: O(n * m) where n, m are lengths
Space Complexity: O(n + m)
"""

from collections import defaultdict

class Solution:
    def countQuadruples(self, firstString: str, secondString: str) -> int:
        first_pos = defaultdict(list)
        second_pos = defaultdict(list)
        
        for i, char in enumerate(firstString):
            first_pos[char].append(i)
        
        for i, char in enumerate(secondString):
            second_pos[char].append(i)
        
        min_diff = float('inf')
        count = 0
        
        for char in first_pos:
            if char in second_pos:
                for i in first_pos[char]:
                    for j in second_pos[char]:
                        diff = i - j
                        if diff < min_diff:
                            min_diff = diff
                            count = 1
                        elif diff == min_diff:
                            count += 1
        
        return count