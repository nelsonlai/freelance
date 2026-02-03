"""
Problem: Strobogrammatic Number
Difficulty: Easy
Tags: array, string, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def isStrobogrammatic(self, num: str) -> bool:
        strobogrammatic = {'0': '0', '1': '1', '6': '9', '8': '8', '9': '6'}
        left, right = 0, len(num) - 1
        
        while left <= right:
            if num[left] not in strobogrammatic or strobogrammatic[num[left]] != num[right]:
                return False
            left += 1
            right -= 1
        
        return True