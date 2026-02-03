"""
Problem: Maximum Erasure Value
Difficulty: Medium
Tags: array, hash, sliding window

Approach: Sliding window - find longest subarray with unique elements, track max sum
Time Complexity: O(n) where n is length
Space Complexity: O(n) for hash set
"""

class Solution:
    def maximumUniqueSubarray(self, nums: List[int]) -> int:
        seen = set()
        left = 0
        current_sum = 0
        max_sum = 0
        
        for right in range(len(nums)):
            while nums[right] in seen:
                seen.remove(nums[left])
                current_sum -= nums[left]
                left += 1
            
            seen.add(nums[right])
            current_sum += nums[right]
            max_sum = max(max_sum, current_sum)
        
        return max_sum