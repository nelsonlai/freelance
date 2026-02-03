"""
Problem: Max Difference You Can Get From Changing an Integer
Difficulty: Medium
Tags: greedy, math

Approach: For max, replace first non-9 digit with 9. For min, replace first non-0/1 digit with 0/1
Time Complexity: O(log num)
Space Complexity: O(log num)
"""

class Solution:
    def maxDiff(self, num: int) -> int:
        s = str(num)
        
        # Find max: replace first non-9 with 9
        max_str = s
        for char in s:
            if char != '9':
                max_str = s.replace(char, '9')
                break
        
        # Find min: replace first non-0/1 with 0 (if not first) or 1 (if first)
        min_str = s
        if s[0] != '1':
            min_str = s.replace(s[0], '1')
        else:
            for char in s[1:]:
                if char not in '01':
                    min_str = s.replace(char, '0')
                    break
        
        return int(max_str) - int(min_str)