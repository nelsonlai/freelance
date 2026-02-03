class Solution {
    private int originalColor;
    private int newColor;
    private int[][] image;
    
    public int[][] floodFill(int[][] image, int sr, int sc, int color) {
        if (image[sr][sc] == color) {
            return image;
        }
        
        this.image = image;
        this.originalColor = image[sr][sc];
        this.newColor = color;
        
        dfs(sr, sc);
        return image;
    }
    
    private void dfs(int r, int c) {
        if (r < 0 || r >= image.length || c < 0 || c >= image[0].length || image[r][c] != originalColor) {
            return;
        }
        image[r][c] = newColor;
        dfs(r + 1, c);
        dfs(r - 1, c);
        dfs(r, c + 1);
        dfs(r, c - 1);
    }
}
