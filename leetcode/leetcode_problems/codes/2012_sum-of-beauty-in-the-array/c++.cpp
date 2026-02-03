/*
 * Problem: Sum of Beauty in the Array
 * Difficulty: Medium
 * Tags: array, prefix/suffix arrays
 * 
 * Approach: Precompute max from left and min from right for each position
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int sumOfBeauties(vector<int>& nums) {
        int n = nums.size();
        vector<int> maxLeft(n);
        vector<int> minRight(n);
        
        maxLeft[0] = nums[0];
        for (int i = 1; i < n; i++) {
            maxLeft[i] = max(maxLeft[i - 1], nums[i]);
        }
        
        minRight[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            minRight[i] = min(minRight[i + 1], nums[i]);
        }
        
        int result = 0;
        for (int i = 1; i < n - 1; i++) {
            if (maxLeft[i - 1] < nums[i] && nums[i] < minRight[i + 1]) {
                result += 2;
            } else if (nums[i - 1] < nums[i] && nums[i] < nums[i + 1]) {
                result += 1;
            }
        }
        
        return result;
    }
};