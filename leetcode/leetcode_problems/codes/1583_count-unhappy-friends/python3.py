"""
Problem: Count Unhappy Friends
Difficulty: Medium
Tags: array, sort

Approach: Build preference map, check if any friend prefers someone over their current pair
Time Complexity: O(n^2) where n is number of friends
Space Complexity: O(n^2) for preference map
"""

class Solution:
    def unhappyFriends(self, n: int, preferences: List[List[int]], pairs: List[List[int]]) -> int:
        pref_map = {}
        for i, pref in enumerate(preferences):
            pref_map[i] = {person: rank for rank, person in enumerate(pref)}
        
        pair_map = {}
        for x, y in pairs:
            pair_map[x] = y
            pair_map[y] = x
        
        unhappy = set()
        
        for x in range(n):
            y = pair_map[x]
            for u in range(n):
                if u != x and u != y:
                    v = pair_map[u]
                    if pref_map[x].get(u, n) < pref_map[x].get(y, n) and \
                       pref_map[u].get(x, n) < pref_map[u].get(v, n):
                        unhappy.add(x)
                        unhappy.add(u)
        
        return len(unhappy)