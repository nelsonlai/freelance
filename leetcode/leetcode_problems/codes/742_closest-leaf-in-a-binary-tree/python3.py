from collections import defaultdict, deque

class Solution:
    def findClosestLeaf(self, root: Optional[TreeNode], k: int) -> int:
        graph = defaultdict(list)
        leaves = set()
        
        def buildGraph(node, parent):
            if not node:
                return
            if parent:
                graph[node.val].append(parent.val)
            if node.left:
                graph[node.val].append(node.left.val)
                buildGraph(node.left, node)
            if node.right:
                graph[node.val].append(node.right.val)
                buildGraph(node.right, node)
            if not node.left and not node.right:
                leaves.add(node.val)
        
        buildGraph(root, None)
        
        queue = deque([k])
        visited = {k}
        
        while queue:
            node = queue.popleft()
            if node in leaves:
                return node
            for neighbor in graph[node]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append(neighbor)
        
        return -1
