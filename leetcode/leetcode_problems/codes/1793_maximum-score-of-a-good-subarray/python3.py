"""
Problem: Maximum Score of a Good Subarray
Difficulty: Hard
Tags: array, search, stack, two pointers

Approach: Two pointers - expand from k, always choose larger side
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def maximumScore(self, nums: List[int], k: int) -> int:
        n = len(nums)
        left, right = k, k
        min_val = nums[k]
        result = nums[k]
        
        while left > 0 or right < n - 1:
            if left == 0:
                right += 1
            elif right == n - 1:
                left -= 1
            elif nums[left - 1] < nums[right + 1]:
                right += 1
            else:
                left -= 1
            
            min_val = min(min_val, nums[left], nums[right])
            result = max(result, min_val * (right - left + 1))
        
        return result