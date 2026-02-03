"""
Problem: H-Index
Difficulty: Medium
Tags: array, sort, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def hIndex(self, citations: List[int]) -> int:
        citations.sort(reverse=True)
        
        for i, citation in enumerate(citations):
            if i + 1 > citation:
                return i
        
        return len(citations)