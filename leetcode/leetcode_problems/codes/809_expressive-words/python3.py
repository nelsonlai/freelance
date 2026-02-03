class Solution:
    def expressiveWords(self, s: str, words: List[str]) -> int:
        def getGroups(word):
            groups = []
            i = 0
            while i < len(word):
                j = i
                while j < len(word) and word[j] == word[i]:
                    j += 1
                groups.append((word[i], j - i))
                i = j
            return groups
        
        sGroups = getGroups(s)
        result = 0
        
        for word in words:
            wGroups = getGroups(word)
            if len(sGroups) != len(wGroups):
                continue
            valid = True
            for (sc, scount), (wc, wcount) in zip(sGroups, wGroups):
                if sc != wc:
                    valid = False
                    break
                if scount < wcount or (scount < 3 and scount != wcount):
                    valid = False
                    break
            if valid:
                result += 1
        
        return result
