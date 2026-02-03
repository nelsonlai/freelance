"""
Problem: Delete Columns to Make Sorted II
Difficulty: Medium
Tags: array, string, graph, greedy

Approach: Greedy - keep columns that maintain lexicographic order, track which rows are already sorted
Time Complexity: O(n * m) where n is number of strings, m is length
Space Complexity: O(n) for tracking sorted rows
"""

class Solution:
    def minDeletionSize(self, strs: List[str]) -> int:
        n = len(strs)
        m = len(strs[0])
        deleted = 0
        sorted_rows = [False] * (n - 1)  # Track if row i is sorted relative to row i+1
        
        for j in range(m):
            # Check if we can keep this column
            can_keep = True
            new_sorted = sorted_rows.copy()
            
            for i in range(n - 1):
                if not sorted_rows[i] and strs[i][j] > strs[i + 1][j]:
                    can_keep = False
                    break
                elif not sorted_rows[i] and strs[i][j] < strs[i + 1][j]:
                    new_sorted[i] = True
            
            if can_keep:
                sorted_rows = new_sorted
            else:
                deleted += 1
        
        return deleted