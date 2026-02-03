"""
Problem: Parsing A Boolean Expression
Difficulty: Hard
Tags: string, stack

Approach: Use stack to parse nested expressions, evaluate operators
Time Complexity: O(n) where n is expression length
Space Complexity: O(n) for stack
"""

class Solution:
    def parseBoolExpr(self, expression: str) -> bool:
        stack = []
        
        for char in expression:
            if char == ',':
                continue
            if char != ')':
                stack.append(char)
            else:
                operands = []
                while stack[-1] != '(':
                    operands.append(stack.pop())
                stack.pop()  # Remove '('
                operator = stack.pop()
                
                if operator == '!':
                    result = not operands[0]
                elif operator == '&':
                    result = all(operands)
                else:  # '|'
                    result = any(operands)
                
                stack.append(result)
        
        return stack[0]