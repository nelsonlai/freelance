"""
Problem: Single-Row Keyboard
Difficulty: Easy
Tags: string, hash

Approach: Create position map, calculate cumulative distance
Time Complexity: O(n) where n is the length of word
Space Complexity: O(1) since keyboard has 26 characters
"""

class Solution:
    def calculateTime(self, keyboard: str, word: str) -> int:
        pos_map = {char: i for i, char in enumerate(keyboard)}
        total_time = 0
        current_pos = 0
        
        for char in word:
            target_pos = pos_map[char]
            total_time += abs(target_pos - current_pos)
            current_pos = target_pos
        
        return total_time