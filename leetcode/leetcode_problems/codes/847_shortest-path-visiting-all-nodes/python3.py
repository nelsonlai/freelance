from collections import deque

class Solution:
    def shortestPathLength(self, graph: List[List[int]]) -> int:
        n = len(graph)
        target = (1 << n) - 1
        queue = deque([(i, 1 << i) for i in range(n)])
        visited = set(queue)
        steps = 0
        
        while queue:
            for _ in range(len(queue)):
                node, state = queue.popleft()
                if state == target:
                    return steps
                for neighbor in graph[node]:
                    newState = state | (1 << neighbor)
                    if (neighbor, newState) not in visited:
                        visited.add((neighbor, newState))
                        queue.append((neighbor, newState))
            steps += 1
        
        return -1
