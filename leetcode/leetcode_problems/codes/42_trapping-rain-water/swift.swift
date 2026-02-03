class Solution {
    func trap(_ height: [Int]) -> Int {
        if height.isEmpty {
            return 0
        }
        
        var left = 0, right = height.count - 1
        var leftMax = 0, rightMax = 0
        var water = 0
        
        while left < right {
            if height[left] < height[right] {
                if height[left] >= leftMax {
                    leftMax = height[left]
                } else {
                    water += leftMax - height[left]
                }
                left += 1
            } else {
                if height[right] >= rightMax {
                    rightMax = height[right]
                } else {
                    water += rightMax - height[right]
                }
                right -= 1
            }
        }
        
        return water
    }
}