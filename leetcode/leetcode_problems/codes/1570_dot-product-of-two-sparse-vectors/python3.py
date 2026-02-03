"""
Problem: Dot Product of Two Sparse Vectors
Difficulty: Medium
Tags: array, hash

Approach: Store only non-zero indices and values, compute dot product efficiently
Time Complexity: O(n) for init, O(k) for dotProduct where k is non-zero count
Space Complexity: O(k) for non-zero entries
"""

class SparseVector:
    def __init__(self, nums: List[int]):
        self.non_zero = {}
        for i, num in enumerate(nums):
            if num != 0:
                self.non_zero[i] = num

    # Return the dotProduct of two sparse vectors
    def dotProduct(self, vec: 'SparseVector') -> int:
        result = 0
        for idx, val in self.non_zero.items():
            if idx in vec.non_zero:
                result += val * vec.non_zero[idx]
        return result