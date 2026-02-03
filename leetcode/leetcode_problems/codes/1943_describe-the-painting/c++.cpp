/*
 * Problem: Describe the Painting
 * Difficulty: Medium
 * Tags: array, hash, sort, sweep line
 * 
 * Approach: Sweep line to track color changes at each position
 * Time Complexity: O(n log n) where n is segments
 * Space Complexity: O(n)
 */

#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    vector<vector<long long>> splitPainting(vector<vector<int>>& segments) {
        map<int, long long> events;
        
        for (auto& seg : segments) {
            events[seg[0]] += seg[2];
            events[seg[1]] -= seg[2];
        }
        
        vector<vector<long long>> result;
        long long currentColor = 0;
        int prevPos = -1;
        
        for (auto& [pos, color] : events) {
            if (prevPos != -1 && currentColor > 0) {
                result.push_back({prevPos, pos, currentColor});
            }
            
            currentColor += color;
            prevPos = pos;
        }
        
        return result;
    }
};