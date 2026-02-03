"""
Problem: Reverse Vowels of a String
Difficulty: Easy
Tags: array, string

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def reverseVowels(self, s: str) -> str:
        vowels = set('aeiouAEIOU')
        s_list = list(s)
        left, right = 0, len(s_list) - 1
        
        while left < right:
            while left < right and s_list[left] not in vowels:
                left += 1
            while left < right and s_list[right] not in vowels:
                right -= 1
            
            if left < right:
                s_list[left], s_list[right] = s_list[right], s_list[left]
                left += 1
                right -= 1
        
        return ''.join(s_list)