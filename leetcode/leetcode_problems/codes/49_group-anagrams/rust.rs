// Problem: Group Anagrams
// Difficulty: Medium
// Tags: array, string, hash, sort
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) for hash map

use std::collections::HashMap;

impl Solution {
    pub fn group_anagrams(strs: Vec<String>) -> Vec<Vec<String>> {
        let mut groups: HashMap<String, Vec<String>> = HashMap::new();
        for s in strs {
            let mut chars: Vec<char> = s.chars().collect();
            chars.sort();
            let key: String = chars.into_iter().collect();
            groups.entry(key).or_insert_with(Vec::new).push(s);
        }
        groups.into_values().collect()
    }
}