/*
 * Problem: Minimize Product Sum of Two Arrays
 * Difficulty: Medium
 * Tags: array, greedy, sort
 * 
 * Approach: Sort one ascending, one descending, multiply corresponding elements
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(1)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minProductSum(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end(), greater<int>());
        
        int result = 0;
        for (int i = 0; i < nums1.size(); i++) {
            result += nums1[i] * nums2[i];
        }
        
        return result;
    }
};