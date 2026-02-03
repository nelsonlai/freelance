"""
Problem: Describe the Painting
Difficulty: Medium
Tags: array, hash, sort, sweep line

Approach: Sweep line to track color changes at each position
Time Complexity: O(n log n) where n is segments
Space Complexity: O(n)
"""

from collections import defaultdict

class Solution:
    def splitPainting(self, segments: List[List[int]]) -> List[List[int]]:
        events = defaultdict(int)
        
        for start, end, color in segments:
            events[start] += color
            events[end] -= color
        
        sorted_positions = sorted(events.keys())
        result = []
        current_color = 0
        prev_pos = None
        
        for pos in sorted_positions:
            if prev_pos is not None and current_color > 0:
                result.append([prev_pos, pos, current_color])
            
            current_color += events[pos]
            prev_pos = pos
        
        return result