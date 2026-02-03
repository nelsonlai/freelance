"""
Problem: Iterator for Combination
Difficulty: Medium
Tags: string, graph, sort

Approach: Generate all combinations, store in list, iterate through them
Time Complexity: O(C(n,k)) for init, O(1) for next/hasNext
Space Complexity: O(C(n,k)) for storing combinations
"""

from itertools import combinations

class CombinationIterator:

    def __init__(self, characters: str, combinationLength: int):
        self.combos = [''.join(combo) for combo in combinations(characters, combinationLength)]
        self.idx = 0

    def next(self) -> str:
        result = self.combos[self.idx]
        self.idx += 1
        return result

    def hasNext(self) -> bool:
        return self.idx < len(self.combos)