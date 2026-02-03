/*
 * Problem: Minimum Operations to Convert Number
 * Difficulty: Medium
 * Tags: array, search, BFS
 * 
 * Approach: BFS to find shortest path from start to goal using operations
 * Time Complexity: O(n * range) where range is [0, 1000]
 * Space Complexity: O(range)
 */

#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int minimumOperations(vector<int>& nums, int start, int goal) {
        queue<pair<int, int>> q;
        q.push({start, 0});
        unordered_set<int> visited;
        visited.insert(start);
        
        while (!q.empty()) {
            auto [current, steps] = q.front();
            q.pop();
            
            if (current == goal) {
                return steps;
            }
            
            for (int num : nums) {
                // Try all three operations
                vector<int> nextVals = {current + num, current - num, current ^ num};
                for (int nextVal : nextVals) {
                    if (nextVal == goal) {
                        return steps + 1;
                    }
                    
                    // Only consider values in valid range [0, 1000]
                    if (nextVal >= 0 && nextVal <= 1000 && visited.find(nextVal) == visited.end()) {
                        visited.insert(nextVal);
                        q.push({nextVal, steps + 1});
                    }
                }
            }
        }
        
        return -1;
    }
};