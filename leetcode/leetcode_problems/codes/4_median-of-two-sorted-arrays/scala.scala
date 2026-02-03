object Solution {
    def findMedianSortedArrays(nums1: Array[Int], nums2: Array[Int]): Double = {
        var nums1 = nums1
        var nums2 = nums2
        if (nums1.length > nums2.length) {
            val temp = nums1
            nums1 = nums2
            nums2 = temp
        }
        
        val m = nums1.length
        val n = nums2.length
        var left = 0
        var right = m
        
        while (left <= right) {
            val partition1 = (left + right) / 2
            val partition2 = (m + n + 1) / 2 - partition1
            
            val maxLeft1 = if (partition1 == 0) Int.MinValue else nums1(partition1 - 1)
            val minRight1 = if (partition1 == m) Int.MaxValue else nums1(partition1)
            
            val maxLeft2 = if (partition2 == 0) Int.MinValue else nums2(partition2 - 1)
            val minRight2 = if (partition2 == n) Int.MaxValue else nums2(partition2)
            
            if (maxLeft1 <= minRight2 && maxLeft2 <= minRight1) {
                if ((m + n) % 2 == 0) {
                    return (math.max(maxLeft1, maxLeft2) + math.min(minRight1, minRight2)) / 2.0
                } else {
                    return math.max(maxLeft1, maxLeft2).toDouble
                }
            } else if (maxLeft1 > minRight2) {
                right = partition1 - 1
            } else {
                left = partition1 + 1
            }
        }
        
        0.0
    }
}