/*
 * Problem: Average Height of Buildings in Each Segment
 * Difficulty: Medium
 * Tags: array, greedy, sort, line sweep
 * 
 * Approach: Use line sweep to merge overlapping buildings, calculate average heights
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> averageHeightOfBuildings(vector<vector<int>>& buildings) {
        vector<vector<int>> events;
        
        for (auto& building : buildings) {
            int start = building[0];
            int end = building[1];
            int height = building[2];
            events.push_back({start, height, 1});
            events.push_back({end, height, -1});
        }
        
        sort(events.begin(), events.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] != b[0]) {
                return a[0] < b[0];
            }
            return a[2] > b[2]; // End before start
        });
        
        vector<vector<int>> result;
        long long currentSum = 0;
        int currentCount = 0;
        int prevPos = -1;
        
        for (auto& event : events) {
            int pos = event[0];
            int height = event[1];
            int delta = event[2];
            
            if (prevPos != -1 && prevPos < pos && currentCount > 0) {
                int avgHeight = currentSum / currentCount;
                if (!result.empty() && result.back()[1] == prevPos && 
                    result.back()[2] == avgHeight) {
                    // Merge with previous segment
                    result.back()[1] = pos;
                } else {
                    result.push_back({prevPos, pos, avgHeight});
                }
            }
            
            currentSum += height * delta;
            currentCount += delta;
            prevPos = pos;
        }
        
        return result;
    }
};