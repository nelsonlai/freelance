"""
Problem: Find Unique Binary String
Difficulty: Medium
Tags: array, string, hash, Cantor's diagonal argument

Approach: Use diagonal argument - flip i-th bit of i-th string
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def findDifferentBinaryString(self, nums: List[str]) -> str:
        result = []
        for i in range(len(nums)):
            # Flip the i-th bit of the i-th string
            if nums[i][i] == '0':
                result.append('1')
            else:
                result.append('0')
        return ''.join(result)