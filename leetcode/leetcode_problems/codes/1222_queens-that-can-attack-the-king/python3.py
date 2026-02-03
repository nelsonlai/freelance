"""
Problem: Queens That Can Attack the King
Difficulty: Medium
Tags: array

Approach: Check 8 directions from king, find closest queen in each direction
Time Complexity: O(8 * n) where n is number of queens
Space Complexity: O(1) excluding result
"""

class Solution:
    def queensAttacktheKing(self, queens: List[List[int]], king: List[int]) -> List[List[int]]:
        queen_set = {(q[0], q[1]) for q in queens}
        directions = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
        result = []
        
        for dr, dc in directions:
            r, c = king[0] + dr, king[1] + dc
            while 0 <= r < 8 and 0 <= c < 8:
                if (r, c) in queen_set:
                    result.append([r, c])
                    break
                r += dr
                c += dc
        
        return result