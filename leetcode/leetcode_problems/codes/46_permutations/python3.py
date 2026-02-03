"""
Problem: Permutations
Difficulty: Medium
Tags: array

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        result = []
        
        def backtrack(current):
            if len(current) == len(nums):
                result.append(current[:])
                return
            
            for num in nums:
                if num not in current:
                    current.append(num)
                    backtrack(current)
                    current.pop()
        
        backtrack([])
        return result