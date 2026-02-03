/*
 * Problem: Avoid Flood in The City
 * Difficulty: Medium
 * Tags: array, greedy, hash, search, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <unordered_map>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        int n = rains.size();
        vector<int> result(n, -1);
        unordered_map<int, int> fullLakes;
        priority_queue<int, vector<int>, greater<int>> dryDays;
        
        for (int i = 0; i < n; i++) {
            int lake = rains[i];
            if (lake == 0) {
                dryDays.push(i);
            } else {
                if (fullLakes.find(lake) != fullLakes.end()) {
                    if (dryDays.empty()) {
                        return {};
                    }
                    int dryDay = dryDays.top();
                    dryDays.pop();
                    if (dryDay < fullLakes[lake]) {
                        return {};
                    }
                    result[dryDay] = lake;
                }
                fullLakes[lake] = i;
            }
        }
        
        while (!dryDays.empty()) {
            result[dryDays.top()] = 1;
            dryDays.pop();
        }
        
        return result;
    }
};