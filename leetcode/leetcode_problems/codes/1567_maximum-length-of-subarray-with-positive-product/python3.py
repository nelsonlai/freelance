"""
Problem: Maximum Length of Subarray With Positive Product
Difficulty: Medium
Tags: array, dp, greedy

Approach: Track positive and negative subarray lengths, update on each element
Time Complexity: O(n) where n is length of nums
Space Complexity: O(1)
"""

class Solution:
    def getMaxLen(self, nums: List[int]) -> int:
        pos_len = neg_len = 0
        max_len = 0
        
        for num in nums:
            if num > 0:
                pos_len = pos_len + 1
                neg_len = neg_len + 1 if neg_len > 0 else 0
            elif num < 0:
                new_pos = neg_len + 1 if neg_len > 0 else 0
                new_neg = pos_len + 1
                pos_len, neg_len = new_pos, new_neg
            else:
                pos_len = neg_len = 0
            
            max_len = max(max_len, pos_len)
        
        return max_len