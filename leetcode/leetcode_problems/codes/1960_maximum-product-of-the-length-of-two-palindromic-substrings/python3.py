"""
Problem: Maximum Product of the Length of Two Palindromic Substrings
Difficulty: Hard
Tags: string, Manacher's algorithm, palindrome

Approach: Use Manacher's algorithm to find all palindromes, maximize product
Time Complexity: O(n^2) where n is length
Space Complexity: O(n)
"""

class Solution:
    def maxProduct(self, s: str) -> int:
        n = len(s)
        
        def manacher(s):
            s_new = '#' + '#'.join(s) + '#'
            n_new = len(s_new)
            p = [0] * n_new
            center = right = 0
            
            for i in range(n_new):
                if i < right:
                    p[i] = min(right - i, p[2 * center - i])
                
                while i + p[i] + 1 < n_new and i - p[i] - 1 >= 0 and \
                      s_new[i + p[i] + 1] == s_new[i - p[i] - 1]:
                    p[i] += 1
                
                if i + p[i] > right:
                    center = i
                    right = i + p[i]
            
            return [p[i] for i in range(1, n_new - 1, 2)]
        
        # Get palindrome lengths for each center
        pal_lengths = manacher(s)
        
        # Find max product of two non-overlapping palindromes
        max_product = 0
        
        for i in range(n):
            for j in range(i + 1, n):
                len1 = pal_lengths[i] if i < len(pal_lengths) else 1
                len2 = pal_lengths[j] if j < len(pal_lengths) else 1
                
                # Check if they don't overlap
                start1 = i - (len1 - 1) // 2
                end1 = i + len1 // 2
                start2 = j - (len2 - 1) // 2
                end2 = j + len2 // 2
                
                if end1 < start2:
                    max_product = max(max_product, len1 * len2)
        
        return max_product