"""
Problem: Minimize the Difference Between Target and Chosen Elements
Difficulty: Medium
Tags: array, dp

Approach: DP - track all possible sums, find closest to target
Time Complexity: O(n * m * sum_range) where n is rows, m is cols
Space Complexity: O(sum_range)
"""

class Solution:
    def minimizeTheDifference(self, mat: List[List[int]], target: int) -> int:
        possible_sums = {0}
        
        for row in mat:
            new_sums = set()
            row_min = min(row)
            row_max = max(row)
            for s in possible_sums:
                for num in row:
                    new_sum = s + num
                    if new_sum <= target + row_max:
                        new_sums.add(new_sum)
            possible_sums = new_sums
        
        min_diff = float('inf')
        for s in possible_sums:
            min_diff = min(min_diff, abs(s - target))
        
        return min_diff