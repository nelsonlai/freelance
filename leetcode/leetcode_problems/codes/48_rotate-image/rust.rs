// Problem: Rotate Image
// Difficulty: Medium
// Tags: array, math
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

impl Solution {
    pub fn rotate(matrix: &mut Vec<Vec<i32>>) {
        let n = matrix.len();
        // Transpose
        for i in 0..n {
            for j in i..n {
                let temp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
            }
        }
        
        // Reverse each row
        for i in 0..n {
            matrix[i].reverse();
        }
    }
}