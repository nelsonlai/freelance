"""
Problem: Minimum Swaps to Group All 1's Together
Difficulty: Medium
Tags: array

Approach: Sliding window - count total 1s, find window with max 1s, swaps = total - max_in_window
Time Complexity: O(n) where n is the length of data
Space Complexity: O(1)
"""

class Solution:
    def minSwaps(self, data: List[int]) -> int:
        total_ones = sum(data)
        if total_ones == 0:
            return 0
        
        max_ones_in_window = 0
        current_ones = 0
        
        for i in range(len(data)):
            current_ones += data[i]
            if i >= total_ones:
                current_ones -= data[i - total_ones]
            max_ones_in_window = max(max_ones_in_window, current_ones)
        
        return total_ones - max_ones_in_window