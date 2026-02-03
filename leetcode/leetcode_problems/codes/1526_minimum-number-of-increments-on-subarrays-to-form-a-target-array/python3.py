"""
Problem: Minimum Number of Increments on Subarrays to Form a Target Array
Difficulty: Hard
Tags: array, dp, greedy, stack

Approach: Greedy - operations needed equals sum of positive differences between consecutive elements
Time Complexity: O(n) where n is length of target
Space Complexity: O(1)
"""

class Solution:
    def minNumberOperations(self, target: List[int]) -> int:
        result = target[0]
        for i in range(1, len(target)):
            if target[i] > target[i-1]:
                result += target[i] - target[i-1]
        return result