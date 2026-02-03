"""
Problem: Subsequence of Size K With the Largest Even Sum
Difficulty: Medium
Tags: array, greedy, sort

Approach: Sort and select k largest, adjust if sum is odd
Time Complexity: O(n log n) where n is array length
Space Complexity: O(1)
"""

class Solution:
    def largestEvenSum(self, nums: List[int], k: int) -> int:
        nums.sort(reverse=True)
        
        # Take k largest
        selected = nums[:k]
        total = sum(selected)
        
        if total % 2 == 0:
            return total
        
        # Sum is odd, need to swap one even with one odd or vice versa
        result = -1
        
        # Try replacing smallest even in selected with largest odd not selected
        smallest_even = None
        for i in range(k - 1, -1, -1):
            if selected[i] % 2 == 0:
                smallest_even = selected[i]
                break
        
        if smallest_even is not None:
            for i in range(k, len(nums)):
                if nums[i] % 2 == 1:
                    result = max(result, total - smallest_even + nums[i])
                    break
        
        # Try replacing smallest odd in selected with largest even not selected
        smallest_odd = None
        for i in range(k - 1, -1, -1):
            if selected[i] % 2 == 1:
                smallest_odd = selected[i]
                break
        
        if smallest_odd is not None:
            for i in range(k, len(nums)):
                if nums[i] % 2 == 0:
                    result = max(result, total - smallest_odd + nums[i])
                    break
        
        return result