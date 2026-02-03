"""
Problem: Defuse the Bomb
Difficulty: Easy
Tags: array, sliding window

Approach: For each position, sum k next (if k>0) or k previous (if k<0) elements
Time Complexity: O(n * |k|) where n is length
Space Complexity: O(n)
"""

class Solution:
    def decrypt(self, code: List[int], k: int) -> List[int]:
        n = len(code)
        result = [0] * n
        
        if k == 0:
            return result
        
        for i in range(n):
            total = 0
            if k > 0:
                for j in range(1, k + 1):
                    total += code[(i + j) % n]
            else:
                for j in range(1, -k + 1):
                    total += code[(i - j) % n]
            result[i] = total
        
        return result