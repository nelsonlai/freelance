// Problem: Spiral Matrix
// Difficulty: Medium
// Tags: array
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

func spiralOrder(matrix [][]int) []int {
    if len(matrix) == 0 || len(matrix[0]) == 0 {
        return []int{}
    }
    
    result := []int{}
    top, bottom := 0, len(matrix)-1
    left, right := 0, len(matrix[0])-1
    
    for top <= bottom && left <= right {
        // Right
        for j := left; j <= right; j++ {
            result = append(result, matrix[top][j])
        }
        top++
        
        // Down
        for i := top; i <= bottom; i++ {
            result = append(result, matrix[i][right])
        }
        right--
        
        // Left
        if top <= bottom {
            for j := right; j >= left; j-- {
                result = append(result, matrix[bottom][j])
            }
            bottom--
        }
        
        // Up
        if left <= right {
            for i := bottom; i >= top; i-- {
                result = append(result, matrix[i][left])
            }
            left++
        }
    }
    
    return result
}