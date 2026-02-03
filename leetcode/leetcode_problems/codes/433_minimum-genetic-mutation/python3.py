"""
Problem: Minimum Genetic Mutation
Difficulty: Medium
Tags: string, hash, search

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import deque

class Solution:
    def minMutation(self, startGene: str, endGene: str, bank: List[str]) -> int:
        bank_set = set(bank)
        if endGene not in bank_set:
            return -1
        
        queue = deque([(startGene, 0)])
        visited = {startGene}
        chars = ['A', 'C', 'G', 'T']
        
        while queue:
            gene, mutations = queue.popleft()
            if gene == endGene:
                return mutations
            
            for i in range(len(gene)):
                for char in chars:
                    if char != gene[i]:
                        new_gene = gene[:i] + char + gene[i+1:]
                        if new_gene in bank_set and new_gene not in visited:
                            visited.add(new_gene)
                            queue.append((new_gene, mutations + 1))
        
        return -1