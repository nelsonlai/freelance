"""
Problem: Smallest Greater Multiple Made of Two Digits
Difficulty: Medium
Tags: math, BFS

Approach: BFS to find smallest number > k made of only digit1 and digit2
Time Complexity: O(2^log(k)) in worst case
Space Complexity: O(2^log(k))
"""

from collections import deque

class Solution:
    def findInteger(self, k: int, digit1: int, digit2: int) -> int:
        digits = sorted(set([digit1, digit2]))
        if not digits:
            return -1
        
        queue = deque([0])
        visited = {0}
        
        while queue:
            num = queue.popleft()
            
            for digit in digits:
                next_num = num * 10 + digit
                if next_num > k:
                    return next_num
                
                if next_num not in visited and next_num > 0:
                    visited.add(next_num)
                    queue.append(next_num)
        
        return -1