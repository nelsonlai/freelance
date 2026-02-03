"""
Problem: Minimum Window Substring
Difficulty: Hard
Tags: array, string, tree, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

class Solution:
    def minWindow(self, s: str, t: str) -> str:
        if not s or not t:
            return ""
        
        from collections import Counter
        need = Counter(t)
        window = {}
        left = 0
        valid = 0
        start = 0
        min_len = float('inf')
        
        for right, char in enumerate(s):
            if char in need:
                window[char] = window.get(char, 0) + 1
                if window[char] == need[char]:
                    valid += 1
            
            while valid == len(need):
                if right - left + 1 < min_len:
                    start = left
                    min_len = right - left + 1
                
                if s[left] in need:
                    if window[s[left]] == need[s[left]]:
                        valid -= 1
                    window[s[left]] -= 1
                left += 1
        
        return "" if min_len == float('inf') else s[start:start + min_len]