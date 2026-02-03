"""
Problem: Make Sum Divisible by P
Difficulty: Medium
Tags: array, hash

Approach: Find minimum subarray with sum ≡ total_sum (mod p), use prefix sum with hash map
Time Complexity: O(n) where n is length of nums
Space Complexity: O(p) for hash map
"""

class Solution:
    def minSubarray(self, nums: List[int], p: int) -> int:
        total = sum(nums) % p
        if total == 0:
            return 0
        
        prefix = 0
        last_pos = {0: -1}
        result = len(nums)
        
        for i, num in enumerate(nums):
            prefix = (prefix + num) % p
            target = (prefix - total) % p
            
            if target in last_pos:
                result = min(result, i - last_pos[target])
            
            last_pos[prefix] = i
        
        return result if result < len(nums) else -1