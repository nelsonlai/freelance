"""
Problem: Linked List in Binary Tree
Difficulty: Medium
Tags: tree, search, linked_list

Approach: DFS - try matching from each node, recursively match linked list
Time Complexity: O(n * m) where n is tree nodes, m is list length
Space Complexity: O(h) for recursion stack
"""

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def isSubPath(self, head: Optional[ListNode], root: Optional[TreeNode]) -> bool:
        def match(node, list_node):
            if not list_node:
                return True
            if not node or node.val != list_node.val:
                return False
            return match(node.left, list_node.next) or match(node.right, list_node.next)
        
        if not root:
            return False
        
        if match(root, head):
            return True
        
        return self.isSubPath(head, root.left) or self.isSubPath(head, root.right)