"""
Problem: Complex Number Multiplication
Difficulty: Medium
Tags: string, math

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def complexNumberMultiply(self, num1: str, num2: str) -> str:
        def parse_complex(num):
            parts = num[:-1].split('+')
            return int(parts[0]), int(parts[1])
        
        a1, b1 = parse_complex(num1)
        a2, b2 = parse_complex(num2)
        
        real = a1 * a2 - b1 * b2
        imag = a1 * b2 + a2 * b1
        
        return f"{real}+{imag}i"