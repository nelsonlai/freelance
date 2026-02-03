object Solution {
    def generateMatrix(n: Int): Array[Array[Int]] = {
        val matrix = Array.ofDim[Int](n, n)
        var num = 1
        var top = 0
        var bottom = n - 1
        var left = 0
        var right = n - 1
        
        while (top <= bottom && left <= right) {
            // Right
            for (j <- left to right) {
                matrix(top)(j) = num
                num += 1
            }
            top += 1
            
            // Down
            for (i <- top to bottom) {
                matrix(i)(right) = num
                num += 1
            }
            right -= 1
            
            // Left
            if (top <= bottom) {
                for (j <- right to left by -1) {
                    matrix(bottom)(j) = num
                    num += 1
                }
                bottom -= 1
            }
            
            // Up
            if (left <= right) {
                for (i <- bottom to top by -1) {
                    matrix(i)(left) = num
                    num += 1
                }
                left += 1
            }
        }
        
        matrix
    }
}