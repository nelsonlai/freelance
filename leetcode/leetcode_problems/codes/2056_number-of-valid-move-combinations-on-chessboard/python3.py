"""
Problem: Number of Valid Move Combinations On Chessboard
Difficulty: Hard
Tags: array, string, backtracking, DFS

Approach: Generate all possible move combinations, check for collisions
Time Complexity: O(8^n * n^2) where n is number of pieces
Space Complexity: O(n)
"""

class Solution:
    def countCombinations(self, pieces: List[str], positions: List[List[int]]) -> int:
        n = len(pieces)
        directions = {
            'rook': [(0, 1), (0, -1), (1, 0), (-1, 0)],
            'queen': [(0, 1), (0, -1), (1, 0), (-1, 0), (1, 1), (1, -1), (-1, 1), (-1, -1)],
            'bishop': [(1, 1), (1, -1), (-1, 1), (-1, -1)]
        }
        
        def get_moves(piece, pos):
            """Get all possible moves for a piece from position"""
            moves = [pos]  # Can stay in place
            for dx, dy in directions[piece]:
                for dist in range(1, 8):
                    x, y = pos[0] + dx * dist, pos[1] + dy * dist
                    if 1 <= x <= 8 and 1 <= y <= 8:
                        moves.append([x, y])
                    else:
                        break
            return moves
        
        def is_valid(positions_at_time):
            """Check if positions are valid (no two pieces at same position)"""
            seen = set()
            for pos in positions_at_time:
                pos_tuple = tuple(pos)
                if pos_tuple in seen:
                    return False
                seen.add(pos_tuple)
            return True
        
        def backtrack(index, current_paths):
            """Backtrack to generate all valid combinations"""
            if index == n:
                # Check all time steps
                max_time = max(len(path) for path in current_paths)
                for t in range(max_time):
                    positions_at_t = []
                    for path in current_paths:
                        if t < len(path):
                            positions_at_t.append(path[t])
                        else:
                            positions_at_t.append(path[-1])  # Stay at last position
                    
                    if not is_valid(positions_at_t):
                        return 0
                return 1
            
            result = 0
            piece = pieces[index]
            start_pos = positions[index]
            moves = get_moves(piece, start_pos)
            
            for move in moves:
                # Generate path from start to move
                path = []
                dx = 0 if move[0] == start_pos[0] else (1 if move[0] > start_pos[0] else -1)
                dy = 0 if move[1] == start_pos[1] else (1 if move[1] > start_pos[1] else -1)
                
                x, y = start_pos[0], start_pos[1]
                while True:
                    path.append([x, y])
                    if x == move[0] and y == move[1]:
                        break
                    x += dx
                    y += dy
                
                current_paths.append(path)
                result += backtrack(index + 1, current_paths)
                current_paths.pop()
            
            return result
        
        return backtrack(0, [])