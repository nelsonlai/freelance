"""
Problem: Permutations II
Difficulty: Medium
Tags: array, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def permuteUnique(self, nums: List[int]) -> List[List[int]]:
        nums.sort()
        result = []
        used = [False] * len(nums)
        
        def backtrack(current):
            if len(current) == len(nums):
                result.append(current[:])
                return
            
            for i in range(len(nums)):
                if used[i] or (i > 0 and nums[i] == nums[i-1] and not used[i-1]):
                    continue
                used[i] = True
                current.append(nums[i])
                backtrack(current)
                current.pop()
                used[i] = False
        
        backtrack([])
        return result