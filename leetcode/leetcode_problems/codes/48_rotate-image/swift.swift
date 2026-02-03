class Solution {
    func rotate(_ matrix: inout [[Int]]) {
        let n = matrix.count
        // Transpose
        for i in 0..<n {
            for j in i..<n {
                let temp = matrix[i][j]
                matrix[i][j] = matrix[j][i]
                matrix[j][i] = temp
            }
        }
        
        // Reverse each row
        for i in 0..<n {
            matrix[i].reverse()
        }
    }
}