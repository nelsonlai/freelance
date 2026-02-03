"""
Problem: Ransom Note
Difficulty: Easy
Tags: string, hash

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import Counter

class Solution:
    def canConstruct(self, ransomNote: str, magazine: str) -> bool:
        magazine_count = Counter(magazine)
        ransom_count = Counter(ransomNote)
        
        for char, count in ransom_count.items():
            if magazine_count[char] < count:
                return False
        
        return True