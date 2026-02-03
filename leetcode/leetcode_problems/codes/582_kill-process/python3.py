"""
Problem: Kill Process
Difficulty: Medium
Tags: array, tree, hash, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

from collections import defaultdict

class Solution:
    def killProcess(self, pid: List[int], ppid: List[int], kill: int) -> List[int]:
        children = defaultdict(list)
        for i in range(len(ppid)):
            children[ppid[i]].append(pid[i])
        
        result = []
        stack = [kill]
        
        while stack:
            process = stack.pop()
            result.append(process)
            stack.extend(children[process])
        
        return result