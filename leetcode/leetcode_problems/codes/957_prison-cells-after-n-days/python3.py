"""
Problem: Prison Cells After N Days
Difficulty: Medium
Tags: array, math, hash

Approach: Detect cycle - states repeat, use hash map to find cycle length
Time Complexity: O(min(n, cycle_length * 8))
Space Complexity: O(cycle_length * 8) for storing states
"""

class Solution:
    def prisonAfterNDays(self, cells: List[int], n: int) -> List[int]:
        seen = {}
        state = tuple(cells)
        
        for day in range(n):
            if state in seen:
                cycle_length = day - seen[state]
                remaining = n - day
                cycle_pos = remaining % cycle_length
                # Find the state at cycle_pos days after the cycle starts
                for s, d in seen.items():
                    if d == seen[state] + cycle_pos:
                        return list(s)
            
            seen[state] = day
            
            # Calculate next state
            next_cells = [0] * 8
            for i in range(1, 7):
                next_cells[i] = 1 if state[i-1] == state[i+1] else 0
            state = tuple(next_cells)
        
        return list(state)