class Solution {
    func jump(_ nums: [Int]) -> Int {
        var jumps = 0
        var currentEnd = 0
        var farthest = 0
        
        for i in 0..<nums.count - 1 {
            farthest = max(farthest, i + nums[i])
            if i == currentEnd {
                jumps += 1
                currentEnd = farthest
            }
        }
        
        return jumps
    }
}