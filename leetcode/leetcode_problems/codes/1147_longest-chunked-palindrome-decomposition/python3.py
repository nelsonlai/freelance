"""
Problem: Longest Chunked Palindrome Decomposition
Difficulty: Hard
Tags: array, string, tree, dp, greedy, hash

Approach: Greedy - match shortest prefix and suffix, recursively solve middle
Time Complexity: O(n^2) in worst case where n is length of text
Space Complexity: O(n) for recursion stack
"""

class Solution:
    def longestDecomposition(self, text: str) -> int:
        n = len(text)
        if n == 0:
            return 0
        
        # Try to match prefix and suffix
        for i in range(1, n // 2 + 1):
            if text[:i] == text[n-i:]:
                return 2 + self.longestDecomposition(text[i:n-i])
        
        return 1