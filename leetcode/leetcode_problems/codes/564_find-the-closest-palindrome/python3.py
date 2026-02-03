"""
Problem: Find the Closest Palindrome
Difficulty: Hard
Tags: string, math

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def nearestPalindromic(self, n: str) -> str:
        length = len(n)
        num = int(n)
        
        candidates = set()
        candidates.add(10**(length-1) - 1)
        candidates.add(10**length + 1)
        
        prefix = int(n[:(length+1)//2])
        for i in [-1, 0, 1]:
            candidate = str(prefix + i)
            if length % 2 == 0:
                candidate += candidate[::-1]
            else:
                candidate += candidate[:-1][::-1]
            candidates.add(int(candidate))
        
        candidates.discard(num)
        
        result = None
        min_diff = float('inf')
        for candidate in candidates:
            diff = abs(candidate - num)
            if diff < min_diff or (diff == min_diff and candidate < result):
                min_diff = diff
                result = candidate
        
        return str(result)