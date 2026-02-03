"""
Problem: Number of Longest Increasing Subsequence
Difficulty: Medium
Tags: array, tree, dp

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def findNumberOfLIS(self, nums: List[int]) -> int:
        n = len(nums)
        lengths = [1] * n
        counts = [1] * n
        
        for i in range(n):
            for j in range(i):
                if nums[j] < nums[i]:
                    if lengths[j] + 1 > lengths[i]:
                        lengths[i] = lengths[j] + 1
                        counts[i] = counts[j]
                    elif lengths[j] + 1 == lengths[i]:
                        counts[i] += counts[j]
        
        max_length = max(lengths)
        return sum(counts[i] for i in range(n) if lengths[i] == max_length)