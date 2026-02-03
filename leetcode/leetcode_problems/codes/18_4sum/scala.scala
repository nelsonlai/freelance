import scala.util.Sorting

object Solution {
    def fourSum(nums: Array[Int], target: Int): List[List[Int]] = {
        Sorting.quickSort(nums)
        var result = List[List[Int]]()
        val n = nums.length
        
        for (i <- 0 until n - 3) {
            if (i > 0 && nums(i) == nums(i - 1)) {
                // skip duplicates
            } else {
                for (j <- (i + 1) until n - 2) {
                    if (j > i + 1 && nums(j) == nums(j - 1)) {
                        // skip duplicates
                    } else {
                        var left = j + 1
                        var right = n - 1
                        
                        while (left < right) {
                            val sum = nums(i).toLong + nums(j) + nums(left) + nums(right)
                            if (sum == target) {
                                result = List(nums(i), nums(j), nums(left), nums(right)) :: result
                                while (left < right && nums(left) == nums(left + 1)) left += 1
                                while (left < right && nums(right) == nums(right - 1)) right -= 1
                                left += 1
                                right -= 1
                            } else if (sum < target) {
                                left += 1
                            } else {
                                right -= 1
                            }
                        }
                    }
                }
            }
        }
        
        result.reverse
    }
}