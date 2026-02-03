"""
Problem: Find the Winner of an Array Game
Difficulty: Medium
Tags: array

Approach: Simulate - track current winner and consecutive wins, if wins k times return
Time Complexity: O(n) where n is length of arr
Space Complexity: O(1)
"""

class Solution:
    def getWinner(self, arr: List[int], k: int) -> int:
        if k >= len(arr):
            return max(arr)
        
        winner = arr[0]
        wins = 0
        
        for i in range(1, len(arr)):
            if arr[i] > winner:
                winner = arr[i]
                wins = 1
            else:
                wins += 1
            
            if wins == k:
                return winner
        
        return winner