"""
Problem: Max Value of Equation
Difficulty: Hard
Tags: array, sort, queue, heap

Approach: Use deque to maintain yi - xi in decreasing order, maximize yi + xi + (yj - xj)
Time Complexity: O(n) where n is number of points
Space Complexity: O(n) for deque
"""

from collections import deque

class Solution:
    def findMaxValueOfEquation(self, points: List[List[int]], k: int) -> int:
        dq = deque()
        max_value = float('-inf')
        
        for x, y in points:
            while dq and x - dq[0][1] > k:
                dq.popleft()
            
            if dq:
                max_value = max(max_value, x + y + dq[0][0])
            
            while dq and dq[-1][0] <= y - x:
                dq.pop()
            
            dq.append((y - x, x))
        
        return max_value