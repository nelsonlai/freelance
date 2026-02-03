"""
Problem: Next Palindrome Using Same Digits
Difficulty: Hard
Tags: array, string, two pointers

Approach: Find next permutation of first half, mirror to create palindrome
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def nextPalindrome(self, num: str) -> str:
        n = len(num)
        half = list(num[:n//2])
        
        # Find next permutation
        i = len(half) - 2
        while i >= 0 and half[i] >= half[i+1]:
            i -= 1
        
        if i < 0:
            return ""
        
        j = len(half) - 1
        while half[j] <= half[i]:
            j -= 1
        
        half[i], half[j] = half[j], half[i]
        half[i+1:] = reversed(half[i+1:])
        
        # Create palindrome
        first_half = ''.join(half)
        if n % 2 == 0:
            return first_half + first_half[::-1]
        else:
            return first_half + num[n//2] + first_half[::-1]