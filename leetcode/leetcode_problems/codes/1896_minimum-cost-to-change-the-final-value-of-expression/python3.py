"""
Problem: Minimum Cost to Change the Final Value of Expression
Difficulty: Hard
Tags: string, tree, dp, math, stack

Approach: Parse expression tree, DP to track min cost to flip value
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def minOperationsToFlip(self, expression: str) -> int:
        stack = []
        ops = []
        
        for char in expression:
            if char == '(':
                stack.append(char)
            elif char == ')':
                while stack and stack[-1] != '(':
                    ops.append(stack.pop())
                stack.pop()
            elif char in '&|':
                while stack and stack[-1] in '&|':
                    ops.append(stack.pop())
                stack.append(char)
            else:  # digit
                ops.append(char)
        
        while stack:
            ops.append(stack.pop())
        
        # Evaluate with DP: (value, min_cost_to_flip)
        eval_stack = []
        
        for op in ops:
            if op == '&':
                b = eval_stack.pop()
                a = eval_stack.pop()
                if a[0] and b[0]:  # 1 & 1 = 1
                    cost = min(a[1], b[1]) + 1
                    eval_stack.append((1, cost))
                elif not a[0] and not b[0]:  # 0 & 0 = 0
                    cost = min(a[1], b[1]) + 1
                    eval_stack.append((0, cost))
                else:  # 1 & 0 = 0
                    eval_stack.append((0, 1))
            elif op == '|':
                b = eval_stack.pop()
                a = eval_stack.pop()
                if a[0] and b[0]:  # 1 | 1 = 1
                    eval_stack.append((1, 1))
                elif not a[0] and not b[0]:  # 0 | 0 = 0
                    cost = min(a[1], b[1]) + 1
                    eval_stack.append((0, cost))
                else:  # 1 | 0 = 1
                    cost = min(a[1], b[1]) + 1
                    eval_stack.append((1, cost))
            else:  # digit
                val = int(op)
                eval_stack.append((val, 1))
        
        return eval_stack[0][1] if eval_stack[0][0] == 1 else eval_stack[0][1]