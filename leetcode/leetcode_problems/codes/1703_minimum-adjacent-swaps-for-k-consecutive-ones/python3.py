"""
Problem: Minimum Adjacent Swaps for K Consecutive Ones
Difficulty: Hard
Tags: array, greedy, sliding window, median

Approach: Collect positions of ones, use sliding window to find minimum swaps to center k ones
Time Complexity: O(n) where n is length
Space Complexity: O(n) for positions
"""

class Solution:
    def minMoves(self, nums: List[int], k: int) -> int:
        ones = [i for i, num in enumerate(nums) if num == 1]
        n = len(ones)
        
        # Calculate prefix sum
        prefix = [0]
        for i in range(n):
            prefix.append(prefix[-1] + ones[i])
        
        result = float('inf')
        
        # Sliding window of size k
        for i in range(n - k + 1):
            # Median index in the window
            mid = i + k // 2
            median = ones[mid]
            
            # Calculate cost: sum of distances from all ones to median
            left_count = mid - i
            right_count = i + k - 1 - mid
            
            left_sum = prefix[mid] - prefix[i]
            right_sum = prefix[i + k] - prefix[mid + 1]
            
            cost = (median * left_count - left_sum) + (right_sum - median * right_count)
            
            # Subtract cost of moving ones (each swap moves one position)
            cost -= (left_count * (left_count + 1) // 2) + (right_count * (right_count + 1) // 2)
            
            result = min(result, cost)
        
        return result