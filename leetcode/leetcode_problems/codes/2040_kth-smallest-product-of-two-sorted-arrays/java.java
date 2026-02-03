/**
 * Problem: Kth Smallest Product of Two Sorted Arrays
 * Difficulty: Hard
 * Tags: array, sort, search, binary search
 * 
 * Approach: Binary search on answer, count products <= mid
 * Time Complexity: O(n * m * log(max_product)) where n, m are array lengths
 * Space Complexity: O(1)
 */

import java.util.*;

class Solution {
    public long kthSmallestProduct(int[] nums1, int[] nums2, long k) {
        long left = -10000000000L;
        long right = 10000000000L;
        
        while (left < right) {
            long mid = (left + right) / 2;
            if (countProducts(nums1, nums2, mid) >= k) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
    
    private long countProducts(int[] nums1, int[] nums2, long mid) {
        long count = 0;
        for (int num1 : nums1) {
            if (num1 == 0) {
                if (mid >= 0) {
                    count += nums2.length;
                }
            } else if (num1 > 0) {
                // num1 * num2 <= mid => num2 <= mid / num1
                long target = mid / num1;
                if (mid < 0 && mid % num1 != 0) {
                    target--;
                }
                // Count nums2 <= target
                int idx = Arrays.binarySearch(nums2, (int)target + 1);
                if (idx < 0) {
                    idx = -(idx + 1);
                }
                count += idx;
            } else {  // num1 < 0
                // num1 * num2 <= mid => num2 >= mid / num1 (reverse)
                long target = mid / num1;
                if (mid < 0 && mid % num1 != 0) {
                    target++;
                }
                // Count nums2 >= target
                int idx = Arrays.binarySearch(nums2, (int)target);
                if (idx < 0) {
                    idx = -(idx + 1);
                }
                count += nums2.length - idx;
            }
        }
        return count;
    }
}