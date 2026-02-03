"""
Problem: Paint House II
Difficulty: Hard
Tags: array, dp

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def minCostII(self, costs: List[List[int]]) -> int:
        if not costs or not costs[0]:
            return 0
        
        n, k = len(costs), len(costs[0])
        
        for i in range(1, n):
            min1 = min2 = float('inf')
            min1_idx = -1
            
            for j in range(k):
                if costs[i - 1][j] < min1:
                    min2 = min1
                    min1 = costs[i - 1][j]
                    min1_idx = j
                elif costs[i - 1][j] < min2:
                    min2 = costs[i - 1][j]
            
            for j in range(k):
                if j == min1_idx:
                    costs[i][j] += min2
                else:
                    costs[i][j] += min1
        
        return min(costs[-1])