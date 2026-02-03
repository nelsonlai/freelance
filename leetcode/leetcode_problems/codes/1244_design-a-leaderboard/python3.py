"""
Problem: Design A Leaderboard
Difficulty: Medium
Tags: hash, sort

Approach: Use hash map to store scores, sort for topK
Time Complexity: O(1) for addScore/reset, O(n log n) for topK
Space Complexity: O(n) for score map
"""

class Leaderboard:

    def __init__(self):
        self.scores = {}

    def addScore(self, playerId: int, score: int) -> None:
        if playerId not in self.scores:
            self.scores[playerId] = 0
        self.scores[playerId] += score

    def top(self, K: int) -> int:
        sorted_scores = sorted(self.scores.values(), reverse=True)
        return sum(sorted_scores[:K])

    def reset(self, playerId: int) -> None:
        if playerId in self.scores:
            del self.scores[playerId]