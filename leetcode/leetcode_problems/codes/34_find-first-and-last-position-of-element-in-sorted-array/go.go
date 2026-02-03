// Problem: Find First and Last Position of Element in Sorted Array
// Difficulty: Medium
// Tags: array, sort, search
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

func searchRange(nums []int, target int) []int {
    first := findFirst(nums, target)
    if first == -1 {
        return []int{-1, -1}
    }
    last := findLast(nums, target)
    return []int{first, last}
}

func findFirst(nums []int, target int) int {
    left, right := 0, len(nums)-1
    result := -1
    for left <= right {
        mid := left + (right-left)/2
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

func findLast(nums []int, target int) int {
    left, right := 0, len(nums)-1
    result := -1
    for left <= right {
        mid := left + (right-left)/2
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