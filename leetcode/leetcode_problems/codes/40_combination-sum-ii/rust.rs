// Problem: Combination Sum II
// Difficulty: Medium
// Tags: array
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

impl Solution {
    pub fn combination_sum2(mut candidates: Vec<i32>, target: i32) -> Vec<Vec<i32>> {
        candidates.sort();
        let mut result = Vec::new();
        let mut path = Vec::new();
        
        Self::backtrack(&candidates, target, 0, &mut path, &mut result);
        result
    }
    
    fn backtrack(candidates: &Vec<i32>, target: i32, start: usize, path: &mut Vec<i32>, result: &mut Vec<Vec<i32>>) {
        if target == 0 {
            result.push(path.clone());
            return;
        }
        if target < 0 {
            return;
        }
        
        for i in start..candidates.len() {
            if i > start && candidates[i] == candidates[i - 1] {
                continue;
            }
            path.push(candidates[i]);
            Self::backtrack(candidates, target - candidates[i], i + 1, path, result);
            path.pop();
        }
    }
}