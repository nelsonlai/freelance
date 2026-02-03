// Problem: Sqrt(x)
// Difficulty: Easy
// Tags: math, search
// 
// Approach: Newton's method for square root
// Time Complexity: O(log log n) - converges quadratically
// Space Complexity: O(1)

impl Solution {
    pub fn my_sqrt(x: i32) -> i32 {
        if x < 2 {
            return x;
        }
        
        // Newton's method: x_{n+1} = (x_n + S/x_n) / 2
        let mut guess = x as i64;
        while guess * guess > x as i64 {
            guess = (guess + x as i64 / guess) / 2;
        }
        
        guess as i32
    }
}