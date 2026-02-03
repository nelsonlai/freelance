"""
Problem: Robot Bounded In Circle
Difficulty: Medium
Tags: string, math

Approach: After one cycle, if robot returns to origin or faces different direction, it's bounded
Time Complexity: O(n) where n is instructions length
Space Complexity: O(1)
"""

class Solution:
    def isRobotBounded(self, instructions: str) -> bool:
        x, y = 0, 0
        dx, dy = 0, 1  # facing north
        
        for instruction in instructions:
            if instruction == 'G':
                x += dx
                y += dy
            elif instruction == 'L':
                dx, dy = -dy, dx
            else:  # 'R'
                dx, dy = dy, -dx
        
        # Bounded if returns to origin or doesn't face north
        return (x == 0 and y == 0) or (dx, dy) != (0, 1)