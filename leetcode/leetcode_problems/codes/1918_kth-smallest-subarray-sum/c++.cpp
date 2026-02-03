/*
 * Problem: Kth Smallest Subarray Sum
 * Difficulty: Medium
 * Tags: array, search, binary search
 * 
 * Approach: Binary search on answer, count subarrays with sum <= target
 * Time Complexity: O(n log(sum)) where sum is total sum
 * Space Complexity: O(1)
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
private:
    int countSubarrays(vector<int>& nums, int target) {
        int count = 0;
        int left = 0;
        int currentSum = 0;
        
        for (int right = 0; right < nums.size(); right++) {
            currentSum += nums[right];
            while (currentSum > target) {
                currentSum -= nums[left];
                left++;
            }
            count += right - left + 1;
        }
        
        return count;
    }
    
public:
    int kthSmallestSubarraySum(vector<int>& nums, int k) {
        int left = *min_element(nums.begin(), nums.end());
        int right = 0;
        for (int num : nums) {
            right += num;
        }
        
        int result = right;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (countSubarrays(nums, mid) >= k) {
                result = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return result;
    }
};