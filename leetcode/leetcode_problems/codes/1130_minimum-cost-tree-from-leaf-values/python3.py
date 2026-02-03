"""
Problem: Minimum Cost Tree From Leaf Values
Difficulty: Medium
Tags: array, tree, dp, greedy, stack

Approach: Greedy with stack - always merge smallest adjacent pairs
Time Complexity: O(n) where n is the length of arr
Space Complexity: O(n) for stack
"""

class Solution:
    def mctFromLeafValues(self, arr: List[int]) -> int:
        stack = [float('inf')]
        result = 0
        
        for num in arr:
            while stack[-1] <= num:
                mid = stack.pop()
                result += mid * min(stack[-1], num)
            stack.append(num)
        
        while len(stack) > 2:
            result += stack.pop() * stack[-1]
        
        return result