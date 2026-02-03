"""
Problem: String Compression
Difficulty: Medium
Tags: array, string

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def compress(self, chars: List[str]) -> int:
        write = 0
        read = 0
        
        while read < len(chars):
            char = chars[read]
            count = 0
            
            while read < len(chars) and chars[read] == char:
                read += 1
                count += 1
            
            chars[write] = char
            write += 1
            
            if count > 1:
                for digit in str(count):
                    chars[write] = digit
                    write += 1
        
        return write