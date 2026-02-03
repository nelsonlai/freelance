// Problem: Longest Substring Without Repeating Characters
// Difficulty: Medium
// Tags: array, string, tree, hash
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(h) for recursion stack where h is height

use std::collections::HashMap;

impl Solution {
    pub fn length_of_longest_substring(s: String) -> i32 {
        let mut char_index = HashMap::new();
        let mut left = 0;
        let mut max_len = 0;
        let chars: Vec<char> = s.chars().collect();
        
        for right in 0..chars.len() {
            let c = chars[right];
            if let Some(&idx) = char_index.get(&c) {
                if idx >= left {
                    left = idx + 1;
                }
            }
            char_index.insert(c, right);
            max_len = max_len.max((right - left + 1) as i32);
        }
        
        max_len
    }
}