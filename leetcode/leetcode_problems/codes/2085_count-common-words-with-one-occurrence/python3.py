"""
Problem: Count Common Words With One Occurrence
Difficulty: Easy
Tags: array, string, hash

Approach: Count frequencies in both arrays, find words with count 1 in both
Time Complexity: O(n + m) where n, m are array lengths
Space Complexity: O(n + m)
"""

from collections import Counter

class Solution:
    def countWords(self, words1: List[str], words2: List[str]) -> int:
        count1 = Counter(words1)
        count2 = Counter(words2)
        
        result = 0
        for word in count1:
            if count1[word] == 1 and count2.get(word, 0) == 1:
                result += 1
        
        return result