"""
Problem: Verbal Arithmetic Puzzle
Difficulty: Hard
Tags: array, string, math

Approach: Backtracking with pruning - assign digits to letters, check equation
Time Complexity: O(10! / (10-n)!) where n is unique letters
Space Complexity: O(n) for recursion stack
"""

class Solution:
    def isSolvable(self, words: List[str], result: str) -> bool:
        all_words = words + [result]
        first_chars = {word[0] for word in all_words}
        chars = set()
        for word in all_words:
            chars.update(word)
        chars = list(chars)
        n = len(chars)
        
        # Calculate coefficient for each character
        coeff = {c: 0 for c in chars}
        for word in words:
            for i, c in enumerate(reversed(word)):
                coeff[c] += 10 ** i
        for i, c in enumerate(reversed(result)):
            coeff[c] -= 10 ** i
        
        used = [False] * 10
        
        def backtrack(idx, total):
            if idx == n:
                return total == 0
            
            char = chars[idx]
            start = 1 if char in first_chars else 0
            
            for digit in range(start, 10):
                if not used[digit]:
                    used[digit] = True
                    if backtrack(idx + 1, total + coeff[char] * digit):
                        return True
                    used[digit] = False
            
            return False
        
        return backtrack(0, 0)