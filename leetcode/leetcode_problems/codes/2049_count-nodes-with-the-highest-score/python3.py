"""
Problem: Count Nodes With the Highest Score
Difficulty: Medium
Tags: array, tree, search, DFS

Approach: Build tree, calculate subtree sizes, compute scores for each node
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(n)
"""

from collections import defaultdict

class Solution:
    def countHighestScoreNodes(self, parents: List[int]) -> int:
        n = len(parents)
        children = defaultdict(list)
        
        # Build tree
        for i in range(1, n):
            children[parents[i]].append(i)
        
        # Calculate subtree sizes
        subtree_size = [0] * n
        
        def dfs(node):
            size = 1
            for child in children[node]:
                size += dfs(child)
            subtree_size[node] = size
            return size
        
        dfs(0)
        
        # Calculate scores
        max_score = 0
        count = 0
        
        for i in range(n):
            score = 1
            remaining = n - 1
            
            for child in children[i]:
                score *= subtree_size[child]
                remaining -= subtree_size[child]
            
            if remaining > 0:
                score *= remaining
            
            if score > max_score:
                max_score = score
                count = 1
            elif score == max_score:
                count += 1
        
        return count