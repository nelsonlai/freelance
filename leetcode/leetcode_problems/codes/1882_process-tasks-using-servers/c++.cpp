/*
 * Problem: Process Tasks Using Servers
 * Difficulty: Medium
 * Tags: array, queue, heap
 * 
 * Approach: Use two heaps - available servers and busy servers
 * Time Complexity: O(m log n) where m is tasks, n is servers
 * Space Complexity: O(n)
 */

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> available;
        for (int i = 0; i < servers.size(); i++) {
            available.push({servers[i], i});
        }
        
        priority_queue<pair<long long, pair<int, int>>, vector<pair<long long, pair<int, int>>>, greater<pair<long long, pair<int, int>>>> busy;
        
        vector<int> result;
        long long time = 0;
        
        for (int i = 0; i < tasks.size(); i++) {
            time = max(time, (long long)i);
            
            while (!busy.empty() && busy.top().first <= time) {
                auto [finishTime, server] = busy.top();
                busy.pop();
                available.push(server);
            }
            
            if (!available.empty()) {
                auto [weight, idx] = available.top();
                available.pop();
                result.push_back(idx);
                busy.push({time + tasks[i], {weight, idx}});
            } else {
                auto [finishTime, server] = busy.top();
                busy.pop();
                time = finishTime;
                result.push_back(server.second);
                busy.push({time + tasks[i], server});
            }
        }
        
        return result;
    }
};