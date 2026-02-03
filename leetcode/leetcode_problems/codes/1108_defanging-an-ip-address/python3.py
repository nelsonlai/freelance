"""
Problem: Defanging an IP Address
Difficulty: Easy
Tags: string

Approach: Replace '.' with '[.]'
Time Complexity: O(n)
Space Complexity: O(n) for result
"""

class Solution:
    def defangIPaddr(self, address: str) -> str:
        return address.replace('.', '[.]')