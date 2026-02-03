// Problem: String to Integer (atoi)
// Difficulty: Medium
// Tags: string
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

impl Solution {
    pub fn my_atoi(s: String) -> i32 {
        let s = s.trim();
        if s.is_empty() {
            return 0;
        }
        
        let mut sign = 1;
        let mut i = 0;
        let chars: Vec<char> = s.chars().collect();
        
        if chars[0] == '-' {
            sign = -1;
            i = 1;
        } else if chars[0] == '+' {
            i = 1;
        }
        
        let mut result: i32 = 0;
        while i < chars.len() && chars[i].is_ascii_digit() {
            let digit = chars[i] as i32 - '0' as i32;
            if result > i32::MAX / 10 || 
                (result == i32::MAX / 10 && digit > 7) {
                return if sign == 1 { i32::MAX } else { i32::MIN };
            }
            result = result * 10 + digit;
            i += 1;
        }
        
        sign * result
    }
}