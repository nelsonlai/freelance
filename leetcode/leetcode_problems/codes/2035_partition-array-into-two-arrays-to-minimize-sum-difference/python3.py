"""
Problem: Partition Array Into Two Arrays to Minimize Sum Difference
Difficulty: Hard
Tags: array, dp, search, meet-in-middle

Approach: Meet-in-middle - split array in half, find all possible sums for each half
Time Complexity: O(n * 2^(n/2))
Space Complexity: O(2^(n/2))
"""

class Solution:
    def minimumDifference(self, nums: List[int]) -> int:
        n = len(nums)
        total = sum(nums)
        target = total // 2
        
        # Split array in half
        left = nums[:n//2]
        right = nums[n//2:]
        
        # Generate all possible sums for left half with different sizes
        left_sums = {}
        for mask in range(1 << len(left)):
            s = sum(left[i] for i in range(len(left)) if mask & (1 << i) else 0)
            count = bin(mask).count('1')
            if count not in left_sums:
                left_sums[count] = []
            left_sums[count].append(s)
        
        # Sort for binary search
        for count in left_sums:
            left_sums[count].sort()
        
        # Generate all possible sums for right half
        result = float('inf')
        for mask in range(1 << len(right)):
            s = sum(right[i] for i in range(len(right)) if mask & (1 << i) else 0)
            count = bin(mask).count('1')
            needed_count = n // 2 - count
            
            if needed_count in left_sums:
                # Binary search for closest sum to target - s
                arr = left_sums[needed_count]
                import bisect
                idx = bisect.bisect_left(arr, target - s)
                
                # Check closest values
                for i in [idx - 1, idx, idx + 1]:
                    if 0 <= i < len(arr):
                        sum1 = s + arr[i]
                        sum2 = total - sum1
                        result = min(result, abs(sum1 - sum2))
        
        return result