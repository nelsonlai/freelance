// Problem: Pow(x, n)
// Difficulty: Medium
// Tags: array, math
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

impl Solution {
    pub fn my_pow(x: f64, n: i32) -> f64 {
        if n == 0 {
            return 1.0;
        }
        let mut x = x;
        let mut n = n as i64;
        if n < 0 {
            x = 1.0 / x;
            n = -n;
        }
        
        let mut result = 1.0;
        let mut current = x;
        let mut exp = n;
        
        while exp > 0 {
            if exp % 2 == 1 {
                result *= current;
            }
            current *= current;
            exp /= 2;
        }
        
        result
    }
}