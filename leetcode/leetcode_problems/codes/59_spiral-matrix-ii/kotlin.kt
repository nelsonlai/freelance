class Solution {
    fun generateMatrix(n: Int): Array<IntArray> {
        val matrix = Array(n) { IntArray(n) }
        var num = 1
        var top = 0
        var bottom = n - 1
        var left = 0
        var right = n - 1
        
        while (top <= bottom && left <= right) {
            // Right
            for (j in left..right) {
                matrix[top][j] = num++
            }
            top++
            
            // Down
            for (i in top..bottom) {
                matrix[i][right] = num++
            }
            right--
            
            // Left
            if (top <= bottom) {
                for (j in right downTo left) {
                    matrix[bottom][j] = num++
                }
                bottom--
            }
            
            // Up
            if (left <= right) {
                for (i in bottom downTo top) {
                    matrix[i][left] = num++
                }
                left++
            }
        }
        
        return matrix
    }
}