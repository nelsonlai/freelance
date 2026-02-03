"""
Problem: Shortest Word Distance
Difficulty: Easy
Tags: array, string

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def shortestDistance(self, wordsDict: List[str], word1: str, word2: str) -> int:
        index1 = index2 = -1
        min_distance = float('inf')
        
        for i, word in enumerate(wordsDict):
            if word == word1:
                index1 = i
                if index2 != -1:
                    min_distance = min(min_distance, abs(index1 - index2))
            elif word == word2:
                index2 = i
                if index1 != -1:
                    min_distance = min(min_distance, abs(index1 - index2))
        
        return min_distance