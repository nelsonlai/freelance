// Problem: Trapping Rain Water
// Difficulty: Hard
// Tags: array, dp, stack
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) or O(n * m) for DP table

func trap(height []int) int {
    if len(height) == 0 {
        return 0
    }
    
    left, right := 0, len(height)-1
    leftMax, rightMax := 0, 0
    water := 0
    
    for left < right {
        if height[left] < height[right] {
            if height[left] >= leftMax {
                leftMax = height[left]
            } else {
                water += leftMax - height[left]
            }
            left++
        } else {
            if height[right] >= rightMax {
                rightMax = height[right]
            } else {
                water += rightMax - height[right]
            }
            right--
        }
    }
    
    return water
}