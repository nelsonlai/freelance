"""
Problem: Longest Subsequence Repeated k Times
Difficulty: Hard
Tags: string, graph, greedy, backtracking

Approach: Generate candidate subsequences, check if they appear k times
Time Complexity: O(26^L * n) where L is length of subsequence
Space Complexity: O(L)
"""

from collections import Counter

class Solution:
    def longestSubsequenceRepeatedK(self, s: str, k: int) -> str:
        # Count character frequencies
        count = Counter(s)
        # Only consider characters that appear at least k times
        candidates = [char for char, freq in count.items() if freq >= k]
        candidates.sort()
        
        # Try all possible subsequences of increasing length
        result = ""
        
        def isSubsequence(subseq, s):
            """Check if subseq appears k times in s"""
            occurrences = 0
            i = 0
            while i < len(s) and occurrences < k:
                j = 0
                start = i
                while start < len(s) and j < len(subseq):
                    if s[start] == subseq[j]:
                        j += 1
                    start += 1
                if j == len(subseq):
                    occurrences += 1
                    i = start
                else:
                    i += 1
            return occurrences >= k
        
        # Generate all possible subsequences using backtracking
        def backtrack(current, remaining_chars):
            nonlocal result
            if len(current) > len(result) and isSubsequence(current, s):
                result = current
            
            if len(current) >= len(s) // k:
                return
            
            # Try adding each remaining character
            for i, char in enumerate(remaining_chars):
                new_current = current + char
                backtrack(new_current, remaining_chars)
        
        backtrack("", candidates)
        return result