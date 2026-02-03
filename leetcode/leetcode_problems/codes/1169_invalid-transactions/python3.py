"""
Problem: Invalid Transactions
Difficulty: Medium
Tags: array, string, hash, sort

Approach: Parse transactions, group by name, check for invalid conditions
Time Complexity: O(n^2) in worst case where n is number of transactions
Space Complexity: O(n) for storing transactions
"""

class Solution:
    def invalidTransactions(self, transactions: List[str]) -> List[str]:
        from collections import defaultdict
        
        parsed = []
        for t in transactions:
            name, time, amount, city = t.split(',')
            parsed.append((name, int(time), int(amount), city))
        
        invalid = set()
        name_to_transactions = defaultdict(list)
        
        for i, (name, time, amount, city) in enumerate(parsed):
            name_to_transactions[name].append((time, city, i))
            
            if amount > 1000:
                invalid.add(i)
        
        for name, trans_list in name_to_transactions.items():
            trans_list.sort()
            for i in range(len(trans_list)):
                time1, city1, idx1 = trans_list[i]
                for j in range(i + 1, len(trans_list)):
                    time2, city2, idx2 = trans_list[j]
                    if time2 - time1 > 60:
                        break
                    if city1 != city2:
                        invalid.add(idx1)
                        invalid.add(idx2)
        
        return [transactions[i] for i in invalid]