/**
 * Problem: Range Sum Query 2D - Mutable
 * Difficulty: Medium
 * Tags: array, tree
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

class NumMatrix {
    private int[][] matrix;
    private int[][] bit;
    private int m;
    private int n;

    public NumMatrix(int[][] matrix) {
        if (matrix == null || matrix.length == 0 || matrix[0].length == 0) {
            return;
        }
        this.matrix = matrix;
        this.m = matrix.length;
        this.n = matrix[0].length;
        this.bit = new int[m + 1][n + 1];
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                updateBIT(i, j, matrix[i][j]);
            }
        }
    }
    
    private void updateBIT(int row, int col, int delta) {
        for (int i = row + 1; i <= m; i += i & -i) {
            for (int j = col + 1; j <= n; j += j & -j) {
                bit[i][j] += delta;
            }
        }
    }
    
    private int queryBIT(int row, int col) {
        int sum = 0;
        for (int i = row + 1; i > 0; i -= i & -i) {
            for (int j = col + 1; j > 0; j -= j & -j) {
                sum += bit[i][j];
            }
        }
        return sum;
    }
    
    public void update(int row, int col, int val) {
        int delta = val - matrix[row][col];
        matrix[row][col] = val;
        updateBIT(row, col, delta);
    }
    
    public int sumRegion(int row1, int col1, int row2, int col2) {
        return queryBIT(row2, col2) - queryBIT(row1 - 1, col2) - 
               queryBIT(row2, col1 - 1) + queryBIT(row1 - 1, col1 - 1);
    }
}

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * obj.update(row,col,val);
 * int param_2 = obj.sumRegion(row1,col1,row2,col2);
 */