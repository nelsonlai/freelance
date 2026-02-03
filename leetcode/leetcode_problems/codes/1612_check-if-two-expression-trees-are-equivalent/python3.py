"""
Problem: Check If Two Expression Trees are Equivalent
Difficulty: Medium
Tags: tree, hash, search

Approach: Count frequency of variables in both trees, compare
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(n) for frequency map
"""

from collections import Counter

# Definition for a binary tree node.
# class Node(object):
#     def __init__(self, val=" ", left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def checkEquivalence(self, root1: 'Node', root2: 'Node') -> bool:
        def count_vars(node):
            if not node:
                return Counter()
            
            if node.val not in ['+', '-', '*', '/']:
                return Counter([node.val])
            
            left_count = count_vars(node.left)
            right_count = count_vars(node.right)
            return left_count + right_count
        
        return count_vars(root1) == count_vars(root2)