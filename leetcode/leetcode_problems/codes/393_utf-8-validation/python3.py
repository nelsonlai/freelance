"""
Problem: UTF-8 Validation
Difficulty: Medium
Tags: array

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def validUtf8(self, data: List[int]) -> bool:
        i = 0
        while i < len(data):
            byte = data[i]
            
            if byte >> 7 == 0:
                i += 1
            elif byte >> 5 == 0b110:
                if i + 1 >= len(data) or data[i + 1] >> 6 != 0b10:
                    return False
                i += 2
            elif byte >> 4 == 0b1110:
                if i + 2 >= len(data) or data[i + 1] >> 6 != 0b10 or data[i + 2] >> 6 != 0b10:
                    return False
                i += 3
            elif byte >> 3 == 0b11110:
                if i + 3 >= len(data) or data[i + 1] >> 6 != 0b10 or data[i + 2] >> 6 != 0b10 or data[i + 3] >> 6 != 0b10:
                    return False
                i += 4
            else:
                return False
        
        return True