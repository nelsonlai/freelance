from collections import deque

class Solution:
    def kSimilarity(self, s1: str, s2: str) -> int:
        if s1 == s2:
            return 0
        
        queue = deque([(s1, 0)])
        visited = {s1}
        
        while queue:
            s, steps = queue.popleft()
            if s == s2:
                return steps
            
            i = 0
            while i < len(s) and s[i] == s2[i]:
                i += 1
            
            for j in range(i + 1, len(s)):
                if s[j] == s2[i] and s[j] != s2[j]:
                    newS = s[:i] + s[j] + s[i+1:j] + s[i] + s[j+1:]
                    if newS not in visited:
                        visited.add(newS)
                        queue.append((newS, steps + 1))
        
        return -1
