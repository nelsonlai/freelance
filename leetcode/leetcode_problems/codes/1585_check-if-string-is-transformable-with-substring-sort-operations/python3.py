"""
Problem: Check If String Is Transformable With Substring Sort Operations
Difficulty: Hard
Tags: string, tree, greedy, sort

Approach: For each digit in t, check if it can be moved from s. Track positions of each digit.
Time Complexity: O(n * 10) where n is length of strings
Space Complexity: O(n) for position queues
"""

from collections import deque

class Solution:
    def isTransformable(self, s: str, t: str) -> bool:
        if len(s) != len(t):
            return False
        
        positions = [deque() for _ in range(10)]
        for i, char in enumerate(s):
            positions[int(char)].append(i)
        
        for char in t:
            digit = int(char)
            if not positions[digit]:
                return False
            
            pos = positions[digit][0]
            for smaller in range(digit):
                if positions[smaller] and positions[smaller][0] < pos:
                    return False
            
            positions[digit].popleft()
        
        return True