/*
 * Problem: Kth Smallest Product of Two Sorted Arrays
 * Difficulty: Hard
 * Tags: array, sort, search, binary search
 * 
 * Approach: Binary search on answer, count products <= mid
 * Time Complexity: O(n * m * log(max_product)) where n, m are array lengths
 * Space Complexity: O(1)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    long long countProducts(vector<int>& nums1, vector<int>& nums2, long long mid) {
        long long count = 0;
        for (int num1 : nums1) {
            if (num1 == 0) {
                if (mid >= 0) {
                    count += nums2.size();
                }
            } else if (num1 > 0) {
                // num1 * num2 <= mid => num2 <= mid / num1
                long long target = mid / num1;
                if (mid < 0 && mid % num1 != 0) {
                    target--;
                }
                // Count nums2 <= target
                int idx = upper_bound(nums2.begin(), nums2.end(), (int)target) - nums2.begin();
                count += idx;
            } else {  // num1 < 0
                // num1 * num2 <= mid => num2 >= mid / num1 (reverse)
                long long target = mid / num1;
                if (mid < 0 && mid % num1 != 0) {
                    target++;
                }
                // Count nums2 >= target
                int idx = lower_bound(nums2.begin(), nums2.end(), (int)target) - nums2.begin();
                count += nums2.size() - idx;
            }
        }
        return count;
    }
    
public:
    long long kthSmallestProduct(vector<int>& nums1, vector<int>& nums2, long long k) {
        long long left = -10000000000LL;
        long long right = 10000000000LL;
        
        while (left < right) {
            long long mid = (left + right) / 2;
            if (countProducts(nums1, nums2, mid) >= k) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
};