// Problem: 3Sum Closest
// Difficulty: Medium
// Tags: array, sort
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

impl Solution {
    pub fn three_sum_closest(mut nums: Vec<i32>, target: i32) -> i32 {
        nums.sort();
        let mut closest_sum = nums[0] + nums[1] + nums[2];
        
        for i in 0..nums.len().saturating_sub(2) {
            let mut left = i + 1;
            let mut right = nums.len() - 1;
            
            while left < right {
                let current_sum = nums[i] + nums[left] + nums[right];
                if (current_sum - target).abs() < (closest_sum - target).abs() {
                    closest_sum = current_sum;
                }
                
                if current_sum < target {
                    left += 1;
                } else if current_sum > target {
                    right -= 1;
                } else {
                    return current_sum;
                }
            }
        }
        
        closest_sum
    }
}