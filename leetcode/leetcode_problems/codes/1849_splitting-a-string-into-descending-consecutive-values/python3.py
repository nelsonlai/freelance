"""
Problem: Splitting a String Into Descending Consecutive Values
Difficulty: Medium
Tags: string, backtracking

Approach: Backtracking - try all possible first numbers, then recursively check
Time Complexity: O(n^2) where n is length
Space Complexity: O(n) for recursion
"""

class Solution:
    def splitString(self, s: str) -> bool:
        def backtrack(start, prev_val):
            if start == len(s):
                return True
            
            for end in range(start + 1, len(s) + 1):
                current_val = int(s[start:end])
                if prev_val is None or current_val == prev_val - 1:
                    if backtrack(end, current_val):
                        return True
                elif current_val > prev_val:
                    break
            
            return False
        
        return backtrack(0, None)