"""
Problem: Group Shifted Strings
Difficulty: Medium
Tags: array, string, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import defaultdict

class Solution:
    def groupStrings(self, strings: List[str]) -> List[List[str]]:
        def getKey(s):
            if not s:
                return ""
            key = []
            base = ord(s[0])
            for char in s:
                diff = (ord(char) - base) % 26
                key.append(str(diff))
            return ','.join(key)
        
        groups = defaultdict(list)
        for s in strings:
            groups[getKey(s)].append(s)
        
        return list(groups.values())