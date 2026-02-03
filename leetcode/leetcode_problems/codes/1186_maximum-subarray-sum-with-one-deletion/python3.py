"""
Problem: Maximum Subarray Sum with One Deletion
Difficulty: Medium
Tags: array, dp

Approach: DP - track max sum ending at i with 0 or 1 deletion
Time Complexity: O(n) where n is the length of arr
Space Complexity: O(1) using variables
"""

class Solution:
    def maximumSum(self, arr: List[int]) -> int:
        # no_delete: max sum ending at current index without deletion
        # one_delete: max sum ending at current index with one deletion
        no_delete = arr[0]
        one_delete = 0
        max_sum = arr[0]
        
        for i in range(1, len(arr)):
            # Can delete current element or had already deleted
            one_delete = max(no_delete, one_delete + arr[i])
            # Normal Kadane's algorithm
            no_delete = max(arr[i], no_delete + arr[i])
            max_sum = max(max_sum, no_delete, one_delete)
        
        return max_sum