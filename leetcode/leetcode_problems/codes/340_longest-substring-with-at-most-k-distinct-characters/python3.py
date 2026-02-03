"""
Problem: Longest Substring with At Most K Distinct Characters
Difficulty: Medium
Tags: array, string, tree, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

from collections import defaultdict

class Solution:
    def lengthOfLongestSubstringKDistinct(self, s: str, k: int) -> int:
        if k == 0:
            return 0
        
        char_count = defaultdict(int)
        left = 0
        max_length = 0
        
        for right in range(len(s)):
            char_count[s[right]] += 1
            
            while len(char_count) > k:
                char_count[s[left]] -= 1
                if char_count[s[left]] == 0:
                    del char_count[s[left]]
                left += 1
            
            max_length = max(max_length, right - left + 1)
        
        return max_length