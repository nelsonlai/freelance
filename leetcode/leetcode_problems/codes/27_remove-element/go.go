// Problem: Remove Element
// Difficulty: Easy
// Tags: array, sort
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

func removeElement(nums []int, val int) int {
    writeIndex := 0
    for i := 0; i < len(nums); i++ {
        if nums[i] != val {
            nums[writeIndex] = nums[i]
            writeIndex++
        }
    }
    return writeIndex
}