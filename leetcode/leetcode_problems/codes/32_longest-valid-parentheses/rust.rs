// Problem: Longest Valid Parentheses
// Difficulty: Hard
// Tags: string, tree, dp, stack
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) or O(n * m) for DP table

impl Solution {
    pub fn longest_valid_parentheses(s: String) -> i32 {
        let mut stack = vec![-1];
        let mut max_len = 0;
        
        for (i, ch) in s.chars().enumerate() {
            if ch == '(' {
                stack.push(i as i32);
            } else {
                stack.pop();
                if stack.is_empty() {
                    stack.push(i as i32);
                } else {
                    max_len = max_len.max(i as i32 - stack.last().unwrap());
                }
            }
        }
        
        max_len
    }
}