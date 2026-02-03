"""
Problem: Can Place Flowers
Difficulty: Easy
Tags: array, greedy

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def canPlaceFlowers(self, flowerbed: List[int], n: int) -> bool:
        count = 0
        for i in range(len(flowerbed)):
            if flowerbed[i] == 0:
                left_empty = (i == 0) or (flowerbed[i-1] == 0)
                right_empty = (i == len(flowerbed) - 1) or (flowerbed[i+1] == 0)
                
                if left_empty and right_empty:
                    flowerbed[i] = 1
                    count += 1
                    if count >= n:
                        return True
        
        return count >= n