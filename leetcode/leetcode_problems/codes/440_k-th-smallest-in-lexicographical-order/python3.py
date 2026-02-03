"""
Problem: K-th Smallest in Lexicographical Order
Difficulty: Hard
Tags: graph

Approach: Optimized algorithm based on problem constraints
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def findKthNumber(self, n: int, k: int) -> int:
        def countNumbers(prefix):
            count = 0
            next_prefix = prefix + 1
            current = prefix
            while current <= n:
                count += min(next_prefix, n + 1) - current
                current *= 10
                next_prefix *= 10
            return count
        
        current = 1
        k -= 1
        
        while k > 0:
            count = countNumbers(current)
            if count <= k:
                current += 1
                k -= count
            else:
                current *= 10
                k -= 1
        
        return current