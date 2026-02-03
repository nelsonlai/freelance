class Solution {
    func generateMatrix(_ n: Int) -> [[Int]] {
        var matrix = Array(repeating: Array(repeating: 0, count: n), count: n)
        var num = 1
        var top = 0, bottom = n - 1
        var left = 0, right = n - 1
        
        while top <= bottom && left <= right {
            // Right
            for j in left...right {
                matrix[top][j] = num
                num += 1
            }
            top += 1
            
            // Down
            for i in top...bottom {
                matrix[i][right] = num
                num += 1
            }
            right -= 1
            
            // Left
            if top <= bottom {
                for j in stride(from: right, through: left, by: -1) {
                    matrix[bottom][j] = num
                    num += 1
                }
                bottom -= 1
            }
            
            // Up
            if left <= right {
                for i in stride(from: bottom, through: top, by: -1) {
                    matrix[i][left] = num
                    num += 1
                }
                left += 1
            }
        }
        
        return matrix
    }
}