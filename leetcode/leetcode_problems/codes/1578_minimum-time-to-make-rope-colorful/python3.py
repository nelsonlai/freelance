"""
Problem: Minimum Time to Make Rope Colorful
Difficulty: Medium
Tags: array, string, dp, greedy

Approach: For consecutive same colors, keep the one with max time, remove others
Time Complexity: O(n) where n is length of colors
Space Complexity: O(1)
"""

class Solution:
    def minCost(self, colors: str, neededTime: List[int]) -> int:
        result = 0
        i = 0
        n = len(colors)
        
        while i < n:
            j = i
            total = 0
            max_time = 0
            
            while j < n and colors[j] == colors[i]:
                total += neededTime[j]
                max_time = max(max_time, neededTime[j])
                j += 1
            
            if j > i + 1:
                result += total - max_time
            
            i = j
        
        return result