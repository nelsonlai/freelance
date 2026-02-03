class Solution {
    func maxArea(_ height: [Int]) -> Int {
        var left = 0
        var right = height.count - 1
        var maxArea = 0
        
        while left < right {
            let width = right - left
            let area = width * min(height[left], height[right])
            maxArea = max(maxArea, area)
            
            if height[left] < height[right] {
                left += 1
            } else {
                right -= 1
            }
        }
        
        return maxArea
    }
}