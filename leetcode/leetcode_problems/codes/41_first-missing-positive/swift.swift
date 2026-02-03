class Solution {
    func firstMissingPositive(_ nums: [Int]) -> Int {
        var nums = nums
        let n = nums.count
        
        // Place each number in its correct position
        var i = 0
        while i < n {
            let num = nums[i]
            if num >= 1 && num <= n && nums[num - 1] != num {
                nums.swapAt(i, num - 1)
            } else {
                i += 1
            }
        }
        
        // Find the first missing positive
        for i in 0..<n {
            if nums[i] != i + 1 {
                return i + 1
            }
        }
        
        return n + 1
    }
}