"""
Problem: Number Of Rectangles That Can Form The Largest Square
Difficulty: Easy
Tags: array

Approach: Find minimum side for each rectangle, count rectangles with max minimum side
Time Complexity: O(n) where n is number of rectangles
Space Complexity: O(1)
"""

class Solution:
    def countGoodRectangles(self, rectangles: List[List[int]]) -> int:
        max_side = 0
        count = 0
        
        for l, w in rectangles:
            side = min(l, w)
            if side > max_side:
                max_side = side
                count = 1
            elif side == max_side:
                count += 1
        
        return count