/*
 * Problem: The Skyline Problem
 * Difficulty: Hard
 * Tags: array, tree, dp, sort, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<vector<int>> events;
        for (auto& building : buildings) {
            events.push_back({building[0], -building[2], building[1]});
            events.push_back({building[1], 0, 0});
        }
        
        sort(events.begin(), events.end());
        
        vector<vector<int>> result;
        priority_queue<pair<int, int>> heap;
        heap.push({0, INT_MAX});
        int prevHeight = 0;
        
        for (auto& event : events) {
            while (heap.top().second <= event[0]) {
                heap.pop();
            }
            
            if (event[1] < 0) {
                heap.push({-event[1], event[2]});
            }
            
            int currentHeight = heap.top().first;
            if (currentHeight != prevHeight) {
                result.push_back({event[0], currentHeight});
                prevHeight = currentHeight;
            }
        }
        
        return result;
    }
};