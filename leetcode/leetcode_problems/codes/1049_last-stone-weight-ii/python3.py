"""
Problem: Last Stone Weight II
Difficulty: Medium
Tags: array, dp

Approach: Partition stones into two groups with minimum difference - subset sum problem
Time Complexity: O(n * sum(stones))
Space Complexity: O(sum(stones))
"""

class Solution:
    def lastStoneWeightII(self, stones: List[int]) -> int:
        total = sum(stones)
        target = total // 2
        dp = {0}
        
        for stone in stones:
            new_dp = set()
            for s in dp:
                if s + stone <= target:
                    new_dp.add(s + stone)
                new_dp.add(s)
            dp = new_dp
        
        max_sum = max(dp)
        return total - 2 * max_sum