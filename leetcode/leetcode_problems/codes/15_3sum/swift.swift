class Solution {
    func threeSum(_ nums: [Int]) -> [[Int]] {
        let sorted = nums.sorted()
        var result = [[Int]]()
        
        for i in 0..<sorted.count - 2 {
            if i > 0 && sorted[i] == sorted[i - 1] {
                continue
            }
            
            var left = i + 1
            var right = sorted.count - 1
            
            while left < right {
                let sum = sorted[i] + sorted[left] + sorted[right]
                if sum == 0 {
                    result.append([sorted[i], sorted[left], sorted[right]])
                    while left < right && sorted[left] == sorted[left + 1] {
                        left += 1
                    }
                    while left < right && sorted[right] == sorted[right - 1] {
                        right -= 1
                    }
                    left += 1
                    right -= 1
                } else if sum < 0 {
                    left += 1
                } else {
                    right -= 1
                }
            }
        }
        
        return result
    }
}