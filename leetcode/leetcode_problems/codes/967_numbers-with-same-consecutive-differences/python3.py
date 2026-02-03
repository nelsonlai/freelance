"""
Problem: Numbers With Same Consecutive Differences
Difficulty: Medium
Tags: array, search

Approach: DFS - generate numbers digit by digit, ensuring consecutive digits differ by k
Time Complexity: O(2^n) in worst case
Space Complexity: O(2^n) for result
"""

class Solution:
    def numsSameConsecDiff(self, n: int, k: int) -> List[int]:
        result = []
        
        def dfs(num, remaining):
            if remaining == 0:
                result.append(num)
                return
            
            last_digit = num % 10
            if last_digit + k < 10:
                dfs(num * 10 + last_digit + k, remaining - 1)
            if k > 0 and last_digit - k >= 0:
                dfs(num * 10 + last_digit - k, remaining - 1)
        
        for i in range(1, 10):
            dfs(i, n - 1)
        
        return result