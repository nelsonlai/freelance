/**
 * Problem: Container With Most Water
 * Difficulty: Medium
 * Tags: array, dp, greedy
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

function maxArea(height: number[]): number {
    let left = 0, right = height.length - 1;
    let maxArea = 0;
    
    while (left < right) {
        const width = right - left;
        const area = width * Math.min(height[left], height[right]);
        maxArea = Math.max(maxArea, area);
        
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }
    
    return maxArea;
};