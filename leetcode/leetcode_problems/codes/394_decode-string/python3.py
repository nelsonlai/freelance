"""
Problem: Decode String
Difficulty: Medium
Tags: string, stack

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def decodeString(self, s: str) -> str:
        stack = []
        current_string = ""
        current_num = 0
        
        for char in s:
            if char.isdigit():
                current_num = current_num * 10 + int(char)
            elif char == '[':
                stack.append((current_string, current_num))
                current_string = ""
                current_num = 0
            elif char == ']':
                prev_string, num = stack.pop()
                current_string = prev_string + current_string * num
            else:
                current_string += char
        
        return current_string