"""
Problem: Maximum Number of Ones
Difficulty: Hard
Tags: greedy, math, sort, queue, heap

Approach: Count frequency of each position in repeating pattern, choose positions with highest frequency
Time Complexity: O(sideLength^2) where sideLength is the pattern size
Space Complexity: O(sideLength^2) for frequency counting
"""

class Solution:
    def maximumNumberOfOnes(self, width: int, height: int, sideLength: int, maxOnes: int) -> int:
        # Count how many times each position in the pattern appears
        freq = []
        for i in range(sideLength):
            for j in range(sideLength):
                # Count occurrences of position (i, j) in the full grid
                count_i = (width - i + sideLength - 1) // sideLength
                count_j = (height - j + sideLength - 1) // sideLength
                freq.append(count_i * count_j)
        
        # Choose top maxOnes positions
        freq.sort(reverse=True)
        return sum(freq[:maxOnes])