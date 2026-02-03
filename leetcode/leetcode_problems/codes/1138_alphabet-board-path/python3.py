"""
Problem: Alphabet Board Path
Difficulty: Medium
Tags: string, hash

Approach: Calculate position for each character, move U/D then L/R (special case for 'z')
Time Complexity: O(n) where n is the length of target
Space Complexity: O(1)
"""

class Solution:
    def alphabetBoardPath(self, target: str) -> str:
        board = ["abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"]
        char_to_pos = {}
        for i, row in enumerate(board):
            for j, char in enumerate(row):
                char_to_pos[char] = (i, j)
        
        result = []
        r, c = 0, 0
        
        for char in target:
            tr, tc = char_to_pos[char]
            
            # Special case: if going to 'z', move left first, then down
            if char == 'z' and c != 0:
                result.append('L' * c)
                c = 0
                result.append('D' * (tr - r))
                r = tr
            else:
                # Move vertically first
                if tr < r:
                    result.append('U' * (r - tr))
                elif tr > r:
                    result.append('D' * (tr - r))
                
                # Then move horizontally
                if tc < c:
                    result.append('L' * (c - tc))
                elif tc > c:
                    result.append('R' * (tc - c))
            
            result.append('!')
            r, c = tr, tc
        
        return ''.join(result)