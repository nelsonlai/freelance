"""
Problem: Valid Word Square
Difficulty: Easy
Tags: array, string

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def validWordSquare(self, words: List[str]) -> bool:
        n = len(words)
        for i in range(n):
            for j in range(len(words[i])):
                if j >= n or i >= len(words[j]) or words[i][j] != words[j][i]:
                    return False
        return True