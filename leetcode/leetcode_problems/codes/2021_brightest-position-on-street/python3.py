"""
Problem: Brightest Position on Street
Difficulty: Medium
Tags: array, sort, line sweep

Approach: Use line sweep - mark start and end of light coverage
Time Complexity: O(n log n) for sorting
Space Complexity: O(n)
"""

from collections import defaultdict

class Solution:
    def brightestPosition(self, lights: List[List[int]]) -> int:
        events = []
        
        for pos, range_val in lights:
            start = pos - range_val
            end = pos + range_val + 1
            events.append((start, 1))
            events.append((end, -1))
        
        events.sort()
        
        max_brightness = 0
        current_brightness = 0
        result_pos = 0
        
        for pos, delta in events:
            current_brightness += delta
            if current_brightness > max_brightness:
                max_brightness = current_brightness
                result_pos = pos
        
        return result_pos