// Problem: 3Sum Closest
// Difficulty: Medium
// Tags: array, sort
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

import "sort"

func threeSumClosest(nums []int, target int) int {
    sort.Ints(nums)
    closestSum := nums[0] + nums[1] + nums[2]
    
    for i := 0; i < len(nums)-2; i++ {
        left, right := i+1, len(nums)-1
        for left < right {
            currentSum := nums[i] + nums[left] + nums[right]
            if abs(currentSum-target) < abs(closestSum-target) {
                closestSum = currentSum
            }
            
            if currentSum < target {
                left++
            } else if currentSum > target {
                right--
            } else {
                return currentSum
            }
        }
    }
    
    return closestSum
}

func abs(x int) int {
    if x < 0 {
        return -x
    }
    return x
}