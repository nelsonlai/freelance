"""
Problem: Serialize and Deserialize N-ary Tree
Difficulty: Hard
Tags: string, tree, search

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

"""
# Definition for a Node.
class Node(object):
    def __init__(self, val: Optional[int] = None, children: Optional[List['Node']] = None):
        if children is None:
            children = []
        self.val = val
        self.children = children
"""

class Codec:
    def serialize(self, root: 'Node') -> str:
        if not root:
            return ""
        
        result = []
        
        def dfs(node):
            result.append(str(node.val))
            result.append(str(len(node.children)))
            for child in node.children:
                dfs(child)
        
        dfs(root)
        return ",".join(result)
    
    def deserialize(self, data: str) -> 'Node':
        if not data:
            return None
        
        values = data.split(",")
        index = 0
        
        def dfs():
            nonlocal index
            if index >= len(values):
                return None
            
            val = int(values[index])
            index += 1
            num_children = int(values[index])
            index += 1
            
            children = []
            for _ in range(num_children):
                children.append(dfs())
            
            return Node(val, children)
        
        return dfs()