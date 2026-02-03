"""
Problem: Minimum Number of Days to Make m Bouquets
Difficulty: Medium
Tags: array, search

Approach: Binary search on days, check if can make m bouquets
Time Complexity: O(n * log(max(bloomDay)))
Space Complexity: O(1)
"""

class Solution:
    def minDays(self, bloomDay: List[int], m: int, k: int) -> int:
        if m * k > len(bloomDay):
            return -1
        
        def canMake(days):
            bouquets = 0
            flowers = 0
            for day in bloomDay:
                if day <= days:
                    flowers += 1
                    if flowers == k:
                        bouquets += 1
                        flowers = 0
                else:
                    flowers = 0
            return bouquets >= m
        
        left, right = min(bloomDay), max(bloomDay)
        while left < right:
            mid = (left + right) // 2
            if canMake(mid):
                right = mid
            else:
                left = mid + 1
        
        return left