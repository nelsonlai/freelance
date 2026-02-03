"""
Problem: Stepping Numbers
Difficulty: Medium
Tags: math, sort, search

Approach: BFS/DFS to generate all stepping numbers, filter by range
Time Complexity: O(10 * 2^d) where d is number of digits
Space Complexity: O(2^d) for queue
"""

from collections import deque

class Solution:
    def countSteppingNumbers(self, low: int, high: int) -> List[int]:
        result = []
        queue = deque(range(1, 10))
        
        while queue:
            num = queue.popleft()
            if num > high:
                continue
            if num >= low:
                result.append(num)
            
            last_digit = num % 10
            if last_digit > 0:
                queue.append(num * 10 + last_digit - 1)
            if last_digit < 9:
                queue.append(num * 10 + last_digit + 1)
        
        if low == 0:
            result.insert(0, 0)
        
        return sorted(result)