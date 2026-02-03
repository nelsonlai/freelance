/**
 * Problem: Number of Valid Move Combinations On Chessboard
 * Difficulty: Hard
 * Tags: array, string, backtracking, DFS
 * 
 * Approach: Generate all possible move combinations, check for collisions
 * Time Complexity: O(8^n * n^2) where n is number of pieces
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    private Map<String, int[][]> directions = new HashMap<>();
    
    public int countCombinations(String[] pieces, int[][] positions) {
        directions.put("rook", new int[][]{{0, 1}, {0, -1}, {1, 0}, {-1, 0}});
        directions.put("queen", new int[][]{{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}});
        directions.put("bishop", new int[][]{{1, 1}, {1, -1}, {-1, 1}, {-1, -1}});
        
        return backtrack(pieces, positions, 0, new ArrayList<>());
    }
    
    private List<int[]> getMoves(String piece, int[] pos) {
        List<int[]> moves = new ArrayList<>();
        moves.add(new int[]{pos[0], pos[1]});  // Can stay in place
        
        for (int[] dir : directions.get(piece)) {
            int dx = dir[0], dy = dir[1];
            for (int dist = 1; dist < 8; dist++) {
                int x = pos[0] + dx * dist;
                int y = pos[1] + dy * dist;
                if (x >= 1 && x <= 8 && y >= 1 && y <= 8) {
                    moves.add(new int[]{x, y});
                } else {
                    break;
                }
            }
        }
        return moves;
    }
    
    private boolean isValid(List<int[]> positionsAtTime) {
        Set<String> seen = new HashSet<>();
        for (int[] pos : positionsAtTime) {
            String key = pos[0] + "," + pos[1];
            if (seen.contains(key)) {
                return false;
            }
            seen.add(key);
        }
        return true;
    }
    
    private int backtrack(String[] pieces, int[][] positions, int index, List<List<int[]>> currentPaths) {
        if (index == pieces.length) {
            // Check all time steps
            int maxTime = 0;
            for (List<int[]> path : currentPaths) {
                maxTime = Math.max(maxTime, path.size());
            }
            
            for (int t = 0; t < maxTime; t++) {
                List<int[]> positionsAtT = new ArrayList<>();
                for (List<int[]> path : currentPaths) {
                    if (t < path.size()) {
                        positionsAtT.add(path.get(t));
                    } else {
                        positionsAtT.add(path.get(path.size() - 1));  // Stay at last position
                    }
                }
                
                if (!isValid(positionsAtT)) {
                    return 0;
                }
            }
            return 1;
        }
        
        int result = 0;
        String piece = pieces[index];
        int[] startPos = positions[index];
        List<int[]> moves = getMoves(piece, startPos);
        
        for (int[] move : moves) {
            // Generate path from start to move
            List<int[]> path = new ArrayList<>();
            int dx = move[0] == startPos[0] ? 0 : (move[0] > startPos[0] ? 1 : -1);
            int dy = move[1] == startPos[1] ? 0 : (move[1] > startPos[1] ? 1 : -1);
            
            int x = startPos[0], y = startPos[1];
            while (true) {
                path.add(new int[]{x, y});
                if (x == move[0] && y == move[1]) {
                    break;
                }
                x += dx;
                y += dy;
            }
            
            currentPaths.add(path);
            result += backtrack(pieces, positions, index + 1, currentPaths);
            currentPaths.remove(currentPaths.size() - 1);
        }
        
        return result;
    }
}