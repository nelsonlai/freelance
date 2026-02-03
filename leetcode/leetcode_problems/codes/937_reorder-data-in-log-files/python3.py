"""
Problem: Reorder Data in Log Files
Difficulty: Medium
Tags: array, string, graph, sort

Approach: Separate letter logs and digit logs, sort letter logs by content then identifier
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for separating logs
"""

class Solution:
    def reorderLogFiles(self, logs: List[str]) -> List[str]:
        letter_logs = []
        digit_logs = []
        
        for log in logs:
            parts = log.split(' ', 1)
            if parts[1][0].isdigit():
                digit_logs.append(log)
            else:
                letter_logs.append((parts[1], parts[0], log))
        
        letter_logs.sort()
        return [log for _, _, log in letter_logs] + digit_logs