"""
Problem: How Many Apples Can You Put into the Basket
Difficulty: Easy
Tags: array, greedy, sort

Approach: Sort weights, greedily add smallest apples first until limit reached
Time Complexity: O(n log n) where n is number of apples
Space Complexity: O(1)
"""

class Solution:
    def maxNumberOfApples(self, weight: List[int]) -> int:
        weight.sort()
        total = 0
        count = 0
        
        for w in weight:
            if total + w <= 5000:
                total += w
                count += 1
            else:
                break
        
        return count