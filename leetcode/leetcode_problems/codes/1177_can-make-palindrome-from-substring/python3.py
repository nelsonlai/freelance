"""
Problem: Can Make Palindrome from Substring
Difficulty: Medium
Tags: array, string, tree, hash

Approach: Use prefix XOR to count character frequencies, check if can form palindrome with k replacements
Time Complexity: O(n + q) where n is length of s, q is number of queries
Space Complexity: O(n) for prefix array
"""

class Solution:
    def canMakePaliQueries(self, s: str, queries: List[List[int]]) -> List[bool]:
        n = len(s)
        # Use bitmask to track character parity (odd/even count)
        prefix = [0] * (n + 1)
        
        for i in range(n):
            prefix[i+1] = prefix[i] ^ (1 << (ord(s[i]) - ord('a')))
        
        result = []
        for left, right, k in queries:
            # XOR of prefix gives character parity in substring
            mask = prefix[right+1] ^ prefix[left]
            # Count number of characters with odd frequency
            odd_count = bin(mask).count('1')
            # Need at most odd_count // 2 replacements to make palindrome
            result.append(odd_count // 2 <= k)
        
        return result