"""
Problem: Partitioning Into Minimum Number Of Deci-Binary Numbers
Difficulty: Medium
Tags: string, greedy

Approach: Answer is the maximum digit in the string
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def minPartitions(self, n: str) -> int:
        return int(max(n))