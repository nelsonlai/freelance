"""
Problem: Closest Subsequence Sum
Difficulty: Hard
Tags: array, dp, sort, meet in middle

Approach: Split array in half, generate all subset sums, use two pointers to find closest
Time Complexity: O(2^(n/2) * log(2^(n/2))) where n is length
Space Complexity: O(2^(n/2))
"""

import bisect

class Solution:
    def minAbsDifference(self, nums: List[int], goal: int) -> int:
        n = len(nums)
        mid = n // 2
        
        def generate_sums(arr):
            sums = [0]
            for num in arr:
                new_sums = []
                for s in sums:
                    new_sums.append(s + num)
                sums.extend(new_sums)
            return sorted(set(sums))
        
        left_sums = generate_sums(nums[:mid])
        right_sums = generate_sums(nums[mid:])
        
        result = float('inf')
        
        for left_sum in left_sums:
            target = goal - left_sum
            pos = bisect.bisect_left(right_sums, target)
            
            if pos < len(right_sums):
                result = min(result, abs(left_sum + right_sums[pos] - goal))
            if pos > 0:
                result = min(result, abs(left_sum + right_sums[pos - 1] - goal))
        
        return result