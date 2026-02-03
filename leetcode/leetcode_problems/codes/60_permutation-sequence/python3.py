"""
Problem: Permutation Sequence
Difficulty: Hard
Tags: math

Approach: Optimized algorithm based on problem constraints
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def getPermutation(self, n: int, k: int) -> str:
        nums = [str(i) for i in range(1, n + 1)]
        result = []
        k -= 1  # Convert to 0-indexed
        
        # Calculate factorials
        fact = [1] * n
        for i in range(1, n):
            fact[i] = fact[i - 1] * i
        
        for i in range(n - 1, -1, -1):
            index = k // fact[i]
            result.append(nums.pop(index))
            k %= fact[i]
        
        return ''.join(result)