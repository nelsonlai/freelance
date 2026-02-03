/*
 * Problem: Minimum Time Difference
 * Difficulty: Medium
 * Tags: array, string, math, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <climits>

using namespace std;

class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        vector<int> minutes;
        for (string time : timePoints) {
            size_t pos = time.find(':');
            int h = stoi(time.substr(0, pos));
            int m = stoi(time.substr(pos + 1));
            minutes.push_back(h * 60 + m);
        }
        sort(minutes.begin(), minutes.end());
        
        int minDiff = INT_MAX;
        for (int i = 0; i < minutes.size(); i++) {
            int diff = minutes[i] - minutes[(i - 1 + minutes.size()) % minutes.size()];
            minDiff = min(minDiff, min(diff, 1440 - diff));
        }
        
        return minDiff;
    }
};