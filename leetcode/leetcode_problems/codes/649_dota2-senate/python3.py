"""
Problem: Dota2 Senate
Difficulty: Medium
Tags: string, greedy, queue

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

from collections import deque

class Solution:
    def predictPartyVictory(self, senate: str) -> str:
        r_queue = deque()
        d_queue = deque()
        
        for i, char in enumerate(senate):
            if char == 'R':
                r_queue.append(i)
            else:
                d_queue.append(i)
        
        while r_queue and d_queue:
            r_idx = r_queue.popleft()
            d_idx = d_queue.popleft()
            
            if r_idx < d_idx:
                r_queue.append(r_idx + len(senate))
            else:
                d_queue.append(d_idx + len(senate))
        
        return "Radiant" if r_queue else "Dire"