// Problem: First Missing Positive
// Difficulty: Hard
// Tags: array, hash, sort
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) for hash map

impl Solution {
    pub fn first_missing_positive(mut nums: Vec<i32>) -> i32 {
        let n = nums.len();
        
        // Place each number in its correct position
        let mut i = 0;
        while i < n {
            let num = nums[i] as usize;
            if num >= 1 && num <= n && nums[num - 1] != nums[i] {
                nums.swap(i, num - 1);
            } else {
                i += 1;
            }
        }
        
        // Find the first missing positive
        for i in 0..n {
            if nums[i] != (i + 1) as i32 {
                return (i + 1) as i32;
            }
        }
        
        (n + 1) as i32
    }
}