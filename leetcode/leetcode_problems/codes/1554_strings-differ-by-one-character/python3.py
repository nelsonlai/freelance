"""
Problem: Strings Differ by One Character
Difficulty: Medium
Tags: string, hash

Approach: For each position, create hash of string with that position masked, check for duplicates
Time Complexity: O(n * m) where n is number of strings, m is length
Space Complexity: O(n * m) for hash set
"""

class Solution:
    def differByOne(self, dict: List[str]) -> bool:
        n = len(dict)
        if n == 0:
            return False
        
        m = len(dict[0])
        
        for j in range(m):
            seen = set()
            for i in range(n):
                masked = dict[i][:j] + '*' + dict[i][j+1:]
                if masked in seen:
                    return True
                seen.add(masked)
        
        return False