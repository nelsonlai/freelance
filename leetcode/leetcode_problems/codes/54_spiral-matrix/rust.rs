// Problem: Spiral Matrix
// Difficulty: Medium
// Tags: array
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

impl Solution {
    pub fn spiral_order(matrix: Vec<Vec<i32>>) -> Vec<i32> {
        if matrix.is_empty() || matrix[0].is_empty() {
            return Vec::new();
        }
        
        let mut result = Vec::new();
        let mut top = 0;
        let mut bottom = matrix.len() - 1;
        let mut left = 0;
        let mut right = matrix[0].len() - 1;
        
        while top <= bottom && left <= right {
            // Right
            for j in left..=right {
                result.push(matrix[top][j]);
            }
            top += 1;
            
            // Down
            for i in top..=bottom {
                result.push(matrix[i][right]);
            }
            if right == 0 {
                break;
            }
            right -= 1;
            
            // Left
            if top <= bottom {
                for j in (left..=right).rev() {
                    result.push(matrix[bottom][j]);
                }
                if bottom == 0 {
                    break;
                }
                bottom -= 1;
            }
            
            // Up
            if left <= right {
                for i in (top..=bottom).rev() {
                    result.push(matrix[i][left]);
                }
                left += 1;
            }
        }
        
        result
    }
}