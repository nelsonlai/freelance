"""
Problem: Number of Valid Words for Each Puzzle
Difficulty: Hard
Tags: array, string, hash

Approach: Use bitmask to represent character sets, count words matching puzzle constraints
Time Complexity: O(W * L + P * 2^7) where W is words, L is avg word length, P is puzzles
Space Complexity: O(W) for word masks
"""

class Solution:
    def findNumOfValidWords(self, words: List[str], puzzles: List[str]) -> List[int]:
        from collections import Counter
        
        # Convert words to bitmasks
        word_masks = Counter()
        for word in words:
            mask = 0
            for char in word:
                mask |= (1 << (ord(char) - ord('a')))
            word_masks[mask] += 1
        
        result = []
        for puzzle in puzzles:
            first_char_mask = 1 << (ord(puzzle[0]) - ord('a'))
            puzzle_mask = 0
            for char in puzzle:
                puzzle_mask |= (1 << (ord(char) - ord('a')))
            
            count = 0
            # Try all subsets of puzzle characters that include first character
            subset = puzzle_mask
            while subset:
                if subset & first_char_mask:
                    count += word_masks[subset]
                subset = (subset - 1) & puzzle_mask
            
            result.append(count)
        
        return result