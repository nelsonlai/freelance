"""
Problem: Different Ways to Add Parentheses
Difficulty: Medium
Tags: string, dp, math

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def diffWaysToCompute(self, expression: str) -> List[int]:
        if expression.isdigit():
            return [int(expression)]
        
        result = []
        for i, char in enumerate(expression):
            if char in '+-*':
                left = self.diffWaysToCompute(expression[:i])
                right = self.diffWaysToCompute(expression[i+1:])
                
                for l in left:
                    for r in right:
                        if char == '+':
                            result.append(l + r)
                        elif char == '-':
                            result.append(l - r)
                        else:
                            result.append(l * r)
        
        return result