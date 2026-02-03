"""
Problem: Find Duplicate File in System
Difficulty: Medium
Tags: array, string, tree, hash, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

from collections import defaultdict

class Solution:
    def findDuplicate(self, paths: List[str]) -> List[List[str]]:
        content_map = defaultdict(list)
        
        for path in paths:
            parts = path.split()
            directory = parts[0]
            
            for file_info in parts[1:]:
                name, content = file_info.split('(')
                content = content[:-1]
                full_path = directory + '/' + name
                content_map[content].append(full_path)
        
        return [paths for paths in content_map.values() if len(paths) > 1]