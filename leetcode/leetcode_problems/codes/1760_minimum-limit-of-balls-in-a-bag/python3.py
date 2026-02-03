"""
Problem: Minimum Limit of Balls in a Bag
Difficulty: Medium
Tags: array, search, binary search

Approach: Binary search on penalty, check if can split bags within maxOperations
Time Complexity: O(n * log(max)) where max is max value
Space Complexity: O(1)
"""

class Solution:
    def minimumSize(self, nums: List[int], maxOperations: int) -> int:
        def canSplit(penalty):
            operations = 0
            for num in nums:
                if num > penalty:
                    operations += (num - 1) // penalty
                if operations > maxOperations:
                    return False
            return True
        
        left, right = 1, max(nums)
        
        while left < right:
            mid = (left + right) // 2
            if canSplit(mid):
                right = mid
            else:
                left = mid + 1
        
        return left