class Solution {
    fun nextPermutation(nums: IntArray): Unit {
        var i = nums.size - 2
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--
        }
        
        if (i >= 0) {
            var j = nums.size - 1
            while (nums[j] <= nums[i]) {
                j--
            }
            nums[i] = nums[j].also { nums[j] = nums[i] }
        }
        
        var left = i + 1
        var right = nums.size - 1
        while (left < right) {
            nums[left] = nums[right].also { nums[right] = nums[left] }
            left++
            right--
        }
    }
}