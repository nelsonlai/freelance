"""
Problem: Smallest Missing Genetic Value in Each Subtree
Difficulty: Hard
Tags: array, tree, graph, DFS, union-find

Approach: DFS to collect values in each subtree, find smallest missing value
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(n)
"""

from collections import defaultdict

class Solution:
    def smallestMissingValueSubtree(self, parents: List[int], nums: List[int]) -> List[int]:
        n = len(parents)
        children = defaultdict(list)
        
        # Build tree
        for i in range(1, n):
            children[parents[i]].append(i)
        
        result = [1] * n
        
        # Find node with value 1 (if exists)
        node_with_one = -1
        for i in range(n):
            if nums[i] == 1:
                node_with_one = i
                break
        
        if node_with_one == -1:
            return result
        
        # Collect all values in path from node_with_one to root
        visited = set()
        current = node_with_one
        missing = 1
        
        while current != -1:
            # DFS to collect all values in subtree of current
            stack = [current]
            subtree_values = set()
            
            while stack:
                node = stack.pop()
                if node in visited:
                    continue
                visited.add(node)
                subtree_values.add(nums[node])
                
                for child in children[node]:
                    if child not in visited:
                        stack.append(child)
            
            # Find smallest missing value
            while missing in subtree_values:
                missing += 1
            
            result[current] = missing
            current = parents[current] if current < n else -1
        
        return result