"""
Problem: Stone Game VI
Difficulty: Medium
Tags: array, greedy, math, sort

Approach: Sort by sum of alice and bob values, Alice and Bob take turns picking
Time Complexity: O(n log n) for sorting
Space Complexity: O(n)
"""

class Solution:
    def stoneGameVI(self, aliceValues: List[int], bobValues: List[int]) -> int:
        stones = sorted([(aliceValues[i] + bobValues[i], aliceValues[i], bobValues[i]) 
                        for i in range(len(aliceValues))], reverse=True)
        
        alice_score = 0
        bob_score = 0
        
        for i, (_, alice_val, bob_val) in enumerate(stones):
            if i % 2 == 0:
                alice_score += alice_val
            else:
                bob_score += bob_val
        
        if alice_score > bob_score:
            return 1
        elif alice_score < bob_score:
            return -1
        else:
            return 0