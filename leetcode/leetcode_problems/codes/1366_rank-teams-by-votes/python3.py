"""
Problem: Rank Teams by Votes
Difficulty: Medium
Tags: array, string, hash, sort

Approach: Count votes for each position, sort by vote counts then alphabetically
Time Complexity: O(n * m + m log m) where n is votes, m is teams
Space Complexity: O(m) for vote counts
"""

from collections import defaultdict

class Solution:
    def rankTeams(self, votes: List[str]) -> str:
        n = len(votes[0])
        vote_count = defaultdict(lambda: [0] * n)
        
        for vote in votes:
            for i, team in enumerate(vote):
                vote_count[team][i] += 1
        
        teams = sorted(vote_count.keys())
        return ''.join(sorted(teams, key=lambda t: (vote_count[t], -ord(t)), reverse=True))