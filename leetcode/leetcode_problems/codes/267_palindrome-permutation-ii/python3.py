"""
Problem: Palindrome Permutation II
Difficulty: Medium
Tags: string, hash

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import Counter

class Solution:
    def generatePalindromes(self, s: str) -> List[str]:
        count = Counter(s)
        odd_chars = [char for char, cnt in count.items() if cnt % 2 == 1]
        
        if len(odd_chars) > 1:
            return []
        
        mid = odd_chars[0] if odd_chars else ""
        half = []
        for char, cnt in count.items():
            half.extend([char] * (cnt // 2))
        
        result = []
        self.permute(half, 0, mid, result)
        return result
    
    def permute(self, chars, start, mid, result):
        if start == len(chars):
            result.append(''.join(chars) + mid + ''.join(reversed(chars)))
            return
        
        seen = set()
        for i in range(start, len(chars)):
            if chars[i] not in seen:
                seen.add(chars[i])
                chars[start], chars[i] = chars[i], chars[start]
                self.permute(chars, start + 1, mid, result)
                chars[start], chars[i] = chars[i], chars[start]