"""
Problem: Video Stitching
Difficulty: Medium
Tags: array, dp, greedy

Approach: Greedy - sort clips, extend coverage as far as possible
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def videoStitching(self, clips: List[List[int]], time: int) -> int:
        clips.sort()
        result = 0
        end = 0
        i = 0
        
        while end < time:
            max_end = end
            while i < len(clips) and clips[i][0] <= end:
                max_end = max(max_end, clips[i][1])
                i += 1
            
            if max_end == end:
                return -1
            
            end = max_end
            result += 1
        
        return result