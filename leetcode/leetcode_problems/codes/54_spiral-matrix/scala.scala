object Solution {
    def spiralOrder(matrix: Array[Array[Int]]): List[Int] = {
        if (matrix.isEmpty || matrix(0).isEmpty) {
            return List.empty
        }
        
        var result = List[Int]()
        var top = 0
        var bottom = matrix.length - 1
        var left = 0
        var right = matrix(0).length - 1
        
        while (top <= bottom && left <= right) {
            // Right
            for (j <- left to right) {
                result = result :+ matrix(top)(j)
            }
            top += 1
            
            // Down
            for (i <- top to bottom) {
                result = result :+ matrix(i)(right)
            }
            right -= 1
            
            // Left
            if (top <= bottom) {
                for (j <- right to left by -1) {
                    result = result :+ matrix(bottom)(j)
                }
                bottom -= 1
            }
            
            // Up
            if (left <= right) {
                for (i <- bottom to top by -1) {
                    result = result :+ matrix(i)(left)
                }
                left += 1
            }
        }
        
        result
    }
}