"""
Problem: Merge BSTs to Create Single BST
Difficulty: Hard
Tags: array, tree, hash, search, BST validation

Approach: Find root (not a leaf in other trees), merge trees, validate BST
Time Complexity: O(n * m) where n is trees, m is nodes
Space Complexity: O(n * m)
"""

class Solution:
    def canMerge(self, trees: List[TreeNode]) -> Optional[TreeNode]:
        from collections import defaultdict
        
        val_to_node = {}
        leaf_vals = set()
        
        for tree in trees:
            val_to_node[tree.val] = tree
            if tree.left:
                leaf_vals.add(tree.left.val)
            if tree.right:
                leaf_vals.add(tree.right.val)
        
        root = None
        for tree in trees:
            if tree.val not in leaf_vals:
                if root:
                    return None
                root = tree
        
        if not root:
            return None
        
        def validate(node, min_val, max_val):
            if not node:
                return True
            if node.val <= min_val or node.val >= max_val:
                return False
            return validate(node.left, min_val, node.val) and validate(node.right, node.val, max_val)
        
        def merge(node):
            if not node:
                return
            
            if node.left and node.left.val in val_to_node:
                node.left = val_to_node[node.left.val]
                del val_to_node[node.left.val]
                merge(node.left)
            
            if node.right and node.right.val in val_to_node:
                node.right = val_to_node[node.right.val]
                del val_to_node[node.right.val]
                merge(node.right)
        
        merge(root)
        
        if len(val_to_node) > 1:
            return None
        
        if validate(root, float('-inf'), float('inf')):
            return root
        return None