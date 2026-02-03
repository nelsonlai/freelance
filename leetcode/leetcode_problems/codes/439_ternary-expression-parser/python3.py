"""
Problem: Ternary Expression Parser
Difficulty: Medium
Tags: string, stack

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def parseTernary(self, expression: str) -> str:
        stack = []
        i = len(expression) - 1
        
        while i >= 0:
            if expression[i] == '?':
                condition = stack.pop()
                true_val = stack.pop()
                false_val = stack.pop()
                stack.append(true_val if condition == 'T' else false_val)
                i -= 1
            elif expression[i] != ':':
                stack.append(expression[i])
            i -= 1
        
        return stack[0]