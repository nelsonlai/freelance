"""
Problem: Sliding Window Median
Difficulty: Hard
Tags: array, hash, queue, heap

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

import bisect

class Solution:
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        window = sorted(nums[:k])
        result = []
        
        def get_median():
            if k % 2 == 0:
                return (window[k//2-1] + window[k//2]) / 2.0
            else:
                return float(window[k//2])
        
        result.append(get_median())
        
        for i in range(k, len(nums)):
            window.remove(nums[i-k])
            bisect.insort(window, nums[i])
            result.append(get_median())
        
        return result