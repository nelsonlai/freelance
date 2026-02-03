/**
 * Problem: Leftmost Column with at Least a One
 * Difficulty: Medium
 * Tags: array, sort, search
 * 
 * Approach: Start from top-right, move left if 1, down if 0
 * Time Complexity: O(rows + cols)
 * Space Complexity: O(1)
 */

/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * interface BinaryMatrix {
 *     public int get(int row, int col);
 *     public List<Integer> dimensions();
 * };
 */

class Solution {
    public int leftMostColumnWithOne(BinaryMatrix binaryMatrix) {
        List<Integer> dims = binaryMatrix.dimensions();
        int rows = dims.get(0);
        int cols = dims.get(1);
        
        int row = 0, col = cols - 1;
        int result = -1;
        
        while (row < rows && col >= 0) {
            if (binaryMatrix.get(row, col) == 1) {
                result = col;
                col--;
            } else {
                row++;
            }
        }
        
        return result;
    }
}
