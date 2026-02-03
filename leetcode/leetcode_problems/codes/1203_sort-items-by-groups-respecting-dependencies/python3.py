"""
Problem: Sort Items by Groups Respecting Dependencies
Difficulty: Hard
Tags: array, graph, sort, search

Approach: Two-level topological sort - first sort groups, then sort items within groups
Time Complexity: O(n + m + E) where E is number of dependencies
Space Complexity: O(n + m) for graphs
"""

from collections import defaultdict, deque

class Solution:
    def sortItems(self, n: int, m: int, group: List[int], beforeItems: List[List[int]]) -> List[int]:
        # Assign groups to items without groups
        group_id = m
        for i in range(n):
            if group[i] == -1:
                group[i] = group_id
                group_id += 1
        
        # Build graphs
        item_graph = defaultdict(list)
        item_indegree = [0] * n
        group_graph = defaultdict(list)
        group_indegree = defaultdict(int)
        
        for i in range(n):
            for prev in beforeItems[i]:
                item_graph[prev].append(i)
                item_indegree[i] += 1
                
                if group[prev] != group[i]:
                    if group[prev] not in group_graph:
                        group_indegree[group[i]] = group_indegree.get(group[i], 0)
                    if group[i] not in group_graph[group[prev]]:
                        group_graph[group[prev]].append(group[i])
                        group_indegree[group[i]] = group_indegree.get(group[i], 0) + 1
        
        # Topological sort groups
        group_queue = deque([g for g in range(group_id) if group_indegree.get(g, 0) == 0])
        group_order = []
        
        while group_queue:
            g = group_queue.popleft()
            group_order.append(g)
            for next_group in group_graph[g]:
                group_indegree[next_group] -= 1
                if group_indegree[next_group] == 0:
                    group_queue.append(next_group)
        
        if len(group_order) != group_id:
            return []
        
        # Topological sort items within each group
        group_items = defaultdict(list)
        for i in range(n):
            group_items[group[i]].append(i)
        
        result = []
        for g in group_order:
            items = group_items[g]
            item_queue = deque([i for i in items if item_indegree[i] == 0])
            group_result = []
            
            while item_queue:
                item = item_queue.popleft()
                group_result.append(item)
                for next_item in item_graph[item]:
                    if group[next_item] == g:
                        item_indegree[next_item] -= 1
                        if item_indegree[next_item] == 0:
                            item_queue.append(next_item)
            
            if len(group_result) != len(items):
                return []
            
            result.extend(group_result)
        
        return result if len(result) == n else []