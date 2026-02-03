"""
Problem: Serialize and Deserialize BST
Difficulty: Medium
Tags: string, tree, search

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Codec:

    def serialize(self, root: Optional[TreeNode]) -> str:
        if not root:
            return ""
        
        result = []
        
        def preorder(node):
            if node:
                result.append(str(node.val))
                preorder(node.left)
                preorder(node.right)
        
        preorder(root)
        return ",".join(result)
    
    def deserialize(self, data: str) -> Optional[TreeNode]:
        if not data:
            return None
        
        values = [int(x) for x in data.split(",")]
        
        def build(min_val, max_val):
            if not values or values[0] < min_val or values[0] > max_val:
                return None
            
            val = values.pop(0)
            node = TreeNode(val)
            node.left = build(min_val, val)
            node.right = build(val, max_val)
            return node
        
        return build(float('-inf'), float('inf'))