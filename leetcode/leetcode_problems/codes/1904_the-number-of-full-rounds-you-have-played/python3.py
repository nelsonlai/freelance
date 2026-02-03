"""
Problem: The Number of Full Rounds You Have Played
Difficulty: Medium
Tags: string, math

Approach: Convert to minutes, round up login, round down logout, count 15-min intervals
Time Complexity: O(1)
Space Complexity: O(1)
"""

class Solution:
    def numberOfRounds(self, loginTime: str, logoutTime: str) -> int:
        def toMinutes(time):
            h, m = map(int, time.split(':'))
            return h * 60 + m
        
        login = toMinutes(loginTime)
        logout = toMinutes(logoutTime)
        
        if logout < login:
            logout += 24 * 60
        
        # Round up login to next 15-min mark
        login = ((login + 14) // 15) * 15
        # Round down logout to previous 15-min mark
        logout = (logout // 15) * 15
        
        if logout < login:
            return 0
        
        return (logout - login) // 15