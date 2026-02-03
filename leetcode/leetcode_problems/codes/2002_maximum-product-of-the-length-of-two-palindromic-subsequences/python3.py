"""
Problem: Maximum Product of the Length of Two Palindromic Subsequences
Difficulty: Medium
Tags: string, dp, bitmask

Approach: Use bitmask to enumerate all subsequences, find palindromic ones, maximize product
Time Complexity: O(3^n) where n is length
Space Complexity: O(2^n)
"""

class Solution:
    def maxProduct(self, s: str) -> int:
        n = len(s)
        palindromes = []
        
        # Find all palindromic subsequences
        for mask in range(1, 1 << n):
            subseq = []
            for i in range(n):
                if mask & (1 << i):
                    subseq.append(s[i])
            
            if subseq == subseq[::-1]:
                palindromes.append(mask)
        
        max_product = 0
        
        # Find two non-overlapping palindromic subsequences
        for i in range(len(palindromes)):
            for j in range(i + 1, len(palindromes)):
                if palindromes[i] & palindromes[j] == 0:  # No overlap
                    len1 = bin(palindromes[i]).count('1')
                    len2 = bin(palindromes[j]).count('1')
                    max_product = max(max_product, len1 * len2)
        
        return max_product