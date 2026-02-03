"""
Problem: Remove K Digits
Difficulty: Medium
Tags: string, greedy, stack

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def removeKdigits(self, num: str, k: int) -> str:
        stack = []
        
        for digit in num:
            while stack and k > 0 and stack[-1] > digit:
                stack.pop()
                k -= 1
            stack.append(digit)
        
        while k > 0:
            stack.pop()
            k -= 1
        
        result = ''.join(stack).lstrip('0')
        return result if result else '0'