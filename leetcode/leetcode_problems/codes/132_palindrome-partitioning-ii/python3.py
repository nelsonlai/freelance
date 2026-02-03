"""
Problem: Palindrome Partitioning II
Difficulty: Hard
Tags: string, tree, dp

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def minCut(self, s: str) -> int:
        n = len(s)
        isPalindrome = [[False] * n for _ in range(n)]
        
        for i in range(n):
            isPalindrome[i][i] = True
        for i in range(n - 1):
            if s[i] == s[i + 1]:
                isPalindrome[i][i + 1] = True
        
        for length in range(3, n + 1):
            for i in range(n - length + 1):
                j = i + length - 1
                if s[i] == s[j] and isPalindrome[i + 1][j - 1]:
                    isPalindrome[i][j] = True
        
        dp = [0] * n
        for i in range(n):
            if isPalindrome[0][i]:
                dp[i] = 0
            else:
                dp[i] = i
                for j in range(i):
                    if isPalindrome[j + 1][i]:
                        dp[i] = min(dp[i], dp[j] + 1)
        
        return dp[n - 1]