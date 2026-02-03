"""
Problem: Jump Game V
Difficulty: Hard
Tags: array, dp, sort

Approach: DP with memoization - can jump left/right within distance d if lower
Time Complexity: O(n * d) where n is array length
Space Complexity: O(n) for memoization
"""

class Solution:
    def maxJumps(self, arr: List[int], d: int) -> int:
        n = len(arr)
        memo = {}
        
        def dfs(i):
            if i in memo:
                return memo[i]
            
            max_jumps = 1
            
            # Jump right
            for j in range(i + 1, min(i + d + 1, n)):
                if arr[j] >= arr[i]:
                    break
                max_jumps = max(max_jumps, 1 + dfs(j))
            
            # Jump left
            for j in range(i - 1, max(i - d - 1, -1), -1):
                if arr[j] >= arr[i]:
                    break
                max_jumps = max(max_jumps, 1 + dfs(j))
            
            memo[i] = max_jumps
            return max_jumps
        
        result = 0
        for i in range(n):
            result = max(result, dfs(i))
        
        return result