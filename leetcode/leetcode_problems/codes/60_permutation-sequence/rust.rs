// Problem: Permutation Sequence
// Difficulty: Hard
// Tags: math
// 
// Approach: Optimized algorithm based on problem constraints
// Time Complexity: O(n) to O(n^2) depending on approach
// Space Complexity: O(1) to O(n) depending on approach

impl Solution {
    pub fn get_permutation(n: i32, k: i32) -> String {
        let mut nums: Vec<i32> = (1..=n).collect();
        let mut fact = vec![1; n as usize];
        for i in 1..n as usize {
            fact[i] = fact[i - 1] * (i as i32);
        }
        
        let mut k = k - 1; // Convert to 0-indexed
        let mut result = String::new();
        
        for i in (0..n as usize).rev() {
            let index = (k / fact[i]) as usize;
            result.push_str(&nums[index].to_string());
            nums.remove(index);
            k %= fact[i];
        }
        
        result
    }
}