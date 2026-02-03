"""
Problem: Synonymous Sentences
Difficulty: Medium
Tags: array, string, graph, hash, sort

Approach: Union-Find to group synonyms, backtracking to generate all sentences
Time Complexity: O(2^n * m) where n is words, m is synonyms per word
Space Complexity: O(n) for recursion stack
"""

from collections import defaultdict

class Solution:
    def generateSentences(self, synonyms: List[List[str]], text: str) -> List[str]:
        parent = {}
        
        def find(x):
            if x not in parent:
                parent[x] = x
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        
        def union(x, y):
            px, py = find(x), find(y)
            if px != py:
                parent[px] = py
        
        for syn in synonyms:
            union(syn[0], syn[1])
        
        # Group synonyms
        groups = defaultdict(list)
        for word in parent:
            root = find(word)
            groups[root].append(word)
        
        for root in groups:
            groups[root].sort()
        
        words = text.split()
        result = []
        
        def backtrack(idx, current):
            if idx == len(words):
                result.append(' '.join(current))
                return
            
            word = words[idx]
            if word in parent:
                root = find(word)
                for synonym in groups[root]:
                    backtrack(idx + 1, current + [synonym])
            else:
                backtrack(idx + 1, current + [word])
        
        backtrack(0, [])
        return sorted(result)