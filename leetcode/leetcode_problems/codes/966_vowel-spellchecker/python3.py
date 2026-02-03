"""
Problem: Vowel Spellchecker
Difficulty: Medium
Tags: array, string, hash

Approach: Use three hash maps: exact match, case-insensitive, vowel-insensitive
Time Complexity: O(n + m) where n is wordlist size, m is queries size
Space Complexity: O(n) for hash maps
"""

import re

class Solution:
    def spellchecker(self, wordlist: List[str], queries: List[str]) -> List[str]:
        exact_match = {word: word for word in wordlist}
        case_insensitive = {}
        vowel_insensitive = {}
        
        def devowel(word):
            return re.sub(r'[aeiouAEIOU]', '#', word)
        
        for word in wordlist:
            lower = word.lower()
            if lower not in case_insensitive:
                case_insensitive[lower] = word
            devoweled = devowel(lower)
            if devoweled not in vowel_insensitive:
                vowel_insensitive[devoweled] = word
        
        result = []
        for query in queries:
            if query in exact_match:
                result.append(query)
            elif query.lower() in case_insensitive:
                result.append(case_insensitive[query.lower()])
            elif devowel(query.lower()) in vowel_insensitive:
                result.append(vowel_insensitive[devowel(query.lower())])
            else:
                result.append("")
        
        return result