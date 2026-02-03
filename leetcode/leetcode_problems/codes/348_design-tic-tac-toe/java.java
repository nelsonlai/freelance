/**
 * Problem: Design Tic-Tac-Toe
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

class TicTacToe {
    private int n;
    private int[] rows;
    private int[] cols;
    private int diag;
    private int antiDiag;

    public TicTacToe(int n) {
        this.n = n;
        this.rows = new int[n];
        this.cols = new int[n];
        this.diag = 0;
        this.antiDiag = 0;
    }
    
    public int move(int row, int col, int player) {
        int value = player == 1 ? 1 : -1;
        
        rows[row] += value;
        cols[col] += value;
        
        if (row == col) {
            diag += value;
        }
        if (row + col == n - 1) {
            antiDiag += value;
        }
        
        if (Math.abs(rows[row]) == n || Math.abs(cols[col]) == n || 
            Math.abs(diag) == n || Math.abs(antiDiag) == n) {
            return player;
        }
        
        return 0;
    }
}

/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe obj = new TicTacToe(n);
 * int param_1 = obj.move(row,col,player);
 */