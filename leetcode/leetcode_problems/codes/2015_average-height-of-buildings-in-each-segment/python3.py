"""
Problem: Average Height of Buildings in Each Segment
Difficulty: Medium
Tags: array, greedy, sort, line sweep

Approach: Use line sweep to merge overlapping buildings, calculate average heights
Time Complexity: O(n log n) for sorting
Space Complexity: O(n)
"""

from collections import defaultdict

class Solution:
    def averageHeightOfBuildings(self, buildings: List[List[int]]) -> List[List[int]]:
        events = []
        
        for start, end, height in buildings:
            events.append((start, height, 1))
            events.append((end, height, -1))
        
        events.sort()
        
        result = []
        current_sum = 0
        current_count = 0
        prev_pos = None
        
        for pos, height, delta in events:
            if prev_pos is not None and prev_pos < pos and current_count > 0:
                avg_height = current_sum // current_count
                if result and result[-1][1] == prev_pos and result[-1][2] == avg_height:
                    # Merge with previous segment
                    result[-1][1] = pos
                else:
                    result.append([prev_pos, pos, avg_height])
            
            current_sum += height * delta
            current_count += delta
            prev_pos = pos
        
        return result