"""
Problem: Array With Elements Not Equal to Average of Neighbors
Difficulty: Medium
Tags: array, greedy, sort

Approach: Sort and interleave small and large elements
Time Complexity: O(n log n) for sorting
Space Complexity: O(n)
"""

class Solution:
    def rearrangeArray(self, nums: List[int]) -> List[int]:
        nums.sort()
        n = len(nums)
        result = []
        
        left, right = 0, n - 1
        while left <= right:
            if left == right:
                result.append(nums[left])
                break
            result.append(nums[left])
            result.append(nums[right])
            left += 1
            right -= 1
        
        return result