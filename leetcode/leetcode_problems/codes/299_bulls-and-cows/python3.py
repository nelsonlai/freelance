"""
Problem: Bulls and Cows
Difficulty: Medium
Tags: string, hash

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import Counter

class Solution:
    def getHint(self, secret: str, guess: str) -> str:
        bulls = 0
        cows = 0
        
        secret_count = Counter()
        guess_count = Counter()
        
        for i in range(len(secret)):
            if secret[i] == guess[i]:
                bulls += 1
            else:
                secret_count[secret[i]] += 1
                guess_count[guess[i]] += 1
        
        for char in secret_count:
            if char in guess_count:
                cows += min(secret_count[char], guess_count[char])
        
        return f"{bulls}A{cows}B"