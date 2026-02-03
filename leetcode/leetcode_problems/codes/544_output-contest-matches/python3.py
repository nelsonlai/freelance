"""
Problem: Output Contest Matches
Difficulty: Medium
Tags: string

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def findContestMatch(self, n: int) -> str:
        teams = [str(i) for i in range(1, n + 1)]
        
        while len(teams) > 1:
            new_teams = []
            for i in range(len(teams) // 2):
                new_teams.append(f"({teams[i]},{teams[len(teams)-1-i]})")
            teams = new_teams
        
        return teams[0]