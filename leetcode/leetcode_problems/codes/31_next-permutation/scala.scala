object Solution {
    def nextPermutation(nums: Array[Int]): Unit = {
        var i = nums.length - 2
        while (i >= 0 && nums(i) >= nums(i + 1)) {
            i -= 1
        }
        
        if (i >= 0) {
            var j = nums.length - 1
            while (nums(j) <= nums(i)) {
                j -= 1
            }
            val temp = nums(i)
            nums(i) = nums(j)
            nums(j) = temp
        }
        
        var left = i + 1
        var right = nums.length - 1
        while (left < right) {
            val temp = nums(left)
            nums(left) = nums(right)
            nums(right) = temp
            left += 1
            right -= 1
        }
    }
}