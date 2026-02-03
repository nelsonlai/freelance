"""
Problem: Number of Ways to Reorder Array to Get Same BST
Difficulty: Hard
Tags: array, tree, graph, dp, math, search

Approach: Recursive - split into left/right subtrees, use combinatorics to count interleavings
Time Complexity: O(n^2) where n is length of nums
Space Complexity: O(n) for recursion
"""

MOD = 10**9 + 7

class Solution:
    def numOfWays(self, nums: List[int]) -> int:
        def nCr(n, r):
            if r > n or r < 0:
                return 0
            if r == 0 or r == n:
                return 1
            r = min(r, n - r)
            result = 1
            for i in range(r):
                result = result * (n - i) // (i + 1)
            return result % MOD
        
        def ways(arr):
            if len(arr) <= 2:
                return 1
            
            root = arr[0]
            left = [x for x in arr if x < root]
            right = [x for x in arr if x > root]
            
            left_ways = ways(left)
            right_ways = ways(right)
            
            return (nCr(len(left) + len(right), len(left)) * left_ways % MOD * right_ways) % MOD
        
        return (ways(nums) - 1) % MOD