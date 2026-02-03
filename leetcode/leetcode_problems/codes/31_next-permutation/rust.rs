// Problem: Next Permutation
// Difficulty: Medium
// Tags: array, graph, sort
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

impl Solution {
    pub fn next_permutation(nums: &mut Vec<i32>) {
        let mut i = nums.len() as i32 - 2;
        while i >= 0 && nums[i as usize] >= nums[(i + 1) as usize] {
            i -= 1;
        }
        
        if i >= 0 {
            let mut j = nums.len() - 1;
            while nums[j] <= nums[i as usize] {
                j -= 1;
            }
            nums.swap(i as usize, j);
        }
        
        let mut left = (i + 1) as usize;
        let mut right = nums.len() - 1;
        while left < right {
            nums.swap(left, right);
            left += 1;
            right -= 1;
        }
    }
}