"""
Problem: Equal Sum Arrays With Minimum Number of Operations
Difficulty: Medium
Tags: array, greedy, hash, sort

Approach: Calculate difference, greedily use largest changes from smaller array and smallest from larger
Time Complexity: O(n log n) for sorting
Space Complexity: O(n)
"""

class Solution:
    def minOperations(self, nums1: List[int], nums2: List[int]) -> int:
        sum1, sum2 = sum(nums1), sum(nums2)
        
        if sum1 == sum2:
            return 0
        
        if sum1 > sum2:
            nums1, nums2 = nums2, nums1
            sum1, sum2 = sum2, sum1
        
        diff = sum2 - sum1
        
        # Changes possible from nums1 (increase): 6 - num
        # Changes possible from nums2 (decrease): num - 1
        changes = []
        for num in nums1:
            changes.append(6 - num)
        for num in nums2:
            changes.append(num - 1)
        
        changes.sort(reverse=True)
        
        operations = 0
        for change in changes:
            if diff <= 0:
                break
            diff -= change
            operations += 1
        
        return operations if diff <= 0 else -1