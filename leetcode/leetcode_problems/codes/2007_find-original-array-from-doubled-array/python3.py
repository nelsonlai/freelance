"""
Problem: Find Original Array From Doubled Array
Difficulty: Medium
Tags: array, greedy, hash, sort

Approach: Sort and use greedy - match each number with its double
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for hash map
"""

from collections import Counter

class Solution:
    def findOriginalArray(self, changed: List[int]) -> List[int]:
        if len(changed) % 2 != 0:
            return []
        
        count = Counter(changed)
        changed.sort()
        result = []
        
        for num in changed:
            if count[num] == 0:
                continue
            
            double = num * 2
            if count[double] == 0:
                return []
            
            count[num] -= 1
            count[double] -= 1
            result.append(num)
        
        return result