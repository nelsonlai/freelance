/*
 * Problem: Minimum Interval to Include Each Query
 * Difficulty: Hard
 * Tags: array, sort, search, queue, heap
 * 
 * Approach: Sort intervals and queries, use heap to track active intervals
 * Time Complexity: O(n log n + q log q) where n is intervals, q is queries
 * Space Complexity: O(n + q)
 */

#include <vector>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;

class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        sort(intervals.begin(), intervals.end());
        
        vector<pair<int, int>> sortedQueries;
        for (int i = 0; i < queries.size(); i++) {
            sortedQueries.push_back({queries[i], i});
        }
        sort(sortedQueries.begin(), sortedQueries.end());
        
        vector<int> result(queries.size(), -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
        int i = 0;
        
        for (auto& query : sortedQueries) {
            int q = query.first;
            int idx = query.second;
            
            while (i < intervals.size() && intervals[i][0] <= q) {
                int size = intervals[i][1] - intervals[i][0] + 1;
                heap.push({size, intervals[i][1]});
                i++;
            }
            
            while (!heap.empty() && heap.top().second < q) {
                heap.pop();
            }
            
            if (!heap.empty()) {
                result[idx] = heap.top().first;
            }
        }
        
        return result;
    }
};