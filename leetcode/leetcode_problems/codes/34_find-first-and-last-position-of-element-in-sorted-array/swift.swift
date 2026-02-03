class Solution {
    func searchRange(_ nums: [Int], _ target: Int) -> [Int] {
        let first = findFirst(nums, target)
        if first == -1 {
            return [-1, -1]
        }
        let last = findLast(nums, target)
        return [first, last]
    }
    
    private func findFirst(_ nums: [Int], _ target: Int) -> Int {
        var left = 0
        var right = nums.count - 1
        var result = -1
        while left <= right {
            let mid = left + (right - left) / 2
            if nums[mid] == target {
                result = mid
                right = mid - 1
            } else if nums[mid] < target {
                left = mid + 1
            } else {
                right = mid - 1
            }
        }
        return result
    }
    
    private func findLast(_ nums: [Int], _ target: Int) -> Int {
        var left = 0
        var right = nums.count - 1
        var result = -1
        while left <= right {
            let mid = left + (right - left) / 2
            if nums[mid] == target {
                result = mid
                left = mid + 1
            } else if nums[mid] < target {
                left = mid + 1
            } else {
                right = mid - 1
            }
        }
        return result
    }
}