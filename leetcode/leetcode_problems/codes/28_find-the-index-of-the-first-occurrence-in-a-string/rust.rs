// Problem: Find the Index of the First Occurrence in a String
// Difficulty: Easy
// Tags: array, string, stack
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

impl Solution {
    pub fn str_str(haystack: String, needle: String) -> i32 {
        if needle.is_empty() {
            return 0;
        }
        
        let n = haystack.len();
        let m = needle.len();
        
        for i in 0..=n.saturating_sub(m) {
            if haystack[i..i + m] == needle {
                return i as i32;
            }
        }
        
        -1
    }
}