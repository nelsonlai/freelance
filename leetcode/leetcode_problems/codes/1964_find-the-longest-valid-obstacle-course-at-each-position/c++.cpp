/*
 * Problem: Find the Longest Valid Obstacle Course at Each Position
 * Difficulty: Hard
 * Tags: array, tree, search, binary search, LIS
 * 
 * Approach: Longest Increasing Subsequence (LIS) with binary search
 * Time Complexity: O(n log n) where n is obstacles
 * Space Complexity: O(n)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {
        int n = obstacles.size();
        vector<int> result(n);
        vector<int> dp;  // dp[i] = smallest ending value for LIS of length i+1
        
        for (int i = 0; i < n; i++) {
            auto it = upper_bound(dp.begin(), dp.end(), obstacles[i]);
            if (it == dp.end()) {
                dp.push_back(obstacles[i]);
            } else {
                *it = obstacles[i];
            }
            result[i] = it - dp.begin() + 1;
        }
        
        return result;
    }
};