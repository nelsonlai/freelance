"""
Problem: Minimum Time to Type Word Using Special Typewriter
Difficulty: Easy
Tags: string, greedy

Approach: Calculate min distance between consecutive characters (clockwise or counterclockwise)
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def minTimeToType(self, word: str) -> int:
        time = 0
        current = 'a'
        
        for char in word:
            diff = abs(ord(char) - ord(current))
            time += min(diff, 26 - diff) + 1  # +1 for typing
            current = char
        
        return time