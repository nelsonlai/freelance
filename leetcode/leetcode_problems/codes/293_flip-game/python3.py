"""
Problem: Flip Game
Difficulty: Easy
Tags: string

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def generatePossibleNextMoves(self, currentState: str) -> List[str]:
        result = []
        for i in range(len(currentState) - 1):
            if currentState[i] == '+' and currentState[i + 1] == '+':
                result.append(currentState[:i] + '--' + currentState[i + 2:])
        return result