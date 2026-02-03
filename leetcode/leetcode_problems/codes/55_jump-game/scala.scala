object Solution {
    def canJump(nums: Array[Int]): Boolean = {
        var farthest = 0
        for (i <- nums.indices) {
            if (i > farthest) {
                return false
            }
            farthest = math.max(farthest, i + nums(i))
            if (farthest >= nums.length - 1) {
                return true
            }
        }
        true
    }
}