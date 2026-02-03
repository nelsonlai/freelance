from collections import Counter

class Solution:
    def wordSubsets(self, words1: List[str], words2: List[str]) -> List[str]:
        def get_count(word):
            count = [0] * 26
            for c in word:
                count[ord(c) - ord('a')] += 1
            return count
        
        max_count = [0] * 26
        for word in words2:
            count = get_count(word)
            for i in range(26):
                max_count[i] = max(max_count[i], count[i])
        
        result = []
        for word in words1:
            count = get_count(word)
            if all(count[i] >= max_count[i] for i in range(26)):
                result.append(word)
        
        return result
