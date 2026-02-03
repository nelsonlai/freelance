// Problem: Add Binary
// Difficulty: Easy
// Tags: string, math
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

impl Solution {
    pub fn add_binary(a: String, b: String) -> String {
        let mut result = Vec::new();
        let mut carry = 0;
        let mut a_chars: Vec<char> = a.chars().rev().collect();
        let mut b_chars: Vec<char> = b.chars().rev().collect();
        let mut i = 0;
        let mut j = 0;
        
        while i < a_chars.len() || j < b_chars.len() || carry > 0 {
            let mut total = carry;
            if i < a_chars.len() {
                total += a_chars[i].to_digit(10).unwrap() as i32;
                i += 1;
            }
            if j < b_chars.len() {
                total += b_chars[j].to_digit(10).unwrap() as i32;
                j += 1;
            }
            result.push((total % 2).to_string());
            carry = total / 2;
        }
        
        result.reverse();
        result.join("")
    }
}