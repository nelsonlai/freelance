// Problem: Integer to Roman
// Difficulty: Medium
// Tags: string, math, hash
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) for hash map

impl Solution {
    pub fn int_to_roman(num: i32) -> String {
        let values = vec![1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1];
        let symbols = vec!["M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"];
        
        let mut num = num;
        let mut result = String::new();
        
        for i in 0..values.len() {
            let count = num / values[i];
            for _ in 0..count {
                result.push_str(symbols[i]);
            }
            num %= values[i];
        }
        
        result
    }
}