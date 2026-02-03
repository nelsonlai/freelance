"""
Problem: Distinct Numbers in Each Subarray
Difficulty: Medium
Tags: array, hash, sliding window

Approach: Sliding window with frequency map
Time Complexity: O(n) where n is length
Space Complexity: O(k)
"""

from collections import defaultdict

class Solution:
    def distinctNumbers(self, nums: List[int], k: int) -> List[int]:
        count = defaultdict(int)
        result = []
        
        for i in range(len(nums)):
            count[nums[i]] += 1
            
            if i >= k - 1:
                result.append(len(count))
                
                # Remove leftmost element
                count[nums[i - k + 1]] -= 1
                if count[nums[i - k + 1]] == 0:
                    del count[nums[i - k + 1]]
        
        return result