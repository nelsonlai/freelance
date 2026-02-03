/**
 * Problem: Spiral Matrix II
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

/**
 * @param {number} n
 * @return {number[][]}
 */
var generateMatrix = function(n) {
    const matrix = Array(n).fill(null).map(() => Array(n).fill(0));
    let num = 1;
    let top = 0, bottom = n - 1;
    let left = 0, right = n - 1;
    
    while (top <= bottom && left <= right) {
        // Right
        for (let j = left; j <= right; j++) {
            matrix[top][j] = num++;
        }
        top++;
        
        // Down
        for (let i = top; i <= bottom; i++) {
            matrix[i][right] = num++;
        }
        right--;
        
        // Left
        if (top <= bottom) {
            for (let j = right; j >= left; j--) {
                matrix[bottom][j] = num++;
            }
            bottom--;
        }
        
        // Up
        if (left <= right) {
            for (let i = bottom; i >= top; i--) {
                matrix[i][left] = num++;
            }
            left++;
        }
    }
    
    return matrix;
};