"""
Problem: Beautiful Arrangement II
Difficulty: Medium
Tags: array, math

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def constructArray(self, n: int, k: int) -> List[int]:
        result = []
        left, right = 1, n
        
        while left <= right:
            if k > 1:
                if k % 2 == 1:
                    result.append(left)
                    left += 1
                else:
                    result.append(right)
                    right -= 1
                k -= 1
            else:
                result.append(left)
                left += 1
        
        return result