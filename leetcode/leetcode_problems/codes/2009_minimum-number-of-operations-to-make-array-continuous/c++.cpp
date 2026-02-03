/*
 * Problem: Minimum Number of Operations to Make Array Continuous
 * Difficulty: Hard
 * Tags: array, hash, search, sliding window
 * 
 * Approach: Sort and deduplicate, use sliding window to find longest valid subarray
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n)
 */

#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        set<int> uniqueSet(nums.begin(), nums.end());
        vector<int> unique(uniqueSet.begin(), uniqueSet.end());
        int m = unique.size();
        
        // Find longest subarray where unique[j] - unique[i] < n
        int maxKeep = 0;
        int j = 0;
        
        for (int i = 0; i < m; i++) {
            while (j < m && unique[j] < unique[i] + n) {
                j++;
            }
            maxKeep = max(maxKeep, j - i);
        }
        
        return n - maxKeep;
    }
};