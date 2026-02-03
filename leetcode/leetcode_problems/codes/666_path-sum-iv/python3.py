"""
Problem: Path Sum IV
Difficulty: Medium
Tags: array, tree, hash, sort, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

from collections import defaultdict

class Solution:
    def pathSum(self, nums: List[int]) -> int:
        tree = {}
        for num in nums:
            depth = num // 100
            pos = (num // 10) % 10
            val = num % 10
            tree[(depth, pos)] = val
        
        result = 0
        
        def dfs(depth, pos, path_sum):
            nonlocal result
            if (depth, pos) not in tree:
                return
            
            path_sum += tree[(depth, pos)]
            
            left = (depth + 1, 2 * pos - 1)
            right = (depth + 1, 2 * pos)
            
            if left not in tree and right not in tree:
                result += path_sum
                return
            
            if left in tree:
                dfs(depth + 1, 2 * pos - 1, path_sum)
            if right in tree:
                dfs(depth + 1, 2 * pos, path_sum)
        
        dfs(1, 1, 0)
        return result