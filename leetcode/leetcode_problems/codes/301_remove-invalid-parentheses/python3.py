"""
Problem: Remove Invalid Parentheses
Difficulty: Hard
Tags: string, search

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def removeInvalidParentheses(self, s: str) -> List[str]:
        def is_valid(s):
            count = 0
            for char in s:
                if char == '(':
                    count += 1
                elif char == ')':
                    count -= 1
                    if count < 0:
                        return False
            return count == 0
        
        def remove(s, last_i, last_j, pair):
            count = 0
            for i in range(last_i, len(s)):
                if s[i] == pair[0]:
                    count += 1
                elif s[i] == pair[1]:
                    count -= 1
                
                if count >= 0:
                    continue
                
                for j in range(last_j, i + 1):
                    if s[j] == pair[1] and (j == last_j or s[j - 1] != pair[1]):
                        remove(s[:j] + s[j + 1:], i, j, pair)
                return
            
            reversed_s = s[::-1]
            if pair[0] == '(':
                remove(reversed_s, 0, 0, [')', '('])
            else:
                result.append(reversed_s)
        
        result = []
        remove(s, 0, 0, ['(', ')'])
        return result