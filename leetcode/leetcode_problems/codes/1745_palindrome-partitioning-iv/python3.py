"""
Problem: Palindrome Partitioning IV
Difficulty: Hard
Tags: string, dp

Approach: Precompute palindrome table, check if can split into 3 palindromes
Time Complexity: O(n^2) where n is length
Space Complexity: O(n^2)
"""

class Solution:
    def checkPartitioning(self, s: str) -> bool:
        n = len(s)
        is_palindrome = [[False] * n for _ in range(n)]
        
        # Precompute palindromes
        for i in range(n):
            is_palindrome[i][i] = True
        
        for i in range(n - 1):
            if s[i] == s[i + 1]:
                is_palindrome[i][i + 1] = True
        
        for length in range(3, n + 1):
            for i in range(n - length + 1):
                j = i + length - 1
                if s[i] == s[j] and is_palindrome[i + 1][j - 1]:
                    is_palindrome[i][j] = True
        
        # Check if can split into 3 palindromes
        for i in range(1, n):
            for j in range(i + 1, n):
                if is_palindrome[0][i - 1] and is_palindrome[i][j - 1] and is_palindrome[j][n - 1]:
                    return True
        
        return False