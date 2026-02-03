"""
Problem: Car Fleet II
Difficulty: Hard
Tags: array, math, stack, monotonic stack

Approach: Use stack - process from right, calculate collision time, maintain stack of cars that haven't collided
Time Complexity: O(n) where n is number of cars
Space Complexity: O(n) for stack
"""

class Solution:
    def getCollisionTimes(self, cars: List[List[int]]) -> List[float]:
        n = len(cars)
        result = [-1.0] * n
        stack = []
        
        for i in range(n - 1, -1, -1):
            pos, speed = cars[i]
            
            # Remove cars that will never collide with current car
            while stack:
                j = stack[-1]
                j_pos, j_speed = cars[j]
                
                # If current car is slower, it will never catch up
                if speed <= j_speed:
                    stack.pop()
                    continue
                
                # Calculate collision time
                collision_time = (j_pos - pos) / (speed - j_speed)
                
                # If collision happens after j's collision, j will be gone
                if result[j] > 0 and collision_time > result[j]:
                    stack.pop()
                    continue
                
                result[i] = collision_time
                break
            
            stack.append(i)
        
        return result