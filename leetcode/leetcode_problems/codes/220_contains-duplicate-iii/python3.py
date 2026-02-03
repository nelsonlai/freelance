"""
Problem: Contains Duplicate III
Difficulty: Hard
Tags: array, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def containsNearbyAlmostDuplicate(self, nums: List[int], indexDiff: int, valueDiff: int) -> bool:
        if valueDiff < 0:
            return False
        
        buckets = {}
        bucket_size = valueDiff + 1
        
        for i, num in enumerate(nums):
            bucket_id = num // bucket_size if num >= 0 else (num + 1) // bucket_size - 1
            
            if bucket_id in buckets:
                return True
            
            if bucket_id - 1 in buckets and abs(num - buckets[bucket_id - 1]) <= valueDiff:
                return True
            
            if bucket_id + 1 in buckets and abs(num - buckets[bucket_id + 1]) <= valueDiff:
                return True
            
            buckets[bucket_id] = num
            
            if i >= indexDiff:
                old_bucket = nums[i - indexDiff] // bucket_size if nums[i - indexDiff] >= 0 else (nums[i - indexDiff] + 1) // bucket_size - 1
                del buckets[old_bucket]
        
        return False