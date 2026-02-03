// Problem: Roman to Integer
// Difficulty: Easy
// Tags: string, math, hash
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) for hash map

use std::collections::HashMap;

impl Solution {
    pub fn roman_to_int(s: String) -> i32 {
        let mut roman_map = HashMap::new();
        roman_map.insert('I', 1);
        roman_map.insert('V', 5);
        roman_map.insert('X', 10);
        roman_map.insert('L', 50);
        roman_map.insert('C', 100);
        roman_map.insert('D', 500);
        roman_map.insert('M', 1000);
        
        let chars: Vec<char> = s.chars().collect();
        let mut result = 0;
        
        for i in 0..chars.len() {
            let current = *roman_map.get(&chars[i]).unwrap();
            if i < chars.len() - 1 {
                let next = *roman_map.get(&chars[i + 1]).unwrap();
                if current < next {
                    result -= current;
                } else {
                    result += current;
                }
            } else {
                result += current;
            }
        }
        
        result
    }
}