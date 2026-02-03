import java.util.*;

class Solution {
    public int snakesAndLadders(int[][] board) {
        int n = board.length;
        int target = n * n;
        
        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{1, 0});
        Set<Integer> visited = new HashSet<>();
        visited.add(1);
        
        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            int pos = curr[0];
            int moves = curr[1];
            
            if (pos == target) {
                return moves;
            }
            
            for (int i = 1; i <= 6; i++) {
                int nextPos = pos + i;
                if (nextPos > target) break;
                
                int[] coord = getPos(nextPos, n);
                int r = coord[0], c = coord[1];
                
                if (board[r][c] != -1) {
                    nextPos = board[r][c];
                }
                
                if (!visited.contains(nextPos)) {
                    visited.add(nextPos);
                    queue.offer(new int[]{nextPos, moves + 1});
                }
            }
        }
        
        return -1;
    }
    
    private int[] getPos(int num, int n) {
        int row = (num - 1) / n;
        int col = (num - 1) % n;
        if (row % 2 == 1) {
            col = n - 1 - col;
        }
        row = n - 1 - row;
        return new int[]{row, col};
    }
}
