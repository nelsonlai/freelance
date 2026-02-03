"""
Problem: Employee Importance
Difficulty: Medium
Tags: array, tree, hash, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

"""
# Definition for Employee.
class Employee:
    def __init__(self, id: int, importance: int, subordinates: List[int]):
        self.id = id
        self.importance = importance
        self.subordinates = subordinates
"""

from collections import defaultdict

class Solution:
    def getImportance(self, employees: List['Employee'], id: int) -> int:
        employee_map = {emp.id: emp for emp in employees}
        
        def dfs(emp_id):
            emp = employee_map[emp_id]
            total = emp.importance
            for sub_id in emp.subordinates:
                total += dfs(sub_id)
            return total
        
        return dfs(id)