"""
Problem: Student Attendance Record I
Difficulty: Easy
Tags: string

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def checkRecord(self, s: str) -> bool:
        count_a = 0
        count_l = 0
        
        for char in s:
            if char == 'A':
                count_a += 1
                if count_a >= 2:
                    return False
                count_l = 0
            elif char == 'L':
                count_l += 1
                if count_l >= 3:
                    return False
            else:
                count_l = 0
        
        return True