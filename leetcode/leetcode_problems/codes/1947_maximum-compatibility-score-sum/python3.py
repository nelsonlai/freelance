"""
Problem: Maximum Compatibility Score Sum
Difficulty: Medium
Tags: array, dp, bitmask, Hungarian algorithm

Approach: DP with bitmask - assign students to mentors optimally
Time Complexity: O(n * 2^n) where n is students
Space Complexity: O(2^n)
"""

class Solution:
    def maxCompatibilitySum(self, students: List[List[int]], mentors: List[List[int]]) -> int:
        n = len(students)
        
        def score(s, m):
            return sum(1 for i in range(len(s)) if s[i] == m[i])
        
        @lru_cache(None)
        def dp(mask, mentor_idx):
            if mentor_idx == n:
                return 0
            
            result = 0
            for i in range(n):
                if not (mask & (1 << i)):
                    s = score(students[i], mentors[mentor_idx])
                    result = max(result, s + dp(mask | (1 << i), mentor_idx + 1))
            
            return result
        
        return dp(0, 0)