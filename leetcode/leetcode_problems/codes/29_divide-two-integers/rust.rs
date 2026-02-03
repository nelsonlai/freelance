// Problem: Divide Two Integers
// Difficulty: Medium
// Tags: math
// 
// Approach: Optimized algorithm based on problem constraints
// Time Complexity: O(n) to O(n^2) depending on approach
// Space Complexity: O(1) to O(n) depending on approach

impl Solution {
    pub fn divide(dividend: i32, divisor: i32) -> i32 {
        if dividend == i32::MIN && divisor == -1 {
            return i32::MAX;
        }
        
        let negative = (dividend < 0) != (divisor < 0);
        let mut dvd = (dividend as i64).abs();
        let dvs = (divisor as i64).abs();
        
        let mut quotient = 0;
        while dvd >= dvs {
            let mut temp = dvs;
            let mut multiple = 1;
            while dvd >= (temp << 1) {
                temp <<= 1;
                multiple <<= 1;
            }
            dvd -= temp;
            quotient += multiple;
        }
        
        if negative {
            -(quotient as i32)
        } else {
            quotient as i32
        }
    }
}