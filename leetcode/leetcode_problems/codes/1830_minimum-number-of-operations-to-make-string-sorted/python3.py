"""
Problem: Minimum Number of Operations to Make String Sorted
Difficulty: Hard
Tags: string, math, combinatorics

Approach: Count inversions using combinatorics - count smaller permutations
Time Complexity: O(n * 26) where n is length
Space Complexity: O(n)
"""

from collections import Counter
import math

class Solution:
    def makeStringSorted(self, s: str) -> int:
        MOD = 10**9 + 7
        n = len(s)
        result = 0
        
        # Precompute factorials and inverse factorials
        fact = [1] * (n + 1)
        inv_fact = [1] * (n + 1)
        for i in range(1, n + 1):
            fact[i] = (fact[i-1] * i) % MOD
            inv_fact[i] = pow(fact[i], MOD - 2, MOD)
        
        count = Counter(s)
        
        for i, char in enumerate(s):
            # Count smaller characters
            smaller = sum(count[c] for c in count if c < char)
            
            if smaller > 0:
                # Calculate permutations
                total = fact[n - i - 1]
                for c in count:
                    total = (total * inv_fact[count[c]]) % MOD
                
                result = (result + smaller * total) % MOD
            
            count[char] -= 1
            if count[char] == 0:
                del count[char]
        
        return result