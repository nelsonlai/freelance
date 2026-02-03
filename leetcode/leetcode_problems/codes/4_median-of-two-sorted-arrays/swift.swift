class Solution {
    func findMedianSortedArrays(_ nums1: [Int], _ nums2: [Int]) -> Double {
        var nums1 = nums1
        var nums2 = nums2
        if nums1.count > nums2.count {
            swap(&nums1, &nums2)
        }
        
        let m = nums1.count
        let n = nums2.count
        var left = 0
        var right = m
        
        while left <= right {
            let partition1 = (left + right) / 2
            let partition2 = (m + n + 1) / 2 - partition1
            
            let maxLeft1 = partition1 == 0 ? Int.min : nums1[partition1 - 1]
            let minRight1 = partition1 == m ? Int.max : nums1[partition1]
            
            let maxLeft2 = partition2 == 0 ? Int.min : nums2[partition2 - 1]
            let minRight2 = partition2 == n ? Int.max : nums2[partition2]
            
            if maxLeft1 <= minRight2 && maxLeft2 <= minRight1 {
                if (m + n) % 2 == 0 {
                    return Double(max(maxLeft1, maxLeft2) + min(minRight1, minRight2)) / 2.0
                } else {
                    return Double(max(maxLeft1, maxLeft2))
                }
            } else if maxLeft1 > minRight2 {
                right = partition1 - 1
            } else {
                left = partition1 + 1
            }
        }
        
        return 0.0
    }
}