"""
Problem: Number of Spaces Cleaning Robot Cleaned
Difficulty: Medium
Tags: array, simulation, BFS

Approach: Simulate robot movement with direction changes, track visited cells
Time Complexity: O(m * n) where m, n are grid dimensions
Space Complexity: O(m * n)
"""

class Solution:
    def numberOfCleanRooms(self, room: List[List[int]]) -> int:
        m, n = len(room), len(room[0])
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]  # right, down, left, up
        dir_idx = 0
        x, y = 0, 0
        visited = set()
        cleaned = set()
        
        # Track state: (x, y, direction) to detect cycles
        state_visited = set()
        
        while True:
            # Clean current cell
            cleaned.add((x, y))
            state = (x, y, dir_idx)
            
            # Check for cycle
            if state in state_visited:
                break
            state_visited.add(state)
            
            # Try to move forward
            dx, dy = directions[dir_idx]
            nx, ny = x + dx, y + dy
            
            if 0 <= nx < m and 0 <= ny < n and room[nx][ny] == 0:
                # Can move forward
                x, y = nx, ny
            else:
                # Turn right
                dir_idx = (dir_idx + 1) % 4
        
        return len(cleaned)