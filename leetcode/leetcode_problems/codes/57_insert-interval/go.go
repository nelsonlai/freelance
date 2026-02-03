// Problem: Insert Interval
// Difficulty: Medium
// Tags: array, sort
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

func insert(intervals [][]int, newInterval []int) [][]int {
    result := [][]int{}
    i := 0
    
    // Add all intervals before newInterval
    for i < len(intervals) && intervals[i][1] < newInterval[0] {
        result = append(result, intervals[i])
        i++
    }
    
    // Merge overlapping intervals
    for i < len(intervals) && intervals[i][0] <= newInterval[1] {
        if intervals[i][0] < newInterval[0] {
            newInterval[0] = intervals[i][0]
        }
        if intervals[i][1] > newInterval[1] {
            newInterval[1] = intervals[i][1]
        }
        i++
    }
    
    result = append(result, newInterval)
    
    // Add remaining intervals
    for i < len(intervals) {
        result = append(result, intervals[i])
        i++
    }
    
    return result
}