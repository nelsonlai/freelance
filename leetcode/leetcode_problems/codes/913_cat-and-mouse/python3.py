from functools import lru_cache

class Solution:
    def catMouseGame(self, graph: List[List[int]]) -> int:
        @lru_cache(None)
        def dfs(mouse, cat, turn):
            if turn == 0:
                if mouse == 0:
                    return 1
                if mouse == cat:
                    return 2
                if turn >= 2 * len(graph):
                    return 0
                
                result = 2
                for next_pos in graph[mouse]:
                    next_result = dfs(next_pos, cat, 1)
                    if next_result == 1:
                        return 1
                    if next_result == 0:
                        result = 0
                return result
            else:
                if cat == mouse:
                    return 2
                if cat == 0:
                    return 1
                if turn >= 2 * len(graph):
                    return 0
                
                result = 1
                for next_pos in graph[cat]:
                    if next_pos == 0:
                        continue
                    next_result = dfs(mouse, next_pos, 0)
                    if next_result == 2:
                        return 2
                    if next_result == 0:
                        result = 0
                return result
        
        return dfs(1, 2, 0)
