"""
Problem: Subsets II
Difficulty: Medium
Tags: array

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def subsetsWithDup(self, nums: List[int]) -> List[List[int]]:
        nums.sort()
        result = []
        
        def backtrack(start, current_subset):
            result.append(list(current_subset))
            
            for i in range(start, len(nums)):
                if i > start and nums[i] == nums[i - 1]:
                    continue
                current_subset.append(nums[i])
                backtrack(i + 1, current_subset)
                current_subset.pop()
        
        backtrack(0, [])
        return result