"""
Problem: Shortest Way to Form String
Difficulty: Medium
Tags: array, string, greedy, search

Approach: Greedy - try to match as many characters as possible from source in each pass
Time Complexity: O(m * n) where m is source length, n is target length
Space Complexity: O(1)
"""

class Solution:
    def shortestWay(self, source: str, target: str) -> int:
        result = 0
        target_idx = 0
        
        while target_idx < len(target):
            found = False
            for char in source:
                if target_idx < len(target) and target[target_idx] == char:
                    target_idx += 1
                    found = True
            
            if not found:
                return -1
            result += 1
        
        return result