class Solution:
    def boldWords(self, words: List[str], s: str) -> str:
        n = len(s)
        bold = [False] * n
        
        for word in words:
            start = 0
            while True:
                idx = s.find(word, start)
                if idx == -1:
                    break
                for i in range(idx, idx + len(word)):
                    bold[i] = True
                start = idx + 1
        
        result = []
        for i in range(n):
            if bold[i] and (i == 0 or not bold[i - 1]):
                result.append("<b>")
            result.append(s[i])
            if bold[i] and (i == n - 1 or not bold[i + 1]):
                result.append("</b>")
        
        return ''.join(result)
