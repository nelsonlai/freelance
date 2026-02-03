"""
Problem: Powerful Integers
Difficulty: Medium
Tags: math, hash

Approach: Generate all x^i + y^j <= bound, use set to avoid duplicates
Time Complexity: O(log(bound)^2)
Space Complexity: O(log(bound)^2)
"""

class Solution:
    def powerfulIntegers(self, x: int, y: int, bound: int) -> List[int]:
        result = set()
        
        i = 0
        while True:
            x_power = x ** i
            if x_power > bound:
                break
            
            j = 0
            while True:
                y_power = y ** j
                total = x_power + y_power
                if total > bound:
                    break
                result.add(total)
                if y == 1:
                    break
                j += 1
            
            if x == 1:
                break
            i += 1
        
        return list(result)