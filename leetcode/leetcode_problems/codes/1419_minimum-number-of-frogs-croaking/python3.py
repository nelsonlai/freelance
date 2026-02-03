"""
Problem: Minimum Number of Frogs Croaking
Difficulty: Medium
Tags: string

Approach: Track count of each letter in 'croak', need max concurrent frogs
Time Complexity: O(n) where n is length of string
Space Complexity: O(1)
"""

class Solution:
    def minNumberOfFrogs(self, croakOfFrogs: str) -> int:
        count = {'c': 0, 'r': 0, 'o': 0, 'a': 0, 'k': 0}
        max_frogs = 0
        active_frogs = 0
        
        for char in croakOfFrogs:
            if char not in count:
                return -1
            
            count[char] += 1
            
            if char == 'c':
                active_frogs += 1
                max_frogs = max(max_frogs, active_frogs)
            elif char == 'k':
                active_frogs -= 1
            
            if not (count['c'] >= count['r'] >= count['o'] >= count['a'] >= count['k']):
                return -1
        
        return max_frogs if active_frogs == 0 else -1