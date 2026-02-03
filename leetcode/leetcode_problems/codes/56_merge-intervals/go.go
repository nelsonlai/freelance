// Problem: Merge Intervals
// Difficulty: Medium
// Tags: array, sort
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

import "sort"

func merge(intervals [][]int) [][]int {
    if len(intervals) == 0 {
        return [][]int{}
    }
    
    sort.Slice(intervals, func(i, j int) bool {
        return intervals[i][0] < intervals[j][0]
    })
    
    result := [][]int{intervals[0]}
    
    for i := 1; i < len(intervals); i++ {
        current := intervals[i]
        last := result[len(result)-1]
        if current[0] <= last[1] {
            if current[1] > last[1] {
                last[1] = current[1]
            }
        } else {
            result = append(result, current)
        }
    }
    
    return result
}