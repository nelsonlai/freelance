"""
Problem: Kth Smallest Subarray Sum
Difficulty: Medium
Tags: array, search, binary search

Approach: Binary search on answer, count subarrays with sum <= target
Time Complexity: O(n log(sum)) where sum is total sum
Space Complexity: O(1)
"""

class Solution:
    def kthSmallestSubarraySum(self, nums: List[int], k: int) -> int:
        def countSubarrays(target):
            count = 0
            left = 0
            current_sum = 0
            
            for right in range(len(nums)):
                current_sum += nums[right]
                while current_sum > target:
                    current_sum -= nums[left]
                    left += 1
                count += right - left + 1
            
            return count
        
        left, right = min(nums), sum(nums)
        result = right
        
        while left <= right:
            mid = (left + right) // 2
            if countSubarrays(mid) >= k:
                result = mid
                right = mid - 1
            else:
                left = mid + 1
        
        return result