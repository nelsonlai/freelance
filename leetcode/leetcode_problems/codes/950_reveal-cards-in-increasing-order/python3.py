"""
Problem: Reveal Cards In Increasing Order
Difficulty: Medium
Tags: array, sort, queue

Approach: Simulate reverse process - start with sorted deck and work backwards
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for deque
"""

from collections import deque

class Solution:
    def deckRevealedIncreasing(self, deck: List[int]) -> List[int]:
        deck.sort()
        n = len(deck)
        result = [0] * n
        indices = deque(range(n))
        
        for card in deck:
            idx = indices.popleft()
            result[idx] = card
            if indices:
                indices.append(indices.popleft())
        
        return result