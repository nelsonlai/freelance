"""
Problem: Valid Sudoku
Difficulty: Medium
Tags: array, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def isValidSudoku(self, board: List[List[str]]) -> bool:
        seen = set()
        
        for i in range(9):
            for j in range(9):
                if board[i][j] != '.':
                    num = board[i][j]
                    row_key = f"row-{i}-{num}"
                    col_key = f"col-{j}-{num}"
                    box_key = f"box-{i//3}-{j//3}-{num}"
                    
                    if row_key in seen or col_key in seen or box_key in seen:
                        return False
                    
                    seen.add(row_key)
                    seen.add(col_key)
                    seen.add(box_key)
        
        return True