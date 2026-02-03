"""
Problem: Maximum Equal Frequency
Difficulty: Hard
Tags: array, hash

Approach: Track frequency counts, check if can remove one element to make all frequencies equal
Time Complexity: O(n) where n is length of nums
Space Complexity: O(n) for frequency maps
"""

from collections import Counter

class Solution:
    def maxEqualFreq(self, nums: List[int]) -> int:
        freq = Counter()
        count_freq = Counter()
        max_len = 0
        
        for i, num in enumerate(nums):
            if num in freq:
                count_freq[freq[num]] -= 1
                if count_freq[freq[num]] == 0:
                    del count_freq[freq[num]]
            
            freq[num] += 1
            count_freq[freq[num]] += 1
            
            # Check if valid after removing one element
            if len(count_freq) == 1:
                # All have same frequency
                max_len = i + 1
            elif len(count_freq) == 2:
                keys = sorted(count_freq.keys())
                # Case 1: One element with frequency 1, rest with frequency k
                if keys[0] == 1 and count_freq[1] == 1:
                    max_len = i + 1
                # Case 2: One element with frequency k+1, rest with frequency k
                elif keys[1] - keys[0] == 1 and count_freq[keys[1]] == 1:
                    max_len = i + 1
        
        return max_len