"""
Problem: Longest Substring Of All Vowels in Order
Difficulty: Medium
Tags: array, string, two pointers

Approach: Track valid substring with all vowels in order
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def longestBeautifulSubstring(self, word: str) -> int:
        vowels = {'a': 0, 'e': 1, 'i': 2, 'o': 3, 'u': 4}
        result = 0
        start = 0
        current_vowel = -1
        
        for i, char in enumerate(word):
            if char not in vowels:
                start = i + 1
                current_vowel = -1
                continue
            
            vowel_idx = vowels[char]
            if vowel_idx == current_vowel or vowel_idx == current_vowel + 1:
                if vowel_idx == current_vowel + 1:
                    current_vowel = vowel_idx
                if current_vowel == 4:  # 'u'
                    result = max(result, i - start + 1)
            else:
                start = i
                current_vowel = vowel_idx if char == 'a' else -1
        
        return result