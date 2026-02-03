"""
Problem: Finding the Users Active Minutes
Difficulty: Medium
Tags: array, hash

Approach: Count unique minutes per user, then count users per UAM
Time Complexity: O(n) where n is logs
Space Complexity: O(n)
"""

from collections import defaultdict

class Solution:
    def findingUsersActiveMinutes(self, logs: List[List[int]], k: int) -> List[int]:
        user_minutes = defaultdict(set)
        
        for user_id, minute in logs:
            user_minutes[user_id].add(minute)
        
        uam_count = defaultdict(int)
        for user_id in user_minutes:
            uam = len(user_minutes[user_id])
            if 1 <= uam <= k:
                uam_count[uam] += 1
        
        return [uam_count[i] for i in range(1, k + 1)]