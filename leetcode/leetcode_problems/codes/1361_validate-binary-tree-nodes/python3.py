"""
Problem: Validate Binary Tree Nodes
Difficulty: Medium
Tags: tree, graph, search

Approach: Check for single root, no cycles, all nodes reachable
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(n) for visited set
"""

from collections import deque

class Solution:
    def validateBinaryTreeNodes(self, n: int, leftChild: List[int], rightChild: List[int]) -> bool:
        # Find root (node with no incoming edges)
        has_parent = set()
        for i in range(n):
            if leftChild[i] != -1:
                has_parent.add(leftChild[i])
            if rightChild[i] != -1:
                has_parent.add(rightChild[i])
        
        roots = [i for i in range(n) if i not in has_parent]
        if len(roots) != 1:
            return False
        
        # BFS from root to check connectivity and cycles
        visited = set()
        queue = deque([roots[0]])
        
        while queue:
            node = queue.popleft()
            if node in visited:
                return False
            visited.add(node)
            
            if leftChild[node] != -1:
                queue.append(leftChild[node])
            if rightChild[node] != -1:
                queue.append(rightChild[node])
        
        return len(visited) == n