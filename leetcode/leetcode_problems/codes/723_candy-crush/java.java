import java.util.*;

class Solution {
    public int[][] candyCrush(int[][] board) {
        int m = board.length, n = board[0].length;
        boolean stable = false;
        
        while (!stable) {
            stable = true;
            Set<String> toCrush = new HashSet<>();
            
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (board[i][j] == 0) continue;
                    if (j < n - 2 && board[i][j] == board[i][j+1] && board[i][j] == board[i][j+2]) {
                        toCrush.add(i + "," + j);
                        toCrush.add(i + "," + (j+1));
                        toCrush.add(i + "," + (j+2));
                    }
                    if (i < m - 2 && board[i][j] == board[i+1][j] && board[i][j] == board[i+2][j]) {
                        toCrush.add(i + "," + j);
                        toCrush.add((i+1) + "," + j);
                        toCrush.add((i+2) + "," + j);
                    }
                }
            }
            
            if (!toCrush.isEmpty()) {
                stable = false;
                for (String pos : toCrush) {
                    String[] parts = pos.split(",");
                    board[Integer.parseInt(parts[0])][Integer.parseInt(parts[1])] = 0;
                }
            }
            
            for (int j = 0; j < n; j++) {
                int write = m - 1;
                for (int i = m - 1; i >= 0; i--) {
                    if (board[i][j] != 0) {
                        board[write][j] = board[i][j];
                        write--;
                    }
                }
                for (int i = write; i >= 0; i--) {
                    board[i][j] = 0;
                }
            }
        }
        
        return board;
    }
}
