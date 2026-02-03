"""
Problem: Fancy Sequence
Difficulty: Hard
Tags: design, math, lazy propagation

Approach: Use lazy propagation - track cumulative add and multiply operations
Time Complexity: O(1) for append/addAll/multAll, O(1) for getIndex
Space Complexity: O(n) for values
"""

MOD = 10**9 + 7

class Fancy:

    def __init__(self):
        self.values = []
        self.add = 0
        self.mult = 1

    def append(self, val: int) -> None:
        # Reverse operations to get original value
        val = (val - self.add) * pow(self.mult, MOD - 2, MOD) % MOD
        self.values.append(val)

    def addAll(self, inc: int) -> None:
        self.add = (self.add + inc) % MOD

    def multAll(self, m: int) -> None:
        self.add = (self.add * m) % MOD
        self.mult = (self.mult * m) % MOD

    def getIndex(self, idx: int) -> int:
        if idx >= len(self.values):
            return -1
        return (self.values[idx] * self.mult + self.add) % MOD