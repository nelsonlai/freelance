"""
Problem: Split a String Into the Max Number of Unique Substrings
Difficulty: Medium
Tags: string, tree, hash

Approach: Backtracking - try all possible splits, track unique substrings
Time Complexity: O(2^n) in worst case
Space Complexity: O(n) for recursion and set
"""

class Solution:
    def maxUniqueSplit(self, s: str) -> int:
        def backtrack(start, seen):
            if start == len(s):
                return 0
            
            result = 0
            for end in range(start + 1, len(s) + 1):
                substring = s[start:end]
                if substring not in seen:
                    seen.add(substring)
                    result = max(result, 1 + backtrack(end, seen))
                    seen.remove(substring)
            
            return result
        
        return backtrack(0, set())