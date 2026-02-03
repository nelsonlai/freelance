from collections import Counter

class Solution:
    def shortestCompletingWord(self, licensePlate: str, words: List[str]) -> str:
        target = Counter(c.lower() for c in licensePlate if c.isalpha())
        result = None
        
        for word in words:
            wordCount = Counter(word.lower())
            if all(wordCount[c] >= target[c] for c in target):
                if result is None or len(word) < len(result):
                    result = word
        
        return result
