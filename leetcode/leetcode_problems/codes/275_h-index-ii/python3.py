"""
Problem: H-Index II
Difficulty: Medium
Tags: array, sort, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def hIndex(self, citations: List[int]) -> int:
        n = len(citations)
        left, right = 0, n - 1
        
        while left <= right:
            mid = (left + right) // 2
            if citations[mid] >= n - mid:
                right = mid - 1
            else:
                left = mid + 1
        
        return n - left