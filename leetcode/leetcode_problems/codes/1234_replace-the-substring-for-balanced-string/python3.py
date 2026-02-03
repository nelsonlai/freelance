"""
Problem: Replace the Substring for Balanced String
Difficulty: Medium
Tags: array, string, tree

Approach: Sliding window - find minimum substring to replace so remaining has balanced counts
Time Complexity: O(n) where n is length of s
Space Complexity: O(1)
"""

from collections import Counter

class Solution:
    def balancedString(self, s: str) -> int:
        n = len(s)
        target = n // 4
        count = Counter(s)
        
        # Count excess characters
        excess = {}
        for char in 'QWER':
            if count[char] > target:
                excess[char] = count[char] - target
        
        if not excess:
            return 0
        
        left = 0
        min_len = n
        window_count = Counter()
        
        for right in range(n):
            window_count[s[right]] += 1
            
            # Check if window contains all excess characters
            while all(window_count.get(char, 0) >= excess.get(char, 0) for char in excess):
                min_len = min(min_len, right - left + 1)
                window_count[s[left]] -= 1
                left += 1
        
        return min_len