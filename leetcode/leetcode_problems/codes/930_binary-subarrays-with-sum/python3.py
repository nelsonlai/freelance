"""
Problem: Binary Subarrays With Sum
Difficulty: Medium
Tags: array, hash

Approach: Use prefix sum with hash map to count subarrays with sum equal to goal
Time Complexity: O(n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def numSubarraysWithSum(self, nums: List[int], goal: int) -> int:
        count = {0: 1}
        prefix_sum = 0
        result = 0
        
        for num in nums:
            prefix_sum += num
            # Count subarrays ending at current position with sum = goal
            if prefix_sum - goal in count:
                result += count[prefix_sum - goal]
            count[prefix_sum] = count.get(prefix_sum, 0) + 1
        
        return result