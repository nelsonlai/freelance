"""
Problem: Beautiful Arrangement
Difficulty: Medium
Tags: array, dp

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def countArrangement(self, n: int) -> int:
        def backtrack(pos, used):
            if pos > n:
                return 1
            
            count = 0
            for i in range(1, n + 1):
                if not used[i] and (i % pos == 0 or pos % i == 0):
                    used[i] = True
                    count += backtrack(pos + 1, used)
                    used[i] = False
            
            return count
        
        used = [False] * (n + 1)
        return backtrack(1, used)