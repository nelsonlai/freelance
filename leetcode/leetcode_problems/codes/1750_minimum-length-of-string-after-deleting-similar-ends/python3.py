"""
Problem: Minimum Length of String After Deleting Similar Ends
Difficulty: Medium
Tags: array, string, two pointers

Approach: Use two pointers to remove matching characters from both ends
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def minimumLength(self, s: str) -> int:
        left, right = 0, len(s) - 1
        
        while left < right and s[left] == s[right]:
            char = s[left]
            while left <= right and s[left] == char:
                left += 1
            while left <= right and s[right] == char:
                right -= 1
        
        return right - left + 1