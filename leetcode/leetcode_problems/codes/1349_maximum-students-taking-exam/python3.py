"""
Problem: Maximum Students Taking Exam
Difficulty: Hard
Tags: array, dp

Approach: DP with bitmask - track valid seating patterns for each row
Time Complexity: O(m * 4^n) where m is rows, n is cols
Space Complexity: O(m * 2^n) for DP table
"""

class Solution:
    def maxStudents(self, seats: List[List[str]]) -> int:
        m, n = len(seats), len(seats[0])
        
        def valid_mask(row, mask):
            for j in range(n):
                if mask & (1 << j):
                    if seats[row][j] == '#':
                        return False
                    if j > 0 and mask & (1 << (j - 1)):
                        return False
            return True
        
        dp = {}
        dp[0] = 0
        
        for i in range(m):
            new_dp = {}
            for prev_mask, count in dp.items():
                for mask in range(1 << n):
                    if not valid_mask(i, mask):
                        continue
                    
                    # Check conflict with previous row
                    if (mask & (prev_mask << 1)) or (mask & (prev_mask >> 1)):
                        continue
                    
                    student_count = bin(mask).count('1')
                    new_dp[mask] = max(new_dp.get(mask, 0), count + student_count)
            
            dp = new_dp if new_dp else {0: 0}
        
        return max(dp.values()) if dp else 0