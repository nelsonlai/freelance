// Problem: Jump Game II
// Difficulty: Medium
// Tags: array, dp, greedy
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) or O(n * m) for DP table

impl Solution {
    pub fn jump(nums: Vec<i32>) -> i32 {
        let mut jumps = 0;
        let mut current_end = 0;
        let mut farthest = 0;
        
        for i in 0..nums.len() - 1 {
            farthest = farthest.max(i as i32 + nums[i]);
            if i as i32 == current_end {
                jumps += 1;
                current_end = farthest;
            }
        }
        
        jumps
    }
}