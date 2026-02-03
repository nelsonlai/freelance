"""
Problem: Check If N and Its Double Exist
Difficulty: Easy
Tags: array, hash, sort, search

Approach: Use set to store seen numbers, check if 2*num or num/2 exists
Time Complexity: O(n) where n is length of arr
Space Complexity: O(n) for set
"""

class Solution:
    def checkIfExist(self, arr: List[int]) -> bool:
        seen = set()
        for num in arr:
            if 2 * num in seen or (num % 2 == 0 and num // 2 in seen):
                return True
            seen.add(num)
        return False