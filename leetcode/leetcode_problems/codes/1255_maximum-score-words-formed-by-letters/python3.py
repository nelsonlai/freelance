"""
Problem: Maximum Score Words Formed by Letters
Difficulty: Hard
Tags: array, string, dp, hash

Approach: Backtracking - try all word combinations, check if can form with available letters
Time Complexity: O(2^n * m) where n is words, m is avg word length
Space Complexity: O(n) for recursion stack
"""

from collections import Counter

class Solution:
    def maxScoreWords(self, words: List[str], letters: List[str], score: List[int]) -> int:
        letter_count = Counter(letters)
        word_scores = []
        word_counts = []
        
        for word in words:
            word_count = Counter(word)
            word_score = sum(score[ord(c) - ord('a')] * word_count[c] for c in word_count)
            word_scores.append(word_score)
            word_counts.append(word_count)
        
        max_score = 0
        
        def backtrack(idx, current_count, current_score):
            nonlocal max_score
            max_score = max(max_score, current_score)
            
            for i in range(idx, len(words)):
                # Check if can use this word
                can_use = True
                new_count = current_count.copy()
                for char, need in word_counts[i].items():
                    if new_count.get(char, 0) < need:
                        can_use = False
                        break
                    new_count[char] -= need
                
                if can_use:
                    backtrack(i + 1, new_count, current_score + word_scores[i])
        
        backtrack(0, letter_count, 0)
        return max_score