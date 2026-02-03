"""
Problem: Non-decreasing Subsequences
Difficulty: Medium
Tags: array, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def findSubsequences(self, nums: List[int]) -> List[List[int]]:
        result = set()
        
        def backtrack(index, sequence):
            if len(sequence) >= 2:
                result.add(tuple(sequence))
            
            for i in range(index, len(nums)):
                if not sequence or nums[i] >= sequence[-1]:
                    backtrack(i + 1, sequence + [nums[i]])
        
        backtrack(0, [])
        return [list(seq) for seq in result]