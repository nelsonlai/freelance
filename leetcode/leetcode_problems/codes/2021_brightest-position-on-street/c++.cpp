/*
 * Problem: Brightest Position on Street
 * Difficulty: Medium
 * Tags: array, sort, line sweep
 * 
 * Approach: Use line sweep - mark start and end of light coverage
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int brightestPosition(vector<vector<int>>& lights) {
        vector<pair<int, int>> events;
        
        for (auto& light : lights) {
            int pos = light[0];
            int range = light[1];
            events.push_back({pos - range, 1});
            events.push_back({pos + range + 1, -1});
        }
        
        sort(events.begin(), events.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first != b.first) {
                return a.first < b.first;
            }
            return a.second > b.second; // End before start
        });
        
        int maxBrightness = 0;
        int currentBrightness = 0;
        int resultPos = 0;
        
        for (auto& [pos, delta] : events) {
            currentBrightness += delta;
            if (currentBrightness > maxBrightness) {
                maxBrightness = currentBrightness;
                resultPos = pos;
            }
        }
        
        return resultPos;
    }
};