"""
Problem: Making File Names Unique
Difficulty: Medium
Tags: array, string, hash

Approach: Track used names, if exists append (k) and increment k
Time Complexity: O(n^2) in worst case
Space Complexity: O(n) for used set
"""

class Solution:
    def getFolderNames(self, names: List[str]) -> List[str]:
        used = set()
        result = []
        
        for name in names:
            if name not in used:
                result.append(name)
                used.add(name)
            else:
                k = 1
                while f"{name}({k})" in used:
                    k += 1
                new_name = f"{name}({k})"
                result.append(new_name)
                used.add(new_name)
        
        return result