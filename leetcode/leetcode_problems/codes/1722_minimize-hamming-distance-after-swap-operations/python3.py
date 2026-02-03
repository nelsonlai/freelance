"""
Problem: Minimize Hamming Distance After Swap Operations
Difficulty: Medium
Tags: array, graph, search, union-find

Approach: Use Union-Find to group swappable indices, count frequency differences per group
Time Complexity: O(n * α(n)) where α is inverse Ackermann
Space Complexity: O(n)
"""

from collections import Counter, defaultdict

class Solution:
    def minimumHammingDistance(self, source: List[int], target: List[int], allowedSwaps: List[List[int]]) -> int:
        n = len(source)
        parent = list(range(n))
        
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        
        def union(x, y):
            px, py = find(x), find(y)
            if px != py:
                parent[px] = py
        
        for u, v in allowedSwaps:
            union(u, v)
        
        # Group indices by root
        groups = defaultdict(list)
        for i in range(n):
            groups[find(i)].append(i)
        
        result = 0
        
        for group in groups.values():
            source_freq = Counter(source[i] for i in group)
            target_freq = Counter(target[i] for i in group)
            
            # Count mismatches
            for num, count in target_freq.items():
                if num in source_freq:
                    mismatch = max(0, count - source_freq[num])
                else:
                    mismatch = count
                result += mismatch
        
        return result