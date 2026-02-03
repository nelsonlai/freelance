"""
Problem: Pairs of Songs With Total Durations Divisible by 60
Difficulty: Medium
Tags: array, hash

Approach: Count remainders modulo 60, find pairs that sum to 60 or 0
Time Complexity: O(n)
Space Complexity: O(60) = O(1)
"""

from collections import defaultdict

class Solution:
    def numPairsDivisibleBy60(self, time: List[int]) -> int:
        count = defaultdict(int)
        result = 0
        
        for t in time:
            remainder = t % 60
            complement = (60 - remainder) % 60
            result += count[complement]
            count[remainder] += 1
        
        return result