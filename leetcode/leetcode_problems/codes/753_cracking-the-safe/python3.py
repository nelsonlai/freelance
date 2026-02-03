class Solution:
    def crackSafe(self, n: int, k: int) -> str:
        visited = set()
        result = []
        
        def dfs(node):
            for x in range(k):
                neighbor = node + str(x)
                if neighbor not in visited:
                    visited.add(neighbor)
                    dfs(neighbor[1:])
                    result.append(str(x))
        
        start = "0" * (n - 1)
        dfs(start)
        return "".join(result) + start
