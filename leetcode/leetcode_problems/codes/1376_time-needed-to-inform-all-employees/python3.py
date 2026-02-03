"""
Problem: Time Needed to Inform All Employees
Difficulty: Medium
Tags: array, tree, graph, search

Approach: Build tree, DFS from head to find maximum path sum
Time Complexity: O(n) where n is number of employees
Space Complexity: O(n) for tree
"""

from collections import defaultdict

class Solution:
    def numOfMinutes(self, n: int, headID: int, manager: List[int], informTime: List[int]) -> int:
        tree = defaultdict(list)
        for i in range(n):
            if manager[i] != -1:
                tree[manager[i]].append(i)
        
        def dfs(node):
            max_time = 0
            for child in tree[node]:
                max_time = max(max_time, dfs(child))
            return informTime[node] + max_time
        
        return dfs(headID)