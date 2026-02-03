// Problem: Longest Palindromic Substring
// Difficulty: Medium
// Tags: array, string, tree, dp
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) or O(n * m) for DP table

impl Solution {
    pub fn longest_palindrome(s: String) -> String {
        if s.is_empty() {
            return String::new();
        }
        
        let chars: Vec<char> = s.chars().collect();
        let mut start = 0;
        let mut max_len = 1;
        
        fn expand_around_center(chars: &[char], left: i32, right: i32) -> i32 {
            let mut left = left;
            let mut right = right;
            while left >= 0 && right < chars.len() as i32 && chars[left as usize] == chars[right as usize] {
                left -= 1;
                right += 1;
            }
            right - left - 1
        }
        
        for i in 0..chars.len() {
            let len1 = expand_around_center(&chars, i as i32, i as i32);
            let len2 = expand_around_center(&chars, i as i32, (i + 1) as i32);
            let len = len1.max(len2);
            
            if len > max_len {
                start = i - ((len - 1) / 2) as usize;
                max_len = len as usize;
            }
        }
        
        chars[start..start + max_len].iter().collect()
    }
}