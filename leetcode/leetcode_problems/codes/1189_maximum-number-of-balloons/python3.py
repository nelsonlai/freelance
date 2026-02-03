"""
Problem: Maximum Number of Balloons
Difficulty: Easy
Tags: string, hash

Approach: Count character frequencies, calculate how many "balloon" can be formed
Time Complexity: O(n) where n is the length of text
Space Complexity: O(1) since at most 26 characters
"""

class Solution:
    def maxNumberOfBalloons(self, text: str) -> int:
        from collections import Counter
        
        char_count = Counter(text)
        balloon_count = {
            'b': 1,
            'a': 1,
            'l': 2,
            'o': 2,
            'n': 1
        }
        
        max_count = float('inf')
        for char, needed in balloon_count.items():
            available = char_count.get(char, 0)
            max_count = min(max_count, available // needed)
        
        return max_count if max_count != float('inf') else 0