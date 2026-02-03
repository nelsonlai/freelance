"""
Problem: Evaluate the Bracket Pairs of a String
Difficulty: Medium
Tags: array, string, hash

Approach: Build knowledge map, replace brackets with values
Time Complexity: O(n + k) where n is string length, k is knowledge size
Space Complexity: O(k)
"""

class Solution:
    def evaluate(self, s: str, knowledge: List[List[str]]) -> str:
        knowledge_map = {key: value for key, value in knowledge}
        result = []
        i = 0
        
        while i < len(s):
            if s[i] == '(':
                j = i + 1
                while s[j] != ')':
                    j += 1
                key = s[i+1:j]
                result.append(knowledge_map.get(key, '?'))
                i = j + 1
            else:
                result.append(s[i])
                i += 1
        
        return ''.join(result)