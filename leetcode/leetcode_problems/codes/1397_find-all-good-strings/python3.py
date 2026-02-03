"""
Problem: Find All Good Strings
Difficulty: Hard
Tags: string, tree, dp

Approach: Digit DP with KMP - count strings in range [s1, s2] without evil substring
Time Complexity: O(n * m * 26) where n is length, m is evil length
Space Complexity: O(n * m) for DP table
"""

class Solution:
    def findGoodStrings(self, n: int, s1: str, s2: str, evil: str) -> int:
        MOD = 10**9 + 7
        m = len(evil)
        
        # KMP failure function
        fail = [0] * m
        j = 0
        for i in range(1, m):
            while j > 0 and evil[i] != evil[j]:
                j = fail[j - 1]
            if evil[i] == evil[j]:
                j += 1
            fail[i] = j
        
        def count_less_than(s, evil_state):
            dp = {}
            
            def dfs(pos, tight, state):
                if (pos, tight, state) in dp:
                    return dp[(pos, tight, state)]
                
                if state == m:
                    return 0
                
                if pos == len(s):
                    return 1
                
                result = 0
                limit = ord(s[pos]) - ord('a') if tight else 25
                
                for c in range(limit + 1):
                    char = chr(ord('a') + c)
                    new_tight = tight and (c == limit)
                    new_state = state
                    
                    while new_state > 0 and char != evil[new_state]:
                        new_state = fail[new_state - 1]
                    if char == evil[new_state]:
                        new_state += 1
                    
                    result = (result + dfs(pos + 1, new_tight, new_state)) % MOD
                
                dp[(pos, tight, state)] = result
                return result
            
            return dfs(0, True, 0)
        
        total = count_less_than(s2, 0)
        subtract = count_less_than(s1, 0)
        
        # Check if s1 contains evil
        state = 0
        for char in s1:
            while state > 0 and char != evil[state]:
                state = fail[state - 1]
            if char == evil[state]:
                state += 1
            if state == m:
                subtract += 1
                break
        
        return (total - subtract) % MOD