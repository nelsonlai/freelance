"""
Problem: Alert Using Same Key-Card Three or More Times in a One Hour Period
Difficulty: Medium
Tags: array, string, hash, sort

Approach: Group by name, sort times, check if any 3 consecutive times are within 1 hour
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for hash map
"""

from collections import defaultdict

class Solution:
    def alertNames(self, keyName: List[str], keyTime: List[str]) -> List[str]:
        name_times = defaultdict(list)
        
        for name, time_str in zip(keyName, keyTime):
            hours, minutes = map(int, time_str.split(':'))
            total_minutes = hours * 60 + minutes
            name_times[name].append(total_minutes)
        
        result = []
        for name, times in name_times.items():
            times.sort()
            for i in range(len(times) - 2):
                if times[i + 2] - times[i] <= 60:
                    result.append(name)
                    break
        
        return sorted(result)