"""
Problem: Next Closest Time
Difficulty: Medium
Tags: string, hash

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def nextClosestTime(self, time: str) -> str:
        digits = sorted(set(time.replace(':', '')))
        time_list = list(time.replace(':', ''))
        
        for i in range(3, -1, -1):
            for digit in digits:
                if digit > time_list[i]:
                    time_list[i] = digit
                    for j in range(i + 1, 4):
                        time_list[j] = digits[0]
                    candidate = ''.join(time_list)
                    if candidate[:2] < '24' and candidate[2:] < '60':
                        return candidate[:2] + ':' + candidate[2:]
        
        return digits[0] * 2 + ':' + digits[0] * 2