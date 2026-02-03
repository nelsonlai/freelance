"""
Problem: Remove Sub-Folders from the Filesystem
Difficulty: Medium
Tags: array, string, search

Approach: Sort folders, keep only folders that are not subfolders of previous ones
Time Complexity: O(n log n) for sorting
Space Complexity: O(1) excluding result
"""

class Solution:
    def removeSubfolders(self, folder: List[str]) -> List[str]:
        folder.sort()
        result = [folder[0]]
        
        for f in folder[1:]:
            # Check if current folder is a subfolder of last added folder
            last = result[-1]
            if not f.startswith(last + '/'):
                result.append(f)
        
        return result