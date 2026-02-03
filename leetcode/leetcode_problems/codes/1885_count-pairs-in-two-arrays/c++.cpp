/*
 * Problem: Count Pairs in Two Arrays
 * Difficulty: Medium
 * Tags: array, sort, search, binary search
 * 
 * Approach: Rearrange inequality, sort and use binary search
 * Time Complexity: O(n log n) where n is length
 * Space Complexity: O(n)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long countPairs(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> diff(n);
        for (int i = 0; i < n; i++) {
            diff[i] = nums1[i] - nums2[i];
        }
        sort(diff.begin(), diff.end());
        
        long long result = 0;
        for (int i = 0; i < n; i++) {
            int target = -diff[i];
            auto it = upper_bound(diff.begin(), diff.end(), target);
            int idx = it - diff.begin();
            result += n - max(idx, i + 1);
        }
        
        return result;
    }
};