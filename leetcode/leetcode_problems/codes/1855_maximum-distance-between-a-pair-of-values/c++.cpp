/*
 * Problem: Maximum Distance Between a Pair of Values
 * Difficulty: Medium
 * Tags: array, search, two pointers
 * 
 * Approach: Two pointers - for each i, find rightmost j where nums1[i] <= nums2[j]
 * Time Complexity: O(n + m) where n, m are array lengths
 * Space Complexity: O(1)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int result = 0;
        int j = 0;
        
        for (int i = 0; i < nums1.size(); i++) {
            while (j < nums2.size() && nums1[i] <= nums2[j]) {
                j++;
            }
            
            if (j > i + 1) {
                result = max(result, j - 1 - i);
            }
        }
        
        return result;
    }
};