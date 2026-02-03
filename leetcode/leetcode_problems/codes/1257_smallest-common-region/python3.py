"""
Problem: Smallest Common Region
Difficulty: Medium
Tags: array, string, tree, hash, search

Approach: Build parent map, find LCA by tracking path from region1 to root
Time Complexity: O(n) where n is total regions
Space Complexity: O(n) for parent map
"""

class Solution:
    def findSmallestRegion(self, regions: List[List[str]], region1: str, region2: str) -> str:
        parent = {}
        for region_list in regions:
            root = region_list[0]
            for child in region_list[1:]:
                parent[child] = root
        
        # Find path from region1 to root
        path = set()
        curr = region1
        while curr:
            path.add(curr)
            curr = parent.get(curr)
        
        # Find first common ancestor
        curr = region2
        while curr:
            if curr in path:
                return curr
            curr = parent.get(curr)
        
        return None