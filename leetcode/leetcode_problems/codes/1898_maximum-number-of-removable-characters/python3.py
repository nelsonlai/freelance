"""
Problem: Maximum Number of Removable Characters
Difficulty: Medium
Tags: array, string, search, binary search

Approach: Binary search on number of removals, check if p is still subsequence
Time Complexity: O(k log k) where k is removable length
Space Complexity: O(n)
"""

class Solution:
    def maximumRemovals(self, s: str, p: str, removable: List[int]) -> int:
        def canRemove(k):
            removed = set(removable[:k])
            j = 0
            for i, char in enumerate(s):
                if i in removed:
                    continue
                if j < len(p) and char == p[j]:
                    j += 1
            return j == len(p)
        
        left, right = 0, len(removable)
        result = 0
        
        while left <= right:
            mid = (left + right) // 2
            if canRemove(mid):
                result = mid
                left = mid + 1
            else:
                right = mid - 1
        
        return result