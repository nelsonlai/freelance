class Solution {

    /**
     * @param Integer[] $nums1
     * @param Integer[] $nums2
     * @return Float
     */
    function findMedianSortedArrays($nums1, $nums2) {
        if (count($nums1) > count($nums2)) {
            $temp = $nums1;
            $nums1 = $nums2;
            $nums2 = $temp;
        }
        
        $m = count($nums1);
        $n = count($nums2);
        $left = 0;
        $right = $m;
        
        while ($left <= $right) {
            $partition1 = intval(($left + $right) / 2);
            $partition2 = intval(($m + $n + 1) / 2) - $partition1;
            
            $maxLeft1 = ($partition1 == 0) ? PHP_INT_MIN : $nums1[$partition1 - 1];
            $minRight1 = ($partition1 == $m) ? PHP_INT_MAX : $nums1[$partition1];
            
            $maxLeft2 = ($partition2 == 0) ? PHP_INT_MIN : $nums2[$partition2 - 1];
            $minRight2 = ($partition2 == $n) ? PHP_INT_MAX : $nums2[$partition2];
            
            if ($maxLeft1 <= $minRight2 && $maxLeft2 <= $minRight1) {
                if (($m + $n) % 2 == 0) {
                    return (max($maxLeft1, $maxLeft2) + min($minRight1, $minRight2)) / 2.0;
                } else {
                    return max($maxLeft1, $maxLeft2);
                }
            } else if ($maxLeft1 > $minRight2) {
                $right = $partition1 - 1;
            } else {
                $left = $partition1 + 1;
            }
        }
        
        return 0.0;
    }
}