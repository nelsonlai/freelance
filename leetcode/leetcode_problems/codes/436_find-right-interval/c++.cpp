/*
 * Problem: Find Right Interval
 * Difficulty: Medium
 * Tags: array, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<pair<int, int>> starts;
        for (int i = 0; i < n; i++) {
            starts.push_back({intervals[i][0], i});
        }
        sort(starts.begin(), starts.end());
        
        vector<int> result(n);
        for (int i = 0; i < n; i++) {
            int end = intervals[i][1];
            int left = 0, right = n - 1;
            int idx = -1;
            
            while (left <= right) {
                int mid = (left + right) / 2;
                if (starts[mid].first >= end) {
                    idx = starts[mid].second;
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            
            result[i] = idx;
        }
        
        return result;
    }
};