"""
Problem: Range Addition
Difficulty: Medium
Tags: array

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def getModifiedArray(self, length: int, updates: List[List[int]]) -> List[int]:
        result = [0] * length
        
        for start, end, inc in updates:
            result[start] += inc
            if end + 1 < length:
                result[end + 1] -= inc
        
        for i in range(1, length):
            result[i] += result[i - 1]
        
        return result