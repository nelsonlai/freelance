class Solution:
    def longestWord(self, words: List[str]) -> str:
        words.sort()
        wordSet = set(words)
        result = ""
        
        for word in words:
            if len(word) > len(result) or (len(word) == len(result) and word < result):
                if all(word[:i] in wordSet for i in range(1, len(word))):
                    result = word
        
        return result
