"""
Problem: Compare Strings by Frequency of the Smallest Character
Difficulty: Medium
Tags: array, string, graph, hash, sort, search

Approach: Calculate f(s) for each string, use binary search to count words with higher frequency
Time Complexity: O(n log n) where n is length of words
Space Complexity: O(n) for storing frequencies
"""

class Solution:
    def numSmallerByFrequency(self, queries: List[str], words: List[str]) -> List[int]:
        def f(s):
            if not s:
                return 0
            min_char = min(s)
            return s.count(min_char)
        
        word_freqs = sorted([f(word) for word in words])
        result = []
        
        for query in queries:
            query_freq = f(query)
            # Binary search for count of words with freq > query_freq
            import bisect
            count = len(word_freqs) - bisect.bisect_right(word_freqs, query_freq)
            result.append(count)
        
        return result