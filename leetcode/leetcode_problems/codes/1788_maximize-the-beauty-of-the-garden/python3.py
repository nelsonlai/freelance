"""
Problem: Maximize the Beauty of the Garden
Difficulty: Hard
Tags: array, greedy, hash, prefix sum

Approach: Find pairs of same flower type, use prefix sum for beauty calculation
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def maximumBeauty(self, flowers: List[int]) -> int:
        first_occurrence = {}
        prefix_sum = [0]
        result = float('-inf')
        
        for i, flower in enumerate(flowers):
            prefix_sum.append(prefix_sum[-1] + (flower if flower > 0 else 0))
            
            if flower in first_occurrence:
                # Calculate beauty for subarray from first to current
                start = first_occurrence[flower]
                beauty = prefix_sum[i + 1] - prefix_sum[start] - (2 * flower if flower < 0 else 0)
                result = max(result, beauty)
            else:
                first_occurrence[flower] = i
        
        return result