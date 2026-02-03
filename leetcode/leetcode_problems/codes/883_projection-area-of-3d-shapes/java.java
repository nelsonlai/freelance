class Solution {
    public int projectionArea(int[][] grid) {
        int n = grid.length;
        int result = 0;
        
        for (int i = 0; i < n; i++) {
            int maxRow = 0, maxCol = 0;
            for (int j = 0; j < n; j++) {
                if (grid[i][j] > 0) {
                    result++;
                }
                maxRow = Math.max(maxRow, grid[i][j]);
                maxCol = Math.max(maxCol, grid[j][i]);
            }
            result += maxRow + maxCol;
        }
        
        return result;
    }
}
