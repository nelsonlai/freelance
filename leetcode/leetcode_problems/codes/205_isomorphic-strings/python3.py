"""
Problem: Isomorphic Strings
Difficulty: Easy
Tags: string, hash

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def isIsomorphic(self, s: str, t: str) -> bool:
        if len(s) != len(t):
            return False
        
        s_to_t = {}
        t_to_s = {}
        
        for i in range(len(s)):
            if s[i] in s_to_t:
                if s_to_t[s[i]] != t[i]:
                    return False
            else:
                s_to_t[s[i]] = t[i]
            
            if t[i] in t_to_s:
                if t_to_s[t[i]] != s[i]:
                    return False
            else:
                t_to_s[t[i]] = s[i]
        
        return True