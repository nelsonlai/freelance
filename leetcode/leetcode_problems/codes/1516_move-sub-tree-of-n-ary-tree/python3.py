"""
Problem: Move Sub-Tree of N-Ary Tree
Difficulty: Hard
Tags: tree, search

Approach: Find parent of p, remove p from its parent, add p to q's children, handle if q is in p's subtree
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(h) for recursion stack
"""

"""
# Definition for a Node.
class Node:
    def __init__(self, val: Optional[int] = None, children: Optional[List['Node']] = None):
        self.val = val
        self.children = children if children is not None else []
"""

class Solution:
    def moveSubTree(self, root: 'Node', p: 'Node', q: 'Node') -> 'Node':
        def find_parent(node, target, parent=None):
            if node == target:
                return parent
            for child in node.children:
                result = find_parent(child, target, node)
                if result is not None:
                    return result
            return None
        
        def is_descendant(node, target):
            if node == target:
                return True
            for child in node.children:
                if is_descendant(child, target):
                    return True
            return False
        
        if p == q:
            return root
        
        p_parent = find_parent(root, p)
        
        if is_descendant(p, q):
            q_parent = find_parent(root, q)
            q_parent.children.remove(q)
            if p_parent:
                p_parent.children.remove(p)
                p_parent.children.append(q)
            else:
                root = q
            q.children.append(p)
        else:
            if p_parent:
                p_parent.children.remove(p)
            else:
                root = None
            q.children.append(p)
        
        return root if root else p