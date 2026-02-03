// Problem: 4Sum
// Difficulty: Medium
// Tags: array, sort
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

impl Solution {
    pub fn four_sum(mut nums: Vec<i32>, target: i32) -> Vec<Vec<i32>> {
        nums.sort();
        let mut result = Vec::new();
        let n = nums.len();
        
        for i in 0..n.saturating_sub(3) {
            if i > 0 && nums[i] == nums[i - 1] {
                continue;
            }
            
            for j in (i + 1)..n.saturating_sub(2) {
                if j > i + 1 && nums[j] == nums[j - 1] {
                    continue;
                }
                
                let mut left = j + 1;
                let mut right = n - 1;
                
                while left < right {
                    let sum = nums[i] as i64 + nums[j] as i64 + nums[left] as i64 + nums[right] as i64;
                    if sum == target as i64 {
                        result.push(vec![nums[i], nums[j], nums[left], nums[right]]);
                        while left < right && nums[left] == nums[left + 1] {
                            left += 1;
                        }
                        while left < right && nums[right] == nums[right - 1] {
                            right -= 1;
                        }
                        left += 1;
                        right -= 1;
                    } else if sum < target as i64 {
                        left += 1;
                    } else {
                        right -= 1;
                    }
                }
            }
        }
        
        result
    }
}