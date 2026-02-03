"""
Problem: Count Binary Substrings
Difficulty: Easy
Tags: array, string, tree

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

class Solution:
    def countBinarySubstrings(self, s: str) -> int:
        groups = []
        count = 1
        
        for i in range(1, len(s)):
            if s[i] != s[i-1]:
                groups.append(count)
                count = 1
            else:
                count += 1
        groups.append(count)
        
        result = 0
        for i in range(1, len(groups)):
            result += min(groups[i-1], groups[i])
        
        return result