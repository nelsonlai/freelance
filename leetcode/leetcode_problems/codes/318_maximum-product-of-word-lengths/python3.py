"""
Problem: Maximum Product of Word Lengths
Difficulty: Medium
Tags: array, string

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def maxProduct(self, words: List[str]) -> int:
        masks = []
        for word in words:
            mask = 0
            for char in word:
                mask |= 1 << (ord(char) - ord('a'))
            masks.append(mask)
        
        max_product = 0
        for i in range(len(words)):
            for j in range(i + 1, len(words)):
                if masks[i] & masks[j] == 0:
                    max_product = max(max_product, len(words[i]) * len(words[j]))
        
        return max_product