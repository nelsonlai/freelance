class Solution:
    def flipgame(self, fronts: List[int], backs: List[int]) -> int:
        same = {fronts[i] for i in range(len(fronts)) if fronts[i] == backs[i]}
        result = float('inf')
        
        for i in range(len(fronts)):
            if fronts[i] not in same:
                result = min(result, fronts[i])
            if backs[i] not in same:
                result = min(result, backs[i])
        
        return result if result != float('inf') else 0
