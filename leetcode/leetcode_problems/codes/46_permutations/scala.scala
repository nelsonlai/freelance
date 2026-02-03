object Solution {
    def permute(nums: Array[Int]): List[List[Int]] = {
        var result = List[List[Int]]()
        var current = List[Int]()
        val used = Array.fill(nums.length)(false)
        
        def backtrack(): Unit = {
            if (current.length == nums.length) {
                result = current.reverse :: result
                return
            }
            
            for (i <- nums.indices) {
                if (!used(i)) {
                    used(i) = true
                    current = nums(i) :: current
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