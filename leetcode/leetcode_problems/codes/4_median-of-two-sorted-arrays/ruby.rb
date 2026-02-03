# @param {Integer[]} nums1
# @param {Integer[]} nums2
# @return {Float}
def find_median_sorted_arrays(nums1, nums2)
    if nums1.length > nums2.length
        nums1, nums2 = nums2, nums1
    end
    
    m, n = nums1.length, nums2.length
    left, right = 0, m
    
    while left <= right
        partition1 = (left + right) / 2
        partition2 = (m + n + 1) / 2 - partition1
        
        max_left1 = partition1 == 0 ? -Float::INFINITY : nums1[partition1 - 1]
        min_right1 = partition1 == m ? Float::INFINITY : nums1[partition1]
        
        max_left2 = partition2 == 0 ? -Float::INFINITY : nums2[partition2 - 1]
        min_right2 = partition2 == n ? Float::INFINITY : nums2[partition2]
        
        if max_left1 <= min_right2 && max_left2 <= min_right1
            if (m + n) % 2 == 0
                return ([max_left1, max_left2].max + [min_right1, min_right2].min) / 2.0
            else
                return [max_left1, max_left2].max.to_f
            end
        elsif max_left1 > min_right2
            right = partition1 - 1
        else
            left = partition1 + 1
        end
    end
    
    0.0
end