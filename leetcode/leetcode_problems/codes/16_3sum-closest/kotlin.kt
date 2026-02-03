class Solution {
    fun threeSumClosest(nums: IntArray, target: Int): Int {
        nums.sort()
        var closestSum = nums[0] + nums[1] + nums[2]
        
        for (i in 0 until nums.size - 2) {
            var left = i + 1
            var right = nums.size - 1
            
            while (left < right) {
                val currentSum = nums[i] + nums[left] + nums[right]
                if (Math.abs(currentSum - target) < Math.abs(closestSum - target)) {
                    closestSum = currentSum
                }
                
                if (currentSum < target) {
                    left++
                } else if (currentSum > target) {
                    right--
                } else {
                    return currentSum
                }
            }
        }
        
        return closestSum
    }
}