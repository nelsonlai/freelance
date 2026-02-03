// Problem: Generate Parentheses
// Difficulty: Medium
// Tags: string, dp
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) or O(n * m) for DP table

impl Solution {
    pub fn generate_parenthesis(n: i32) -> Vec<String> {
        let mut result = Vec::new();
        
        fn backtrack(result: &mut Vec<String>, current: String, open: i32, close: i32, max: i32) {
            if current.len() == (2 * max) as usize {
                result.push(current);
                return;
            }
            
            if open < max {
                backtrack(result, current.clone() + "(", open + 1, close, max);
            }
            
            if close < open {
                backtrack(result, current + ")", open, close + 1, max);
            }
        }
        
        backtrack(&mut result, String::new(), 0, 0, n);
        result
    }
}