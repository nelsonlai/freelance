"""
Problem: Largest Component Size by Common Factor
Difficulty: Hard
Tags: array, graph, math, hash

Approach: Union-Find - connect numbers that share common factors
Time Complexity: O(n * sqrt(max(nums))) for factorization
Space Complexity: O(n) for Union-Find
"""

from collections import defaultdict

class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.size = [1] * n
    
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def union(self, x, y):
        px, py = self.find(x), self.find(y)
        if px != py:
            if self.size[px] < self.size[py]:
                px, py = py, px
            self.parent[py] = px
            self.size[px] += self.size[py]

class Solution:
    def largestComponentSize(self, nums: List[int]) -> int:
        n = len(nums)
        uf = UnionFind(n)
        factor_to_indices = defaultdict(list)
        
        # Map each number to its prime factors
        for i, num in enumerate(nums):
            factors = self.getPrimeFactors(num)
            for factor in factors:
                factor_to_indices[factor].append(i)
        
        # Union all indices that share a common factor
        for indices in factor_to_indices.values():
            for i in range(1, len(indices)):
                uf.union(indices[0], indices[i])
        
        return max(uf.size)
    
    def getPrimeFactors(self, n):
        factors = set()
        d = 2
        while d * d <= n:
            if n % d == 0:
                factors.add(d)
                while n % d == 0:
                    n //= d
            d += 1
        if n > 1:
            factors.add(n)
        return factors