"""
Problem: Split Array with Equal Sum
Difficulty: Hard
Tags: array, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def splitArray(self, nums: List[int]) -> bool:
        n = len(nums)
        if n < 7:
            return False
        
        prefix_sum = [0]
        for num in nums:
            prefix_sum.append(prefix_sum[-1] + num)
        
        for j in range(3, n - 3):
            seen = set()
            for i in range(1, j - 1):
                if prefix_sum[i] == prefix_sum[j] - prefix_sum[i + 1]:
                    seen.add(prefix_sum[i])
            
            for k in range(j + 2, n - 1):
                if prefix_sum[n] - prefix_sum[k + 1] == prefix_sum[k] - prefix_sum[j + 1]:
                    if prefix_sum[n] - prefix_sum[k + 1] in seen:
                        return True
        
        return False