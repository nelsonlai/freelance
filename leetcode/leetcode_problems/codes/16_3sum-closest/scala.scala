import scala.util.Sorting

object Solution {
    def threeSumClosest(nums: Array[Int], target: Int): Int = {
        Sorting.quickSort(nums)
        var closestSum = nums(0) + nums(1) + nums(2)
        
        for (i <- 0 until nums.length - 2) {
            var left = i + 1
            var right = nums.length - 1
            
            while (left < right) {
                val currentSum = nums(i) + nums(left) + nums(right)
                if (Math.abs(currentSum - target) < Math.abs(closestSum - target)) {
                    closestSum = currentSum
                }
                
                if (currentSum < target) {
                    left += 1
                } else if (currentSum > target) {
                    right -= 1
                } else {
                    return currentSum
                }
            }
        }
        
        closestSum
    }
}