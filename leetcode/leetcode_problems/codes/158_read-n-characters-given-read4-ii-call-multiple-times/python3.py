"""
Problem: Read N Characters Given read4 II - Call Multiple Times
Difficulty: Hard
Tags: array

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

# The read4 API is already defined for you.
# def read4(buf4: List[str]) -> int:

class Solution:
    def __init__(self):
        self.buffer = []
        self.buffer_size = 0
        self.buffer_index = 0

    def read(self, buf: List[str], n: int) -> int:
        total_read = 0
        
        while total_read < n:
            if self.buffer_index >= self.buffer_size:
                self.buffer = [''] * 4
                self.buffer_size = read4(self.buffer)
                self.buffer_index = 0
                if self.buffer_size == 0:
                    break
            
            buf[total_read] = self.buffer[self.buffer_index]
            total_read += 1
            self.buffer_index += 1
        
        return total_read