"""
Problem: Maximum Number of Non-Overlapping Substrings
Difficulty: Hard
Tags: string, tree, greedy

Approach: Find valid substrings (containing all occurrences of their characters), greedy select shortest first
Time Complexity: O(n * 26) where n is length of s
Space Complexity: O(n) for result
"""

class Solution:
    def maxNumOfSubstrings(self, s: str) -> List[str]:
        first = {}
        last = {}
        for i, char in enumerate(s):
            if char not in first:
                first[char] = i
            last[char] = i
        
        def extend(start, end):
            right = end
            i = start
            while i <= right:
                if first[s[i]] < start:
                    return None
                right = max(right, last[s[i]])
                i += 1
            return (start, right)
        
        intervals = []
        for char in set(s):
            interval = extend(first[char], last[char])
            if interval:
                intervals.append(interval)
        
        intervals.sort(key=lambda x: (x[1], x[0]))
        
        result = []
        prev_end = -1
        for start, end in intervals:
            if start > prev_end:
                result.append(s[start:end+1])
                prev_end = end
        
        return result