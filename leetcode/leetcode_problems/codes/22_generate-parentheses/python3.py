"""
Problem: Generate Parentheses
Difficulty: Medium
Tags: string, dp

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        result = []
        
        def backtrack(current, open_count, close_count):
            if len(current) == 2 * n:
                result.append(current)
                return
            
            if open_count < n:
                backtrack(current + '(', open_count + 1, close_count)
            
            if close_count < open_count:
                backtrack(current + ')', open_count, close_count + 1)
        
        backtrack("", 0, 0)
        return result