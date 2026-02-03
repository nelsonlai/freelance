// Problem: Palindrome Number
// Difficulty: Easy
// Tags: string, math
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

impl Solution {
    pub fn is_palindrome(x: i32) -> bool {
        if x < 0 || (x != 0 && x % 10 == 0) {
            return false;
        }
        
        let mut x = x;
        let mut reversed_half = 0;
        
        while x > reversed_half {
            reversed_half = reversed_half * 10 + x % 10;
            x /= 10;
        }
        
        x == reversed_half || x == reversed_half / 10
    }
}