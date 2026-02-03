"""
Problem: Find Permutation
Difficulty: Medium
Tags: array, string, graph, greedy, stack

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def findPermutation(self, s: str) -> List[int]:
        n = len(s) + 1
        result = list(range(1, n + 1))
        i = 0
        
        while i < len(s):
            if s[i] == 'D':
                j = i
                while j < len(s) and s[j] == 'D':
                    j += 1
                result[i:j+1] = result[i:j+1][::-1]
                i = j
            else:
                i += 1
        
        return result