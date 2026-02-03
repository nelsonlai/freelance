"""
Problem: Find Good Days to Rob the Bank
Difficulty: Medium
Tags: array, dp, prefix sum

Approach: Calculate non-increasing days before and non-decreasing days after each day
Time Complexity: O(n) where n is array length
Space Complexity: O(n)
"""

class Solution:
    def goodDaysToRobBank(self, security: List[int], time: int) -> List[int]:
        n = len(security)
        
        # non_increasing[i] = number of consecutive non-increasing days before i
        non_increasing = [0] * n
        for i in range(1, n):
            if security[i] <= security[i - 1]:
                non_increasing[i] = non_increasing[i - 1] + 1
            else:
                non_increasing[i] = 0
        
        # non_decreasing[i] = number of consecutive non-decreasing days after i
        non_decreasing = [0] * n
        for i in range(n - 2, -1, -1):
            if security[i] <= security[i + 1]:
                non_decreasing[i] = non_decreasing[i + 1] + 1
            else:
                non_decreasing[i] = 0
        
        result = []
        for i in range(n):
            if non_increasing[i] >= time and non_decreasing[i] >= time:
                result.append(i)
        
        return result