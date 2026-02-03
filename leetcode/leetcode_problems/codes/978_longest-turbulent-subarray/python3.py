"""
Problem: Longest Turbulent Subarray
Difficulty: Medium
Tags: array, dp

Approach: DP - track length of turbulent subarray ending at each position
Time Complexity: O(n)
Space Complexity: O(1)
"""

class Solution:
    def maxTurbulenceSize(self, arr: List[int]) -> int:
        if len(arr) == 1:
            return 1
        
        max_len = 1
        up = down = 1
        
        for i in range(1, len(arr)):
            if arr[i] > arr[i-1]:
                up = down + 1
                down = 1
            elif arr[i] < arr[i-1]:
                down = up + 1
                up = 1
            else:
                up = down = 1
            
            max_len = max(max_len, up, down)
        
        return max_len