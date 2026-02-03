// Problem: Container With Most Water
// Difficulty: Medium
// Tags: array, dp, greedy
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) or O(n * m) for DP table

func maxArea(height []int) int {
    left, right := 0, len(height)-1
    maxArea := 0
    
    for left < right {
        width := right - left
        area := width
        if height[left] < height[right] {
            area *= height[left]
            left++
        } else {
            area *= height[right]
            right--
        }
        if area > maxArea {
            maxArea = area
        }
    }
    
    return maxArea
}