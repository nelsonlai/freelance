"""
Problem: Water Bottles
Difficulty: Easy
Tags: math

Approach: Simulate drinking and exchanging bottles
Time Complexity: O(log(numBottles))
Space Complexity: O(1)
"""

class Solution:
    def numWaterBottles(self, numBottles: int, numExchange: int) -> int:
        total = numBottles
        empty = numBottles
        
        while empty >= numExchange:
            new_bottles = empty // numExchange
            total += new_bottles
            empty = empty % numExchange + new_bottles
        
        return total