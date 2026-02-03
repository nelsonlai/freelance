"""
Problem: Queries on a Permutation With Key
Difficulty: Medium
Tags: array, tree

Approach: Simulate - find index, move to front, track positions
Time Complexity: O(q * m) where q is queries length
Space Complexity: O(m) for permutation
"""

class Solution:
    def processQueries(self, queries: List[int], m: int) -> List[int]:
        perm = list(range(1, m + 1))
        result = []
        
        for query in queries:
            idx = perm.index(query)
            result.append(idx)
            perm = [perm[idx]] + perm[:idx] + perm[idx+1:]
        
        return result