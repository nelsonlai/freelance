"""
Problem: Letter Combinations of a Phone Number
Difficulty: Medium
Tags: string, hash

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        if not digits:
            return []
        
        phone_map = {
            '2': 'abc', '3': 'def', '4': 'ghi', '5': 'jkl',
            '6': 'mno', '7': 'pqrs', '8': 'tuv', '9': 'wxyz'
        }
        
        result = []
        
        def backtrack(index, current):
            if index == len(digits):
                result.append(current)
                return
            
            for char in phone_map[digits[index]]:
                backtrack(index + 1, current + char)
        
        backtrack(0, "")
        return result