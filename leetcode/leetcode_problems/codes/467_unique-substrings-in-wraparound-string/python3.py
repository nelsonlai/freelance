"""
Problem: Unique Substrings in Wraparound String
Difficulty: Medium
Tags: string, tree, dp

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def findSubstringInWraproundString(self, s: str) -> int:
        if not s:
            return 0
        
        count = {}
        length = 1
        
        for i in range(len(s)):
            if i > 0 and (ord(s[i]) - ord(s[i-1]) == 1 or (s[i-1] == 'z' and s[i] == 'a')):
                length += 1
            else:
                length = 1
            
            count[s[i]] = max(count.get(s[i], 0), length)
        
        return sum(count.values())