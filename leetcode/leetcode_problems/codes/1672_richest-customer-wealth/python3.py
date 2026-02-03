"""
Problem: Richest Customer Wealth
Difficulty: Easy
Tags: array

Approach: Sum each customer's accounts, find maximum
Time Complexity: O(n * m) where n is customers, m is accounts per customer
Space Complexity: O(1)
"""

class Solution:
    def maximumWealth(self, accounts: List[List[int]]) -> int:
        return max(sum(customer) for customer in accounts)