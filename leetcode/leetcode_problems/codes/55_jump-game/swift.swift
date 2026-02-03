class Solution {
    func canJump(_ nums: [Int]) -> Bool {
        var farthest = 0
        for i in 0..<nums.count {
            if i > farthest {
                return false
            }
            farthest = max(farthest, i + nums[i])
            if farthest >= nums.count - 1 {
                return true
            }
        }
        return true
    }
}