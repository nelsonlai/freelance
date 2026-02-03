"""
Problem: Optimal Account Balancing
Difficulty: Hard
Tags: array, dp

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

from collections import defaultdict

class Solution:
    def minTransfers(self, transactions: List[List[int]]) -> int:
        balance = defaultdict(int)
        for from_person, to_person, amount in transactions:
            balance[from_person] -= amount
            balance[to_person] += amount
        
        debts = [amount for amount in balance.values() if amount != 0]
        
        def dfs(start):
            while start < len(debts) and debts[start] == 0:
                start += 1
            if start == len(debts):
                return 0
            
            min_transfers = float('inf')
            for i in range(start + 1, len(debts)):
                if debts[start] * debts[i] < 0:
                    debts[i] += debts[start]
                    min_transfers = min(min_transfers, 1 + dfs(start + 1))
                    debts[i] -= debts[start]
            
            return min_transfers
        
        return dfs(0)