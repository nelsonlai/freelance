"""
Problem: Number of Pairs of Interchangeable Rectangles
Difficulty: Medium
Tags: array, math, hash

Approach: Count rectangles with same aspect ratio, calculate pairs using n*(n-1)/2
Time Complexity: O(n) where n is number of rectangles
Space Complexity: O(n) for hash map
"""

from collections import defaultdict

class Solution:
    def interchangeableRectangles(self, rectangles: List[List[int]]) -> int:
        ratio_count = defaultdict(int)
        
        for w, h in rectangles:
            # Use GCD to normalize ratio
            g = self.gcd(w, h)
            ratio = (w // g, h // g)
            ratio_count[ratio] += 1
        
        result = 0
        for count in ratio_count.values():
            if count > 1:
                result += count * (count - 1) // 2
        
        return result
    
    def gcd(self, a, b):
        while b:
            a, b = b, a % b
        return a