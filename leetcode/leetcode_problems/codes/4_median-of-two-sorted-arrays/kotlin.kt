class Solution {
    fun findMedianSortedArrays(nums1: IntArray, nums2: IntArray): Double {
        var nums1 = nums1
        var nums2 = nums2
        if (nums1.size > nums2.size) {
            val temp = nums1
            nums1 = nums2
            nums2 = temp
        }
        
        val m = nums1.size
        val n = nums2.size
        var left = 0
        var right = m
        
        while (left <= right) {
            val partition1 = (left + right) / 2
            val partition2 = (m + n + 1) / 2 - partition1
            
            val maxLeft1 = if (partition1 == 0) Int.MIN_VALUE else nums1[partition1 - 1]
            val minRight1 = if (partition1 == m) Int.MAX_VALUE else nums1[partition1]
            
            val maxLeft2 = if (partition2 == 0) Int.MIN_VALUE else nums2[partition2 - 1]
            val minRight2 = if (partition2 == n) Int.MAX_VALUE else nums2[partition2]
            
            if (maxLeft1 <= minRight2 && maxLeft2 <= minRight1) {
                return if ((m + n) % 2 == 0) {
                    (maxOf(maxLeft1, maxLeft2) + minOf(minRight1, minRight2)) / 2.0
                } else {
                    maxOf(maxLeft1, maxLeft2).toDouble()
                }
            } else if (maxLeft1 > minRight2) {
                right = partition1 - 1
            } else {
                left = partition1 + 1
            }
        }
        
        return 0.0
    }
}