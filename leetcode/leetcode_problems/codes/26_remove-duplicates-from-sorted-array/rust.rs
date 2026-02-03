// Problem: Remove Duplicates from Sorted Array
// Difficulty: Easy
// Tags: array, sort
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

impl Solution {
    pub fn remove_duplicates(nums: &mut Vec<i32>) -> i32 {
        if nums.is_empty() {
            return 0;
        }
        
        let mut write_index = 1;
        for i in 1..nums.len() {
            if nums[i] != nums[i - 1] {
                nums[write_index] = nums[i];
                write_index += 1;
            }
        }
        
        write_index as i32
    }
}