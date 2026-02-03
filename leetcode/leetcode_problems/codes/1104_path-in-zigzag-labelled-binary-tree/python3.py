"""
Problem: Path In Zigzag Labelled Binary Tree
Difficulty: Medium
Tags: tree, math

Approach: Find level, work backwards using zigzag pattern
Time Complexity: O(log n)
Space Complexity: O(log n) for result
"""

class Solution:
    def pathInZigZagTree(self, label: int) -> List[int]:
        level = 0
        while (1 << level) <= label:
            level += 1
        level -= 1
        
        result = []
        while label > 0:
            result.append(label)
            # Calculate parent in zigzag tree
            level_start = 1 << level
            level_end = (1 << (level + 1)) - 1
            position = label - level_start
            parent_position = position // 2
            level -= 1
            if level >= 0:
                parent_level_start = 1 << level
                parent_level_end = (1 << (level + 1)) - 1
                # Zigzag: odd levels go right to left
                if level % 2 == 0:
                    label = parent_level_start + parent_position
                else:
                    label = parent_level_end - parent_position
        
        return result[::-1]