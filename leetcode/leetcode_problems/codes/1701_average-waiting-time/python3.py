"""
Problem: Average Waiting Time
Difficulty: Medium
Tags: array, sort, simulation

Approach: Simulate serving customers, track finish time and waiting time
Time Complexity: O(n) where n is number of customers
Space Complexity: O(1)
"""

class Solution:
    def averageWaitingTime(self, customers: List[List[int]]) -> float:
        finish_time = 0
        total_waiting = 0
        
        for arrival, prep_time in customers:
            if finish_time < arrival:
                finish_time = arrival
            finish_time += prep_time
            total_waiting += finish_time - arrival
        
        return total_waiting / len(customers)