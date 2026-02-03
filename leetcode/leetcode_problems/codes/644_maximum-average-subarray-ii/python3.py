"""
Problem: Maximum Average Subarray II
Difficulty: Hard
Tags: array, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def findMaxAverage(self, nums: List[int], k: int) -> float:
        def can_achieve(target):
            prefix = [0]
            min_prefix = 0
            
            for i in range(len(nums)):
                prefix.append(prefix[-1] + nums[i] - target)
                if i >= k - 1:
                    if prefix[-1] >= min_prefix:
                        return True
                    min_prefix = min(min_prefix, prefix[i - k + 2])
            
            return False
        
        left, right = min(nums), max(nums)
        
        while right - left > 1e-5:
            mid = (left + right) / 2
            if can_achieve(mid):
                left = mid
            else:
                right = mid
        
        return left