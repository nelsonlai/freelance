"""
Problem: Falling Squares
Difficulty: Hard
Tags: array, tree, stack

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

class Solution:
    def fallingSquares(self, positions: List[List[int]]) -> List[int]:
        heights = []
        result = []
        
        for left, side_length in positions:
            right = left + side_length
            current_height = side_length
            
            for prev_left, prev_right, prev_height in heights:
                if right > prev_left and left < prev_right:
                    current_height = max(current_height, prev_height + side_length)
            
            heights.append((left, right, current_height))
            result.append(max(h for _, _, h in heights))
        
        return result