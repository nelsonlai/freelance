"""
Problem: Analyze User Website Visit Pattern
Difficulty: Medium
Tags: array, string, graph, hash, sort

Approach: Group by user, sort by timestamp, generate all 3-sequences, count frequency
Time Complexity: O(n^3) in worst case where n is number of visits per user
Space Complexity: O(n^3) for storing sequences
"""

class Solution:
    def mostVisitedPattern(self, username: List[str], timestamp: List[int], website: List[str]) -> List[str]:
        from collections import defaultdict
        from itertools import combinations
        
        # Group visits by user
        user_visits = defaultdict(list)
        for u, t, w in zip(username, timestamp, website):
            user_visits[u].append((t, w))
        
        # Sort each user's visits by timestamp
        for user in user_visits:
            user_visits[user].sort()
        
        # Count 3-sequences
        sequence_count = defaultdict(int)
        for user, visits in user_visits.items():
            websites = [w for _, w in visits]
            sequences = set(combinations(websites, 3))
            for seq in sequences:
                sequence_count[seq] += 1
        
        # Find most visited pattern
        max_count = max(sequence_count.values()) if sequence_count else 0
        candidates = [seq for seq, count in sequence_count.items() if count == max_count]
        return list(min(candidates)) if candidates else []