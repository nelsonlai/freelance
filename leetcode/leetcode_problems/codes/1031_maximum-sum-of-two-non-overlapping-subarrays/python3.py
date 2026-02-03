"""
Problem: Maximum Sum of Two Non-Overlapping Subarrays
Difficulty: Medium
Tags: array, dp

Approach: DP - track max sum of subarray ending at each position for both lengths
Time Complexity: O(n)
Space Complexity: O(n)
"""

class Solution:
    def maxSumTwoNoOverlap(self, nums: List[int], firstLen: int, secondLen: int) -> int:
        n = len(nums)
        prefix = [0]
        for num in nums:
            prefix.append(prefix[-1] + num)
        
        def maxSum(L, M):
            maxL = [0] * n
            max_sum = 0
            
            for i in range(L - 1, n):
                if i >= L:
                    maxL[i] = max(maxL[i - 1], prefix[i + 1] - prefix[i + 1 - L])
                else:
                    maxL[i] = prefix[i + 1] - prefix[i + 1 - L]
            
            for i in range(L + M - 1, n):
                currentM = prefix[i + 1] - prefix[i + 1 - M]
                max_sum = max(max_sum, maxL[i - M] + currentM)
            
            return max_sum
        
        return max(maxSum(firstLen, secondLen), maxSum(secondLen, firstLen))