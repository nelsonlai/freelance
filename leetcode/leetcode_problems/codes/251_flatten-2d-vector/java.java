/**
 * Problem: Flatten 2D Vector
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Vector2D {
    private int[][] vec;
    private int row;
    private int col;

    public Vector2D(int[][] vec) {
        this.vec = vec;
        this.row = 0;
        this.col = 0;
        advance();
    }
    
    private void advance() {
        while (row < vec.length && col >= vec[row].length) {
            row++;
            col = 0;
        }
    }
    
    public int next() {
        int result = vec[row][col];
        col++;
        advance();
        return result;
    }
    
    public boolean hasNext() {
        return row < vec.length;
    }
}

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D obj = new Vector2D(vec);
 * int param_1 = obj.next();
 * boolean param_2 = obj.hasNext();
 */