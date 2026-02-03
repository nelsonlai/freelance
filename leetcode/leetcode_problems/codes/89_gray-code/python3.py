"""
Problem: Gray Code
Difficulty: Medium
Tags: math

Approach: Optimized algorithm based on problem constraints
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def grayCode(self, n: int) -> List[int]:
        result = [0]
        
        for i in range(n):
            size = len(result)
            for j in range(size - 1, -1, -1):
                result.append(result[j] | (1 << i))
        
        return result