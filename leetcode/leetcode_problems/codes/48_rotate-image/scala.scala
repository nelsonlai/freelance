object Solution {
    def rotate(matrix: Array[Array[Int]]): Unit = {
        val n = matrix.length
        // Transpose
        for (i <- 0 until n) {
            for (j <- i until n) {
                val temp = matrix(i)(j)
                matrix(i)(j) = matrix(j)(i)
                matrix(j)(i) = temp
            }
        }
        
        // Reverse each row
        for (i <- 0 until n) {
            matrix(i) = matrix(i).reverse
        }
    }
}