"""
Problem: Longest Well-Performing Interval
Difficulty: Medium
Tags: array, hash, stack

Approach: Convert to prefix sum problem (1 for >8, -1 for <=8), find longest subarray with sum > 0
Time Complexity: O(n) where n is the length of hours
Space Complexity: O(n) for hash map
"""

class Solution:
    def longestWPI(self, hours: List[int]) -> int:
        prefix_sum = 0
        prefix_map = {}
        max_len = 0
        
        for i, hour in enumerate(hours):
            prefix_sum += 1 if hour > 8 else -1
            
            if prefix_sum > 0:
                max_len = i + 1
            else:
                if prefix_sum - 1 in prefix_map:
                    max_len = max(max_len, i - prefix_map[prefix_sum - 1])
                if prefix_sum not in prefix_map:
                    prefix_map[prefix_sum] = i
        
        return max_len