"""
Problem: Get Equal Substrings Within Budget
Difficulty: Medium
Tags: array, string, tree, search

Approach: Sliding window - find longest substring where cost <= maxCost
Time Complexity: O(n) where n is the length of strings
Space Complexity: O(1)
"""

class Solution:
    def equalSubstring(self, s: str, t: str, maxCost: int) -> int:
        left = 0
        current_cost = 0
        max_len = 0
        
        for right in range(len(s)):
            current_cost += abs(ord(s[right]) - ord(t[right]))
            
            while current_cost > maxCost:
                current_cost -= abs(ord(s[left]) - ord(t[left]))
                left += 1
            
            max_len = max(max_len, right - left + 1)
        
        return max_len