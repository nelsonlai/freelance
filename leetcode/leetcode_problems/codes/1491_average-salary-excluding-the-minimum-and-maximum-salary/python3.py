"""
Problem: Average Salary Excluding the Minimum and Maximum Salary
Difficulty: Easy
Tags: array, sort

Approach: Sum all salaries, subtract min and max, divide by (n-2)
Time Complexity: O(n) where n is length of salary
Space Complexity: O(1)
"""

class Solution:
    def average(self, salary: List[int]) -> float:
        return (sum(salary) - min(salary) - max(salary)) / (len(salary) - 2)