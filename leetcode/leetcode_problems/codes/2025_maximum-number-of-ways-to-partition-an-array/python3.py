"""
Problem: Maximum Number of Ways to Partition an Array
Difficulty: Hard
Tags: array, hash, prefix sum

Approach: Use prefix sum and hash map to count partitions before/after changing each element
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

from collections import defaultdict

class Solution:
    def waysToPartition(self, nums: List[int], k: int) -> int:
        n = len(nums)
        total = sum(nums)
        
        # Calculate prefix sum
        prefix = [0] * n
        prefix[0] = nums[0]
        for i in range(1, n):
            prefix[i] = prefix[i - 1] + nums[i]
        
        # Count partitions without changing any element
        result = 0
        for i in range(n - 1):
            if prefix[i] == total - prefix[i]:
                result += 1
        
        # For each position, calculate partitions if we change nums[i] to k
        left_count = defaultdict(int)
        right_count = defaultdict(int)
        
        # Initialize right_count with all prefix sums
        for i in range(n - 1):
            right_count[prefix[i]] += 1
        
        for i in range(n):
            # Change nums[i] from original to k
            diff = k - nums[i]
            new_total = total + diff
            
            # Count partitions
            count = 0
            
            # Partitions in left side (before index i)
            if i > 0:
                # For j < i, new prefix[j] = prefix[j] if j < i
                # We need prefix[j] == (new_total - prefix[j]) / 2
                # Which means 2 * prefix[j] == new_total
                count += left_count.get(new_total // 2, 0)
            
            # Partitions in right side (at or after index i)
            if i < n - 1:
                # For j >= i, new prefix[j] = prefix[j] + diff
                # We need prefix[j] + diff == (new_total - (prefix[j] + diff)) / 2
                # Which means 2 * (prefix[j] + diff) == new_total
                # Or 2 * prefix[j] + 2 * diff == new_total
                # Or 2 * prefix[j] == new_total - 2 * diff
                target = (new_total - 2 * diff) // 2
                count += right_count.get(target, 0)
            
            result = max(result, count)
            
            # Update counts for next iteration
            if i < n - 1:
                right_count[prefix[i]] -= 1
                if i > 0:
                    left_count[prefix[i - 1]] += 1
        
        return result