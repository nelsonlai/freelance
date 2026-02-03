"""
Problem: Maximum Number of Vowels in a Substring of Given Length
Difficulty: Medium
Tags: array, string, tree

Approach: Sliding window - maintain count of vowels in window of size k
Time Complexity: O(n) where n is length of s
Space Complexity: O(1)
"""

class Solution:
    def maxVowels(self, s: str, k: int) -> int:
        vowels = {'a', 'e', 'i', 'o', 'u'}
        max_count = 0
        current_count = sum(1 for c in s[:k] if c in vowels)
        max_count = current_count
        
        for i in range(k, len(s)):
            if s[i - k] in vowels:
                current_count -= 1
            if s[i] in vowels:
                current_count += 1
            max_count = max(max_count, current_count)
        
        return max_count