class Solution {
    public int numMagicSquaresInside(int[][] grid) {
        int result = 0;
        for (int i = 0; i < grid.length - 2; i++) {
            for (int j = 0; j < grid[0].length - 2; j++) {
                if (isMagic(grid, i, j)) {
                    result++;
                }
            }
        }
        return result;
    }
    
    private boolean isMagic(int[][] grid, int i, int j) {
        boolean[] seen = new boolean[10];
        for (int di = 0; di < 3; di++) {
            for (int dj = 0; dj < 3; dj++) {
                int val = grid[i+di][j+dj];
                if (val < 1 || val > 9 || seen[val]) {
                    return false;
                }
                seen[val] = true;
            }
        }
        
        int s = grid[i][j] + grid[i][j+1] + grid[i][j+2];
        return grid[i+1][j] + grid[i+1][j+1] + grid[i+1][j+2] == s &&
               grid[i+2][j] + grid[i+2][j+1] + grid[i+2][j+2] == s &&
               grid[i][j] + grid[i+1][j] + grid[i+2][j] == s &&
               grid[i][j+1] + grid[i+1][j+1] + grid[i+2][j+1] == s &&
               grid[i][j+2] + grid[i+1][j+2] + grid[i+2][j+2] == s &&
               grid[i][j] + grid[i+1][j+1] + grid[i+2][j+2] == s &&
               grid[i][j+2] + grid[i+1][j+1] + grid[i+2][j] == s;
    }
}
