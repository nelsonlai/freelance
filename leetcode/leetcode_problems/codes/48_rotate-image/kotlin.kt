class Solution {
    fun rotate(matrix: Array<IntArray>) {
        val n = matrix.size
        // Transpose
        for (i in 0 until n) {
            for (j in i until n) {
                val temp = matrix[i][j]
                matrix[i][j] = matrix[j][i]
                matrix[j][i] = temp
            }
        }
        
        // Reverse each row
        for (i in 0 until n) {
            for (j in 0 until n / 2) {
                val temp = matrix[i][j]
                matrix[i][j] = matrix[i][n - 1 - j]
                matrix[i][n - 1 - j] = temp
            }
        }
    }
}