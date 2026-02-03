"""
Problem: Longest Word in Dictionary through Deleting
Difficulty: Medium
Tags: array, string, graph, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def findLongestWord(self, s: str, dictionary: List[str]) -> str:
        def is_subsequence(word, s):
            i = 0
            for char in s:
                if i < len(word) and word[i] == char:
                    i += 1
            return i == len(word)
        
        dictionary.sort(key=lambda x: (-len(x), x))
        
        for word in dictionary:
            if is_subsequence(word, s):
                return word
        
        return ""