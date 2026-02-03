// Problem: Jump Game
// Difficulty: Medium
// Tags: array, dp, greedy
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) or O(n * m) for DP table

impl Solution {
    pub fn can_jump(nums: Vec<i32>) -> bool {
        let mut farthest = 0;
        for i in 0..nums.len() {
            if i as i32 > farthest {
                return false;
            }
            farthest = farthest.max(i as i32 + nums[i]);
            if farthest >= nums.len() as i32 - 1 {
                return true;
            }
        }
        true
    }
}