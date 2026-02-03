object Solution {
    def permuteUnique(nums: Array[Int]): List[List[Int]] = {
        val sortedNums = nums.sorted
        var result = List[List[Int]]()
        var current = List[Int]()
        val used = Array.fill(sortedNums.length)(false)
        
        def backtrack(): Unit = {
            if (current.length == sortedNums.length) {
                result = current.reverse :: result
                return
            }
            
            for (i <- sortedNums.indices) {
                if (!used(i) && !(i > 0 && sortedNums(i) == sortedNums(i-1) && !used(i-1))) {
                    used(i) = true
                    current = sortedNums(i) :: current
                    backtrack()
                    current = current.tail
                    used(i) = false
                }
            }
        }
        
        backtrack()
        result.reverse
    }
}