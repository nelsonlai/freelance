class Solution {
    func removeElement(_ nums: inout [Int], _ val: Int) -> Int {
        var writeIndex = 0
        for i in 0..<nums.count {
            if nums[i] != val {
                nums[writeIndex] = nums[i]
                writeIndex += 1
            }
        }
        return writeIndex
    }
}