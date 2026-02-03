"""
Problem: Check if an Original String Exists Given Two Encoded Strings
Difficulty: Hard
Tags: string, dp, memoization

Approach: DP with memoization - decode strings and check if they can match
Time Complexity: O(n * m * 1000) where n, m are string lengths
Space Complexity: O(n * m * 1000)
"""

from functools import lru_cache

class Solution:
    def possiblyEquals(self, s1: str, s2: str) -> bool:
        @lru_cache(maxsize=None)
        def dp(i, j, diff):
            # i: index in s1, j: index in s2, diff: difference in decoded length
            if i == len(s1) and j == len(s2):
                return diff == 0
            
            # Process s1
            if i < len(s1):
                if s1[i].isdigit():
                    num = 0
                    k = i
                    while k < len(s1) and s1[k].isdigit():
                        num = num * 10 + int(s1[k])
                        k += 1
                        if dp(k, j, diff - num):
                            return True
                    return False
                else:
                    if diff < 0:
                        # s2 has more decoded chars, need to match s1[i] with s2's decoded
                        if j < len(s2) and s2[j].isalpha() and s2[j] == s1[i]:
                            return dp(i + 1, j + 1, diff)
                        return False
                    elif diff == 0:
                        # Need to match both
                        if j < len(s2) and s2[j].isalpha() and s2[j] == s1[i]:
                            return dp(i + 1, j + 1, 0)
                        return False
                    else:
                        # s1 has more decoded chars, consume from s1
                        return dp(i + 1, j, diff - 1)
            
            # Process s2
            if j < len(s2):
                if s2[j].isdigit():
                    num = 0
                    k = j
                    while k < len(s2) and s2[k].isdigit():
                        num = num * 10 + int(s2[k])
                        k += 1
                        if dp(i, k, diff + num):
                            return True
                    return False
                else:
                    if diff > 0:
                        # s1 has more decoded chars, need to match s2[j] with s1's decoded
                        if i < len(s1) and s1[i].isalpha() and s1[i] == s2[j]:
                            return dp(i + 1, j + 1, diff)
                        return False
                    elif diff == 0:
                        # Need to match both
                        if i < len(s1) and s1[i].isalpha() and s1[i] == s2[j]:
                            return dp(i + 1, j + 1, 0)
                        return False
                    else:
                        # s2 has more decoded chars, consume from s2
                        return dp(i, j + 1, diff + 1)
            
            return False
        
        return dp(0, 0, 0)