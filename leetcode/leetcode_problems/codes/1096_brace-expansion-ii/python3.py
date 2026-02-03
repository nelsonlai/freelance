"""
Problem: Brace Expansion II
Difficulty: Hard
Tags: string, hash, sort, search, stack

Approach: Parse expression recursively, handle union and concatenation
Time Complexity: O(n * m) where n is options, m is length
Space Complexity: O(n * m) for results
"""

class Solution:
    def braceExpansionII(self, expression: str) -> List[str]:
        def parse(s):
            if not s:
                return ['']
            
            if '{' not in s:
                return [s]
            
            result = []
            i = 0
            while i < len(s):
                if s[i] == '{':
                    j = i + 1
                    depth = 1
                    while j < len(s) and depth > 0:
                        if s[j] == '{':
                            depth += 1
                        elif s[j] == '}':
                            depth -= 1
                        j += 1
                    
                    inner = s[i+1:j-1]
                    inner_options = parse(inner)
                    
                    if result:
                        result = [a + b for a in result for b in inner_options]
                    else:
                        result = inner_options
                    
                    i = j
                else:
                    j = i
                    while j < len(s) and s[j] not in '{,}':
                        j += 1
                    
                    prefix = s[i:j]
                    if result:
                        result = [a + prefix for a in result]
                    else:
                        result = [prefix]
                    
                    i = j
                    
                    if i < len(s) and s[i] == ',':
                        rest = parse(s[i+1:])
                        result = list(set(result + rest))
                        break
            
            return sorted(list(set(result)))
        
        return parse(expression)