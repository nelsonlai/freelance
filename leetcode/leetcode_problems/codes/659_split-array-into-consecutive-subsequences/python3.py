"""
Problem: Split Array into Consecutive Subsequences
Difficulty: Medium
Tags: array, greedy, hash, sort, queue, heap

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import Counter, defaultdict

class Solution:
    def isPossible(self, nums: List[int]) -> bool:
        count = Counter(nums)
        end = defaultdict(int)
        
        for num in nums:
            if count[num] == 0:
                continue
            
            count[num] -= 1
            
            if end[num - 1] > 0:
                end[num - 1] -= 1
                end[num] += 1
            elif count[num + 1] > 0 and count[num + 2] > 0:
                count[num + 1] -= 1
                count[num + 2] -= 1
                end[num + 2] += 1
            else:
                return False
        
        return True