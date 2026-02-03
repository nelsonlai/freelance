object Solution {
    def jump(nums: Array[Int]): Int = {
        var jumps = 0
        var currentEnd = 0
        var farthest = 0
        
        for (i <- 0 until nums.length - 1) {
            farthest = math.max(farthest, i + nums(i))
            if (i == currentEnd) {
                jumps += 1
                currentEnd = farthest
            }
        }
        
        jumps
    }
}