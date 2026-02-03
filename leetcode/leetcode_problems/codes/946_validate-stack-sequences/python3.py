"""
Problem: Validate Stack Sequences
Difficulty: Medium
Tags: array, stack

Approach: Simulate stack operations - push elements and pop when matching
Time Complexity: O(n)
Space Complexity: O(n) for stack
"""

class Solution:
    def validateStackSequences(self, pushed: List[int], popped: List[int]) -> bool:
        stack = []
        pop_idx = 0
        
        for num in pushed:
            stack.append(num)
            while stack and stack[-1] == popped[pop_idx]:
                stack.pop()
                pop_idx += 1
        
        return len(stack) == 0