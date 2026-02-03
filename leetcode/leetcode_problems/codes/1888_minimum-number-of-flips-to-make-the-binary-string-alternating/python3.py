"""
Problem: Minimum Number of Flips to Make the Binary String Alternating
Difficulty: Medium
Tags: array, string, sliding window

Approach: Try both patterns, use sliding window for circular string
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def minFlips(self, s: str) -> int:
        n = len(s)
        s2 = s + s
        
        # Try pattern starting with 0
        pattern1 = ['0' if i % 2 == 0 else '1' for i in range(n)]
        pattern2 = ['1' if i % 2 == 0 else '0' for i in range(n)]
        
        diff1 = diff2 = 0
        result = float('inf')
        
        for i in range(n * 2):
            if s2[i] != pattern1[i % n]:
                diff1 += 1
            if s2[i] != pattern2[i % n]:
                diff2 += 1
            
            if i >= n - 1:
                result = min(result, diff1, diff2)
                if s2[i - n + 1] != pattern1[(i - n + 1) % n]:
                    diff1 -= 1
                if s2[i - n + 1] != pattern2[(i - n + 1) % n]:
                    diff2 -= 1
        
        return result