"""
Problem: Decode the Slanted Ciphertext
Difficulty: Medium
Tags: string, matrix

Approach: Reconstruct diagonal reading pattern from encoded text
Time Complexity: O(n) where n is text length
Space Complexity: O(n)
"""

class Solution:
    def decodeCiphertext(self, encodedText: str, rows: int) -> str:
        if not encodedText:
            return ""
        
        cols = len(encodedText) // rows
        result = []
        
        # Read diagonally starting from each column
        for start_col in range(cols):
            row, col = 0, start_col
            while row < rows and col < cols:
                idx = row * cols + col
                result.append(encodedText[idx])
                row += 1
                col += 1
        
        # Remove trailing spaces
        return ''.join(result).rstrip()