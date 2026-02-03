"""
Problem: Design Parking System
Difficulty: Easy
Tags: design, simulation

Approach: Track available spaces for each car type
Time Complexity: O(1) for addCar
Space Complexity: O(1)
"""

class ParkingSystem:

    def __init__(self, big: int, medium: int, small: int):
        self.spaces = [big, medium, small]

    def addCar(self, carType: int) -> bool:
        if self.spaces[carType - 1] > 0:
            self.spaces[carType - 1] -= 1
            return True
        return False