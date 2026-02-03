// Problem: Merge Intervals
// Difficulty: Medium
// Tags: array, sort
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

impl Solution {
    pub fn merge(mut intervals: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
        if intervals.is_empty() {
            return Vec::new();
        }
        
        intervals.sort_by_key(|x| x[0]);
        let mut result = vec![intervals[0].clone()];
        
        for i in 1..intervals.len() {
            let current = &intervals[i];
            let last = result.last_mut().unwrap();
            if current[0] <= last[1] {
                last[1] = last[1].max(current[1]);
            } else {
                result.push(current.clone());
            }
        }
        
        result
    }
}