// Problem: Two Sum
// Difficulty: Easy
// Tags: array, hash
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) for hash map

use std::collections::HashMap;

impl Solution {
    pub fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
        let mut map = HashMap::new();
        for (i, &num) in nums.iter().enumerate() {
            let complement = target - num;
            if let Some(&idx) = map.get(&complement) {
                return vec![idx as i32, i as i32];
            }
            map.insert(num, i);
        }
        vec![]
    }
}