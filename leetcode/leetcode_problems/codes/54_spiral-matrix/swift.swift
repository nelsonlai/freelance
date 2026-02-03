class Solution {
    func spiralOrder(_ matrix: [[Int]]) -> [Int] {
        if matrix.isEmpty || matrix[0].isEmpty {
            return []
        }
        
        var result: [Int] = []
        var top = 0, bottom = matrix.count - 1
        var left = 0, right = matrix[0].count - 1
        
        while top <= bottom && left <= right {
            // Right
            for j in left...right {
                result.append(matrix[top][j])
            }
            top += 1
            
            // Down
            for i in top...bottom {
                result.append(matrix[i][right])
            }
            right -= 1
            
            // Left
            if top <= bottom {
                for j in stride(from: right, through: left, by: -1) {
                    result.append(matrix[bottom][j])
                }
                bottom -= 1
            }
            
            // Up
            if left <= right {
                for i in stride(from: bottom, through: top, by: -1) {
                    result.append(matrix[i][left])
                }
                left += 1
            }
        }
        
        return result
    }
}