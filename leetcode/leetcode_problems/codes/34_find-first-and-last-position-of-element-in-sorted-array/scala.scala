object Solution {
    def searchRange(nums: Array[Int], target: Int): Array[Int] = {
        val first = findFirst(nums, target)
        if (first == -1) {
            return Array(-1, -1)
        }
        val last = findLast(nums, target)
        Array(first, last)
    }
    
    def findFirst(nums: Array[Int], target: Int): Int = {
        var left = 0
        var right = nums.length - 1
        var result = -1
        while (left <= right) {
            val mid = left + (right - left) / 2
            if (nums(mid) == target) {
                result = mid
                right = mid - 1
            } else if (nums(mid) < target) {
                left = mid + 1
            } else {
                right = mid - 1
            }
        }
        result
    }
    
    def findLast(nums: Array[Int], target: Int): Int = {
        var left = 0
        var right = nums.length - 1
        var result = -1
        while (left <= right) {
            val mid = left + (right - left) / 2
            if (nums(mid) == target) {
                result = mid
                left = mid + 1
            } else if (nums(mid) < target) {
                left = mid + 1
            } else {
                right = mid - 1
            }
        }
        result
    }
}