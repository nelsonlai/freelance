// Problem: Container With Most Water
// Difficulty: Medium
// Tags: array, dp, greedy
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) or O(n * m) for DP table

impl Solution {
    pub fn max_area(height: Vec<i32>) -> i32 {
        let mut left = 0;
        let mut right = height.len() - 1;
        let mut max_area = 0;
        
        while left < right {
            let width = (right - left) as i32;
            let area = width * height[left].min(height[right]);
            max_area = max_area.max(area);
            
            if height[left] < height[right] {
                left += 1;
            } else {
                right -= 1;
            }
        }
        
        max_area
    }
}