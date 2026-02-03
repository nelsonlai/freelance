"""
Problem: Sum Game
Difficulty: Medium
Tags: string, greedy, math

Approach: Alice wins if sum difference != 0 or question mark difference is odd
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def sumGame(self, num: str) -> bool:
        n = len(num)
        left_sum = 0
        left_q = 0
        right_sum = 0
        right_q = 0
        
        for i in range(n // 2):
            if num[i] == '?':
                left_q += 1
            else:
                left_sum += int(num[i])
        
        for i in range(n // 2, n):
            if num[i] == '?':
                right_q += 1
            else:
                right_sum += int(num[i])
        
        diff = left_sum - right_sum
        q_diff = left_q - right_q
        
        if q_diff == 0:
            return diff != 0
        
        if q_diff % 2 == 1:
            return True
        
        # Bob can balance if diff == 4.5 * q_diff
        return diff != 9 * q_diff // 2