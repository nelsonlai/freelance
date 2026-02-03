"""
Problem: Basic Calculator
Difficulty: Hard
Tags: string, math, stack

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def calculate(self, s: str) -> int:
        stack = []
        num = 0
        sign = 1
        result = 0
        
        for char in s:
            if char.isdigit():
                num = num * 10 + int(char)
            elif char == '+':
                result += sign * num
                num = 0
                sign = 1
            elif char == '-':
                result += sign * num
                num = 0
                sign = -1
            elif char == '(':
                stack.append(result)
                stack.append(sign)
                result = 0
                sign = 1
            elif char == ')':
                result += sign * num
                num = 0
                result *= stack.pop()
                result += stack.pop()
        
        return result + sign * num