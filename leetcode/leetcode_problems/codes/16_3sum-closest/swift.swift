class Solution {
    func threeSumClosest(_ nums: [Int], _ target: Int) -> Int {
        let sorted = nums.sorted()
        var closestSum = sorted[0] + sorted[1] + sorted[2]
        
        for i in 0..<sorted.count - 2 {
            var left = i + 1
            var right = sorted.count - 1
            
            while left < right {
                let currentSum = sorted[i] + sorted[left] + sorted[right]
                if abs(currentSum - target) < abs(closestSum - target) {
                    closestSum = currentSum
                }
                
                if currentSum < target {
                    left += 1
                } else if currentSum > target {
                    right -= 1
                } else {
                    return currentSum
                }
            }
        }
        
        return closestSum
    }
}