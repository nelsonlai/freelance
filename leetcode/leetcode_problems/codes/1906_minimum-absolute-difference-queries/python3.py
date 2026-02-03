"""
Problem: Minimum Absolute Difference Queries
Difficulty: Medium
Tags: array, hash, prefix sum

Approach: For each query, find all distinct numbers in range, compute min diff
Time Complexity: O(n * 100 + q * 100) where q is queries, numbers are 1-100
Space Complexity: O(n * 100)
"""

class Solution:
    def minDifference(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        n = len(nums)
        # prefix[i][j] = count of number j in nums[0:i]
        prefix = [[0] * 101]
        
        for num in nums:
            new_row = prefix[-1][:]
            new_row[num] += 1
            prefix.append(new_row)
        
        result = []
        for l, r in queries:
            # Get distinct numbers in range
            distinct = []
            for i in range(1, 101):
                if prefix[r + 1][i] - prefix[l][i] > 0:
                    distinct.append(i)
            
            if len(distinct) < 2:
                result.append(-1)
            else:
                min_diff = float('inf')
                for i in range(len(distinct) - 1):
                    min_diff = min(min_diff, distinct[i + 1] - distinct[i])
                result.append(min_diff)
        
        return result