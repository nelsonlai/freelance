"""
Problem: Rearrange Spaces Between Words
Difficulty: Easy
Tags: string

Approach: Count spaces and words, distribute spaces evenly between words
Time Complexity: O(n) where n is length of text
Space Complexity: O(n) for result
"""

class Solution:
    def reorderSpaces(self, text: str) -> str:
        words = text.split()
        total_spaces = text.count(' ')
        
        if len(words) == 1:
            return words[0] + ' ' * total_spaces
        
        spaces_between = total_spaces // (len(words) - 1)
        spaces_remaining = total_spaces % (len(words) - 1)
        
        return (' ' * spaces_between).join(words) + ' ' * spaces_remaining