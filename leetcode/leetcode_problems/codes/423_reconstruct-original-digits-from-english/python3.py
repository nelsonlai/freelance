"""
Problem: Reconstruct Original Digits from English
Difficulty: Medium
Tags: string, math, hash

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import Counter

class Solution:
    def originalDigits(self, s: str) -> str:
        count = Counter(s)
        
        digits = [0] * 10
        
        digits[0] = count['z']
        digits[2] = count['w']
        digits[4] = count['u']
        digits[6] = count['x']
        digits[8] = count['g']
        
        digits[3] = count['h'] - digits[8]
        digits[5] = count['f'] - digits[4]
        digits[7] = count['s'] - digits[6]
        digits[1] = count['o'] - digits[0] - digits[2] - digits[4]
        digits[9] = count['i'] - digits[5] - digits[6] - digits[8]
        
        result = []
        for i in range(10):
            result.extend([str(i)] * digits[i])
        
        return ''.join(result)