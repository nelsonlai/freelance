// Problem: Spiral Matrix II
// Difficulty: Medium
// Tags: array
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

func generateMatrix(n int) [][]int {
    matrix := make([][]int, n)
    for i := range matrix {
        matrix[i] = make([]int, n)
    }
    
    num := 1
    top, bottom := 0, n-1
    left, right := 0, n-1
    
    for top <= bottom && left <= right {
        // Right
        for j := left; j <= right; j++ {
            matrix[top][j] = num
            num++
        }
        top++
        
        // Down
        for i := top; i <= bottom; i++ {
            matrix[i][right] = num
            num++
        }
        right--
        
        // Left
        if top <= bottom {
            for j := right; j >= left; j-- {
                matrix[bottom][j] = num
                num++
            }
            bottom--
        }
        
        // Up
        if left <= right {
            for i := bottom; i >= top; i-- {
                matrix[i][left] = num
                num++
            }
            left++
        }
    }
    
    return matrix
}