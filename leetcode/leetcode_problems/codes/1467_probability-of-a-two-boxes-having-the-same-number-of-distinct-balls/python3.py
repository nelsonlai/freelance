"""
Problem: Probability of a Two Boxes Having The Same Number of Distinct Balls
Difficulty: Hard
Tags: array, dp, math

Approach: DP with memoization - count ways to split balls with same distinct colors
Time Complexity: O(n * total_balls^2) where n is number of colors
Space Complexity: O(n * total_balls^2) for memo
"""

from functools import lru_cache
import math

class Solution:
    def getProbability(self, balls: List[int]) -> float:
        total = sum(balls)
        n = len(balls)
        
        @lru_cache(None)
        def ways(color, box1_count, box1_colors, box2_count, box2_colors):
            if color == n:
                if box1_count == box2_count and box1_colors == box2_colors:
                    return 1
                return 0
            
            result = 0
            for i in range(balls[color] + 1):
                new_box1 = box1_count + i
                new_box2 = box2_count + (balls[color] - i)
                new_colors1 = box1_colors + (1 if i > 0 else 0)
                new_colors2 = box2_colors + (1 if i < balls[color] else 0)
                
                comb = math.comb(balls[color], i)
                result += comb * ways(color + 1, new_box1, new_colors1, new_box2, new_colors2)
            
            return result
        
        total_ways = ways(0, 0, 0, 0, 0)
        all_ways = math.comb(total, total // 2)
        
        return total_ways / all_ways