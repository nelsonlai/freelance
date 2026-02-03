"""
Problem: Minimum Domino Rotations For Equal Row
Difficulty: Medium
Tags: array, greedy

Approach: Try making all tops or all bottoms equal to first top or first bottom value
Time Complexity: O(n)
Space Complexity: O(1)
"""

class Solution:
    def minDominoRotations(self, tops: List[int], bottoms: List[int]) -> int:
        def check(target):
            top_rotations = bottom_rotations = 0
            for i in range(len(tops)):
                if tops[i] != target and bottoms[i] != target:
                    return -1
                if tops[i] != target:
                    top_rotations += 1
                if bottoms[i] != target:
                    bottom_rotations += 1
            return min(top_rotations, bottom_rotations)
        
        result = check(tops[0])
        if result != -1:
            return result
        
        result = check(bottoms[0])
        return result