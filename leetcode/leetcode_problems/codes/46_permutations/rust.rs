// Problem: Permutations
// Difficulty: Medium
// Tags: array
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

impl Solution {
    pub fn permute(nums: Vec<i32>) -> Vec<Vec<i32>> {
        let mut result = Vec::new();
        let mut current = Vec::new();
        let mut used = vec![false; nums.len()];
        Self::backtrack(&mut result, &mut current, &nums, &mut used);
        result
    }
    
    fn backtrack(result: &mut Vec<Vec<i32>>, current: &mut Vec<i32>, 
                 nums: &Vec<i32>, used: &mut Vec<bool>) {
        if current.len() == nums.len() {
            result.push(current.clone());
            return;
        }
        
        for i in 0..nums.len() {
            if used[i] {
                continue;
            }
            used[i] = true;
            current.push(nums[i]);
            Self::backtrack(result, current, nums, used);
            current.pop();
            used[i] = false;
        }
    }
}