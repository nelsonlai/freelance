object Solution {
    def plusOne(digits: Array[Int]): Array[Int] = {
        val result = digits.clone()
        for (i <- result.length - 1 to 0 by -1) {
            if (result(i) < 9) {
                result(i) += 1
                return result
            }
            result(i) = 0
        }
        
        (1 +: result).toArray
    }
}