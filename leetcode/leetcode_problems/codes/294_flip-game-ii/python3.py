"""
Problem: Flip Game II
Difficulty: Medium
Tags: string, dp, math

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def canWin(self, currentState: str) -> bool:
        memo = {}
        
        def canWinHelper(s):
            if s in memo:
                return memo[s]
            
            for i in range(len(s) - 1):
                if s[i] == '+' and s[i + 1] == '+':
                    new_s = s[:i] + '--' + s[i + 2:]
                    if not canWinHelper(new_s):
                        memo[s] = True
                        return True
            
            memo[s] = False
            return False
        
        return canWinHelper(currentState)