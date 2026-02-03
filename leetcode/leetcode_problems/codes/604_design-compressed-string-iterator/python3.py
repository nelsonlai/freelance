"""
Problem: Design Compressed String Iterator
Difficulty: Easy
Tags: array, string

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

import re

class StringIterator:
    def __init__(self, compressedString: str):
        self.chars = []
        self.counts = []
        
        pairs = re.findall(r'([a-zA-Z])(\d+)', compressedString)
        for char, count in pairs:
            self.chars.append(char)
            self.counts.append(int(count))
        
        self.index = 0

    def next(self) -> str:
        if not self.hasNext():
            return ' '
        
        result = self.chars[self.index]
        self.counts[self.index] -= 1
        
        if self.counts[self.index] == 0:
            self.index += 1
        
        return result

    def hasNext(self) -> bool:
        return self.index < len(self.chars) and self.counts[self.index] > 0