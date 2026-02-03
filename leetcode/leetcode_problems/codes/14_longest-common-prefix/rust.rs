// Problem: Longest Common Prefix
// Difficulty: Easy
// Tags: array, string
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

impl Solution {
    pub fn longest_common_prefix(strs: Vec<String>) -> String {
        if strs.is_empty() {
            return String::new();
        }
        
        let first = strs[0].as_bytes();
        for i in 0..first.len() {
            let char = first[i];
            for j in 1..strs.len() {
                let bytes = strs[j].as_bytes();
                if i >= bytes.len() || bytes[i] != char {
                    return strs[0][..i].to_string();
                }
            }
        }
        
        strs[0].clone()
    }
}