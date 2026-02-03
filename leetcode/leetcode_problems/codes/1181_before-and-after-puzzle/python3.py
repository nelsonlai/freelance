"""
Problem: Before and After Puzzle
Difficulty: Medium
Tags: array, string, graph, hash, sort

Approach: Group phrases by first and last word, combine matching phrases
Time Complexity: O(n^2) where n is number of phrases
Space Complexity: O(n) for hash maps
"""

class Solution:
    def beforeAndAfterPuzzles(self, phrases: List[str]) -> List[str]:
        from collections import defaultdict
        
        first_word_map = defaultdict(list)
        last_word_map = defaultdict(list)
        
        for i, phrase in enumerate(phrases):
            words = phrase.split()
            first_word = words[0]
            last_word = words[-1]
            first_word_map[first_word].append(i)
            last_word_map[last_word].append(i)
        
        result = set()
        for last_word, indices in last_word_map.items():
            if last_word in first_word_map:
                for i in indices:
                    for j in first_word_map[last_word]:
                        if i != j:
                            words_i = phrases[i].split()
                            words_j = phrases[j].split()
                            combined = ' '.join(words_i[:-1] + words_j)
                            result.add(combined)
        
        return sorted(list(result))