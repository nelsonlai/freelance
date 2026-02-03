"""
Problem: Find the Kth Largest Integer in the Array
Difficulty: Medium
Tags: array, string, sort, queue, heap

Approach: Sort by integer value, return k-th largest
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def kthLargestNumber(self, nums: List[str], k: int) -> str:
        nums.sort(key=lambda x: (len(x), x), reverse=True)
        return nums[k-1]