/*
 * Problem: Widest Pair of Indices With Equal Range Sum
 * Difficulty: Medium
 * Tags: array, hash, prefix sum
 * 
 * Approach: Use prefix sum difference, find widest pair with same difference
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int widestPairOfIndices(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> diffMap;
        diffMap[0] = -1;
        int diff = 0;
        int maxWidth = 0;
        
        for (int i = 0; i < nums1.size(); i++) {
            diff += nums1[i] - nums2[i];
            if (diffMap.find(diff) != diffMap.end()) {
                maxWidth = max(maxWidth, i - diffMap[diff]);
            } else {
                diffMap[diff] = i;
            }
        }
        
        return maxWidth;
    }
};