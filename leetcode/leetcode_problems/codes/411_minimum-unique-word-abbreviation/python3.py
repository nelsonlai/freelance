"""
Problem: Minimum Unique Word Abbreviation
Difficulty: Hard
Tags: array, string, tree

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

class Solution:
    def minAbbreviation(self, target: str, dictionary: List[str]) -> str:
        def getAbbr(word, mask):
            abbr = []
            count = 0
            for i in range(len(word)):
                if mask & (1 << i):
                    if count > 0:
                        abbr.append(str(count))
                        count = 0
                    abbr.append(word[i])
                else:
                    count += 1
            if count > 0:
                abbr.append(str(count))
            return ''.join(abbr)
        
        def isValid(mask):
            for word in dictionary:
                if len(word) != len(target):
                    continue
                valid = True
                for i in range(len(target)):
                    if mask & (1 << i):
                        if target[i] != word[i]:
                            valid = False
                            break
                if valid:
                    return False
            return True
        
        n = len(target)
        min_len = float('inf')
        result = target
        
        for mask in range(1 << n):
            if isValid(mask):
                abbr = getAbbr(target, mask)
                if len(abbr) < min_len:
                    min_len = len(abbr)
                    result = abbr
        
        return result