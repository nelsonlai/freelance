"""
Problem: Longest Duplicate Substring
Difficulty: Hard
Tags: array, string, tree, hash, search

Approach: Binary search on length + rolling hash to check for duplicates
Time Complexity: O(n log n)
Space Complexity: O(n) for hash set
"""

class Solution:
    def longestDupSubstring(self, s: str) -> str:
        n = len(s)
        base = 26
        mod = 10**9 + 7
        
        def search(length):
            hash_set = set()
            hash_val = 0
            power = pow(base, length - 1, mod)
            
            for i in range(length):
                hash_val = (hash_val * base + ord(s[i]) - ord('a')) % mod
            hash_set.add(hash_val)
            
            for i in range(length, n):
                hash_val = ((hash_val - (ord(s[i - length]) - ord('a')) * power) * base + (ord(s[i]) - ord('a'))) % mod
                if hash_val in hash_set:
                    return s[i - length + 1:i + 1]
                hash_set.add(hash_val)
            
            return ""
        
        left, right = 1, n
        result = ""
        
        while left < right:
            mid = (left + right) // 2
            dup = search(mid)
            if dup:
                result = dup
                left = mid + 1
            else:
                right = mid
        
        return result