"""
Problem: Count Items Matching a Rule
Difficulty: Easy
Tags: array, string

Approach: Check each item against the rule
Time Complexity: O(n) where n is number of items
Space Complexity: O(1)
"""

class Solution:
    def countMatches(self, items: List[List[str]], ruleKey: str, ruleValue: str) -> int:
        rule_map = {'type': 0, 'color': 1, 'name': 2}
        idx = rule_map[ruleKey]
        
        return sum(1 for item in items if item[idx] == ruleValue)