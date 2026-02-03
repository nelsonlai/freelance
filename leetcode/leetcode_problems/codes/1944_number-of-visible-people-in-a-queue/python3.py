"""
Problem: Number of Visible People in a Queue
Difficulty: Hard
Tags: array, stack, monotonic stack

Approach: Monotonic stack - count people visible to the right
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def canSeePersonsCount(self, heights: List[int]) -> List[int]:
        n = len(heights)
        result = [0] * n
        stack = []
        
        for i in range(n - 1, -1, -1):
            count = 0
            while stack and heights[stack[-1]] < heights[i]:
                stack.pop()
                count += 1
            
            if stack:
                count += 1
            
            result[i] = count
            stack.append(i)
        
        return result