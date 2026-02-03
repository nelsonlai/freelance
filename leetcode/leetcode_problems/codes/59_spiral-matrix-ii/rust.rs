// Problem: Spiral Matrix II
// Difficulty: Medium
// Tags: array
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

impl Solution {
    pub fn generate_matrix(n: i32) -> Vec<Vec<i32>> {
        let n = n as usize;
        let mut matrix = vec![vec![0; n]; n];
        let mut num = 1;
        let mut top = 0;
        let mut bottom = n - 1;
        let mut left = 0;
        let mut right = n - 1;
        
        while top <= bottom && left <= right {
            // Right
            for j in left..=right {
                matrix[top][j] = num;
                num += 1;
            }
            top += 1;
            
            // Down
            for i in top..=bottom {
                matrix[i][right] = num;
                num += 1;
            }
            if right == 0 {
                break;
            }
            right -= 1;
            
            // Left
            if top <= bottom {
                for j in (left..=right).rev() {
                    matrix[bottom][j] = num;
                    num += 1;
                }
                if bottom == 0 {
                    break;
                }
                bottom -= 1;
            }
            
            // Up
            if left <= right {
                for i in (top..=bottom).rev() {
                    matrix[i][left] = num;
                    num += 1;
                }
                left += 1;
            }
        }
        
        matrix
    }
}