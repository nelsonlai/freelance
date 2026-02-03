"""
Problem: Time Needed to Buy Tickets
Difficulty: Easy
Tags: array, simulation

Approach: Calculate time needed for person k to buy all tickets
Time Complexity: O(n) where n is array length
Space Complexity: O(1)
"""

class Solution:
    def timeRequiredToBuy(self, tickets: List[int], k: int) -> int:
        time = 0
        target = tickets[k]
        
        for i in range(len(tickets)):
            if i < k:
                # People before k: buy min(tickets[i], target) tickets
                time += min(tickets[i], target)
            elif i == k:
                # Person k: buy target tickets
                time += target
            else:
                # People after k: buy min(tickets[i], target - 1) tickets
                time += min(tickets[i], target - 1)
        
        return time