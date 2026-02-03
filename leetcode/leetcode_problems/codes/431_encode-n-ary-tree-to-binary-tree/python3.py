"""
Problem: Encode N-ary Tree to Binary Tree
Difficulty: Hard
Tags: tree, search

Approach: DFS or BFS traversal
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(h) for recursion stack where h is height
"""

"""
# Definition for a Node.
class Node:
    def __init__(self, val: Optional[int] = None, children: Optional[List['Node']] = None):
        self.val = val
        self.children = children
"""

"""
# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None
"""

class Codec:
    # Encodes an n-ary tree to a binary tree.
    def encode(self, root: 'Optional[Node]') -> Optional[TreeNode]:
        if not root:
            return None
        
        binary_root = TreeNode(root.val)
        
        if root.children:
            binary_root.left = self.encode(root.children[0])
            current = binary_root.left
            for i in range(1, len(root.children)):
                current.right = self.encode(root.children[i])
                current = current.right
        
        return binary_root
    
    # Decodes your binary tree to an n-ary tree.
    def decode(self, data: Optional[TreeNode]) -> 'Optional[Node]':
        if not data:
            return None
        
        nary_root = Node(data.val, [])
        
        if data.left:
            child = self.decode(data.left)
            nary_root.children.append(child)
            current = data.left
            while current.right:
                child = self.decode(current.right)
                nary_root.children.append(child)
                current = current.right
        
        return nary_root