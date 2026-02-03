// Problem: Substring with Concatenation of All Words
// Difficulty: Hard
// Tags: array, string, tree, hash
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(h) for recursion stack where h is height

use std::collections::HashMap;

impl Solution {
    pub fn find_substring(s: String, words: Vec<String>) -> Vec<i32> {
        let mut result = Vec::new();
        if s.is_empty() || words.is_empty() {
            return result;
        }
        
        let word_len = words[0].len();
        let mut word_count: HashMap<&str, i32> = HashMap::new();
        for word in &words {
            *word_count.entry(word).or_insert(0) += 1;
        }
        
        let s_bytes = s.as_bytes();
        for i in 0..word_len {
            let mut left = i;
            let mut seen: HashMap<&str, i32> = HashMap::new();
            let mut count = 0;
            
            let mut j = i;
            while j <= s.len().saturating_sub(word_len) {
                let word = std::str::from_utf8(&s_bytes[j..j + word_len]).unwrap();
                
                if word_count.contains_key(word) {
                    *seen.entry(word).or_insert(0) += 1;
                    count += 1;
                    
                    while seen.get(word).unwrap() > word_count.get(word).unwrap() {
                        let left_word = std::str::from_utf8(&s_bytes[left..left + word_len]).unwrap();
                        *seen.get_mut(left_word).unwrap() -= 1;
                        count -= 1;
                        left += word_len;
                    }
                    
                    if count == words.len() {
                        result.push(left as i32);
                        let left_word = std::str::from_utf8(&s_bytes[left..left + word_len]).unwrap();
                        *seen.get_mut(left_word).unwrap() -= 1;
                        count -= 1;
                        left += word_len;
                    }
                } else {
                    seen.clear();
                    count = 0;
                    left = j + word_len;
                }
                j += word_len;
            }
        }
        
        result
    }
}