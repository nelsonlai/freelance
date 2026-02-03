// Problem: Count and Say
// Difficulty: Medium
// Tags: string
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

impl Solution {
    pub fn count_and_say(n: i32) -> String {
        if n == 1 {
            return "1".to_string();
        }
        
        let mut result = "1".to_string();
        for _ in 1..n {
            let mut new_result = String::new();
            let chars: Vec<char> = result.chars().collect();
            let mut i = 0;
            while i < chars.len() {
                let mut count = 1;
                while i + 1 < chars.len() && chars[i] == chars[i + 1] {
                    count += 1;
                    i += 1;
                }
                new_result.push_str(&count.to_string());
                new_result.push(chars[i]);
                i += 1;
            }
            result = new_result;
        }
        
        result
    }
}