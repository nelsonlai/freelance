"""
Problem: Minimum Number of K Consecutive Bit Flips
Difficulty: Hard
Tags: array, queue

Approach: Greedy with difference array - flip when needed, track flip effect
Time Complexity: O(n)
Space Complexity: O(n) for difference array
"""

class Solution:
    def minKBitFlips(self, nums: List[int], k: int) -> int:
        n = len(nums)
        flip_count = 0
        flip_diff = [0] * (n + 1)
        current_flips = 0
        
        for i in range(n):
            current_flips += flip_diff[i]
            
            if (nums[i] + current_flips) % 2 == 0:
                if i + k > n:
                    return -1
                flip_count += 1
                current_flips += 1
                flip_diff[i + k] -= 1
        
        return flip_count