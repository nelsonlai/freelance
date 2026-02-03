"""
Problem: Maximum Sum of 3 Non-Overlapping Subarrays
Difficulty: Hard
Tags: array, graph, dp

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def maxSumOfThreeSubarrays(self, nums: List[int], k: int) -> List[int]:
        n = len(nums)
        prefix_sum = [0]
        for num in nums:
            prefix_sum.append(prefix_sum[-1] + num)
        
        left = [0] * n
        right = [0] * n
        
        total = prefix_sum[k] - prefix_sum[0]
        for i in range(k, n - 2 * k + 1):
            if prefix_sum[i] - prefix_sum[i - k] > total:
                total = prefix_sum[i] - prefix_sum[i - k]
                left[i] = i - k
            else:
                left[i] = left[i - 1]
        
        total = prefix_sum[n] - prefix_sum[n - k]
        right[n - k] = n - k
        for i in range(n - k - 1, 2 * k - 1, -1):
            if prefix_sum[i + k] - prefix_sum[i] >= total:
                total = prefix_sum[i + k] - prefix_sum[i]
                right[i] = i
            else:
                right[i] = right[i + 1]
        
        max_sum = 0
        result = []
        for i in range(k, n - 2 * k + 1):
            l, r = left[i], right[i + k]
            current_sum = (prefix_sum[i + k] - prefix_sum[i] +
                          prefix_sum[l + k] - prefix_sum[l] +
                          prefix_sum[r + k] - prefix_sum[r])
            if current_sum > max_sum:
                max_sum = current_sum
                result = [l, i, r]
        
        return result