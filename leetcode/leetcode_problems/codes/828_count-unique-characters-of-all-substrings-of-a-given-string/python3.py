class Solution:
    def uniqueLetterString(self, s: str) -> int:
        index = {c: [-1, -1] for c in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'}
        result = 0
        
        for i, c in enumerate(s):
            k, j = index[c]
            result += (i - j) * (j - k)
            index[c] = [j, i]
        
        for c in index:
            k, j = index[c]
            result += (len(s) - j) * (j - k)
        
        return result
