"""
Problem: Check Array Formation Through Concatenation
Difficulty: Easy
Tags: array, hash

Approach: Map first element of each piece to the piece, try to match arr sequentially
Time Complexity: O(n) where n is length of arr
Space Complexity: O(m) where m is number of pieces
"""

class Solution:
    def canFormArray(self, arr: List[int], pieces: List[List[int]]) -> bool:
        piece_map = {piece[0]: piece for piece in pieces}
        i = 0
        
        while i < len(arr):
            if arr[i] not in piece_map:
                return False
            
            piece = piece_map[arr[i]]
            for j in range(len(piece)):
                if i + j >= len(arr) or arr[i + j] != piece[j]:
                    return False
                i += 1
        
        return True