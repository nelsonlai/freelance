// Problem: Two Sum
// Difficulty: Easy
// Tags: array, hash
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) for hash map

func twoSum(nums []int, target int) []int {
    m := make(map[int]int)
    for i, num := range nums {
        complement := target - num
        if idx, ok := m[complement]; ok {
            return []int{idx, i}
        }
        m[num] = i
    }
    return []int{}
}