"""
Problem: Display Table of Food Orders in a Restaurant
Difficulty: Medium
Tags: array, string, hash, sort

Approach: Group orders by table, count items per table, format output
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for orders map
"""

from collections import defaultdict

class Solution:
    def displayTable(self, orders: List[List[str]]) -> List[List[str]]:
        tables = defaultdict(lambda: defaultdict(int))
        foods = set()
        
        for _, table, food in orders:
            tables[int(table)][food] += 1
            foods.add(food)
        
        sorted_foods = sorted(foods)
        result = [['Table'] + sorted_foods]
        
        for table in sorted(tables.keys()):
            row = [str(table)]
            for food in sorted_foods:
                row.append(str(tables[table][food]))
            result.append(row)
        
        return result