"""
Problem: Keyboard Row
Difficulty: Easy
Tags: array, string, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def findWords(self, words: List[str]) -> List[str]:
        rows = [
            set("qwertyuiop"),
            set("asdfghjkl"),
            set("zxcvbnm")
        ]
        
        result = []
        for word in words:
            word_lower = word.lower()
            for row in rows:
                if all(c in row for c in word_lower):
                    result.append(word)
                    break
        
        return result