class Solution {
    fun trap(height: IntArray): Int {
        if (height.isEmpty()) {
            return 0
        }
        
        var left = 0
        var right = height.size - 1
        var leftMax = 0
        var rightMax = 0
        var water = 0
        
        while (left < right) {
            if (height[left] < height[right]) {
                if (height[left] >= leftMax) {
                    leftMax = height[left]
                } else {
                    water += leftMax - height[left]
                }
                left++
            } else {
                if (height[right] >= rightMax) {
                    rightMax = height[right]
                } else {
                    water += rightMax - height[right]
                }
                right--
            }
        }
        
        return water
    }
}