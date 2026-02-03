"""
Problem: Partition to K Equal Sum Subsets
Difficulty: Medium
Tags: array, dp

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def canPartitionKSubsets(self, nums: List[int], k: int) -> bool:
        total = sum(nums)
        if total % k != 0:
            return False
        
        target = total // k
        nums.sort(reverse=True)
        used = [False] * len(nums)
        
        def backtrack(start, current_sum, remaining):
            if remaining == 0:
                return True
            
            if current_sum == target:
                return backtrack(0, 0, remaining - 1)
            
            for i in range(start, len(nums)):
                if used[i] or current_sum + nums[i] > target:
                    continue
                
                used[i] = True
                if backtrack(i + 1, current_sum + nums[i], remaining):
                    return True
                used[i] = False
                
                while i + 1 < len(nums) and nums[i] == nums[i + 1]:
                    i += 1
            
            return False
        
        return backtrack(0, 0, k)