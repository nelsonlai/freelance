"""
Problem: Solve the Equation
Difficulty: Medium
Tags: string, math

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

import re

class Solution:
    def solveEquation(self, equation: str) -> str:
        left, right = equation.split('=')
        
        def parse_side(side):
            side = side.replace('+', ' +').replace('-', ' -')
            if side[0] != '-' and side[0] != '+':
                side = '+' + side
            tokens = side.split()
            
            coeff = 0
            const = 0
            
            for token in tokens:
                if 'x' in token:
                    num = token.replace('x', '').replace('+', '').replace('-', '')
                    if not num:
                        num = '1'
                    if token[0] == '-':
                        coeff -= int(num)
                    else:
                        coeff += int(num)
                else:
                    if token[0] == '-':
                        const -= int(token[1:])
                    else:
                        const += int(token[1:])
            
            return coeff, const
        
        left_coeff, left_const = parse_side(left)
        right_coeff, right_const = parse_side(right)
        
        coeff = left_coeff - right_coeff
        const = right_const - left_const
        
        if coeff == 0:
            if const == 0:
                return "Infinite solutions"
            else:
                return "No solution"
        
        return f"x={const // coeff}"