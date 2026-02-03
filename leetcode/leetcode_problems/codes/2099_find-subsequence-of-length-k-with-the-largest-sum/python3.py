"""
Problem: Find Subsequence of Length K With the Largest Sum
Difficulty: Easy
Tags: array, sort, greedy

Approach: Find k largest elements, maintain original order
Time Complexity: O(n log n) where n is array length
Space Complexity: O(n)
"""

class Solution:
    def maxSubsequence(self, nums: List[int], k: int) -> List[int]:
        # Get indices of k largest elements
        indexed = [(nums[i], i) for i in range(len(nums))]
        indexed.sort(key=lambda x: x[0], reverse=True)
        
        # Get top k indices and sort by original position
        top_k_indices = sorted([idx for _, idx in indexed[:k]])
        
        # Return values in original order
        return [nums[i] for i in top_k_indices]