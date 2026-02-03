class Solution {
    fun spiralOrder(matrix: Array<IntArray>): List<Int> {
        if (matrix.isEmpty() || matrix[0].isEmpty()) {
            return emptyList()
        }
        
        val result = mutableListOf<Int>()
        var top = 0
        var bottom = matrix.size - 1
        var left = 0
        var right = matrix[0].size - 1
        
        while (top <= bottom && left <= right) {
            // Right
            for (j in left..right) {
                result.add(matrix[top][j])
            }
            top++
            
            // Down
            for (i in top..bottom) {
                result.add(matrix[i][right])
            }
            right--
            
            // Left
            if (top <= bottom) {
                for (j in right downTo left) {
                    result.add(matrix[bottom][j])
                }
                bottom--
            }
            
            // Up
            if (left <= right) {
                for (i in bottom downTo top) {
                    result.add(matrix[i][left])
                }
                left++
            }
        }
        
        return result
    }
}