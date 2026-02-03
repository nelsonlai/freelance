"""
Problem: Replace Words
Difficulty: Medium
Tags: array, string, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def replaceWords(self, dictionary: List[str], sentence: str) -> str:
        dictionary_set = set(dictionary)
        words = sentence.split()
        
        for i, word in enumerate(words):
            for j in range(1, len(word) + 1):
                if word[:j] in dictionary_set:
                    words[i] = word[:j]
                    break
        
        return ' '.join(words)