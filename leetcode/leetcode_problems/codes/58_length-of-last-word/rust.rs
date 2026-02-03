// Problem: Length of Last Word
// Difficulty: Easy
// Tags: string, tree
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(h) for recursion stack where h is height

impl Solution {
    pub fn length_of_last_word(s: String) -> i32 {
        let s = s.trim_end();
        let mut length = 0;
        for ch in s.chars().rev() {
            if ch == ' ' {
                break;
            }
            length += 1;
        }
        length
    }
}