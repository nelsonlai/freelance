"""
Problem: GCD Sort of an Array
Difficulty: Hard
Tags: array, graph, math, sort, Union-Find

Approach: Union-Find to connect numbers with common factors, check if can sort
Time Complexity: O(n * sqrt(max(nums)) + n log n)
Space Complexity: O(max(nums))
"""

from math import gcd

class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
    
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def union(self, x, y):
        px, py = self.find(x), self.find(y)
        if px != py:
            self.parent[px] = py

class Solution:
    def gcdSort(self, nums: List[int]) -> bool:
        max_num = max(nums)
        uf = UnionFind(max_num + 1)
        
        # Union numbers with common factors
        for num in nums:
            for factor in range(2, int(num ** 0.5) + 1):
                if num % factor == 0:
                    uf.union(num, factor)
                    uf.union(num, num // factor)
        
        # Check if sorted array can be achieved
        sorted_nums = sorted(nums)
        for i, num in enumerate(nums):
            if uf.find(num) != uf.find(sorted_nums[i]):
                return False
        
        return True