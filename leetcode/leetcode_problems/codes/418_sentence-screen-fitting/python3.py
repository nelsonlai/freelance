"""
Problem: Sentence Screen Fitting
Difficulty: Medium
Tags: array, string, dp

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def wordsTyping(self, sentence: List[str], rows: int, cols: int) -> int:
        s = ' '.join(sentence) + ' '
        start = 0
        n = len(s)
        
        for _ in range(rows):
            start += cols
            if s[start % n] == ' ':
                start += 1
            else:
                while start > 0 and s[(start - 1) % n] != ' ':
                    start -= 1
        
        return start // n