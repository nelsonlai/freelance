"""
Problem: Maximum Sum Obtained of Any Permutation
Difficulty: Medium
Tags: array, greedy, sort

Approach: Count frequency of each index, assign largest numbers to most frequent indices
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for frequency array
"""

MOD = 10**9 + 7

class Solution:
    def maxSumRangeQuery(self, nums: List[int], requests: List[List[int]]) -> int:
        n = len(nums)
        freq = [0] * (n + 1)
        
        for start, end in requests:
            freq[start] += 1
            freq[end + 1] -= 1
        
        for i in range(1, n):
            freq[i] += freq[i - 1]
        
        freq = freq[:n]
        freq.sort(reverse=True)
        nums.sort(reverse=True)
        
        result = 0
        for i in range(n):
            result = (result + freq[i] * nums[i]) % MOD
        
        return result