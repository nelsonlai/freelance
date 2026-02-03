"""
Problem: Depth of BST Given Insertion Order
Difficulty: Medium
Tags: array, tree, search, binary search tree

Approach: Use TreeMap-like structure with bisect to track depths
Time Complexity: O(n log n) worst case
Space Complexity: O(n)
"""

import bisect

class Solution:
    def maxDepthBST(self, order: List[int]) -> int:
        depths = {}
        sorted_keys = []
        max_depth = 0
        
        for val in order:
            pos = bisect.bisect_left(sorted_keys, val)
            depth = 1
            
            if pos > 0:
                left_key = sorted_keys[pos - 1]
                depth = max(depth, depths[left_key] + 1)
            
            if pos < len(sorted_keys):
                right_key = sorted_keys[pos]
                depth = max(depth, depths[right_key] + 1)
            
            bisect.insort(sorted_keys, val)
            depths[val] = depth
            max_depth = max(max_depth, depth)
        
        return max_depth