from collections import defaultdict

class Solution:
    def pyramidTransition(self, bottom: str, allowed: List[str]) -> bool:
        rules = defaultdict(list)
        for rule in allowed:
            rules[rule[:2]].append(rule[2])
        
        def dfs(level):
            if len(level) == 1:
                return True
            
            nextLevel = []
            def buildNext(i, current):
                if i == len(level) - 1:
                    if dfs(''.join(current)):
                        return True
                    return False
                
                key = level[i:i+2]
                if key in rules:
                    for char in rules[key]:
                        if buildNext(i + 1, current + [char]):
                            return True
                return False
            
            return buildNext(0, [])
        
        return dfs(bottom)
