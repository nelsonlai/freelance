"""
Problem: Maximum Length of Pair Chain
Difficulty: Medium
Tags: array, dp, greedy, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def findLongestChain(self, pairs: List[List[int]]) -> int:
        pairs.sort(key=lambda x: x[1])
        count = 0
        end = float('-inf')
        
        for pair in pairs:
            if pair[0] > end:
                count += 1
                end = pair[1]
        
        return count