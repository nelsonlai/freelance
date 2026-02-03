"""
Problem: Minimum Number of Operations to Move All Balls to Each Box
Difficulty: Medium
Tags: array, string, prefix sum

Approach: Calculate operations from left and right separately
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def minOperations(self, boxes: str) -> List[int]:
        n = len(boxes)
        result = [0] * n
        
        # Count operations from left
        balls = 0
        operations = 0
        for i in range(n):
            result[i] += operations
            if boxes[i] == '1':
                balls += 1
            operations += balls
        
        # Count operations from right
        balls = 0
        operations = 0
        for i in range(n - 1, -1, -1):
            result[i] += operations
            if boxes[i] == '1':
                balls += 1
            operations += balls
        
        return result