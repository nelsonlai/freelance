from collections import Counter

class Solution:
    def customSortString(self, order: str, s: str) -> str:
        count = Counter(s)
        result = []
        
        for char in order:
            result.append(char * count[char])
            count[char] = 0
        
        for char, freq in count.items():
            result.append(char * freq)
        
        return ''.join(result)
