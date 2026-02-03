class Solution:
    def shortestToChar(self, s: str, c: str) -> List[int]:
        n = len(s)
        result = [n] * n
        pos = -n
        
        for i in range(n):
            if s[i] == c:
                pos = i
            result[i] = i - pos
        
        pos = 2 * n
        for i in range(n - 1, -1, -1):
            if s[i] == c:
                pos = i
            result[i] = min(result[i], pos - i)
        
        return result
