"""
Problem: 132 Pattern
Difficulty: Medium
Tags: array, search, stack

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def find132pattern(self, nums: List[int]) -> bool:
        stack = []
        third = float('-inf')
        
        for num in reversed(nums):
            if num < third:
                return True
            while stack and stack[-1] < num:
                third = stack.pop()
            stack.append(num)
        
        return False