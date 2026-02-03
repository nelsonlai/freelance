/*
 * Problem: Russian Doll Envelopes
 * Difficulty: Hard
 * Tags: array, dp, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        sort(envelopes.begin(), envelopes.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] == b[0]) {
                return b[1] > a[1];
            }
            return a[0] < b[0];
        });
        
        vector<int> dp;
        for (auto& envelope : envelopes) {
            int height = envelope[1];
            auto it = lower_bound(dp.begin(), dp.end(), height);
            if (it == dp.end()) {
                dp.push_back(height);
            } else {
                *it = height;
            }
        }
        
        return dp.size();
    }
};