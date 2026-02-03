from collections import defaultdict

class Solution:
    def numMatchingSubseq(self, s: str, words: List[str]) -> int:
        waiting = defaultdict(list)
        for word in words:
            waiting[word[0]].append(iter(word[1:]))
        
        result = 0
        for char in s:
            old = waiting.pop(char, [])
            for it in old:
                nxt = next(it, None)
                if nxt is None:
                    result += 1
                else:
                    waiting[nxt].append(it)
        
        return result
