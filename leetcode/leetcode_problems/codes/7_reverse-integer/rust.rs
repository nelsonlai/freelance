// Problem: Reverse Integer
// Difficulty: Medium
// Tags: math
// 
// Approach: Optimized algorithm based on problem constraints
// Time Complexity: O(n) to O(n^2) depending on approach
// Space Complexity: O(1) to O(n) depending on approach

impl Solution {
    pub fn reverse(x: i32) -> i32 {
        let mut x = x;
        let mut result: i32 = 0;
        
        while x != 0 {
            let digit = x % 10;
            x /= 10;
            
            if result > i32::MAX / 10 || (result == i32::MAX / 10 && digit > 7) {
                return 0;
            }
            if result < i32::MIN / 10 || (result == i32::MIN / 10 && digit < -8) {
                return 0;
            }
            
            result = result * 10 + digit;
        }
        
        result
    }
}