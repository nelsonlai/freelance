"""
Problem: Brace Expansion
Difficulty: Medium
Tags: string, graph, sort, search, stack

Approach: Parse expression, generate all combinations using backtracking
Time Complexity: O(n * m) where n is options, m is length
Space Complexity: O(n * m) for results
"""

class Solution:
    def expand(self, s: str) -> List[str]:
        def parse(s, i):
            options = []
            current = []
            
            while i < len(s):
                if s[i] == '{':
                    if current:
                        options.append([''.join(current)])
                        current = []
                    i, group = parse_group(s, i + 1)
                    options.append(group)
                elif s[i] == '}':
                    break
                else:
                    current.append(s[i])
                i += 1
            
            if current:
                options.append([''.join(current)])
            
            return options
        
        def parse_group(s, i):
            group = []
            current = []
            
            while i < len(s) and s[i] != '}':
                if s[i] == ',':
                    if current:
                        group.append(''.join(current))
                        current = []
                else:
                    current.append(s[i])
                i += 1
            
            if current:
                group.append(''.join(current))
            
            return i, sorted(group)
        
        def combine(options, idx, current, result):
            if idx == len(options):
                result.append(''.join(current))
                return
            
            for option in options[idx]:
                current.append(option)
                combine(options, idx + 1, current, result)
                current.pop()
        
        options = parse(s, 0)
        result = []
        combine(options, 0, [], result)
        return sorted(result)