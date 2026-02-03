"""
Problem: Distinct Echo Substrings
Difficulty: Hard
Tags: string, tree, hash

Approach: Check all substrings of even length, see if first half equals second half
Time Complexity: O(n^3) in worst case
Space Complexity: O(n^2) for set
"""

class Solution:
    def distinctEchoSubstrings(self, text: str) -> int:
        n = len(text)
        seen = set()
        
        for length in range(2, n + 1, 2):
            for i in range(n - length + 1):
                half = length // 2
                if text[i:i+half] == text[i+half:i+length]:
                    seen.add(text[i:i+length])
        
        return len(seen)