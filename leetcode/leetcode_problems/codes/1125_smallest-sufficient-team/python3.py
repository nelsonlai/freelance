"""
Problem: Smallest Sufficient Team
Difficulty: Hard
Tags: array, string, dp, math

Approach: Bitmask DP - use bitmask to represent skill set, find minimum team
Time Complexity: O(2^m * n) where m is number of skills, n is number of people
Space Complexity: O(2^m) for DP table
"""

class Solution:
    def smallestSufficientTeam(self, req_skills: List[str], people: List[List[str]]) -> List[int]:
        skill_to_id = {skill: i for i, skill in enumerate(req_skills)}
        n_skills = len(req_skills)
        target = (1 << n_skills) - 1
        
        # Convert people to bitmasks
        people_skills = []
        for person in people:
            mask = 0
            for skill in person:
                mask |= (1 << skill_to_id[skill])
            people_skills.append(mask)
        
        # DP: dp[mask] = minimum team for mask
        dp = {0: []}
        
        for i, person_mask in enumerate(people_skills):
            new_dp = dp.copy()
            for mask, team in dp.items():
                new_mask = mask | person_mask
                if new_mask not in new_dp or len(team) + 1 < len(new_dp[new_mask]):
                    new_dp[new_mask] = team + [i]
            dp = new_dp
        
        return dp[target]