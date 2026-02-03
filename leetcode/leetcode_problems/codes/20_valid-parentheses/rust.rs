// Problem: Valid Parentheses
// Difficulty: Easy
// Tags: string, stack
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

use std::collections::HashMap;

impl Solution {
    pub fn is_valid(s: String) -> bool {
        let mut stack = Vec::new();
        let mapping: HashMap<char, char> = [
            (')', '('),
            ('}', '{'),
            (']', '[')
        ].iter().cloned().collect();
        
        for c in s.chars() {
            if let Some(&opening) = mapping.get(&c) {
                if stack.is_empty() || stack.pop().unwrap() != opening {
                    return false;
                }
            } else {
                stack.push(c);
            }
        }
        
        stack.is_empty()
    }
}