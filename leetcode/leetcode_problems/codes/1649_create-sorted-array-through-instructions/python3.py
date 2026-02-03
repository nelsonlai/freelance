"""
Problem: Create Sorted Array through Instructions
Difficulty: Hard
Tags: array, tree, sort, search, binary indexed tree

Approach: Use Binary Indexed Tree (Fenwick Tree) to count numbers less than and greater than current
Time Complexity: O(n log m) where n is instructions, m is max value
Space Complexity: O(m) for BIT
"""

MOD = 10**9 + 7

class BIT:
    def __init__(self, size):
        self.size = size
        self.tree = [0] * (size + 1)
    
    def update(self, index, delta):
        while index <= self.size:
            self.tree[index] += delta
            index += index & -index
    
    def query(self, index):
        result = 0
        while index > 0:
            result += self.tree[index]
            index -= index & -index
        return result

class Solution:
    def createSortedArray(self, instructions: List[int]) -> int:
        max_val = max(instructions)
        bit = BIT(max_val)
        cost = 0
        
        for num in instructions:
            left = bit.query(num - 1)
            right = bit.query(max_val) - bit.query(num)
            cost = (cost + min(left, right)) % MOD
            bit.update(num, 1)
        
        return cost