"""
Problem: Confusing Number II
Difficulty: Hard
Tags: math

Approach: DFS to generate all valid confusing numbers, count those that rotate differently
Time Complexity: O(5^log10(n))
Space Complexity: O(log n) for recursion
"""

class Solution:
    def confusingNumberII(self, n: int) -> int:
        rotate_map = {0: 0, 1: 1, 6: 9, 8: 8, 9: 6}
        valid_digits = [0, 1, 6, 8, 9]
        self.count = 0
        
        def is_confusing(num):
            rotated = 0
            original = num
            while num > 0:
                digit = num % 10
                if digit not in rotate_map:
                    return False
                rotated = rotated * 10 + rotate_map[digit]
                num //= 10
            return rotated != original
        
        def dfs(num):
            if num > n:
                return
            if num > 0 and is_confusing(num):
                self.count += 1
            
            for digit in valid_digits:
                if num == 0 and digit == 0:
                    continue
                dfs(num * 10 + digit)
        
        dfs(0)
        return self.count