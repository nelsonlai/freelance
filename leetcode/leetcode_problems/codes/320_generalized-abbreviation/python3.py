"""
Problem: Generalized Abbreviation
Difficulty: Medium
Tags: string, tree

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

class Solution:
    def generateAbbreviations(self, word: str) -> List[str]:
        result = []
        
        def backtrack(index, current, count):
            if index == len(word):
                if count > 0:
                    current += str(count)
                result.append(current)
                return
            
            backtrack(index + 1, current, count + 1)
            
            if count > 0:
                backtrack(index + 1, current + str(count) + word[index], 0)
            else:
                backtrack(index + 1, current + word[index], 0)
        
        backtrack(0, "", 0)
        return result