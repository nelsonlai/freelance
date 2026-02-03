"""
Problem: Maximum Genetic Difference Query
Difficulty: Hard
Tags: array, tree, hash, search, trie, DFS

Approach: Build tree, use Trie to find max XOR for each query path
Time Complexity: O(n * 18 + q * 18) where n is nodes, q is queries, 18 is bits
Space Complexity: O(n * 18)
"""

class TrieNode:
    def __init__(self):
        self.count = 0
        self.children = [None, None]

class Solution:
    def maxGeneticDifference(self, parents: List[int], queries: List[List[int]]) -> List[int]:
        n = len(parents)
        root_idx = -1
        graph = [[] for _ in range(n)]
        
        for i, p in enumerate(parents):
            if p == -1:
                root_idx = i
            else:
                graph[p].append(i)
        
        query_map = defaultdict(list)
        for idx, (node, val) in enumerate(queries):
            query_map[node].append((val, idx))
        
        result = [0] * len(queries)
        trie = TrieNode()
        
        def add(num):
            node = trie
            for i in range(17, -1, -1):
                bit = (num >> i) & 1
                if not node.children[bit]:
                    node.children[bit] = TrieNode()
                node = node.children[bit]
                node.count += 1
        
        def remove(num):
            node = trie
            for i in range(17, -1, -1):
                bit = (num >> i) & 1
                node = node.children[bit]
                node.count -= 1
        
        def query(num):
            node = trie
            res = 0
            for i in range(17, -1, -1):
                bit = (num >> i) & 1
                target = 1 - bit
                if node.children[target] and node.children[target].count > 0:
                    res |= (1 << i)
                    node = node.children[target]
                else:
                    node = node.children[bit]
            return res
        
        def dfs(node):
            add(node)
            
            for val, idx in query_map[node]:
                result[idx] = query(val)
            
            for child in graph[node]:
                dfs(child)
            
            remove(node)
        
        dfs(root_idx)
        return result