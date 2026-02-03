"""
Problem: Sequence Reconstruction
Difficulty: Medium
Tags: array, graph, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

from collections import defaultdict, deque

class Solution:
    def sequenceReconstruction(self, nums: List[int], sequences: List[List[int]]) -> bool:
        graph = defaultdict(list)
        in_degree = defaultdict(int)
        
        for seq in sequences:
            for i in range(len(seq) - 1):
                graph[seq[i]].append(seq[i + 1])
                in_degree[seq[i + 1]] += 1
                if seq[i] not in in_degree:
                    in_degree[seq[i]] = 0
        
        queue = deque([node for node in nums if in_degree[node] == 0])
        result = []
        
        while queue:
            if len(queue) > 1:
                return False
            node = queue.popleft()
            result.append(node)
            for neighbor in graph[node]:
                in_degree[neighbor] -= 1
                if in_degree[neighbor] == 0:
                    queue.append(neighbor)
        
        return result == nums