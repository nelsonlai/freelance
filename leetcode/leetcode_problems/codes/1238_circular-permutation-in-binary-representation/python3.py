"""
Problem: Circular Permutation in Binary Representation
Difficulty: Medium
Tags: math

Approach: Generate Gray code sequence, rotate to start with given number
Time Complexity: O(2^n) to generate all permutations
Space Complexity: O(2^n) for result
"""

class Solution:
    def circularPermutation(self, n: int, start: int) -> List[int]:
        # Generate Gray code
        gray = [0]
        for i in range(n):
            gray += [g + (1 << i) for g in reversed(gray)]
        
        # Find start index and rotate
        start_idx = gray.index(start)
        return gray[start_idx:] + gray[:start_idx]