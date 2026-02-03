// Problem: Remove Element
// Difficulty: Easy
// Tags: array, sort
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

impl Solution {
    pub fn remove_element(nums: &mut Vec<i32>, val: i32) -> i32 {
        let mut write_index = 0;
        for i in 0..nums.len() {
            if nums[i] != val {
                nums[write_index] = nums[i];
                write_index += 1;
            }
        }
        write_index as i32
    }
}